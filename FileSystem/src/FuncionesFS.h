/*
 * FuncionesFS.h
 *
 *  Created on: 11/9/2017
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <commons/log.h>
#include "Globales.h"
#include <commons/collections/list.h>
#include <semaphore.h>
#include <pthread.h>
#include "Comandos.h"
#include <math.h>

#define idDataNodes 3
#define cantDataNodes 10
#define mb 1048576

extern int numeroCopiasBloque;
t_directory tablaDeDirectorios[100];
extern char* rutaArchivos;
extern t_log* loggerFS;
extern int cantidadDirectorios;
extern int cantBloques;
extern int sizeTotalNodos, nodosLibres;
extern t_list* bitmapsNodos;;
extern t_list* nodosConectados;
extern char* rutaBitmaps;

int validarArchivoYamaFS(char* ruta);

void inicializarTablaDirectorios();

char* rutaSinPrefijoYama(char* ruta);

int bytesACortar(char* mapa);

void* leerDeDataNode(void* parametros);

void guardarTablaDirectorios();

char* buscarRutaArchivo(char* ruta);

int getIndexDirectorio(char* ruta);

char* generarArrayNodos();

int levantarBitmapNodo(int numeroNodo, int sizeNodo);

int buscarPrimerBloqueLibre(int numeroNodo, int sizeNodo);

void actualizarArchivoNodos();

int nodoRepetido(informacionNodo info);

void atenderSolicitudYama(int socketYama, void* envio);

char* generarArrayBloque(int numeroNodo, int numeroBloque);

void guardarEnNodos(char* path, char* nombre, char* tipo, string* mapeoArchivo);

void setearBloqueOcupadoEnBitmap(int numeroNodo, int bloqueLibre);

void setearBloqueLibreEnBitmap(int numeroNodo, int bloqueOcupado);

void actualizarBitmapNodos();

void* enviarADataNode(void* parametros);

informacionNodo* informacionNodosConectados();

void establecerServidor();

int recibirConexionYama();

informacionArchivoFsYama obtenerInfoArchivo(string rutaDatos);

void obtenerInfoNodo(ubicacionBloque* ubicacion);

char* leerArchivo(char* rutaArchivo);

char* rutaSinArchivo(char* rutaArchivo);

char* ultimaParteDeRuta(char* rutaArchivo);
