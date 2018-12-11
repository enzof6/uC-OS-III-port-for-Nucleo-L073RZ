/*
*********************************************************************************************************
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          BOARD SUPPORT PACKAGE
*
* Filename : bsp_int.h
*
* Modified by Darren Sherin 10/10/2018 for STM32L073RZ port.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>


/*
*********************************************************************************************************
*                                     EXTERNAL C LANGUAGE LINKAGE
*
* Note(s) : (1) C++ compilers MUST 'extern'ally declare ALL C function prototypes & variable/object
*               declarations for correct C language linkage.
*********************************************************************************************************
*/

#ifdef __cplusplus
extern  "C" {                                                   /* See Note #1.                        */
#endif



/*
*********************************************************************************************************
*                                               DEFINES
*
* Note(s) : (1) The Cortex-M "Vector Table Offset Register" section states the following:
*
*               You must align the offset to the number of exception entries in the vector table. The
*               minimum alignment is 32 words, enough for up to 16 interrupts. For more interrupts,
*               adjust the alignment by rounding up to the next power of two. For example, if you require
*               21 interrupts, the alignment must be on a 64-word boundary because the required table
*               size is 37 words, and the next power of two is 64. SEE YOUR VENDOR DOCUMENTATION FOR THE
*               ALIGNMENT DETAILS FOR YOUR DEVICE.
*
*********************************************************************************************************
*/

#define  ARMV6M_CORE_EXCS             16u

#define  INT_ID_MAX_NBR               32u                       /* Max. number of ext. interrupt sources. (Check MCU RM)*/

                                                                /* 48 VTOR entries; next power of 2 is 64              */
#define  INT_VTOR_TBL_SIZE         (INT_ID_MAX_NBR + ARMV6M_CORE_EXCS)
#define  INT_VTOR_TBL_ALIGNMENT    (0x100uL)                    /* 64 * 4 = 256 words. See note 1                      */



#define  BSP_INT_ID_WWDG                    0u      /* Window WatchDog Interrupt                               */
#define  BSP_INT_ID_PVD                     1u      /* PVD through EXTI Line detect Interrupt                  */
#define  BSP_INT_ID_RTC                     2u      /* RTC through EXTI Line Interrupt                         */
#define  BSP_INT_ID_FLASH                   3u      /* FLASH Interrupt                                         */
#define  BSP_INT_ID_RCC_CRS                 4u      /* RCC and CRS Interrupts                                  */
#define  BSP_INT_ID_EXTI0_1                 5u      /* EXTI Line 0 and 1 Interrupts                            */
#define  BSP_INT_ID_EXTI2_3                 6u      /* EXTI Line 2 and 3 Interrupts                            */
#define  BSP_INT_ID_EXTI4_15                7u      /* EXTI Line 4 to 15 Interrupts                            */
#define  BSP_INT_ID_TSC                     8u      /* TSC Interrupt                                           */
#define  BSP_INT_ID_DMA_CH1                 9u      /* DMA1 Channel 1 Interrupt                                */
#define  BSP_INT_ID_DMA_CH2_3               10u     /* DMA1 Channel 2 and Channel 3 Interrupts                 */
#define  BSP_INT_ID_DMA_CH4_5_6_7           11u     /* DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
#define  BSP_INT_ID_ADC1_COMP               12u     /* ADC1, COMP1 and COMP2 Interrupts                        */
#define  BSP_INT_ID_LPTIM1                  13u     /* LPTIM1 Interrupt                                        */
#define  BSP_INT_ID_USART4_5                14u     /* USART4 and USART5 Interrupt                             */
#define  BSP_INT_ID_TIM2                    15u     /* TIM2 Interrupt                                          */
#define  BSP_INT_ID_TIM3                    16u     /* TIM3 Interrupt                                          */
#define  BSP_INT_ID_TIM6_DAC                17u     /* TIM6 and DAC Interrupts                                 */
#define  BSP_INT_ID_TIM7                    18u     /* TIM7 Interrupt                                          */
#define  BSP_INT_ID_TIM21                   20u     /* TIM21 Interrupt                                         */
#define  BSP_INT_ID_I2C3                    21u     /* I2C3 Interrupt                                          */
#define  BSP_INT_ID_TIM22                   22u     /* TIM22 Interrupt                                         */
#define  BSP_INT_ID_I2C1                    23u     /* I2C1 Interrupt                                          */
#define  BSP_INT_ID_I2C2                    24u     /* I2C2 Interrupt                                          */
#define  BSP_INT_ID_SPI1                    25u     /* SPI1 Interrupt                                          */
#define  BSP_INT_ID_SPI2                    26u     /* SPI2 Interrupt                                          */
#define  BSP_INT_ID_USART1                  27u     /* USART1 Interrupt                                        */
#define  BSP_INT_ID_USART2                  28u     /* USART2 Interrupt                                        */
#define  BSP_INT_ID_RNG_LPUART1             29u     /* RNG and LPUART1 Interrupts                              */
#define  BSP_INT_ID_LCD                     30u     /* LCD Interrupt                                           */
#define  BSP_INT_ID_USB                     31u     /* USB global Interrupt                                    */

/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/
typedef  enum  bsp_int_id {
  INT_ID_WWDG                    = 0u,     /* Window WatchDog Interrupt                               */
  INT_ID_PVD                     = 1u,      /* PVD through EXTI Line detect Interrupt                  */
  INT_ID_RTC                     = 2u,      /* RTC through EXTI Line Interrupt                         */
  INT_ID_FLASH                   = 3u,      /* FLASH Interrupt                                         */
  INT_ID_RCC_CRS                 = 4u,      /* RCC and CRS Interrupts                                  */
  INT_ID_EXTI0_1                 = 5u,      /* EXTI Line 0 and 1 Interrupts                            */
  INT_ID_EXTI2_3                 = 6u,      /* EXTI Line 2 and 3 Interrupts                            */
  INT_ID_EXTI4_15                = 7u,      /* EXTI Line 4 to 15 Interrupts                            */
  INT_ID_TSC                     = 8u,      /* TSC Interrupt                                           */
  INT_ID_DMA_CH1                 = 9u,      /* DMA1 Channel 1 Interrupt                                */
  INT_ID_DMA_CH2_3               = 10u,     /* DMA1 Channel 2 and Channel 3 Interrupts                 */
  INT_ID_DMA_CH4_5_6_7           = 11u,     /* DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
  INT_ID_ADC1_COMP               = 12u,     /* ADC1, COMP1 and COMP2 Interrupts                        */
  INT_ID_LPTIM1                  = 13u,     /* LPTIM1 Interrupt                                        */
  INT_ID_USART4_5                = 14u,     /* USART4 and USART5 Interrupt                             */
  INT_ID_TIM2                    = 15u,     /* TIM2 Interrupt                                          */
  INT_ID_TIM3                    = 16u,     /* TIM3 Interrupt                                          */
  INT_ID_TIM6_DAC                = 17u,     /* TIM6 and DAC Interrupts                                 */
  INT_ID_TIM7                    = 18u,     /* TIM7 Interrupt                                          */
  INT_ID_TIM21                   = 20u,     /* TIM21 Interrupt                                         */
  INT_ID_I2C3                    = 21u,     /* I2C3 Interrupt                                          */
  INT_ID_TIM22                   = 22u,     /* TIM22 Interrupt                                         */
  INT_ID_I2C1                    = 23u,     /* I2C1 Interrupt                                          */
  INT_ID_I2C2                    = 24u,     /* I2C2 Interrupt                                          */
  INT_ID_SPI1                    = 25u,     /* SPI1 Interrupt                                          */
  INT_ID_SPI2                    = 26u,     /* SPI2 Interrupt                                          */
  INT_ID_USART1                  = 27u,     /* USART1 Interrupt                                        */
  INT_ID_USART2                  = 28u,     /* USART2 Interrupt                                        */
  INT_ID_RNG_LPUART1             = 29u,     /* RNG and LPUART1 Interrupts                              */
  INT_ID_LCD                     = 30u,     /* LCD Interrupt                                           */
  INT_ID_USB                     = 31u,     /* USB global Interrupt                                    */

} BSP_INT_ID;

typedef enum bsp_int_type {                                     /* Types of Interrupt.                                  */
    INT_IRQ,                                                    /* Normal interrupt request.                            */
} BSP_INT_TYPE;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  BSP_IntInit   (void);

void  BSP_IntDisAll (void);

void  BSP_IntEn (CPU_DATA       int_id);

void  BSP_IntDis (CPU_DATA       int_id);

void  BSP_IntClr  (CPU_DATA       int_id);

void  BSP_IntVectSet (BSP_INT_ID     int_id,
                      CPU_INT08U     int_prio,
                      BSP_INT_TYPE   int_type,
                      CPU_FNCT_VOID  isr_handler);

void  BSP_IntPrioSet(CPU_DATA       int_id,
                     CPU_INT08U     prio);



/*
*********************************************************************************************************
*                                   EXTERNAL C LANGUAGE LINKAGE END
*********************************************************************************************************
*/

#ifdef __cplusplus
}                                                               /* End of 'extern'al C lang linkage.   */
#endif


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.              */
