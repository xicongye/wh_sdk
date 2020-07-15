/********************************************************************
*
*   PROJECT:    WH
*
*   FILENAME:   privilege.h
*
*   FUNCTION:   API for manipulating the privilege mode of a RISC-V system
*
*   AUTHOR:     yexc
*
*   DATE:       2019/07/16
*
*   VERSION:    v0.1
*
*   IS_FINISH:  NO
*********************************************************************/
/* Define to prevent recursive inclusion --------------------------*/
#ifndef SDJ2102_PRIV_H
#define SDJ2102_PRIV_H

/* Exported constants ---------------------------------------------*/
/* Includes -------------------------------------------------------*/
#include "platform.h"

/* Exported variables ---------------------------------------------*/
/* Exported macro -------------------------------------------------*/
/* Exported type --------------------------------------------------*/
typedef void (*privilege_entry_point_t)();
/* Exported functions ---------------------------------------------*/
void privilege_drop_to_mode(int privilege_mode, privilege_entry_point_t entry_point, int relocate_sp_flag);
void mem_privilege_drop_to_mode(int privilege_mode, int relocate_sp_flag);

#endif /*SDJ2102_PRIV_H*/

