/*************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   plic.c
*
*   FUNCTION:   implement the interface of global interrup (
*               platform level function )
*
*   AUTHOR:     liaoll      
*
*   DATE:       2017/08/07
*
*   ISFINISH:   NO
*************************************************************************/
/* Includes --------------------------------------------------------*/
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
global_int_handler global_THF[PLIC_NUM];

/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   memzero
* Description   :   set zero
* Input         :   base_addr -- memery address, size -- specific size
* Output        :   none
* Return        :   none
********************************************************************/
void memzero(void* base_addr,unsigned int size)
{
    volatile int i;
    
    for(i = 0; i < size; i++)
    {
        *((char*)base_addr + i) = 0;
    }
}


/********************************************************************
* Function Name :   global_int_init
* Description   :   initialize global interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_init(void)
{
    /*initial: set all interrupt disable */
    memzero((void*)(PLIC_CTRL_ADDR+PLIC_ENABLE_OFFSET),PLIC_ENABLE_SIZE);

    /*initial: set all interrupt priorities to 0 */
    memzero((void*)(PLIC_CTRL_ADDR+PLIC_PRIORITY_OFFSET),PLIC_PRIORITY_SIZE);
    
    /*initial: set the threshold to 0 */
    PLIC_REG(PLIC_THRESHOLD_OFFSET) = 0;
    
}

/********************************************************************
* Function Name :   global_int_enable
* Description   :   enable specific global interrupt
* Input         :   id -- specific interrupt ID code
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_enable(int id)
{
    int reg_addr, reg_offset;

    reg_addr = id / 32;
    reg_offset = id % 32;
    PLIC_REG(PLIC_ENABLE_OFFSET+reg_addr*4) |= 1U<<reg_offset;

}


/********************************************************************
* Function Name :   global_int_disable
* Description   :   disable specific global interrupt
* Input         :   id -- specific interrupt ID code
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_disable(int id)
{
    int reg_addr,reg_offset;

    reg_addr = id / 32 ;
    reg_offset = id % 32;
    PLIC_REG(PLIC_ENABLE_OFFSET+reg_addr*4) &= ~(1U<<reg_offset);
}


/********************************************************************
* Function Name :   global_int_priority
* Description   :   set specific global interrupt's priority
* Input         :   id -- specific interrupt ID code, priority -- 0 to 7
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_priority(int id,int priority)
{
    PLIC_REG(PLIC_PRIORITY_OFFSET + id*4) = priority;
}


/********************************************************************
* Function Name :   global_int_threshold
* Description   :   set global interrupt threshold register to a specific value
* Input         :   priority -- value to set
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_threshold(int priority)
{
    PLIC_REG(PLIC_THRESHOLD_OFFSET) = priority;
}


/********************************************************************
* Function Name :   handle_mint_ext
* Description   :   handle the external interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void handle_mint_ext(void)
{
    int int_num;

    int_num = PLIC_REG(PLIC_CLAIM_OFFSET);
    if((int_num >= 1) && (int_num <= PLIC_NUM))
        global_THF[int_num]();
    else
        return ;
    // complete the interrupt, yexc
    PLIC_REG(PLIC_CLAIM_OFFSET) = int_num;

}

/********************************************************************
* Function Name :   global_int_bind_handler
* Description   :   bind global interrupt to handler function
* Input         :   id -- interrupt ID code, handle_function -- handler function
* Output        :   none
* Return        :   none
********************************************************************/
void global_int_bind_handler(int id, void(*handle_function)())
{
    global_THF[id] = handle_function;
}

