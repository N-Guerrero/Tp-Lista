#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>



struct lista{
    size_t elementos_cant;
    void* primer_nodo;

};

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente_nodo;
}Nodo;

Lista *lista_crear(){
    Lista* lista = malloc(sizeof(Lista));
    if (lista==NULL)return NULL;
    lista->elementos_cant=0;
    lista->primer_nodo=NULL;

    return lista;
}

void lista_destruir(Lista *lista){
    lista->primer_nodo=NULL;
    lista->elementos_cant=0;
    free(lista);
}

size_t lista_cantidad_elementos(Lista *lista){
    if(lista->primer_nodo==NULL)return 0;
    else return lista->elementos_cant;
}
bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa){
    if (posicion>lista->elementos_cant)return false;
    if(lista->primer_nodo==NULL)return false;
    Nodo* aux1=lista->primer_nodo;
    
    if(posicion==1){
        Nodo* ptr_agregado=malloc(sizeof(Nodo));
        if (ptr_agregado==NULL)return false;
        ptr_agregado->elemento=cosa;
        ptr_agregado->siguiente_nodo=lista->primer_nodo;
        lista->primer_nodo=ptr_agregado;
        lista->elementos_cant++;
        return true;
    }

    for(size_t i=1;i<posicion;i++)
        aux1=aux1->siguiente_nodo;

    Nodo* Nuevo=malloc(sizeof(Nodo));
    Nuevo->elemento=cosa;
    Nuevo->siguiente_nodo=aux1->siguiente_nodo;
    aux1->siguiente_nodo=Nuevo;
    lista->elementos_cant++;
    return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa){
    Nodo* aux1=(Nodo*)lista->primer_nodo;
    while(aux1->siguiente_nodo!=NULL){
        aux1=aux1->siguiente_nodo;
    }
    Nodo* nuevo =malloc(sizeof(Nodo));
    if(nuevo==NULL)return false;
    nuevo->elemento=cosa;
    nuevo->siguiente_nodo=NULL;
    aux1->siguiente_nodo=nuevo;
    return true;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,void **elemento_quitado){
    if(lista->primer_nodo==NULL)return false;
    Nodo* anterior =lista->primer_nodo;
    if(posicion==1){
        lista->primer_nodo=anterior->siguiente_nodo;
        elemento_quitado=(void*)&anterior;
        return true;
    }
    for(size_t i=1;i<posicion;i++)
        anterior=anterior->siguiente_nodo;
    Nodo* quitado =anterior->siguiente_nodo;
    anterior->siguiente_nodo=quitado->siguiente_nodo;
    elemento_quitado=(void*)&quitado;

    return true;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,void **elemento_encontrado){

    if(posicion>lista->elementos_cant)return false;
    Nodo* aux=(Nodo*)lista->primer_nodo;
    for(size_t i=0;i<posicion;i++){
        aux=aux->siguiente_nodo;
    }
    if(aux==NULL)return false;

    elemento_encontrado=(void*)&aux;

        return true;
}