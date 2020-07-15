/************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILE_NAME:  cacheSwitch.c  
*
*   FUNCTION:   DCache Enable/Disable Function 
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/08/04
*
*   IS_FINISH:  NO
**********************************************************************************/

/* Includes ------------------------------------------------------------------------*/
#include "platform.h"

/* Private functions ---------------------------------------------------------------*/
/************************************************************************************
 * Function Name: dcache_enable
 * Description  : enable dcache 
 * Input        : none
 * Output       : none
 * Return       : none 
 ************************************************************************************/

void dcache_enable(void) {
  clear_csr(mstatus,MSTATUS_DD) ;
  return;
}

/************************************************************************************
 *  Function Name: dcache_disable
 *  Description  : disable dcache 
 *  Input        : none
 *  Output       : none
 *  Return       : none 
 *************************************************************************************/
void dcache_disable(void) {
  set_csr(mstatus,MSTATUS_DD) ;
  return;
}

/************************************************************************************
 *  Function Name: dcache_flush_block
 *  Description  : flush one block of dcache
 *  Input        : none
 *  Output       : none
 *  Return       : none 
 *************************************************************************************/
int dcache_flush_block(int regs0)
{
    asm(".word(0xfc050073)");
}

/************************************************************************************
 *  Function Name: dcache_flush_all
 *  Description  : flush all blocks of dcache
 *  Input        : none
 *  Output       : none
 *  Return       : none 
 *************************************************************************************/
void dcache_flush_all(void)
{
    asm(".word(0xfc000073)");
}

