/* Define to prevent recursive inclusion --------------------------*/
#ifndef SDJ2102_INT_H
#define SDJ2102_INT_H

/* Includes -------------------------------------------------------*/
/* Exported type --------------------------------------------------*/
/* Exported constants ---------------------------------------------*/
/* Exported variables ---------------------------------------------*/
/* Exported macro -------------------------------------------------*/
/* Exported functions ---------------------------------------------*/
void int_init();
void int_enable();
void int_disable();
int  handle_trap(uintptr_t  mcause, uintptr_t epc);

#endif  /*SDJ2102_INT_H*/
