#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct lista {
	size_t elementos_cant;
	struct nodo *primer_nodo;
};

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente_nodo;
} Nodo;
struct lista_iterador {
	Nodo *nodo_actual;
};

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	if (lista == NULL)
		return NULL;
	lista->elementos_cant = 0;
	lista->primer_nodo = NULL;

	return lista;
}

void lista_destruir(Lista *lista)
{
	if (lista == NULL)
		return;
	Nodo *siguiente = lista->primer_nodo;
	Nodo *destruido = siguiente;
	while (destruido != NULL) {
		siguiente = siguiente->siguiente_nodo;
		free(destruido);
		destruido = siguiente;
	}
	lista->elementos_cant = 0;
	free(lista);
	lista = NULL;
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (lista == NULL)
		return 0;
	if (lista->primer_nodo == NULL)
		return 0;
	else
		return lista->elementos_cant;
}
bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (lista == NULL)
		return false;
	if (posicion > lista->elementos_cant)
		return false;

	Nodo *aux1 = lista->primer_nodo;

	if (posicion == 0) {
		Nodo *ptr_agregado = malloc(sizeof(Nodo));
		if (ptr_agregado == NULL)
			return false;
		ptr_agregado->elemento = cosa;
		ptr_agregado->siguiente_nodo = lista->primer_nodo;
		lista->primer_nodo = ptr_agregado;
		lista->elementos_cant++;
		return true;
	}

	for (size_t i = 0; i < posicion - 1; i++)
		aux1 = aux1->siguiente_nodo;

	Nodo *Nuevo = malloc(sizeof(Nodo));
	if (Nuevo == NULL)
		return false;
	Nuevo->elemento = cosa;
	Nuevo->siguiente_nodo = aux1->siguiente_nodo;
	aux1->siguiente_nodo = Nuevo;
	lista->elementos_cant++;
	return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (lista == NULL)
		return false;
	Nodo *aux1 = lista->primer_nodo;
	Nodo *nuevo = malloc(sizeof(Nodo));
	if (nuevo == NULL)
		return false;
	nuevo->elemento = cosa;
	nuevo->siguiente_nodo = NULL;
	if (aux1 == NULL) { // primer caso, si no hay nodo al inicio
		lista->primer_nodo = nuevo;
		lista->elementos_cant++;
		return true;
	}
	while (aux1->siguiente_nodo != NULL) {
		aux1 = aux1->siguiente_nodo;
	}
	aux1->siguiente_nodo = nuevo;
	lista->elementos_cant++;
	return true;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (lista == NULL)
		return false;
	if (lista->primer_nodo == NULL)
		return false;
	Nodo *anterior = lista->primer_nodo;
	if (posicion == 0) {
		lista->primer_nodo = anterior->siguiente_nodo;
		*elemento_quitado = anterior->elemento;
		free(anterior);
		lista->elementos_cant--;
		return true;
	}
	for (size_t i = 0; i < posicion - 1; i++)
		anterior = anterior->siguiente_nodo;
	Nodo *quitado = anterior->siguiente_nodo;
	anterior->siguiente_nodo = quitado->siguiente_nodo;
	*elemento_quitado = quitado->elemento;
	free(quitado);
	lista->elementos_cant--;

	return true;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (lista == NULL)
		return false;
	if (posicion >= lista->elementos_cant)
		return false;
	if (elemento_encontrado == NULL)
		return true;
	if (posicion == 0) {
		*elemento_encontrado = lista->primer_nodo->elemento;
		return true;
	}
	if (lista->primer_nodo == NULL)
		return false;

	Nodo *aux = (Nodo *)lista->primer_nodo;
	for (size_t i = 0; i < posicion; i++) {
		aux = aux->siguiente_nodo;
	}
	if (aux == NULL)
		return false;
	*elemento_encontrado = aux->elemento;

	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (lista == NULL)
		return false;
	if (comparador == NULL) {
		return NULL;
	}
	Nodo *aux = lista->primer_nodo;
	while (aux != NULL) {
		if (comparador(buscado, aux->elemento) == 0)
			return aux->elemento;
		aux = aux->siguiente_nodo;
	}

	return NULL;
}
void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (lista == NULL)
		return;
	if (lista->primer_nodo == NULL)
		return;
	Nodo *siguiente = lista->primer_nodo;
	Nodo *destruido = siguiente;
	while (destruido != NULL) {
		siguiente = siguiente->siguiente_nodo;
		destructor(destruido->elemento);
		free(destruido);
		destruido = siguiente;
	}

	free(lista);
	lista = NULL;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (lista == NULL)
		return 0;
	size_t iteraciones = 0;
	Nodo *aux = lista->primer_nodo;
	while (aux != NULL) {
		if (aux->elemento == NULL)
			continue;
		bool funcion = f(aux->elemento, ctx);
		if (funcion == false) {
			iteraciones++;
			break;
		}
		iteraciones++;
		aux = aux->siguiente_nodo;
	}
	return iteraciones;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (lista == NULL)
		return NULL;
	Lista_iterador *iterador = malloc(sizeof(Lista_iterador));
	if (iterador == NULL)
		return NULL;
	iterador->nodo_actual = lista->primer_nodo;

	return iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return false;
	if (iterador->nodo_actual == NULL) {
		return false;
	} else
		return true;
}

void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	if (iterador->nodo_actual != NULL)
		iterador->nodo_actual = iterador->nodo_actual->siguiente_nodo;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return NULL;
	if (iterador->nodo_actual == NULL)
		return NULL;
	if (iterador->nodo_actual->elemento != NULL)
		return iterador->nodo_actual->elemento;
	return NULL;
}

void lista_iterador_destruir(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	free(iterador);
	iterador = NULL;
}