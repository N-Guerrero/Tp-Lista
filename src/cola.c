#include "cola.h"
#include  "lista.h"

struct cola {
    Lista* lista;
    
};

Cola *cola_crear(){
    Cola* cola=malloc(sizeof(Cola));
    if (cola==NULL)
        return NULL;
    cola->lista=lista_crear();
    

    return cola;
}
void cola_destruir(Cola *cola){

    lista_destruir(cola->lista);
    
    free(cola);
}

void cola_destruir_todo(Cola *cola, void (*f)(void *)){
    lista_destruir_todo(cola->lista,f);

    free(cola);
}
size_t cola_cantidad(Cola *cola){
    return lista_cantidad_elementos(cola->lista);
}
void *cola_frente(Cola *cola){
    void* encontrado=NULL;
    if(lista_obtener_elemento(cola->lista,1,&encontrado))
        return encontrado;
    return NULL;
}
bool cola_encolar(Cola *cola, void *cosa){
    if(lista_agregar_elemento(cola->lista,1,cosa))
        return true;
    return false;
}
void *cola_desencolar(Cola *cola){
    void* quitado=NULL;
    if(lista_quitar_elemento(cola->lista,lista_cantidad_elementos(cola->lista),&quitado))
        return quitado;
    return NULL;
}
bool cola_esta_vacía(Cola *cola){
    if(lista_cantidad_elementos(cola->lista)!=0)
        return false;
    return true;
}