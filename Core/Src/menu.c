/*
 * menu.c
 *
 *  Created on: Dec 4, 2025
 *      Author: huse2
 */

#include "menu.h"

extern TIM_HandleTypeDef htim4;


char *main_menu_items[] =
		{ " -> Set Frequency", "-> Set DutyCycle", "-> About" };
uint8_t selectedMenuItem = 0;
uint32_t encoderValue = 0;
uint32_t frequency = 0;
uint32_t duty = 0;
uint8_t onoff_flag = 1;

void printMenuItems(uint8_t menuCount) {

	SSD1306_Fill(SSD1306_COLOR_BLACK);

	int i = 0;

	for (i = 0; i < menuCount; i++) {
		SSD1306_GotoXY(0, i * 20);

		if (i == selectedMenuItem) {
			SSD1306_Puts(main_menu_items[i], &Font_7x10, SSD1306_COLOR_BLACK);
		} else {
			SSD1306_Puts(main_menu_items[i], &Font_7x10, SSD1306_COLOR_WHITE);
		}
	}
	SSD1306_UpdateScreen();
}

void handleMenuNavigation(void) {
	printMenuItems(MAIN_MENU_ITEM_COUNT);
	HAL_Delay(150);

	encoderValue = (TIM1->CNT) >> 2;
	selectedMenuItem = encoderValue % MAIN_MENU_ITEM_COUNT;

	SSD1306_Puts(main_menu_items[selectedMenuItem], &Font_7x10,
			SSD1306_COLOR_WHITE);

	if (selectedMenuItem == 0 && SELECT_CLICK) {
		selectedMenuItem = 0;
		(TIM1->CNT) = 0;
		HAL_Delay(500);
		while (1) {
			uint8_t outputStatus = HAL_GPIO_ReadPin(output_ON_GPIO_Port,
					output_ON_Pin);
			if (outputStatus) {
				showInfo();
				break;
			}
			setFrequency();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				(TIM1->CNT) = 0;
				HAL_Delay(500);
				break;
			}
		}
		return;

	}

	if (selectedMenuItem == 1 && SELECT_CLICK) {
		selectedMenuItem = 0;
		(TIM1->CNT) = 0;
		HAL_Delay(500);
		while (1) {
			uint8_t outputStatus = HAL_GPIO_ReadPin(output_ON_GPIO_Port,
					output_ON_Pin);
			if (outputStatus) {
				showInfo();
				break;
			}
			setDutyCycle();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				(TIM1->CNT) = 0;
				HAL_Delay(500);
				break;
			}
		}
		return;

	}

	if (selectedMenuItem == 2 && SELECT_CLICK) {
		selectedMenuItem = 0;
		HAL_Delay(500);
		while (1) {
			showAbout();
			HAL_Delay(150);
			if (SELECT_CLICK) {
				(TIM1->CNT) = 0;
				HAL_Delay(500);
				break;
			}
		}
		return;

	}

	if (ONOFFCLICK) {
		if (!onoff_flag) {
			HAL_GPIO_WritePin(output_OFF_GPIO_Port, output_OFF_Pin, 1);
			HAL_GPIO_WritePin(output_ON_GPIO_Port, output_ON_Pin, 0);
			pwmChannelStop(&htim4, TIM_CHANNEL_1);
			onoff_flag = 1;
		} else {
			HAL_GPIO_WritePin(output_OFF_GPIO_Port, output_OFF_Pin, 0);
			HAL_GPIO_WritePin(output_ON_GPIO_Port, output_ON_Pin, 1);
			setPwmFreqDuty(frequency, duty);
			pwmChannelStart(&htim4, TIM_CHANNEL_1);
			onoff_flag = 0;
		}
	}

}
void setFrequency() {
	char buffer[20];
	//frequency = 0;
	frequency = (TIM1->CNT) >> 2;
	frequency *= 50;
	if (frequency >= 1000000) {
		frequency = 1000000;
	}

	sprintf(buffer, "%ld", frequency);
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(10, 10);
	SSD1306_Puts(buffer, &Font_16x26, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(0, 50);
	SSD1306_Puts("UNIT -> Hertz(Hz)", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}

void setDutyCycle() {
	char buffer[20];
	//duty = 0;
	duty = (TIM1->CNT) >> 2;
	duty *= 5;
	if (duty >= 100) {
		duty = 100;
	}

	sprintf(buffer, "%ld", duty);
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(10, 10);
	SSD1306_Puts(buffer, &Font_16x26, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(0, 50);
	SSD1306_Puts("UNIT -> %DutyCycle", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();

}

void showAbout() {
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(25, 0);
	SSD1306_Puts("SILICON", &Font_11x18, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(40, 25);
	SSD1306_Puts("ROOM", &Font_11x18, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(0, 50);
	SSD1306_Puts("DON'T FORGET SUB !!!!", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}

void showInfo() {
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(25, 0);
	SSD1306_Puts("OUTPUT", &Font_11x18, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(40, 25);
	SSD1306_Puts("ON !!", &Font_11x18, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
	HAL_Delay(2000);
}

