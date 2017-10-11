/*
 * FuncionesHilosFs.c
 *
 *  Created on: 11/10/2017
 *      Author: utnso
 */

#include "FuncionesHilosFs.h"

int clienteYama;

void* levantarServidorFS(void* parametrosServidorFS){

	int maxDatanodes;
	int nuevoDataNode;
	int cantidadNodos;
	informacionNodo info;
	respuesta solicitudInfoArchivo;
	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion = sizeof(direccionCliente);

	int i = 0, j = 0;
	int addrlen;

	struct parametrosServidorHilo*params;
	params = (struct parametrosServidorHilo*) parametrosServidorFS;

	int servidor = params->servidor;

	fd_set datanodes;
	fd_set read_fds_datanodes;

	respuesta conexionNueva, paqueteInfoNodo;
	int bufferPrueba = 2;
	FD_ZERO(&datanodes);    // borra los conjuntos datanodes y temporal
	FD_ZERO(&read_fds_datanodes);
	// añadir listener al conjunto maestro
	FD_SET(servidor, &datanodes);
	// seguir la pista del descriptor de fichero mayor
	maxDatanodes = servidor; // por ahora es éste
	// bucle principal
	while(1){
		read_fds_datanodes = datanodes; // cópialo
		if (select(maxDatanodes+1, &read_fds_datanodes, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(1);
		}
		// explorar conexiones existentes en busca de datos que leer
		for(i = 0; i <= maxDatanodes; i++) {
			if (FD_ISSET(i, &read_fds_datanodes)) { // ¡¡tenemos datos!!
				if (i == servidor) {
					// gestionar nuevas conexiones
					addrlen = sizeof(direccionCliente);
					if ((nuevoDataNode = accept(servidor, (struct sockaddr *)&direccionCliente,
							&addrlen)) == -1) {
						perror("accept");
					} else {
						FD_SET(nuevoDataNode, &datanodes); // añadir al conjunto maestro
						if (nuevoDataNode > maxDatanodes) {    // actualizar el máximo
							maxDatanodes = nuevoDataNode;
						}
						conexionNueva = desempaquetar(nuevoDataNode);
						int idRecibido = *(int*)conexionNueva.envio;

						if (idRecibido == idDataNodes){
							//empaquetar(nuevoDataNode,1,0,&bufferPrueba);//FIXME:SOLO A MODO DE PRUEBA
							paqueteInfoNodo = desempaquetar(nuevoDataNode);
							info = *(informacionNodo*)paqueteInfoNodo.envio;
							if (nodoRepetido(info) == 0){
								log_trace(loggerFS, "Conexion de DataNode %d\n", info.numeroNodo);
								info.bloquesOcupados = info.sizeNodo - levantarBitmapNodo(info.numeroNodo, info.sizeNodo);
								info.socket = nuevoDataNode;
								memcpy(paqueteInfoNodo.envio, &info, sizeof(informacionNodo));
								list_add(nodosConectados,paqueteInfoNodo.envio);
								cantidadNodos = list_size(nodosConectados);
								actualizarArchivoNodos();
							}
							else
								log_trace(loggerFS, "DataNode repetido\n");
						}
						else {
							// gestionar datos de un cliente

						}
					}
				}
			}
		}
	}
	return 0;

}

void* consolaFS(){

	int sizeComando = 256;

	while (1) {
		printf("Introduzca comando: ");
		char* comando = malloc(sizeof(char) * sizeComando);
		bzero(comando, sizeComando);
		comando = readline(">");
		if (comando)
			add_history(comando);

		log_trace(loggerFS, "El usuario ingreso: %s", comando);

		if (string_starts_with(comando, "format")) {
			log_trace(loggerFS, "File system formateado");
		}
		else if (string_starts_with(comando, "rm -d")) {
			if (eliminarDirectorio(comando) == 0)
				log_trace(loggerFS, "Directorio eliminado");
			else
				log_error(loggerFS, "No se pudo eliminar el directorio");
		}
		else if (string_starts_with(comando, "rm -b")) {
			log_trace(loggerFS, "Bloque eliminado");
		}
		else if (string_starts_with(comando, "rm")) {
			if (eliminarArchivo(comando) == 0)
				log_trace(loggerFS, "archivo eliminado");
			else
				log_error(loggerFS, "No se pudo eliminar el archivo");
		}
		else if (string_starts_with(comando, "rename")) {
			if (cambiarNombre(comando) == 0)
				log_trace(loggerFS, "Renombrado");
			else
				log_error(loggerFS, "No se pudo renombrar");

		}
		else if (string_starts_with(comando, "mv")) {
			if (mover(comando) == 0)
				log_trace(loggerFS, "Archivo movido");
			else
				log_error(loggerFS, "No se pudo mover el archivo");
		}
		else if (string_starts_with(comando, "cat")) {
			if (mostrarArchivo(comando) == 0){
			log_trace(loggerFS, "Archivo mostrado");
			}else{
				log_error(loggerFS, "No se pudo mostrar el archivo");
			}
		}
		else if (string_starts_with(comando, "mkdir")) {
			if (crearDirectorio(comando) == 0){

			log_trace(loggerFS, "Directorio creado");// avisar si ya existe
			}else{
				if (crearDirectorio(comando) == 1){
					log_error(loggerFS, "El directorio ya existe");
				}else{
					log_error(loggerFS, "No se pudo crear el directorio");
				}
			}
		}
		else if (string_starts_with(comando, "cpfrom")) {
			if (copiarArchivo(comando) == 1)
				log_trace(loggerFS, "Archivo copiado a yamafs");
			else
				log_error(loggerFS, "No se pudo copiar el archivo");
		}
		else if (string_starts_with(comando, "cpto")) {
			log_trace(loggerFS, "Archivo copiado desde yamafs");
		}
		else if (string_starts_with(comando, "cpblock")) {
			log_trace(loggerFS, "Bloque copiado en el nodo");
		}
		else if (string_starts_with(comando, "md5")) {
			if (generarArchivoMD5(comando) == 0)
				log_trace(loggerFS, "MD5 del archivo");
			else
				log_error(loggerFS, "No se pudo obtener el MD5 del archivo");

		}
		else if (string_starts_with(comando, "ls")) {
			if (listarArchivos(comando) == 0)
				log_trace(loggerFS, "Archivos listados");
			else
				log_error(loggerFS, "El directorio no existe");

		}
		else if (string_starts_with(comando, "info")) {
			if (informacion(comando) == 0)
				log_trace(loggerFS, "Mostrando informacion del archivo");
			else
				log_error(loggerFS, "No se pudo mostrar informacion del archivo");
		}
		else {
			printf("Comando invalido\n");
			log_error(loggerFS, "Comando invalido");
		}
		free(comando);
	}
	return 0;
}

void* manejarConexionYama(){
	respuesta respuestaYama;

	while(1){
		respuestaYama = desempaquetar(clienteYama);

		switch(respuestaYama.idMensaje){
			case mensajeSolicitudInfoNodos:
				solicitudInfoNodos* solicitud = (solicitudInfoNodos*)respuestaYama.envio;
				break;
		}
	}
}
