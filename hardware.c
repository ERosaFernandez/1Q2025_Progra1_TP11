/***************************************************************************//**
	Ejercicio
	hardware.c
	Jun 4, 2025
	
	Descripcion:

	Contiene las funciones de inicializacion,
	direccionamiento, accionamiento y lectura.
	Cuenta con muchas otras funciones internas encargadas
	de verificacion de errores, export y unexport, como
	tambien otras funciones demas:

	-strComp: Compara 2 strings empleando recursividad. recibe 2 punteros a strings a comparar
	Devuelve un 1 si resultan iguales, sino un 0.

	-pinCheck: Verifica que el pin ingresado sea correcto. recibe 1 puntero a string; el pin a evaluar.

	-valueCheck: Verifica que el valor ingresado sea on u off. recibe 1 puntero a string; el valor a evaluar.

	-directCheck: Verifica que el valor ingresado sea in u out. recibe 1 puntero a string; la direccion a evaluar.

	-pinExport: "Pide prestado" al sistema el pin a utilizar. recibe 1 puntero a string; el pin a exportar.

	-pinUnexport: "Devuelve" al sistema el pin que se uso. recibe 1 puntero a string; el pin a "devolver"

	-abortar: En caso de un error, llama a esta funcion para finalizar todos los archivos y cerrar el programa.

	-tryAndRetry: Funcion que repite el proceso de abrir, operar y cerrar archivo para cada etapa hasta que funcione
	o supere la tolerancia de veces que recibe un error. Recibe 6 punteros a strings referenciando el
	path a acceder, el valor a escribir (o "" si se desea leer el path) y los 3 mensajes de error segun cada etapa.
	Devuelve un entero entre -1, 0 y 1:
	Si esta en modo escritura, devuelve un 0 si se hizo todo bien, y un -1 si hubo un error.
	Si esta en modo lectura, devuelve el valor de lectura o un -1 si hubo un error.



 ******************************************************************************/

/*******************************************************************************
 * INCLUSION DE HEADERS
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "hardware.h"


/*******************************************************************************
 * MACROS Y DEFINICIONES DE PREPROCESADOR
 ******************************************************************************/

#define MAXRETRY 5

/*******************************************************************************
 * TYPEDEFS, ESTRUCTURAS, Y ENUMERACIONES
 ******************************************************************************/

typedef uint8_t BOOL;

/*******************************************************************************
 * VARIABLES GLOBALES PUBLICAS
 ******************************************************************************/



/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES PRIVADAS DE ENLACE INTERNO
 ******************************************************************************/

static BOOL strComp (char* s1, char* s2);
static void pinCheck (char* pin);
static void valueCheck (char* valor);
static void directCheck (char* direccion);
static void pinExport (char* pin);
static void pinUnexport (char* pin);
static void abortar ();
static int8_t tryAndRetry(char* path, char* sPut, char* error1, char* error2, char* error3);

/*******************************************************************************
 * VARIABLES GLOBALES CONSTANTES ESTATICAS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES GLOBALES ESTATICAS
 ******************************************************************************/

static char* pines [] = {GPIO17, GPIO4, GPIO18, GPIO23, GPIO24, GPIO25, GPIO22, GPIO27};
/*
 * Arreglo global estatico que representa todos los pines disponibles.
 * Funciona para las funciones que hacen chequeos. A medida
 * que se habiliten mas GPIOs a emplear, mas grande sera este arreglo
 */

/*******************************************************************************
 *******************************************************************************
                        DEFINICION DE FUNCIONES GLOBALES
 *******************************************************************************
 ******************************************************************************/


void pinMode (char* pin, char* direccion){
	pinCheck (pin);
	directCheck(direccion);
	pinExport (pin);

	char path [40] = {0};
	sprintf(path,"/sys/class/gpio/gpio%s/direction",pin);

	char error1 [] = "Error de acceso al direccionamiento pin nn";
	sprintf(error1 + (sizeof(error1)-3),"%s", pin);

	char error2 [] = "Error de direccionamiento del pin nn";
	sprintf(error2 + (sizeof(error2)-3),"%s", pin);

	char error3 [] = "Error de cierre del direccionamiento del pin nn";
	sprintf(error3 + (sizeof(error3)-3),"%s", pin);

	tryAndRetry (path, direccion, error1, error2, error3);
}


void pinSet (char* pin, char* valor){
	valueCheck (valor);
	pinCheck (pin);

	char path [30] = {0};
	sprintf(path,"/sys/class/gpio/gpio%s/value",pin);

	char error1 [] = "Error de acceso al valor del pin nn";
	sprintf(error1 + (sizeof(error1)-3),"%s", pin);

	char error2 [] = "Error de escritura al valor del pin nn";
	sprintf(error2 + (sizeof(error2)-3),"%s", pin);

	char error3 [] = "Error de cierre del finalizador del pin nn";
	sprintf(error3 + (sizeof(error3)-3),"%s", pin);

	tryAndRetry (path, valor, error1, error2, error3);

}


