/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: Kishk
 *
 */

#include "../Services/STD_TYPES.h"
#include "../Services/BIT_MATHS.h"
#include "util/delay.h"
#include "../MCAL/01-DIO/DIO_interface.h"
#include "../MCAL/02- EXTI/EXTI_interface.h"
#include "../MCAL/03- GIE/GIE_interface.h"

#define u8LED_NUMBER			8

void Interrupt_PatternLED(void);
volatile u8 u8Counter = 0, u8Iterator = 0;

int main(void) {
	DIO_enumSetPinDirection(DIO_PORTD_PIN2, DIO_INPUT);
	DIO_voidActivePullUp(DIO_PORTD_PIN2);

	DIO_enumSetPortDirection(DIO_PORTA, DIO_DIRECTION_OUTPUT);

	EXTI_voidInit();

	EXTI_voidCallBack(Interrupt_PatternLED, EXTI_LINE0);
	GIE_void_Enable();

	while (1) {
	}

}

void Interrupt_PatternLED(void) {
	_delay_ms(300);
	u8Counter++;
	if (u8Counter == 1) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_HIGH);
		_delay_ms(500);
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		_delay_ms(500);
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);

	} else if (u8Counter == 2) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER; u8Iterator++) {
			DIO_enumSetPortValue(DIO_PORTA, DIO_HIGH << u8Iterator);
			_delay_ms(250);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
	}

	else if (u8Counter == 3) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER; u8Iterator++) {
			DIO_enumSetPortValue(DIO_PORTA, 0x80 >> u8Iterator);
			_delay_ms(250);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
	}

	else if (u8Counter == 4) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER / 2; u8Iterator++) {
			DIO_enumSetPinValue(DIO_PORTA_PIN3 - u8Iterator, DIO_HIGH);
			DIO_enumSetPinValue(DIO_PORTA_PIN4 + u8Iterator, DIO_HIGH);
			_delay_ms(300);
			DIO_enumSetPinValue(DIO_PORTA_PIN3 - u8Iterator, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTA_PIN4 + u8Iterator, DIO_LOW);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);

	} else if (u8Counter == 5) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);

		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER / 2; u8Iterator++) {
			DIO_enumSetPinValue(DIO_PORTA_PIN0 + u8Iterator, DIO_HIGH);
			DIO_enumSetPinValue(DIO_PORTA_PIN7 - u8Iterator, DIO_HIGH);
			_delay_ms(300);
			DIO_enumSetPinValue(DIO_PORTA_PIN0 + u8Iterator, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTA_PIN7 - u8Iterator, DIO_LOW);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
	}

	else if (u8Counter == 5) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER - 1; u8Iterator++) {
			DIO_enumSetPinValue(u8Iterator, DIO_HIGH);
			_delay_ms(250);
			DIO_enumSetPinValue(u8Iterator, DIO_LOW);
		}
		for (u8Iterator = u8LED_NUMBER - 1; u8Iterator > 0; u8Iterator--) {
			DIO_enumSetPinValue(u8Iterator, DIO_HIGH);
			_delay_ms(250);
			DIO_enumSetPinValue(u8Iterator, DIO_LOW);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
	}

	else if (u8Counter == 6) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER; u8Iterator++) {
			DIO_enumSetPinValue(u8Iterator, DIO_HIGH);
			_delay_ms(300);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
	}

	else if (u8Counter == 7) {
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER / 2; u8Iterator++) {
			DIO_enumSetPinValue(DIO_PORTA_PIN0 + u8Iterator, DIO_HIGH);
			DIO_enumSetPinValue(DIO_PORTA_PIN7 - u8Iterator, DIO_HIGH);
			_delay_ms(300);
		}

		for (u8Iterator = 0; u8Iterator < u8LED_NUMBER / 2; u8Iterator++) {
			DIO_enumSetPinValue(DIO_PORTA_PIN3 - u8Iterator, DIO_LOW);
			DIO_enumSetPinValue(DIO_PORTA_PIN4 + u8Iterator, DIO_LOW);
			_delay_ms(300);
		}
		DIO_enumSetPortValue(DIO_PORTA, DIO_DIRECTION_LOW);
		u8Counter = 0;
	}
	EXTI_voidClearFlag(EXTI_LINE0);
}

