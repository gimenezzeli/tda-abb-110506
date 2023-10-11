#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

nodo_abb_t *crear_nodo(void *elemento){
	nodo_abb_t *nodo_nuevo = malloc(sizeof(nodo_abb_t));

	if(!nodo_nuevo){
		free(nodo_nuevo);
		return NULL;
	}

	nodo_nuevo->izquierda = NULL;
	nodo_nuevo->derecha = NULL;
	nodo_nuevo->elemento = elemento;

	return nodo_nuevo;
}

abb_t *abb_crear(abb_comparador comparador){
	abb_t *arbol = malloc(sizeof(abb_t));

	if(!arbol || !comparador){
		free(arbol);
		return NULL;
	}

	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->tamanio = 0;

	return arbol;
}

nodo_abb_t *extraer_raiz(abb_t *arbol){
	return arbol->nodo_raiz;
}

nodo_abb_t *insertar_rec(nodo_abb_t *raiz, void *elemento, int (*comparador)(void*, void*)){
	if(!raiz){
		raiz = crear_nodo(elemento);
		return raiz;
	}

	int comparacion = comparador(elemento, raiz->elemento);

	if(comparacion<=0){
		raiz->izquierda = insertar_rec(raiz->izquierda, elemento, comparador);
	} else {
		raiz->derecha = insertar_rec(raiz->derecha, elemento, comparador);
	}
	
	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento){
	if(!arbol)
		return NULL;

	nodo_abb_t *raiz = extraer_raiz(arbol);

	arbol->nodo_raiz = insertar_rec(raiz, elemento, arbol->comparador);
	arbol->tamanio++;

	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento){

	return elemento;
}

void *buscar_rec(nodo_abb_t *raiz, void *elemento, int (*comparador)(void*, void*)){
	if(!raiz)
		return NULL;

	int comparacion = comparador(elemento, raiz->elemento);

	if(comparacion == 0)
		return raiz->elemento;

	if(comparacion<0)
		return buscar_rec(raiz->izquierda, elemento, comparador);

	return buscar_rec(raiz->derecha, elemento, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento){
	if(!arbol || !arbol->nodo_raiz)
		return NULL;

	nodo_abb_t *raiz = extraer_raiz(arbol);

	void *elemento_buscado = buscar_rec(raiz, elemento, arbol->comparador);
	if(!elemento_buscado)
		return NULL;
	
	return elemento_buscado;
}

bool abb_vacio(abb_t *arbol){
	return arbol->tamanio==0 || !arbol;
}

size_t abb_tamanio(abb_t *arbol){
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol){
	// nodo_abb_t *raiz = extraer_raiz(arbol);
	// abb_destruir(raiz->izquierda);
	// abb_destruir(raiz->derecha);
	// free(raiz);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
	// if(!arbol || !destructor)
	// 	return NULL;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
