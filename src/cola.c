#include "cola.h"
#include "lista.h"

struct cola {
	Lista *lista;
};

Cola *cola_crear()
{
	Cola *cola = malloc(sizeof(Cola));
	if (cola == NULL)
		return NULL;
	cola->lista = lista_crear();

	return cola;
}
void cola_destruir(Cola *cola)
{
	if (cola == NULL)
		return;
	lista_destruir(cola->lista);

	free(cola);
}

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	if (cola == NULL)
		return;
	lista_destruir_todo(cola->lista, f);

	free(cola);
}
size_t cola_cantidad(Cola *cola)
{
	return lista_cantidad_elementos(cola->lista);
}
void *cola_frente(Cola *cola)
{
	if (cola == NULL)
		return NULL;
	void *encontrado = NULL;
	if (lista_obtener_elemento(cola->lista, 0, &encontrado))
		return encontrado;
	return NULL;
}
bool cola_encolar(Cola *cola, void *cosa)
{
	if (cola == NULL)
		return false;
	if (lista_agregar_al_final(cola->lista, cosa))
		return true;
	return false;
}
void *cola_desencolar(Cola *cola)
{
	if (cola == NULL)
		return NULL;
	void *quitado = NULL;
	if (lista_quitar_elemento(cola->lista, 0, &quitado))
		return quitado;
	return NULL;
}
bool cola_esta_vacía(Cola *cola)
{
	if (cola == NULL)
		return true;
	if (lista_cantidad_elementos(cola->lista) != 0)
		return false;
	return true;
}