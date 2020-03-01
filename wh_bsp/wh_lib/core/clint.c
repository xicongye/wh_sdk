/*************************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   clint.c
*
*   FUNCTION:   implement the interface about the coreplex local interrup that declared 
*               at head file clint.h
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/08/03
* 
*   ISFINISH:   NO
**************************************************************************************************/

/* Includes --------------------------------------------------------*/
#include "csr.h"
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
local_int_handler local_THF[LOCAL_INT_NUM];  //trap handle function 
timer_int_handler timer_THF[1];
soft_int_handler soft_THF[1];

/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/

/* local interrupt  */
/********************************************************************
* Function Name :   local_int_init
* Description   :   initialize local interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void local_int_init(void)
{
    volatile int i;

    for(i = 0; i < LOCAL_INT_NUM; i++)
        clear_csr(mie, MIP_MLIP(i));
}

/********************************************************************
* Function Name :   local_int_enable
* Description   :   enable local interrupt
* Input         :   id -- interrupt ID code
* Output        :   none
* Return        :   none
********************************************************************/
void local_int_enable(int id)
{
    set_csr(mie, MIP_MLIP(id));
}


/********************************************************************
* Function Name :   local_int_disable
* Description   :   disable local interrupt
* Input         :   id -- interrupt ID code
* Output        :   none
* Return        :   none
********************************************************************/
void local_int_disable(int id)
{
    clear_csr(mie,MIP_MLIP(id));
}


/********************************************************************
* Function Name :   local_int_bind_handler
* Description   :   bind the specific interrupt to a handler function
* Input         :   id -- interrupt ID code; handle_function -- IRQ handler function
* Output        :   none
* Return        :   none
********************************************************************/
void local_int_bind_handler(int id,void (* handle_function)(void))
{
    local_THF[id]=handle_function;
}


/********************************************************************
* Function Name :   handle_mint_local
* Description   :   handle the specific interrupt
* Input         :   id -- interrupt ID code
* Output        :   none
* Return        :   none
********************************************************************/
void handle_mint_local(unsigned int id)
{
    local_THF[id]();
}



/* timer interrupt */
/********************************************************************
* Function Name :   timer_int_init
* Description   :   initialize timer interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void timer_int_init(void)
{
    clear_csr(mie,MIE_MTIE);
}


/********************************************************************
* Function Name :   timer_int_disable
* Description   :   disable timer interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void timer_int_disable(void)
{
    clear_csr(mie,MIE_MTIE);
}

/********************************************************************
* Function Name :   timer_int_enable
* Description   :   enable timer interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void timer_int_enable(void)
{
    set_csr(mie,MIE_MTIE);
}


/********************************************************************
* Function Name :   set_timer_val
* Description   :   set timer value
* Input         :   value
* Output        :   none
* Return        :   none
********************************************************************/
void set_timer_val(uint64_t value)
{
    uint64_t low,high;
    low=value%(uint64_t)LOCAL_32BIT_MAX;
    high=value/(uint64_t)LOCAL_32BIT_MAX;

    CLINT_REG(LOCAL_INT_MTIME)=(uint32_t)low;
    CLINT_REG(LOCAL_INT_MTIME+4)=(uint32_t)high;
}

/********************************************************************
* Function Name :   get_timer_val
* Description   :   get timer value
* Input         :   none
* Output        :   none
* Return        :   mtime value
********************************************************************/
uint64_t get_timer_val(void)
{
/*
    uint64_t low,high;
    low = CLINT_REG(LOCAL_INT_MTIME);
    high = CLINT_REG(LOCAL_INT_MTIME+4);
    
    return (((high<<31)<<1) | low);
*/
    return MTIME;
}

/********************************************************************
* Function Name :   set_timer_cmp
* Description   :   set timer comparator register
* Input         :   value
* Output        :   none
* Return        :   none
********************************************************************/
void set_timer_cmp(uint64_t value)
{
/*
    uint64_t low,high;
    low=value%(uint64_t)LOCAL_32BIT_MAX;
    high=value/(uint64_t)LOCAL_32BIT_MAX; 
    CLINT_REG(LOCAL_INT_MTIMECMP) = (uint32_t)low;
    CLINT_REG(LOCAL_INT_MTIMECMP+4) = (uint32_t)high;
*/
    MTIMECMP = value;
}


/********************************************************************
* Function Name :   handle_mint_time
* Description   :   handle timer interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void handle_mint_time(void)
{
    timer_THF[0]();
}


/********************************************************************
* Function Name :   timer_int_bind_handler
* Description   :   bind the timer interrupt to a handler function
* Input         :   handle_function -- IRQ handler function
* Output        :   none
* Return        :   none
********************************************************************/
void timer_int_bind_handler(void(*handle_function)(void))
{
    timer_THF[0]=handle_function;
}



/* software interrupt */
/********************************************************************
* Function Name :   soft_int_init
* Description   :   initialize software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_init(void)
{
    clear_csr(mie,MIE_MSIE);
}


/********************************************************************
* Function Name :   soft_int_enable
* Description   :   enable software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_enable()
{
    set_csr(mie,MIE_MSIE);
}

/********************************************************************
* Function Name :   soft_int_disable
* Description   :   disable software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_disable(void)
{
    clear_csr(mie,MIE_MSIE);
}

/********************************************************************
* Function Name :   soft_int_bind_handler
* Description   :   bind the software interrupt to a handler function
* Input         :   handle_function -- handler function
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_bind_handler(void(*handle_function)(void))
{
    soft_THF[0]=handle_function;
}

/********************************************************************
* Function Name :   soft_int_start
* Description   :   start software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_start(void)
{
    CLINT_REG(LOCAL_INT_MSIP)=0x1;
}

/********************************************************************
* Function Name :   soft_int_stop
* Description   :   stop software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void soft_int_stop(void)
{
    CLINT_REG(LOCAL_INT_MSIP)=0x0;
}

/********************************************************************
* Function Name :   handle_mint_soft
* Description   :   handle software interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void handle_mint_soft(void)
{
    soft_THF[0]();
}
