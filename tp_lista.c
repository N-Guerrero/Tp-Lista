#include "src/csv.h"
#include "src/lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};
bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}
bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;
	return strcmp(p1->nombre, p2->nombre);
}
void liberar_pokemon(void *pokemon)
{
	struct pokemon *liberado = pokemon;
	if (liberado != NULL) {
		// free(liberado->nombre);
		free(liberado);
		liberado = NULL;
	}
}
void agregar_pokemon_desde_archivo(Lista *pokedex, struct archivo_csv *archivo)
{
	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };

	int fuerza;
	int resistencia;
	int destreza;
	char tipo;
	char *nombre = NULL;
	void *punteros[5] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };

	while (leer_linea_csv(archivo, 5, funciones, punteros) == 5) {
		struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
		nuevo_pokemon->nombre = nombre;
		nuevo_pokemon->fuerza = fuerza;
		nuevo_pokemon->destreza = destreza;
		nuevo_pokemon->tipo = tipo;
		nuevo_pokemon->resistencia = resistencia;

		lista_agregar_al_final(pokedex, nuevo_pokemon);

		free(nombre);
	}
	cerrar_archivo_csv(archivo);
}
void mostrar_pokemon(struct pokemon *pokemon)
{
	printf("Nombre: %s\nTipo: %c\nFuerza:%d\nDestreza:%d\nResistencia:%d\n",
	       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->resistencia);
}

int main(int argc, char *argv[])
{
	// recibir un archivo por linea de comandos
	// abrir el archivo csv y parsear pokemones
	// agregar los pokemones a una lista
	//
	// El usuario puede elegir una de dos opciones
	//
	// 1. Ingrear por teclado un nombre y el programa busca el pokemon en la lista
	// 2. Listar todos los pokemones de la pokedex
	//
	//

	char *nombre_file = "pokedex.csv";
	char separador = ';';
	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], argv[2][0]);

	Lista *pokedex = lista_crear();

	if (archivo != NULL)

		agregar_pokemon_desde_archivo(pokedex, archivo);

	// menu

	int opcion = -1;
	do {
		printf("Pokedex iniciada.\nQue desea hacer?\n");
		printf("1.Buscar pokemon en la pokedex\n2.Listar pokemones capturados\n");
		printf("0.salir\n");
		if (scanf("%d", &opcion) != 1)
			printf("opcion invalida\n");
		if (opcion == 1) {
			printf("que pokemon desea buscar?\n");
			char pokemon_buscado[100];
			scanf("%99s", pokemon_buscado);
			struct pokemon buscado = { .nombre = pokemon_buscado };

			struct pokemon *encontrado = lista_buscar_elemento(
				pokedex, &buscado, comparar_nombre_pokemon);

			if (encontrado != NULL) {
				printf("Se encontro al pokemon buscado!!\n");
				mostrar_pokemon(encontrado);
			} else {
				printf("pokemon no encontrado\n");
			}

			opcion = 0;
		}
		if (opcion == 2) {
			for (size_t i = 1; // O(1)
			     i <= lista_cantidad_elementos(pokedex); // O(1)
			     i++) { // O(1)
				struct pokemon *p = NULL;

				if (lista_obtener_elemento(
					    pokedex, i, (void **)&p)) { // O(n)
					mostrar_pokemon(p);

					printf("-----------------------\n");
				}
			}
			opcion = 0;
		}
	} while (opcion != 0);

	lista_destruir_todo(pokedex, liberar_pokemon);
	return 0;
}
