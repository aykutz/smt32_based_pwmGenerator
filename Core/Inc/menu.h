/*
 * menu.h
 *
 *  Created on: Dec 4, 2025
 *      Author: huse2
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "stdio.h"
#include "main.h"
#include "ssd1306.h"
#include "fonts.h"
#include "pwm.h"


#define MAIN_MENU_ITEM_COUNT		3
#define SELECT_CLICK				!(HAL_GPIO_ReadPin(select_GPIO_Port, select_Pin))
#define ONOFFCLICK					(HAL_GPIO_ReadPin(OnOffButton_GPIO_Port, OnOffButton_Pin))

void printMenuItems(uint8_t menuCount);
void handleMenuNavigation(void);
void setFrequency(void);
void showAbout(void);
void setDutyCycle(void);
void showInfo(void);

#endif /* INC_MENU_H_ */
