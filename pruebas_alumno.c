#include "pa2m.h"
#include "src/lista.h"
#include <string.h>
struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};
int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;
	printf("buscado %s comparando %s\n", p1->nombre, p2->nombre);
	return strcmp(p1->nombre, p2->nombre);
}

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}
bool mostrar_pokemon(void *poke, void *ctx)
{
	printf("puntero de pokemon %p\n", poke);
	return true;
}

void probar_destruir_lista(Lista *lista)
{
	lista_destruir(lista);
	// printf("%p\n",(void*)lista);
	// pa2m_afirmar(lista==NULL,"no existe la lista");
}

void probar_agregar_alfinal(Lista *lista, void *cosa)
{
	printf("%p\n", cosa);
	pa2m_afirmar(lista_agregar_al_final(lista, cosa),
		     "se agrego %p al final\n", cosa);
	printf("cant elem %zu\n", lista_cantidad_elementos(lista));
}
void probar_iterar(Lista *lista)
{
	size_t iterados = lista_iterar_elementos(lista, mostrar_pokemon, NULL);
	pa2m_afirmar(iterados == lista_cantidad_elementos(lista),
		     "pokemons iterados correctamente");
}

void probar_obtener(Lista *lista)
{
	struct pokemon *p;
	lista_obtener_elemento(lista, 2, (void **)&p);
	printf("elemento encontrado %p\n", (void *)p);
	printf("nombre del pokemon 2 = %s\n", (p)->nombre);
	pa2m_afirmar(strcmp(p->nombre, "pichu") == 0, "pichu encontrado");
}
void probar_agregar_en_pos(Lista *lista, void *cosa)
{
	printf("%p\n", cosa);
	size_t pos = 2;
	pa2m_afirmar(lista_agregar_elemento(lista, pos, cosa),
		     "se agrego %p en %zu\n", cosa, pos);
	printf("cant elem %zu\n", lista_cantidad_elementos(lista));
}
void probar_eliminar(Lista *lista)
{
	struct pokemon *p;
	bool se_quito = lista_quitar_elemento(lista, 2, (void **)&p);
	pa2m_afirmar(se_quito, "se quito a %s\n", p->nombre);
}
void probar_buscar(Lista *lista)
{
	struct pokemon buscado = { .nombre = "luxray" };
	// struct pokemon* buscado=malloc(sizeof(struct pokemon));
	// buscado->nombre="luxray";
	struct pokemon *encontrado =
		lista_buscar_elemento(lista, &buscado, comparar_nombre_pokemon);
	printf("encontrado p %p\n", (void *)encontrado);
	pa2m_afirmar(strcmp(encontrado->nombre, "luxray") == 0,
		     "pokemon encontrado");
	// free(buscado);
}
int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	// prueba_simple();
	struct pokemon pokemon = { .destreza = 100,
				   .fuerza = 5,
				   .resistencia = 3,
				   .tipo = 'E',
				   .nombre = "luxray" };
	struct pokemon pokemon2 = { .destreza = 10,
				    .fuerza = 5,
				    .resistencia = 3,
				    .tipo = 'E',
				    .nombre = "pichu" };
	struct pokemon pokemon3 = { .destreza = 13,
				    .fuerza = 6,
				    .resistencia = 7,
				    .tipo = 'F',
				    .nombre = "Moltres" };

	struct pokemon pokemon4 = { .destreza = 22,
				    .fuerza = 84,
				    .resistencia = 80,
				    .tipo = 'A',
				    .nombre = "Blastoise" };

	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "existe la lista");

	probar_agregar_alfinal(lista, &pokemon);
	probar_agregar_alfinal(lista, &pokemon2);
	probar_agregar_alfinal(lista, &pokemon3);

	// probar_iterar(lista);

	probar_obtener(lista);

	probar_agregar_en_pos(lista, &pokemon4);
	// printf("--------\n");
	// probar_iterar(lista);
	probar_eliminar(lista);
	// probar_obtener(lista);
	for (size_t i = 1; // O(1)
	     i <= lista_cantidad_elementos(lista); // O(1)
	     i++) {
		struct pokemon *p;
		lista_obtener_elemento(lista, i, (void **)&p);
		printf("%s\n", p->nombre);
	}
	probar_buscar(lista);

	probar_destruir_lista(lista);

	return pa2m_mostrar_reporte();
}
