/*
 * Lab 6.c
 *
 * Created: 20/04/2024 16:15:47
 * Author : luisa
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "Setups/SetupsMicro.h"


void initUART9600(void);
void writeUART(char Caracter); 
void writeTextUART(char * Texto);
void initADC (void); 
volatile uint8_t bufferTX; 

int8_t LOL = 0; 


int main(void)
{
    DDRB = 0x3F;
	DDRC = 0x3F;
	initUART9600();
	sei();
	writeTextUART("Hola Luis Elige una opción");
	writeTextUART("1. Leer Pot");
	writeTextUART("2. Enviar ascii");
	writeUART(10);
	writeUART(13);
	initADC(); 
	
	//PORTD = Varible de USART comunicado del nano
    while (1) 
    {
    }
}

void initUART9600(void){
	//Paso 1: RX como entrada y TX como salida
	DDRD &= ~(1<<DDD0);
	DDRD |= (1<<DDD1);
	
	//Paso 2: Confi. UCSR0A
	UCSR0A = 0; 
	
	//Paso 3: Conf. UCSR0B > donde habilitamos ISR de recepción, habilitamos rx y tx
	UCSR0B = 0;
	
	UCSR0B |= (1<< RXCIE0) |(1<<RXEN0) |(1<<TXEN0);
	
	//Paso 4: Cond. UCSR0C > Asyncrono, Paridad: None, 1 bit de Stop, Data bits 8/bits
	UCSR0C = 0; 
	
	UCSR0C |= (1<< UCSZ01)| (1<< UCSZ00);
	
	//Paso #5: Conf. velocidad de Baudrate: 9600
	
	UBRR0 = 103;  
	
}

void writeTextUART(char * Texto){
	
	for (int i=0; Texto[i]!='\0'; i++){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = Texto[i]; 
	}
}

void writeUART(char Caracter){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = Caracter; 
}

ISR (USART_RX_vect){
	
	bufferTX = UDR0;
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = bufferTX;
	/*switch (bufferTX)
	{
	case bufferTX == 1:
		bufferTX = UDR0;
		PORTB = (bufferTX & 0b00111111);
		PORTC = ((bufferTX & 0b11000000)>>6);
		break;
	case bufferTX == 2:
		//ADC 
		break;
		
	case bufferTX:
		writeTextUART("Selecciona una opción valida");
		break;
		
	}*/
	
	PORTB = (bufferTX & 0b00111111);
	PORTC = ((bufferTX & 0b11000000)>>6);
}
void initADC(void){
	ADMUX|=(1<<MUX2)|(1<<MUX1);
	//JUSTIFICACION IZQUIERDA
	ADMUX |= (1<<ADLAR);
	//REFERENCIA INTERNA
	ADMUX |= (1<<REFS0);
	// HABILITAR INTERRUPCION
	ADCSRA |= (1<<ADIE);
	//PRESCALER 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//HABILITAR
	ADCSRA |= (1<<ADEN);
}

ISR(ADC_vect){
	LOL = ADCH; 
	ADCSRA |= (1<<ADIF);
}