uint8_t pinRead (char* pin){
	int8_t valor = 0;
	pinCheck (pin);

	char path [30] = {0};
	sprintf(path,"/sys/class/gpio/gpio%s/value",pin);

	char error1 [] = "Error de acceso al estado del pin nn";
	sprintf(error1 + (sizeof(error1)-3),"%s", pin);

	char error2 [] = "Error de lectura del pin nn";
	sprintf(error2 + (sizeof(error2)-3),"%s", pin);

	char error3 [] = "Error de cierre del valor del pin nn";
	sprintf(error3 + (sizeof(error3)-3),"%s", pin);

	valor = tryAndRetry (path, "", error1, error2, error3);
	if (valor == -1){
		abortar();
	}

	return ( ((uint8_t) valor) - '0');
}


void finishAll(char* pines [],uint8_t max){
	uint8_t i;
	FILE* pointer;
	char path [40] = {0};

	for (i = 0; i < max; i++){
		sprintf(path,"/sys/class/gpio/gpio%s/direction",pines[i]);
		if ((pointer = fopen (path, "r")) != NULL){
			fclose (pointer);
			pinUnexport (pines[i]);
		}
	}
}


void startAll(char* pines [], uint8_t max, char* modo){
	uint8_t i;
	for (i = 0 ; i < max;i++){
		pinMode (pines [i], modo);
	}
}


/*******************************************************************************
 *******************************************************************************
                        DEFINICION DE FUNCIONES LOCALES
 *******************************************************************************
 ******************************************************************************/


BOOL strComp (char* s1, char* s2){
	if (*s1 != *s2) return 0;
	else if (!(*s1) && !(*s2)) return 1;
	else return strComp (s1+1, s2+1);
}


void pinCheck (char* pin){
	uint8_t i;
	BOOL listo;

	for (i= 0, listo = 0; i < MAXPINES && listo == 0; i++){
		listo = strComp (pin, pines[i]);
	}
	if (!listo){
		printf ("Error de parametro de Pin\n");
		abortar();
	}
}


void valueCheck (char* valor){
	if (!strComp (valor, ON) && !strComp (valor,OFF)){
		printf ("Error de parametro de valor\n");
		abortar();
	}
}


void directCheck (char* direccion){
	if (!strComp (direccion, INPUT) && !strComp (direccion,OUTPUT)){
		printf ("Error de parametro de direccion\n");
		abortar();
	}
}


void pinExport (char* pin){
	char path[] = "/sys/class/gpio/export";

	char error1 [] = "Error de acceso al inicializador del pin nn";
	sprintf(error1 + (sizeof(error1)-3),"%s", pin);

	char error2 [] = "Error de inicializacion del pin nn";
	sprintf(error2 + (sizeof(error2)-3),"%s", pin);

	char error3 [] = "Error de cierre del inicializador del pin nn";
	sprintf(error3 + (sizeof(error3)-3),"%s", pin);

	tryAndRetry (path, pin, error1, error2, error3);

}


void pinUnexport (char* pin){


	char path[] = "/sys/class/gpio/unexport";

	char error1 [] = "Error de acceso a la finalizacion del pin nn";
	sprintf(error1 + (sizeof(error1)-3),"%s", pin);

	char error2 [] = "Error de finalizacion del pin nn";
	sprintf(error2 + (sizeof(error2)-3),"%s", pin);

	char error3 [] = "Error de cierre del finalizador del pin nn";
	sprintf(error3 + (sizeof(error3)-3),"%s", pin);

	tryAndRetry (path, pin, error1, error2, error3);

}


int8_t tryAndRetry(char* path, char* sPut, char* error1, char* error2, char* error3){
	FILE* pointer;
	uint8_t retry;
	uint8_t flag;
	int8_t valor = 0;
	uint8_t lectura=0;

	if (strComp (sPut, "") == 1) lectura = 1;

	for (pointer = fopen (path, lectura? "r" : "w"), retry = 0; pointer == NULL && retry < (MAXRETRY? MAXRETRY : 1); retry++);

	if (pointer == NULL) printf("%s\n", error1);
	else {
		if (!lectura){
			for (retry = 0; (flag = fputs (sPut, pointer)) == EOF && retry < (MAXRETRY? MAXRETRY : 1); retry++);
		}
		else{
			for (retry = 0; (valor = fgetc (pointer)) == EOF && retry < (MAXRETRY? MAXRETRY : 1); retry++);
		}
		if (valor == EOF || flag == EOF) {
			printf("%s\n", error2);
			valor = -1;
		}
		else{

			for (retry = 0; (flag = fclose (pointer)) == EOF && retry < (MAXRETRY? MAXRETRY : 1); retry++);

			if (flag == EOF) printf("%s\n", error3);
		}
	}
	return valor;
}


void abortar (){

	finishAll(pines, MAXPINES);
	exit(1);

}

