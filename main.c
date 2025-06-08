/***************************************************************************//**
	Ejercicio
	main.c
	Jun 6, 2025
	
	Descripcion:

		Se pide controlar 8 leds conectados a una placa Raspberry Pii (RPI), la cual tiene
	instalado el sistema operativo Linux y se encuentra ejecutando su programa desde la
	consola. Los comandos para controlar los leds se ingresarán por consola, y son los
	mismos que en el ejercicio 6 del TP9, a saber:
	• Por teclado, el usuario ingresará el número (del 0 al 7) del LED que se desea
	prender, en tiempo real. (nota: se agrego la posibilidad de conmutar cada LED por separado)
	• Con la letra 't', todos los LEDs deben cambiar al estado opuesto (si están encendidos
	apagarse y si están apagados encenderse).
	• Con la letra 'c', se deberán apagar todos, y con 's', prender todos.
	• Con la letra 'q', el programa finalizará.

	nota: en la raspberry, se uso el comando:
	gcc -Wall -g -o main main.c input.c hardware.c process.c

 ******************************************************************************/

/*******************************************************************************
 * INCLUSION DE HEADERS
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "hardware.h"
#include "input.h"
#include "process.h"
#include "flags.h"

/*******************************************************************************
 * MACROS Y DEFINICIONES DE PREPROCESADOR
 ******************************************************************************/



/*******************************************************************************
 * TYPEDEFS, ESTRUCTURAS, Y ENUMERACIONES
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES GLOBALES PUBLICAS
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES PRIVADAS DE ENLACE INTERNO
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES GLOBALES CONSTANTES ESTATICAS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES GLOBALES ESTATICAS
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
                        DEFINICION DE FUNCIONES GLOBALES
 *******************************************************************************
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
                        DEFINICION DE FUNCIONES LOCALES
 *******************************************************************************
 ******************************************************************************/

int main (){
	int8_t x;
	char* pines [] = {GPIO17, GPIO4, GPIO18, GPIO23, GPIO24, GPIO25, GPIO22, GPIO27};
	startAll(pines, MAXPINES, OUTPUT);
	while ((x = input()) != QUIT){
		process(&pinSet, &pinRead, x, pines, MAXPINES, ON, OFF);
	}
	finishAll(pines, MAXPINES);
	return 0;
}

 
