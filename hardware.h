/***************************************************************************//**
	Ejercicio
	hardware.h
	Jun 4, 2025

	Descripcion:

	Header correspondiente a hardware.c,
	contiene todos los prototipos de funciones y definiciones publicas al usuario.
	Modulo encargado de controlar los GPIOs de la Raspberry PI 3:

	-pinMode: Define la direccion del pin, input o output. Recibe 2 punteros a strings; el pin y la direccion.

	-pinSet: Asigna un valor al pin. Recibe 2 punteros a strings; el pin y el valor.

	-pinRead: Lee el valor de un pin. Recibe 1 puntero a string; el pin a ver.

	-finishAll: Finaliza o "devuelve" todos los pines deseados. Recibe un arreglo de punteros a strings (los pines)
	 y el tamanio de dicho arreglo.

	-startAll: Opuesto al finishAll, inicializa todos los pines deseados con un modo deseado (input/output).
	Recibe un arreglo de strings (pines), su tamanio, y el modo de direccion.

 ******************************************************************************/

#ifndef HARDWARE_H
#define HARDWARE_H

/*******************************************************************************
 * INCLUSION DE HEADERS
 ******************************************************************************/


/*******************************************************************************
 * MACROS Y DEFINICIONES DE PREPROCESADOR
 ******************************************************************************/



/*******************************************************************************
 * TYPEDEFS, ESTRUCTURAS Y ENUMERACIONES
 ******************************************************************************/

#define GPIO17 "17"
#define GPIO4 "4"
#define GPIO18 "18"
#define GPIO23 "23"
#define GPIO24 "24"
#define GPIO25 "25"
#define GPIO22 "22"
#define GPIO27 "27"
#define OUTPUT "out"
#define INPUT "in"
#define ON "1"
#define OFF "0"
#define MAXPINES (sizeof(pines)/sizeof(pines[0]))



/*******************************************************************************
 * PROTOTIPOS DE VARIABLES GLOBALES PUBLICAS
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES PUBLICAS
 ******************************************************************************/

void pinMode (char* pin, char* direccion);
void pinSet (char* pin, char* valor);
uint8_t pinRead (char* pin);
void finishAll(char* pines [],uint8_t max);
void startAll(char* pines [], uint8_t max, char* modo);


/*******************************************************************************
 ******************************************************************************/

#endif // HARDWARE_H
