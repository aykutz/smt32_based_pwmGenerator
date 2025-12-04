/*
 * pwm.h
 *
 *  Created on: Dec 4, 2025
 *      Author: huse2
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_
#include "main.h"

//NOTE
//freq = timer_freq / (arr*prescaler)
#define TIMER_FREQUENCY 			    80000000 // apb1 timer clock
#define PRESCALER_VALUE   				80 // psc 80-1
#define CONSTANT_TIMER_VALUE 			(TIMER_FREQUENCY/PRESCALER_VALUE)


void pwmChannelStart(TIM_HandleTypeDef *htim, uint32_t channel);
void pwmChannelStop(TIM_HandleTypeDef *htim, uint32_t channel);
void setPwmFreqDuty(float f, float dc);

#endif /* INC_PWM_H_ */
