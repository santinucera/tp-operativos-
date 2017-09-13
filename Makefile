OBJ := dataNode.o master.o filesystem.o worker.o yama.o

# CURRENT_DIR := $(shell pwd)
DIR := ${CURDIR}

H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')

HEADERS := -I"$(DIR)/commons_lib/commons" -I"/usr/include" -I"$(DIR)/BibliotecasCompartidas" -I"$(DIR)/commons_lib/commons/collections" -I"$(DIR)/YAMA" -I"$(DIR)/DataNode" -I"$(DIR)/Worker" -I"$(DIR)/Master" -I"$(DIR)/FileSystem"          # Cualquier cosa aca hay un ejemplo http://www.network-theory.co.uk/docs/gccintro/gccintro_22.html
LIBPATH := -L"$(DIR)/BibliotecasCompartidas/Debug"
LIBS := -lcommons -lpthread -lreadline -lm -lBibliotecasCompartidas

CC := gcc -w -g
CFLAGS := -std=c11 $(HEADERS)



#$(BIN): $(OBJ)
#$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
# letra i mayuscula -I<Directory> sirve para los header files
# -L<Directory> directorio de las bibliotecas
# letra ele minuscula -l<nombredelarchivo> sin el .c al final



# -------------------------------------------------------------------------------------------------------------------------------------



# All

all: clean datanode master worker yama fileSystem



# -------------------------------------------------------------------------------------------------------------------------------------

# datanode

datanode: dataNode.o funcionesDN.o
	$(CC) $(LIBPATH) dataNode.o funcionesDN.o -o datanode $(LIBS)


dataNode.o:
	$(CC) $(CFLAGS) -c $(DIR)/DataNode/src/DataNode.c -o dataNode.o

funcionesDN.o:
	$(CC) $(CFLAGS) -c $(DIR)/DataNode/src/FuncionesDN.c -o funcionesDN.o




# Master

master: master.o funcionesMaster.o
	$(CC) $(LIBPATH) master.o funcionesMaster.o -o master $(LIBS)

funcionesMaster.o:
	$(CC) $(CFLAGS) -c $(DIR)/Master/src/FuncionesMaster.c -o funcionesMaster.o

master.o:
	$(CC) $(CFLAGS) -c $(DIR)/Master/src/Master.c -o master.o





# Worker


worker: worker.o
	$(CC) $(LIBPATH) worker.o -o worker $(LIBS)


worker.o:
	$(CC) -c $(CFLAGS) $(DIR)/Worker/src/Worker.c -o worker.o




# FileSystem

funcionesFS.o:
	$(CC) $(CFLAGS) -c $(DIR)/FileSystem/src/FuncionesFS.c -o funcionesFS.o

comandos.o:
	$(CC) $(CFLAGS) -c $(DIR)/FileSystem/src/Comandos.c -o comandos.o

fileSystem: fileSystem.o comandos.o funcionesFS.o
	$(CC) $(LIBPATH) fileSystem.o comandos.o funcionesFS.o -o fileSystem $(LIBS)


fileSystem.o:
	$(CC) $(CFLAGS) -c $(CFLAGS) $(DIR)/FileSystem/src/FileSystem.c -o fileSystem.o





# yama

yama: yama.o
	$(CC) $(LIBPATH) yama.o -o yama $(LIBS)


yama.o:
	$(CC) -c $(CFLAGS) $(DIR)/YAMA/src/YAMA.c -o yama.o




# -------------------------------------------------------------------------------------------------------------------------------------



# Libraries


libclean:
	$(MAKE) uninstall -C $(DIR)/commons_lib/so-commons-library
	$(MAKE) clean -C $(DIR)/commons_lib/so-commons-library


lib:
	$(MAKE) -C $(DIR)/commons_lib/so-commons-library
	$(MAKE) install -C $(DIR)/commons_lib/so-commons-library

# -------------------------------------------------------------------------------------------------------------------------------------

# Clean

clean:
	rm -f yama worker datanode master fileSystem *.o