/***************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   clint.h
*
*   FUNCTION:   define some interface for the coreplex 
*               local interrupt,include software,timer
*               and local interrupt
*   
*   AUTHOR:     liaoll
*   
*   DATE:       2017/08/02
***************************************************************/

/* Define to prevent recursive inclusion --------------------------*/
#ifndef SDJ2102_CLINT_H
#define SDJ2102_CLINT_H

/* Includes -------------------------------------------------------*/
/* Exported constants ---------------------------------------------*/
/* Exported macro -------------------------------------------------*/
/* local interrupt id */
#define LOCAL_INT_NUM   16
#define LOCAL_INT_ID0   0
#define LOCAL_INT_ID1   1
#define LOCAL_INT_ID2   2
#define LOCAL_INT_ID3   3
#define LOCAL_INT_ID4   4
#define LOCAL_INT_ID5   5
#define LOCAL_INT_ID6   6
#define LOCAL_INT_ID7   7
#define LOCAL_INT_ID8   8
#define LOCAL_INT_ID9   9
#define LOCAL_INT_ID10  10
#define LOCAL_INT_ID11  11
#define LOCAL_INT_ID12  12
#define LOCAL_INT_ID13  13
#define LOCAL_INT_ID14  14
#define LOCAL_INT_ID15  15

#define IRQ_M_LOCAL 12
#define MIP_MLIP(x) (1<<(IRQ_M_LOCAL+x))
/* local interrupt id for specific use*/

/* local interrupt memory map */
#define LOCAL_INT_MSIP              0x0000  // software interrupt start-up register
#define LOCAL_INT_SZIE              0x4
#define LOCAL_INT_MTIMECMP          0x4000  // counter interrupt compare register
#define LOCAL_INT_MTIMECMP_SIZE     0x8
#define LOCAL_INT_MTIME             0xBFF8  // counter register
#define LOCAL_INT_MTIME_SIZE        0x8
#define LOCAL_32BIT_MAX             0x10000000

#define MTIME (*((volatile uint64_t *)(CLINT_CTRL_ADDR + LOCAL_INT_MTIME)))
#define MTIMECMP (*((volatile uint64_t *)(CLINT_CTRL_ADDR + LOCAL_INT_MTIMECMP)))

/* Exported type --------------------------------------------------*/
typedef void(*local_int_handler)(void);
typedef void (*timer_int_handler)(void);
typedef void(*soft_int_handler)(void);

/* Exported variables ---------------------------------------------*/
extern local_int_handler local_THF[LOCAL_INT_NUM];  //trap handle function
extern timer_int_handler timer_THF[1];
extern soft_int_handler soft_THF[1];


/* Exported functions ---------------------------------------------*/
void local_int_init(void);
void local_int_enable(int id);
void local_int_disable(int id);
void local_int_bind_handler(int id,void (* handle_function)(void));

void timer_int_init();
void timer_int_enable();
void timer_int_disable();
void set_timer_val(uint64_t value);
uint64_t get_timer_val(void);
void set_timer_cmp(uint64_t value);
void timer_int_bind_handler(void(*handle_function)(void));

void soft_int_init();
void soft_int_enable();
void soft_int_disable();
void soft_int_bind_handler(void(*hanle_function)(void));
void soft_int_start();
void soft_int_stop();

#endif /*SDJ2102_CLINT_H*/
