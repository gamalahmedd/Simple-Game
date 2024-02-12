#include "LCD.h"
#include "KEYPAD.h"
#include "TIMER_ZERO.h"
#include <avr/interrupt.h>

volatile unsigned char counter = 0;
int main(void)
{
	unsigned char remain_time = 10, read_value;
	LCD_vInit();
	KEYPAD_vInit('C');
	TIMER_ZERO_vInitCTCMode(80, 1);
	LCD_vSendString("3 + ? = 8");
	LCD_vMoveCursor(2, 1);
	LCD_vSendString("Remaining Time ");
	LCD_vSendString("10");
    while(1)
    {
        read_value = KEYPAD_u8Read('C');
		if(read_value != NOTPRESSED)
		{
			if(read_value == '5')
			{
				LCD_vClearScreen();
				LCD_vSendString("Correct Answer");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("Congratulations!");
				break;
			}
			else
			{
				LCD_vClearScreen();
				LCD_vSendString("Wrong Answer");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("Try Again Later!");
				break;
			}
		}	
		else
		{
			if(counter >= 100)
			{
				remain_time--;
				counter = 0;
				LCD_vMoveCursor(2, 16);
				LCD_vSendChar((remain_time / 10) + 48);
				LCD_vSendChar((remain_time % 10) + 48);
			}
			if(remain_time == 0)
			{
				LCD_vClearScreen();
				LCD_vSendString("Game Over!");
				break;
			}
		}					
    }
}

ISR(TIMER0_COMP_vect)
{
	counter++;
}