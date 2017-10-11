/*
 * FuncionesYama.h
 *
 *  Created on: 24/9/2017
 *      Author: utnso
 */

#ifndef FUNCIONESYAMA_H_
#define FUNCIONESYAMA_H_

#include "Sockets.h"
#include "Configuracion.h"
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
#include <commons/log.h>
#include "Serializacion.h"
#include <Configuracion.h>
#include "Globales.h"
#include <commons/collections/list.h>
#include "Planificador.h"

#define idMaster 2
#define idDataNodes 3

fd_set master;   // conjunto maestro de descriptores de fichero
fd_set read_fds; // conjunto temporal de descriptores de fichero para select()
int fdmax;        // número máximo de descriptores de fichero
int servidor;     // descriptor de socket a la escucha
int nuevoMaster, socketFs;        // descriptor de socket de nueva conexión aceptada
char buf[256];    // buffer para datos del cliente
int nbytes;
int addrlen;
int i, j;
struct sockaddr_in direccionCliente;

t_log* logger;
struct configuracionYama config;

int conectarseConFs();
void levantarServidorYama(char* ip, int port);
void recibirContenidoMaster();
respuestaInfoNodos* solicitarInformacionAFS(solicitudInfoNodos* solicitud);

int getDisponibilidadBase();

char* obtenerNombreArchivoResultadoTemporal();
int esClock();

#endif /* FUNCIONESYAMA_H_ */
