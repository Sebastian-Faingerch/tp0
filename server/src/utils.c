#include"utils.h"

t_log* logger;

int iniciar_servidor(void)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	//assert(!"no implementado!");

	int socket_servidor;
	
	int err;

	struct addrinfo hints, *server_info, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, PUERTO, &hints, &server_info);

	// Creamos el socket de escucha del servidor

	int fd_escucha = socket(
		server_info->ai_family,
        server_info->ai_socktype,
        server_info->ai_protocol);

	// Asociamos el socket a un puerto

	err = bind(fd_escucha, server_info->ai_addr, server_info->ai_addrlen);


	// Escuchamos las conexiones entrantes

	err = listen(fd_escucha, SOMAXCONN);

	freeaddrinfo(server_info);
	log_trace(logger, "Listo para escuchar a mi cliente");

	return fd_escucha;
}

int esperar_cliente(int fd_escucha)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	int fd_conexion = accept(fd_escucha, NULL, NULL);

	// Aceptamos un nuevo cliente
	int socket_cliente;
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}

int recibir_operacion(int fd_conexion)
{
	size_t bytes;

	int32_t handshake;
	int32_t resultOk = 0;
	int32_t resultError = -1;

	bytes = recv(fd_conexion, &handshake, sizeof(int32_t), MSG_WAITALL);
	if (handshake == 1) {
		bytes = send(fd_conexion, &resultOk, sizeof(int32_t), 0);
	} else {
		bytes = send(fd_conexion, &resultError, sizeof(int32_t), 0);
}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
