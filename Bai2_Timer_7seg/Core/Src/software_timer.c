/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1
#define COUNTER_1HZ 1000
#define COUNTER_25HZ 40
#define COUNTER_100HZ 10

//software timer variable
uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

uint16_t flag_timer3 = 0;
uint16_t timer3_counter = 0;
uint16_t timer3_MUL = 0;

uint16_t flag_timerS = 0;
uint16_t timerS_counter = 0;
uint16_t timerS_MUL = 0;

uint16_t counter_1hz = 0;
uint16_t counter_25hz = 0;
uint16_t counter_100hz = 0;

uint16_t flag_timer7seg = 0;
uint16_t timer7seg_counter = 0;
uint16_t timer7seg_MUL = 0;

uint16_t flag_timer_second = 0;
uint16_t timer_second_counter = 0;
uint16_t timer_second_MUL = 0;

/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;
}

void setTimer3(uint16_t duration){
	timer3_MUL = duration/TIMER_CYCLE_2;
	timer3_counter = timer3_MUL;
	flag_timer3 = 0;
}

void setTimerShift(uint16_t duration){
	timerS_MUL = duration/TIMER_CYCLE_2;
	timerS_counter = timerS_MUL;
	flag_timerS = 0;
}

void setTimer7seg(uint16_t duration){
	timer7seg_MUL = duration/TIMER_CYCLE_2;
	timer7seg_counter = timer7seg_MUL;
	flag_timer7seg = 0;
}

void setTimerSecond(uint16_t duration){
	timer_second_MUL = duration/TIMER_CYCLE_2;
	timer_second_counter = timer_second_MUL;
	flag_timer_second = 0;
}
/**
 *
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}

		if(timer3_counter > 0){
			timer3_counter--;
			if(timer3_counter == 0) {
				flag_timer3 = 1;
				timer3_counter = timer3_MUL;
			}
		}

		if(timerS_counter > 0){
			timerS_counter--;
			if(timerS_counter == 0) {
				flag_timerS = 1;
				timerS_counter = timerS_MUL;
			}
		}

		if(timer7seg_counter > 0){
			timer7seg_counter--;
			if(timer7seg_counter == 0){
				flag_timer7seg = 1;
				timer7seg_counter = timer7seg_MUL;
			}
		}

		if (timer_second_counter > 0){
			timer_second_counter--;
			if(timer_second_counter == 0){
				flag_timer_second = 1;
				timer_second_counter = timer_second_MUL;
			}
		}

		// 1ms interrupt here
//		if(counter_1hz > 0){
//			counter_1hz--;
//		} else {
//			counter_1hz = COUNTER_1HZ;
//			led7_Scan();  // Call 1Hz LED scan function
//		}
//		led7_Scan();
	}
}

