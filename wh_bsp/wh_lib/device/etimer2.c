/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       etimer2.c
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
void etimer2_pwm_mode(int cnt,int val,int count)
{
    ETIMER2_REG(ETIMER_CR) = 0x04;      //pwm_mode
    ETIMER2_REG(ETIMER_CR) |= 0x40;     //CLK_EDGE_UP

    ETIMER2_REG(CNTVAILDR) = cnt;
    ETIMER2_REG(CNTVAIHDR) = cnt>>8;
    ETIMER2_REG(CCVAILDR) = val;
    ETIMER2_REG(CCVAIHDR) = val>>8;

    ETIMER2_REG(PWMTIMVAIDR) = count;
    ETIMER2_REG(PWMTIMVAIHDR) = count>>8;   //total cyc, if set 0,always pwm
    ETIMER2_REG(ETIMER_CR) |= 0x08;     //CLK_START
    //ETIMER2_REG(ETIMER_CR) |= 0x10;       //reset
}



/********************************************************************
* Function Name         :       timer_mode
* Description           :       set timer mode
* Input                 :       - cnt - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer2_timer_mode(int cnt)
{
    ETIMER2_REG(ETIMER_CR) = 0x01;         //timer_mode
    ETIMER2_REG(CNTVAILDR) = cnt;          //value->0
    ETIMER2_REG(CNTVAIHDR) = cnt>>8;
    ETIMER2_REG(ETIMER_CR) |= 0x08;        //CLK_START
}

/********************************************************************
* Function Name         :       count_mode
* Description           :       set count mode
* Input                 :       - cnt - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer2_count_mode(int cnt)
{
    ETIMER2_REG(ETIMER_CR) = 0x02;         //count_mode
    ETIMER2_REG(CNTVAILDR) = cnt;          //0->value
    ETIMER2_REG(CNTVAIHDR) = cnt>>8;
    ETIMER2_REG(ETIMER_CR) |= 0x08;        //CLK_START
}


/********************************************************************
* Function Name         :       event_mode
* Description           :       set event mode
* Input                 :       - cnt - 
*                       :       - clk_edge_mode - 
* Output                :       none
* Return                :       none
********************************************************************/
void etimer2_event_mode(int cnt,char clk_edge_mode)
{
    ETIMER2_REG(ETIMER_CR) = 0x03;              //event_mode
    ETIMER2_REG(ETIMER_CR) |= clk_edge_mode;         //CLK_EDGE,0x00 or 0x40
    ETIMER2_REG(CNTVAILDR) = cnt;               //value->0
    ETIMER2_REG(CNTVAIHDR) = cnt>>8;
    ETIMER2_REG(ETIMER_CR) |= 0x08;             //CLK_START
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
void etimer2_pwmtest_mode(int cnt,int val,int count)
{
    ETIMER2_REG(ETIMER_CR) = 0x05;          //pwm_mode
    ETIMER2_REG(ETIMER_CR) |= 0x40;         //CLK_EDGE_UP
    ETIMER2_REG(CNTVAILDR) = cnt;
    ETIMER2_REG(CNTVAIHDR) = cnt>>8;
    ETIMER2_REG(CCVAILDR) = val;
    ETIMER2_REG(CCVAIHDR) = val>>8;
    ETIMER2_REG(PWMTIMVAIDR) = count;
    ETIMER2_REG(PWMTIMVAIHDR) = count>>8;       //total cyc
    ETIMER2_REG(ETIMER_CR) |= 0x08;         //CLK_START
}



