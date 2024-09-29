#include "pila.h"
#include "lista.h"

struct pila {
	Lista *lista;
};

Pila *pila_crear()
{
	Pila *pila = malloc(sizeof(Pila));
	if (pila == NULL)
		return NULL;
	pila->lista = lista_crear();
	return pila;
}
void pila_destruir(Pila *pila)
{
	if (pila == NULL)
		return;
	lista_destruir(pila->lista);
	free(pila);
}
void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (pila == NULL)
		return;
	lista_destruir_todo(pila->lista, f);
	free(pila);
}
size_t pila_cantidad(Pila *pila)
{
	if (pila == NULL)
		return 0;
	return lista_cantidad_elementos(pila->lista);
}

void *pila_tope(Pila *pila)
{
	if (pila == NULL)
		return NULL;
	void *encontrado = NULL;
	if (lista_obtener_elemento(pila->lista, 0, &encontrado))
		return encontrado;
	return NULL;
}
bool pila_apilar(Pila *pila, void *cosa)
{
	if (pila == NULL)
		return false;
	return lista_agregar_elemento(pila->lista, 0, cosa);
}

void *pila_desapilar(Pila *pila)
{
	if (pila == NULL)
		return NULL;
	void *quitado = NULL;
	if (lista_quitar_elemento(pila->lista, 0, &quitado))
		return quitado;
	return NULL;
}
bool pila_esta_vacía(Pila *pila)
{
	if (pila == NULL)
		return true;
	if (pila_cantidad(pila) != 0)
		return false;
	return true;
}