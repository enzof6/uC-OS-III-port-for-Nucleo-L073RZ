/*
*********************************************************************************************************
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                             OS TICK BSP
*
* Filename : bsp_os.c
*
* Modified by Darren Sherin 10/10/2018 for STM32L073RZ port.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu_core.h>
#include  <os.h>

#include  "bsp_os.h"
#include  "bsp_clk.h"
#include  "bsp_int.h"
#include  "stm32l0xx_hal.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#ifndef  OS_CFG_DYN_TICK_EN                                     /* Dynamic tick only available for uCOS-III             */
#define  OS_CFG_DYN_TICK_EN          DEF_DISABLED
#endif

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
#define  BSP_OS_LPTIMER_MAX_VALUE           DEF_INT_16U_MAX_VAL /* For a 16-bit counter                                 */
#define  BSP_OS_LPTIMER_TICK_RATE_HZ          (10000u)          /* The frequency at which the Timer will run.           */
#define  BSP_OS_LPTICK_TO_OSTICK(lptick)    (((lptick) * OSCfg_TickRate_Hz)/BSP_OS_LPTIMER_TICK_RATE_HZ)
#define  BSP_OS_OSTICK_TO_LPTICK(ostick)    (((ostick) * BSP_OS_LPTIMER_TICK_RATE_HZ)/OSCfg_TickRate_Hz)
#endif


/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*
* Note(s) : (1) BSP_OS_UnTick is used to keep track of any ticks that happen before the OS is ready to
*               awake some tasks.
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
static  OS_TICK  BSP_OS_TicksToGo = 0u;                         /* Stored in OS Tick units.                             */
static  OS_TICK  BSP_OS_LastTick  = 0u;                         /* Stored in OS Tick units.                             */
static  OS_TICK  BSP_OS_UnTick    = 0u;                         /* Stored in OS Tick units. See Note 1                  */

TIM_HandleTypeDef  TimHandle;
#endif


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
static  void  BSP_OS_DynamicTickInit(void);
static  void  BSP_TIM6_ISRHandler   (void);
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_OS_TickInit()
*
* Description : Initializes the tick interrupt for the OS.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) Must be called prior to OSStart() in main().
*
*               (2) This function ensures that the tick interrupt is disabled until BSP_OS_TickEn() is
*                   called in the startup task.
*********************************************************************************************************
*/

void  BSP_OS_TickInit (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_INT32U  cpu_freq;
    CPU_SR_ALLOC();


    cpu_freq = BSP_ClkFreqGet(CLK_ID_HCLK);                     /* Determine SysTick reference freq.                    */

    CPU_CRITICAL_ENTER();
    OS_CPU_SysTickInitFreq(cpu_freq);                           /* Init uC/OS periodic time src (SysTick).              */
    BSP_OS_TickDisable();                                       /* See Note #2.                                         */
    CPU_CRITICAL_EXIT();
#else
    BSP_OS_DynamicTickInit();                                   /* Initialize dynamic tick.                             */
#endif
}


/*
*********************************************************************************************************
*                                         BSP_OS_TickEnable()
*
* Description : Enable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickEnable (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_REG_NVIC_ST_CTRL |= (CPU_REG_NVIC_ST_CTRL_TICKINT |     /* Enables SysTick exception request                    */
                             CPU_REG_NVIC_ST_CTRL_ENABLE);      /* Enables SysTick counter                              */
#else
    BSP_IntEn(BSP_INT_ID_TIM6_DAC);                                 /* Enable Timer interrupt.                              */
    HAL_TIM_Base_Start(&TimHandle);                             /* Start the Timer count generation.                    */
#endif
}


/*
*********************************************************************************************************
*                                        BSP_OS_TickDisable()
*
* Description : Disable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickDisable (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_REG_NVIC_ST_CTRL &= ~(CPU_REG_NVIC_ST_CTRL_TICKINT |    /* Disables SysTick exception request                   */
                              CPU_REG_NVIC_ST_CTRL_ENABLE);     /* Disables SysTick counter                             */
