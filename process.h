/***************************************************************************//**
	Ejercicio
	process.h
	Jun 7, 2025

	Descripcion:

	Header correspondiente a process.c,
	Contiene el prototipo de la funcion process.

	-process: Recibe un numero "select" el cual puede representar un pin especifico o una accion que se realiza sobre todos
	los pines. Se verifica el valor de "select":
	si es una accion, entra en un loop for y modifica todos los pines.
	si es un pin especifico cambia su estado.
	Recibe un puntero a funcion void correspondiente a pinSet, otro puntero a funcion uint (pinRead)
	tambien recibe la seleccion de input, el arreglo de leds y el tamanio de este, al igual
	que los valores de on y off

 ******************************************************************************/

#ifndef PROCESS_H
#define PROCESS_H

/*******************************************************************************
 * INCLUSION DE HEADERS
 ******************************************************************************/



/*******************************************************************************
 * MACROS Y DEFINICIONES DE PREPROCESADOR
 ******************************************************************************/



/*******************************************************************************
 * TYPEDEFS, ESTRUCTURAS Y ENUMERACIONES
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE VARIABLES GLOBALES PUBLICAS
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES PUBLICAS
 ******************************************************************************/

void process (void (*pS)(char*, char*), uint8_t (*pR)(char*), int8_t select, char* pines [], uint8_t max, char* on, char* off);

/*******************************************************************************
 ******************************************************************************/

#endif // PROCESS_H
