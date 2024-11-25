/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
//#include "software_timer.h"

extern uint16_t flag_timer2;
extern uint16_t flag_timer3;
extern uint16_t flag_timer7seg;
extern uint16_t flag_timerS;
extern uint16_t flag_timer_second;

void timer_init();
void setTimer2(uint16_t duration);
void setTimer3(uint16_t duration);
void setTimerShift(uint16_t duration);
void setTimer7seg(uint16_t duratioin);
void setTimerSecond(uint16_t duration);

#endif /* INC_SOFTWARE_TIMER_H_ */