#else
    HAL_TIM_Base_Stop(&TimHandle);                              /* Stop the Timer count generation.                     */
    BSP_IntDis(BSP_INT_ID_TIM6_DAC);                                /* Disable Timer interrupt.                             */
#endif
}


/*
*********************************************************************************************************
*                                            HAL_InitTick()
*
* Description : This function has been overwritten from the STM32Cube HAL libraries because Micrium's RTOS
*               has its own Systick initialization and because it is recomended to initialize the tick
*               after multi-tasking has started.
*
* Argument(s) : TickPriority          Tick interrupt priority.
*
* Return(s)   : HAL_OK.
*
* Caller(s)   : HAL_InitTick ()) is called automatically at the beginning of the program after reset by
*               HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
*
* Note(s)     : none.
*********************************************************************************************************
*/

HAL_StatusTypeDef  HAL_InitTick (uint32_t TickPriority)
{
    HAL_NVIC_SetPriority(0,0,0);

    return (HAL_OK);
}


/*
*********************************************************************************************************
*                                            HAL_GetTick()
*
* Description : This function has been overwritten from the STM32Cube HAL libraries because Micrium's OS's
*               has their own Tick counter values.
*
* Argument(s) : None.
*
* Return(s)   : Tick current value.
*
* Caller(s)   : STM32Cube HAL driver files.
*
* Note(s)     : (1) Please ensure that the Tick Task has a higher priority than the App Start Task.
*********************************************************************************************************
*/

uint32_t  HAL_GetTick (void)
{
    CPU_INT32U  os_tick_ctr;
#if (OS_VERSION >= 30000u)
    OS_ERR      os_err;
#endif

#if (OS_VERSION >= 30000u)
    os_tick_ctr = OSTimeGet(&os_err);
#else
    os_tick_ctr = OSTimeGet();
#endif

    return os_tick_ctr;
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                      uC/OS-III DYNAMIC TICK
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                      BSP_OS_DynamicTickInit()
*
* Description : Initialize timer to use for dynamic tick.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_OS_DynamicTickInit (void)
{
    HAL_StatusTypeDef  hal_stat;
    CPU_INT32U         per_clk;


    __HAL_RCC_TIM6_CLK_ENABLE();                                /* Enable TIMER6 interface clock.                       */

    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM6_STOP;             /* Make sure TIMER5 is stop when core is halted.        */
    per_clk           = BSP_ClkFreqGet(CLK_ID_PCLK1);           /* Get TIMER5 clock frequency.                          */

                                                                /* -------- INITIALIZE TIMER BASE CONFIGURATION ------- */
                                                                /* Prescaler = (TIM5CLK / TIM counter clock) - 1        */
    TimHandle.Instance           = TIM6;
    TimHandle.Init.Prescaler     = (per_clk / BSP_OS_LPTIMER_TICK_RATE_HZ) - 1u ;
    TimHandle.Init.Period        = (BSP_OS_LPTIMER_TICK_RATE_HZ / OSCfg_TickRate_Hz) - 1u ;
    TimHandle.Init.ClockDivision = 0u;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    hal_stat = HAL_TIM_Base_Init(&TimHandle);
    if (hal_stat != HAL_OK) {
        while(1u);                                              /* STOP if error                                        */
    }

    HAL_TIM_Base_Start_IT(&TimHandle);                          /* Start the timer interrupt mode generation.           */
    __HAL_TIM_SET_COUNTER(&TimHandle, 0u);                      /* Reset the timer counter value                        */

                                                                /* ----------- SET INTERRUPT REQUEST HANDLER ---------- */
    BSP_IntVectSet(INT_ID_TIM6_DAC,
                   DEF_NULL,
                   INT_IRQ,
                   BSP_TIM6_ISRHandler);
}


/*
*********************************************************************************************************
*                                        BSP_TIM5_ISRHandler()
*
* Description : BSP-level ISR handler for TIM5.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_TIM6_ISRHandler (void)
{
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    OSIntEnter();
    CPU_CRITICAL_EXIT();

    __HAL_TIM_CLEAR_IT(&TimHandle, TIM_IT_UPDATE);              /* Clear Timer interrupt.                               */

    if (BSP_OS_TicksToGo != 0) {
        __HAL_TIM_SET_COUNTER(&TimHandle, 0u);                  /* Reset the timer counter value                        */
        OSTimeDynTick(BSP_OS_TicksToGo + BSP_OS_UnTick + BSP_OS_LPTICK_TO_OSTICK(__HAL_TIM_GET_COUNTER(&TimHandle)));
        BSP_OS_LastTick += BSP_OS_TicksToGo + BSP_OS_LPTICK_TO_OSTICK(__HAL_TIM_GET_COUNTER(&TimHandle));

        BSP_OS_TicksToGo = 0;
        BSP_OS_UnTick    = 0;
    } else {
                                                                /* No tasks need to be awakened only keep track of time */
        BSP_OS_LastTick += BSP_OS_LPTICK_TO_OSTICK(__HAL_TIM_GET_COUNTER(&TimHandle));
        BSP_OS_UnTick   += BSP_OS_LPTICK_TO_OSTICK(__HAL_TIM_GET_COUNTER(&TimHandle));
    }

    OSIntExit();
}

