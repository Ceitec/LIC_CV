/*
 * LIC_CV_01.c
 *
 * Created: 28.7.2015 17:01:20
 *  Author: Lukas
 */ 


#include <avr/io.h>
//#include <avr/iom32.h>
#include "inc/AllInit.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "inc/common_defs.h"
#include "inc/defines.h"
#include "inc/timer.h"
#include "inc/uart_types.h"
#include "inc/uart_tri_0.h"
#include "inc/Tribus_types.h"
#include "inc/Tribus.h"
#include <stdlib.h>
// Standard Input/Output functions
#include <stdio.h>
#include <string.h>

#include "inc/SPI.h"
#include "inc/mfrc522.h"

//#include <>

volatile byte timer0_flag = 0; // T = 10ms
byte led_timer = 0;

//gobal var MFRC522
uint8_t curr_id[5];
uint16_t card_tipe;
uint8_t str[MAX_LEN];
uint8_t status;



/* MFRC522 Komunikace */
// mode debug
#define DEBUG_ON

/*
check rc522 rfid reader writer presence
*/
/*
void rc522_check_reader()
{
	uint8_t curr_read_status = mfrc522_get_version();
	if (curr_read_status<0x90 || curr_read_status>0x92)
	{
		#if defined(DEBUG_ON)
		printf("NO READER\n");
		#endif
		for(;;);
	}
}
*/

/*
read card serial id
*/
uint8_t rc522_read_card_id(uint8_t *card_id, uint16_t *card_type)
{
	uint8_t status, resx = 0;
	uint8_t buff_data[MAX_LEN];

	*card_type = 0;
	if(mfrc522_is_card(card_type))
	{
		status = mfrc522_get_card_serial(buff_data);
		if (status==CARD_FOUND)
		{
			memcpy(card_id,buff_data,5);//kopi id and checksum at last byte (5th)
			resx = 1;
		}
		else
		{
			resx = 0;
		}
	}
	else
	{
		resx = 0;
	}
	
	return resx;
}



void send_data(void)
{
	uart0_put_data((byte *) &TB_bufOut);
}

//----------------------------------------------------------
ISR(TIMER1_CAPT_vect) {
	// T = 10ms
	timer0_flag = true;
}

//----------------------------------------------------------
void process_timer_100Hz(void)
{
	if (timer0_flag) { // T = 10ms
		timer0_flag = false;
		uart0_ISR_timer();
		if (led_timer > 0) {
			led_timer--;
			if (led_timer == 0) {
				PORTB ^= (1 << PB4);
			}
		}
	}
}

void try_receive_data(void)
{
	byte i;
	byte *ptr;
	
	if (uart0_flags.data_received)
	{
		ptr = uart0_get_data_begin();
		for (i=0; i<9; i++)
		{
			TB_bufIn[i] = *ptr;
			ptr++;
		}
		uart0_get_data_end();
		uart0_flags.data_received = FALSE;
		if (TB_Read() == 0)
		{
			switch (TB_Decode())
			{
				case TB_CMD_VZOREK:
					if (rc522_read_card_id(curr_id, &card_tipe))
					{
						TB_SendSerVzorku(TB_AddrReply, TB_AddrModule, TB_ERR_OK, curr_id[0], curr_id[1], curr_id[2], curr_id[3], curr_id[4]);
					}
					else
					{
						TB_SendAck(TB_CV_ERR_SER, 0);
					}
			}
		}
	}
}

int main(void)
{
/*
	DDRA |= (1 << DDA7) | (1 << DDA6) | (1 << DDA5) | (1 << DDA4) | (1 << DDA3) | (1 << DDA2) | (1 << DDA1);
	DDRB |= (1 << DDB4) | (1 << DDB3);
	DDRC |= (1 << DDC7) | (1 << DDC6) | (1 << DDC5) | (1 << DDC4);
	DDRD |= (1 << DDD4) | (1 << DDD3) | (1 << DDD2);
*/

	
	timer_init();
	uart0_init();
	TB_Callback_setBaud = &uart0_set_baud;
	TB_Callback_TX = &send_data;
	TB_Init((void*) 0x10); // addr in eeprom with settings
	SPI_MasterInit();
	mfrc522_init();
	
	sei();
	
    while(1)
    {
		process_timer_100Hz();
		uart0_process();
		try_receive_data();
    }
}
