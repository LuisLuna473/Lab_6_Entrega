/*
 * Setups.h
 *
 * Created: 24/04/2024 20:20:27
 *  Author: luisa
 */ 


#ifndef SETUPSMICRO_H_
#define SETUPSMICRO_H_
/*
	DEFINICIONES E INCLUDES BASE
*/

#define F_CPU 16000000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

/*
	DEFINICIONES DE VARIABLES
*/
#define Positivo 1
#define Invertido 0
#define Externo 1
#define Interno 0
#define Fast 1
#define Phase 0
#define Todo 1
#define A 0
#define B 1
#define C 2
#define D 3
#define Phase8 0
#define Phase9 1
#define Phase10 2
#define PhaseICR 3
#define PhaseOCR 4
#define Fast8 5
#define Fast9 6
#define Fast10 7
#define FastICR 8
#define FastOCR 9
#define PC7 7



/*
	FUNCIONES
*/

void SetupEntrada(uint8_t PuertoEntrada, uint8_t PinEntrada);
void SetupSalida(uint8_t PuertoSalida ,uint8_t PinSalida);
void SetupTimer0(uint16_t Prescaler0, uint8_t Desvordamiento0 );
void SetupTimer1(uint_fast16_t Prescaler1, uint16_t Desvordamiento1);
void SetupTimer2(uint16_t Prescaler2, uint8_t Desvordamiento2, uint8_t Cristal);
void SetupADC(uint8_t PinADC);
void SetupPWM0(uint8_t ModoPWM0, uint8_t Sentido0, uint8_t SaidaPMW0, uint16_t PrescalerPWM0);
void SetupPWM1(uint8_t ModoPWM1, uint8_t Sentido1, uint8_t SaidaPMW1, uint16_t PrescalerPWM1);
void SetupPWM2(uint8_t ModoPWM2, uint8_t Sentido2, uint8_t SaidaPMW2, uint16_t PrescalerPWM2); 



#endif /* SETUPSMICRO_H_ */