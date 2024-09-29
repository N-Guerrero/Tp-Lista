#include "pila.h"
#include "lista.h"

struct pila{
    Lista* lista;
};

Pila *pila_crear(){
    Pila* pila=malloc(sizeof(Pila));
    if(pila==NULL)
        return NULL;
    pila->lista=lista_crear();
    return pila;
}
void pila_destruir(Pila *pila){

    lista_destruir(pila->lista);
    free(pila);
}
void pila_destruir_todo(Pila *pila, void (*f)(void *)){

    lista_destruir_todo(pila->lista,f);
    free(pila);
}
size_t pila_cantidad(Pila *pila){
    return lista_cantidad_elementos(pila->lista);
}

void *pila_tope(Pila *pila){
    void* encontrado=NULL;
    if(lista_obtener_elemento(pila->lista,lista_cantidad_elementos(pila->lista),&encontrado))
        return encontrado;
    return NULL;
}
bool pila_apilar(Pila *pila, void *cosa){
    return lista_agregar_al_final(pila->lista,cosa);
}

void *pila_desapilar(Pila *pila){
    void* quitado=NULL;
    if(lista_quitar_elemento(pila->lista,pila_cantidad(pila),&quitado))
        return quitado;
    return NULL;
}
bool pila_esta_vacía(Pila *pila){
    if(pila_cantidad(pila)!=0)
        return false;
    return true;
}