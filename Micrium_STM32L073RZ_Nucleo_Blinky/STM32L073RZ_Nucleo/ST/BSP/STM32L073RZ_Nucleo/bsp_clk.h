/*
*********************************************************************************************************
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          BOARD SUPPORT PACKAGE
*                                              NUCLEO-L073RZ
*
* Filename : bsp_clk.h
*
* Modified by Darren Sherin 10/10/2018 for STM32L073RZ port.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_CLK_PRESENT
#define  BSP_CLK_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


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
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/
                                                                /* Clock IDs.                          */
typedef  enum  bsp_clk_id {
    CLK_ID_SYSCLK,
    CLK_ID_HCLK,
    CLK_ID_PCLK1,
    CLK_ID_PCLK2
} BSP_CLK_ID;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_ClkInit   (void);

void         BSP_ClkEnable (BSP_CLK_ID  clk_id);

void         BSP_ClkDisable(BSP_CLK_ID  clk_id);

CPU_INT32U   BSP_ClkFreqGet(BSP_CLK_ID  clk_id);

CPU_BOOLEAN  BSP_ClkFreqSet(BSP_CLK_ID  clk_id,
                            CPU_INT32U  freq);


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
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.              */
