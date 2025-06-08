/***************************************************************************//**
	Ejercicio
	input.c
	Jun 7, 2025
	
	Descripcion:

	Contiene las funciones que controlan el ingreso de datos por consola.

	-instrucciones: Imprime las "reglas" del programa y las condiciones que tiene que seguir el imput. No devuelve ni recibe nada.

 ******************************************************************************/

/*******************************************************************************
 * INCLUSION DE HEADERS
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "input.h"
#include "process.h"
#include "flags.h"

/*******************************************************************************
 * MACROS Y DEFINICIONES DE PREPROCESADOR
 ******************************************************************************/

#define ERRORCHECK if((input = getchar()) != '\n' && input != 0) num = ERROR

/*******************************************************************************
 * TYPEDEFS, ESTRUCTURAS, Y ENUMERACIONES
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES GLOBALES PUBLICAS
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES PRIVADAS DE ENLACE INTERNO
 ******************************************************************************/

static void instrucciones();

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


void instrucciones() {
	printf("\n***********Referencia***********\n");
	printf("*                              *\n");
	printf("* 0-7: Nro. de led a conmutar  *\n");
	printf("* t,T: Conmutar todos los leds *\n");
	printf("* c,C: Apagar todos los leds   *\n");
	printf("* s,S: Encender todos los leds *\n");
	printf("* q,Q: Salir                   *\n");
	printf("*                              *\n");
	printf("********************************\n");
}


int8_t input() {

	int16_t input;
	int8_t num = ERROR;

	instrucciones();

	while (num == ERROR) {
		switch (input = getchar()) {
		case 't':
		case 'T':
			num = TOGGLE;
			break;
		case 'c':
		case 'C':
			num = CLEAR;
			break;
		case 's':
		case 'S':
			num = SET;
			break;
		case 'q':
		case 'Q':
			num = QUIT;
			break;
		default:
			if (input >= '0' && input <= '7') {
					num = (input - '0');
			}
			else num = ERROR;
		}
		if (num != ERROR) ERRORCHECK;
		if (num == ERROR) {
			if (input != '\n') {
				while (getchar() != '\n');
			}
			printf("Valor invalido, ingrese nuevamente:\n");
			instrucciones();
			num = ERROR;
		}
	}
	return num;
}

/*******************************************************************************
 *******************************************************************************
                        DEFINICION DE FUNCIONES LOCALES
 *******************************************************************************
 ******************************************************************************/


 