/*
*********************************************************************************************************
*                                          BSP_OS_TickGet()
*
* Description : Get the OS Tick Counter as if it was running continuously.
*
* Argument(s) : none.
*
* Return(s)   : The effective OS Tick Counter.
*
* Caller(s)   : OS_TaskBlock, OS_TickListInsertDly and OSTimeGet.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickGet (void)
{
    OS_TICK  tick;


    tick = __HAL_TIM_GET_COUNTER(&TimHandle);                   /* Get the timer counter value.                         */
    tick = BSP_OS_LastTick + BSP_OS_LPTICK_TO_OSTICK(tick);

    return (tick);
}


/*
*********************************************************************************************************
*                                        BSP_OS_TickNextSet()
*
* Description : Set the number of OS Ticks to wait before calling OSTimeTick.
*
* Argument(s) : ticks       number of OS Ticks to wait.
*
* Return(s)   : Number of effective OS Ticks until next OSTimeTick.
*
* Caller(s)   : OS_TickTask and OS_TickListInsert.
*
*               This function is an INTERNAL uC/OS-III function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

OS_TICK  BSP_OS_TickNextSet (OS_TICK  ticks)
{
    OS_TICK  lpticks;

                                                                /* Check if OSTimeTick needs to be called.              */
    if (ticks != (OS_TICK)-1) {
                                                                /* Get tick count in TMR units.                         */
        lpticks = BSP_OS_OSTICK_TO_LPTICK(ticks);
                                                                /* Adjust for maximum value.                            */
        if (lpticks > BSP_OS_LPTIMER_MAX_VALUE) {
            BSP_OS_TicksToGo = BSP_OS_LPTICK_TO_OSTICK(BSP_OS_LPTIMER_MAX_VALUE);
            lpticks          = BSP_OS_LPTIMER_MAX_VALUE;
        } else {
            BSP_OS_TicksToGo = ticks;
        }
                                                                /* Adjust for invalid value.                            */
        if ((lpticks & BSP_OS_LPTIMER_MAX_VALUE) == 0) {
            lpticks          = BSP_OS_LPTIMER_MAX_VALUE;
            BSP_OS_TicksToGo = BSP_OS_LPTICK_TO_OSTICK(BSP_OS_LPTIMER_MAX_VALUE);
        }
    } else {
        lpticks          = BSP_OS_LPTIMER_MAX_VALUE;
        BSP_OS_TicksToGo = 0;
    }

    HAL_TIM_Base_Stop(&TimHandle);                              /* Stop the Timer count generation.                     */
    __HAL_TIM_SET_AUTORELOAD(&TimHandle, lpticks - 1);          /* Re-configure auto-reload register and period.        */
    __HAL_TIM_SET_COUNTER(&TimHandle, 0u);                      /* Reset the timer counter value                        */
    HAL_TIM_Base_Start(&TimHandle);                             /* Start the Timer count generation.                    */

                                                                /* Return the number of effective OS ticks that will... */
    return (BSP_OS_TicksToGo);                                  /* ...elapse before the next interrupt.                 */
}


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of uC/OS-III Dynamic Tick module.                */
