/*
 ============================================================================
 Name        : DataNode.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <Sockets.h>
#include <Configuracion.h>
#include <Configuracion.c>

struct configuracionNodo  config;

int main(void) {
	cargarConfiguracionNodo(&config);
	puts("!!!Hello World!!!");
	return EXIT_SUCCESS;
}
