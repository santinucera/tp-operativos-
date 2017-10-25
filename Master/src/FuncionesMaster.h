#ifndef FUNCIONESMASTER_H_
#define FUNCIONESMASTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <Sockets.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <Configuracion.h>
#include <commons/string.h>
#include <Globales.h>
#include <Serializacion.h>
#include <pthread.h>
#include <commons/log.h>

#define mensajeArchivo 2
#define mensajeSolicitudTransformacion 4

typedef struct{
	void* scriptTransformacion;//FIXMe PUEDE CAMBIAR POR EL TEMA DE MMAP
	int bloque;
	int bytesOcupados;
	string archivoTemporal;
}procesarTransformacion;

/*----VARIABLES GLOBALES----*/
t_log* loggerMaster;
int socketYama;
/*--------------------------*/

typedef struct{
	char* ip;
	int port;
	int id;
} parametrosConexionMaster;

void conectarseConYama(char* ip, int port);

void* conectarseConWorkers(parametrosConexionMaster* parametros);

void enviarJobAYama(job* job);

void esperarInstruccionesDeYama();

char* recibirRuta(char* mensaje);

void enviarArchivo(int socketPrograma, char* rutaArchivo);
void enviarArchivoo(int socketPrograma, char* pathArchivo);

job* crearJob(char* argv[]);

//int dameUnID();

#endif /* FUNCIONESMASTER_H_ */
