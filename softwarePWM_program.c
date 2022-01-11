/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: software PWM
 *  Layer arch : MCAL
 *  Created on: Jan 10, 2022
 *  version:1
 *
 */



#include "STD_TYPES.h"
#include "timers_interface.h"
#include "softwarePWM_private.h"
#include "softwarePWM_interface.h"
#include "DIO_interface.h"


void void_Motor1OnMotor2Off(void)
{
	DIO_SetPinValue(PORTD,PIN4,HIGH);
    DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void void_Motor1OffMotor2On(void)
{
	DIO_SetPinValue(PORTD,PIN4,LOW);
    DIO_SetPinValue(PORTD,PIN5,HIGH);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void void_Motor1OffMotor2Off(void)
{
	DIO_SetPinValue(PORTD,PIN4,LOW);
    DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void void_Motor1OnMotor2On(void)
{
	DIO_SetPinValue(PORTD,PIN4,HIGH);
	DIO_SetPinValue(PORTD,PIN5,HIGH);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void void_pwmPinsInit(void)
{
	 void_timersInit() ;
	 u8_setTimer0OverFlowRegTicksBeforeOV(u8_MAX_8BIT_REG_HOLD) ;
	 DIO_SetPinDirection(PORTD,PIN4,OUTPUT);
	 DIO_SetPinDirection(PORTD,PIN5,OUTPUT);
	 DIO_SetPinValue(PORTD,PIN4,LOW);
	 DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t u8_pwmMotorsControl(uint8_t u8_wantedPWMDuty,uint8_t u8_wantedMotorForPwm)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	uint8_t u8_SetCompareVal  ; 
	if(u8_wantedPWMDuty<=u8_PWM_100_DUTY_PERCENT)
	{
		if(u8_wantedPWMDuty>u8_PWM_0_DUTY_PERCENT && u8_wantedPWMDuty<u8_PWM_100_DUTY_PERCENT)
		{
			u8_SetCompareVal = (uint8_t)(((uint16_t)(u8_wantedPWMDuty*u8_MAX_8BIT_REG_HOLD))/u8_PWM_100_DUTY_PERCENT) ;
			u8_setTimer0CompareRegTicksBeforeOV(u8_SetCompareVal) ; 
			switch(u8_wantedMotorForPwm)
			{
				case u8_PWM_TO_M1_STOP_M2 : u8_setCallBack(u8_TIMER0_COMPARE_ON_MATCH,void_Motor1OffMotor2Off) ;
											u8_setCallBack(u8_TIMER0_OVER_FLOW,void_Motor1OnMotor2Off) ;
											break ;  
				case u8_PWM_TO_M2_STOP_M1 : u8_setCallBack(u8_TIMER0_COMPARE_ON_MATCH,void_Motor1OffMotor2Off) ;
											u8_setCallBack(u8_TIMER0_OVER_FLOW,void_Motor1OffMotor2On) ;
											break ; 
				case u8_PWM_TO_M1_AND_M2  : u8_setCallBack(u8_TIMER0_COMPARE_ON_MATCH,void_Motor1OffMotor2Off) ;
											u8_setCallBack(u8_TIMER0_OVER_FLOW,void_Motor1OnMotor2On) ;
											break ; 
				default 				  :  u8_ErrorFlag = u8_NOK ; 
											break ; 
			}
			if(u8_ErrorFlag==u8_OK)
			{
				u8_timerIntModesEn(u8_TIMER0_OVER_FLOW) ; 
				u8_timerIntModesEn(u8_TIMER0_COMPARE_ON_MATCH) ;
			}
		}
		else if (u8_wantedPWMDuty==u8_PWM_0_DUTY_PERCENT&&(u8_wantedMotorForPwm>=u8_PWM_TO_M1_STOP_M2)&&(u8_wantedMotorForPwm<=u8_PWM_TO_M1_AND_M2))
		{
			u8_timerIntModesDis(u8_TIMER0_OVER_FLOW) ;
			u8_timerIntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ; 
			DIO_SetPinValue(PORTD,PIN4,LOW);
			DIO_SetPinValue(PORTD,PIN5,LOW);
		}
		else 
		{
			switch(u8_wantedMotorForPwm)
			{
				case u8_PWM_TO_M1_STOP_M2 : DIO_SetPinValue(PORTD,PIN4,HIGH);
											DIO_SetPinValue(PORTD,PIN5,LOW); 
											break ;  
				case u8_PWM_TO_M2_STOP_M1 : DIO_SetPinValue(PORTD,PIN4,LOW);
											DIO_SetPinValue(PORTD,PIN5,HIGH); 
											break ; 
				case u8_PWM_TO_M1_AND_M2  : DIO_SetPinValue(PORTD,PIN4,HIGH);
											DIO_SetPinValue(PORTD,PIN5,HIGH); 
											break ; 
				default 				  :  u8_ErrorFlag = u8_NOK ; 
											break ; 
			}
			
			if(u8_ErrorFlag==u8_OK)
			{
				u8_timerIntModesDis(u8_TIMER0_OVER_FLOW) ;
				u8_timerIntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ; 
			}
		}
	}
	else 
	{
		u8_ErrorFlag = u8_NOK ; 
	}
	return u8_ErrorFlag ; 
	
}
