/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       etimer.c
*
*       FUNCTION:       etimer driver
*
*       AUTHOR:         yexc
*
*       DATE:           2018/11/09
*
*       IS_FINISH:      NO
*
********************************************************************/
/* Includes --------------------------------------------------------*/
#include "csr.h"
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name         :       pwm_mode
* Description           :       set PWM mode
* Input                 :       - cnt - 
*                       :       - val - 
*                       :       - count - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer_pwm_mode(int cnt,int val,int count)
{
    ETIMER1_REG(ETIMER_CR) = 0x04;      //pwm_mode
    ETIMER1_REG(ETIMER_CR) |= 0x40;     //CLK_EDGE_UP

    ETIMER1_REG(CNTVAILDR) = cnt;
    ETIMER1_REG(CNTVAIHDR) = cnt>>8;
    ETIMER1_REG(CCVAILDR) = val;
    ETIMER1_REG(CCVAIHDR) = val>>8;

    ETIMER1_REG(PWMTIMVAIDR) = count;
    ETIMER1_REG(PWMTIMVAIHDR) = count>>8;   //total cyc, if set 0,always pwm
    ETIMER1_REG(ETIMER_CR) |= 0x08;     //CLK_START
    //ETIMER1_REG(ETIMER_CR) |= 0x10;       //reset
}



/********************************************************************
* Function Name         :       timer_mode
* Description           :       set timer mode
* Input                 :       - cnt - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer_timer_mode(int cnt)
{
    ETIMER1_REG(ETIMER_CR) = 0x01;         //timer_mode
    ETIMER1_REG(CNTVAILDR) = cnt;          //value->0
    ETIMER1_REG(CNTVAIHDR) = cnt>>8;
    ETIMER1_REG(ETIMER_CR) |= 0x08;        //CLK_START
}

/********************************************************************
* Function Name         :       count_mode
* Description           :       set count mode
* Input                 :       - cnt - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer_count_mode(int cnt)
{
    ETIMER1_REG(ETIMER_CR) = 0x02;         //count_mode
    ETIMER1_REG(CNTVAILDR) = cnt;          //0->value
    ETIMER1_REG(CNTVAIHDR) = cnt>>8;
    ETIMER1_REG(ETIMER_CR) |= 0x08;        //CLK_START
}


/********************************************************************
* Function Name         :       event_mode
* Description           :       set event mode
* Input                 :       - cnt - 
*                       :       - clk_edge_mode - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer_event_mode(int cnt,char clk_edge_mode)
{
    ETIMER1_REG(ETIMER_CR) = 0x03;              //event_mode
    ETIMER1_REG(ETIMER_CR) |= clk_edge_mode;         //CLK_EDGE,0x00 or 0x40
    ETIMER1_REG(CNTVAILDR) = cnt;               //value->0
    ETIMER1_REG(CNTVAIHDR) = cnt>>8;
    ETIMER1_REG(ETIMER_CR) |= 0x08;             //CLK_START
}


/********************************************************************
* Function Name         :       pwmtest_mode
* Description           :       set PWM test mode
* Input                 :       - cnt - 
*                       :       - val - 
*                       :       - count - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer_pwmtest_mode(int cnt,int val,int count)
{
    ETIMER1_REG(ETIMER_CR) = 0x05;          //pwm_mode
    ETIMER1_REG(ETIMER_CR) |= 0x40;         //CLK_EDGE_UP
    ETIMER1_REG(CNTVAILDR) = cnt;
    ETIMER1_REG(CNTVAIHDR) = cnt>>8;
    ETIMER1_REG(CCVAILDR) = val;
    ETIMER1_REG(CCVAIHDR) = val>>8;
    ETIMER1_REG(PWMTIMVAIDR) = count;
    ETIMER1_REG(PWMTIMVAIHDR) = count>>8;       //total cyc
    ETIMER1_REG(ETIMER_CR) |= 0x08;         //CLK_START
}



