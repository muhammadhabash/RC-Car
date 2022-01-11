/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: Timer0
 *  Layer arch : MCAL
 *  Created on: Jan 9, 2022
 *  version:1
 *
 */


#ifndef __timers__interface__
#define __timers__interface__


#define u8_OC0_DISCONNECTED					13
#define u8_OC0_CLEAR_ON_COMPARE_MATCH		14
#define u8_OC0_SET_ON_COMPARE_MATCH	  		15
#define u8_TOGGLE_ON_COMPARE_MATCH			16



#define u8_OK								1
#define u8_NOK								0


#define u8_MAX_8BIT_REG_HOLD				255


/*choose one of timer 0 modes :- 
 *1-u8_NORMAL_MODE					
 *2-u8_PWM_PHASE_CORRECT_MODE  	
 *3-u8_CTC_MODE					
 *4-u8_FAST_PWM_MODE				
 */
#define u8_TIMER0_MODE_CONFIG 			    u8_NORMAL_MODE
					
/* choose clock source:-					
 *1-u8_NO_CLK_TIMER_STOP   					
 *2-u8_INTERNAL_CLK_NO_PRE  				
 *3-u8_INTERNAL_CLK_PRE_8					
 *4-u8_INTERNAL_CLK_PRE_64					
 *5-u8_INTERNAL_CLK_PRE_256					
 *6-u8_INTERNAL_CLK_PRE_1024				
 *7-u8_EXTERNAL_CLK_FALLING					
 *8-u8_EXTERNAL_CLK_RISING					
 */					
#define u8_TIMER0_1_CLOCK_SELECT			u8_INTERNAL_CLK_PRE_64

/*OC0 config if one of pwm modes set:-
 *1-u8_OC0_DISCONNECTED				
 *2-u8_OC0_CLEAR_ON_COMPARE_MATCH
 *3-u8_OC0_SET_ON_COMPARE_MATCH	  
 */
#define u8_TIMER0_COMP_MATCH_PWM_CONFIG		u8_OC0_DISCONNECTED

/*OC0 config if one of non-pwm modes set:-
 *1-u8_OC0_DISCONNECTED				
 *2-u8_TOGGLE_ON_COMPARE_MATCH
 *3-u8_OC0_CLEAR_ON_COMPARE_MATCH
 *4-u8_OC0_SET_ON_COMPARE_MATCH	
 */
#define u8_TIMER0_COMP_MATCH_NON_PWM_CONFIG u8_OC0_DISCONNECTED



#define u8_TIMER0_OVER_FLOW					17
#define u8_TIMER0_COMPARE_ON_MATCH			18

void void_timersInit(void) ; 
uint8_t u8_StartTimer0WithclockAndPrescalerSelect(uint8_t u8_preScallerVal) ;
uint8_t u8_timerClearIntFlag(uint8_t u8_wantedIntClearFlag) ;
uint8_t u8_timerIntModesEn(uint8_t u8_wantedIntModeEn) ;
uint8_t u8_timerIntModesDis(uint8_t u8_wantedIntModeDis) ;
uint8_t u8_timerClearIntFlag(uint8_t u8_wantedIntFlagMode) ;
uint8_t u8_setTimer0CompareRegTicksBeforeOV(uint8_t u8_wantedTicksToCompare) ;
uint8_t u8_setTimer0OverFlowRegTicksBeforeOV(uint8_t u8_wantedTicksBeforeOV) ;
uint8_t u8_setCallBack(uint8_t u8_wantedISRModeToSet,void(*ISRFuncToSet)(void))  ;
void void_stopTimer0(void) ;






#endif
