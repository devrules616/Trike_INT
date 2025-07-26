/*
 * Trike_m328.c
 *	two motor trike using Atmega328
 * Created: 22-07-2025 19:58:08
 * Author : skid_row
 */ 
#define F_CPU 8000000UL		//8Mhz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define IN1 PINC1		//M1 +ve
#define IN2 PINC2		//	
#define IN3 PINC3		//M2 +ve
#define IN4 PINC4
#define MOTOR_PORT PORTC
#define MOTOR_DDR  DDRC
#define SENSOR_DDR DDRD
#define SENSOR_PORT PORTD
/*----left sensor attached to pin4(PD2/INT0) & right sensor attached to pin5(PD3/INT1)  -----*/
ISR (INT0_vect)
{	MOTOR_PORT=0x12;
	_delay_ms(400);
	MOTOR_PORT=0x00;
	//left sensor triggered
	/*if ((PIND&(1<<PIND3)))	//PD3 (right sensor not triggered i.e it is still high)
	{
		MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
		MOTOR_PORT=0x14;_delay_ms(250);// MOVE BACK a few hundred milliseconds _delay_ms(190)
		MOTOR_PORT=0x12;_delay_ms(190);// TURN RIGHT say 45 degrees
		MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
	}
	 else
	 {
		 MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
		 MOTOR_PORT=0x14;_delay_ms(400);// MOVE BACK a few hundred milliseconds _delay_ms(400)
		 MOTOR_PORT=0x12;_delay_ms(190);// TURN RIGHT say 90 degrees
		 MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
	 }*/
	
}

ISR (INT1_vect)
{	MOTOR_PORT=0x0C;
	_delay_ms(400);
	MOTOR_PORT=0x00;
	//right sensor triggered
	/*if ((PIND&(1<<PIND3)))	//PD3 (right sensor not triggered i.e it is still high)
	{
		MOTOR_PORT=0x00;_delay_ms(50); //STOP few milliseconds	_delay_ms(5)
		MOTOR_PORT=0x14;_delay_ms(250);// MOVE BACK a few hundred milliseconds _delay_ms(190)
		MOTOR_PORT=0x0C;_delay_ms(190);// TURN LEFT say 45 degrees
		MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
	}
	else
	{
		MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
		MOTOR_PORT=0x14;_delay_ms(400);// MOVE BACK a few hundred milliseconds _delay_ms(400)
		MOTOR_PORT=0x0C;_delay_ms(190);// TURN LEFT say 90 degrees
		MOTOR_PORT=0x00;_delay_ms(50);//STOP few milliseconds	_delay_ms(5)
	}*/
}


int main(void)
{	EICRA |= (1 << ISC01) | (1 << ISC11);   // Falling edge for INT0 and INT1
	EICRA &= ~((1 << ISC00) | (1 << ISC10));
	EIMSK |= ((1<<INT1)|(1<<INT0));
	
	SENSOR_DDR &= ~(1<<PIND2);
	SENSOR_DDR &= ~(1<<PIND3);	//PD2 , PD3 set as inputs
	SENSOR_PORT |= (1 << PIND2) | (1 << PIND3);		//pull up enabled
	MOTOR_DDR =0x1E;		//0x1E		0b00011110 to set reqd. pins as output
    MOTOR_PORT=0x00;		// init to DEAD STOP
	sei();		//interrupt enabled
    while (1) 
    {
		//fwd movement code	IN1-1, IN2-0, IN3-1, IN4-0
	MOTOR_PORT=0x0A;
	
	
	/*//back movement code	IN1-0, IN2-1, IN3-0, IN4-1
	MOTOR_PORT=0x14;
	*/
	
	/*//right movement code		IN1-1, IN2-0, IN3-0, IN4-1
	MOTOR_PORT=0x12;
	*/
	
	/*//left movement code		IN1-0, IN2-1, IN3-1, IN4-0
	MOTOR_PORT=0x0C;
	*/
    }
}

