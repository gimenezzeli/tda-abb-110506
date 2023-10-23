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

nodo_abb_t *insertar_rec(nodo_abb_t *raiz, void *elemento, int (*comparador)(void*, void*)){
	if(!comparador)
		return NULL;
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

	arbol->nodo_raiz = insertar_rec(arbol->nodo_raiz, elemento, arbol->comparador);
	arbol->tamanio++;

	return arbol;
}

nodo_abb_t *buscar_predecesor(nodo_abb_t *raiz, void **elemento){
	if(!raiz->derecha){
		nodo_abb_t *izquierdo = raiz->izquierda;
		*elemento = raiz->elemento;
		free(raiz);
		return izquierdo;
	}
	raiz->derecha = buscar_predecesor(raiz->derecha, elemento);
	return raiz;
}

nodo_abb_t *quitar_rec(abb_t *arbol, nodo_abb_t *raiz, void *elemento, bool *se_elimino){
	if(!raiz)
		return NULL;

	int comparacion = arbol->comparador(elemento, raiz->elemento);

	// Nodo con el valor a eliminar encontrado
	if(comparacion == 0){
		// Caso 1: con 0 o 1 hijo
		if (!raiz->derecha || !raiz->izquierda){
			nodo_abb_t *nuevo_hijo = raiz->izquierda;
			if(!nuevo_hijo)
				nuevo_hijo = raiz->derecha;
			free(raiz);
			*se_elimino = true;
			arbol->tamanio--;
			return nuevo_hijo;
		} else if(raiz->derecha && raiz->izquierda){ // Caso 2: con 2 hijos
			void *elemento_aux = NULL;
			raiz->izquierda = buscar_predecesor(raiz->izquierda, &elemento_aux);
			raiz->elemento = elemento_aux;
			*se_elimino = true;
			arbol->tamanio--;
			return raiz;
		}
	}

	if(comparacion<0){
		raiz->izquierda = quitar_rec(arbol, raiz->izquierda, elemento, se_elimino);
	} else if(comparacion>0){
		raiz->derecha = quitar_rec(arbol, raiz->derecha, elemento, se_elimino);
	}
	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento){
	if(!arbol)
		return NULL;

	bool se_elimino = false;
	arbol->nodo_raiz = quitar_rec(arbol, arbol->nodo_raiz, elemento, &se_elimino);
	
	if(!se_elimino){
		return NULL;
	}

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
	if(!arbol)
		return NULL;

	void *elemento_buscado = buscar_rec(arbol->nodo_raiz, elemento, arbol->comparador);
	if(!elemento_buscado)
		return NULL;
	
	return elemento_buscado;
}

bool abb_vacio(abb_t *arbol){
	return !arbol || arbol->tamanio==0;
}

size_t abb_tamanio(abb_t *arbol){
	if(!arbol)
		return 0;
	return arbol->tamanio;
}

void destruir_todo_rec(nodo_abb_t *raiz, void (*destructor)(void *)){
	if(!raiz)
		return;
	
	if(destructor!=NULL)
		destructor(raiz->elemento);

	destruir_todo_rec(raiz->derecha, destructor);
	destruir_todo_rec(raiz->izquierda, destructor);
	free(raiz);
}

void abb_destruir(abb_t *arbol){
	if (!arbol) 
		return;
	destruir_todo_rec(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
	if(!arbol)
		return;

	destruir_todo_rec(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_recorrer_preorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, 
							size_t *contador){
	if(!raiz || *contador>=tamanio_array)
		return *contador;
	
	if(*contador<tamanio_array){
		array[(*contador)++] = raiz->elemento;
	}
	*contador = abb_recorrer_preorden(raiz->izquierda, array, tamanio_array, contador);
	*contador = abb_recorrer_preorden(raiz->derecha, array, tamanio_array, contador);
	return *contador;
}

size_t recorrer_inorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, 
						size_t *contador){
	if(!raiz || *contador>=tamanio_array)
		return *contador;
	
	*contador = recorrer_inorden(raiz->izquierda, array, tamanio_array, contador);
	if(*contador<tamanio_array){
		array[(*contador)++] = raiz->elemento;
	}
	*contador = recorrer_inorden(raiz->derecha, array, tamanio_array, contador);
	return *contador;
}

size_t recorrer_postorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, 
							size_t *contador){
	if(!raiz || *contador>=tamanio_array)
		return *contador;
	
	*contador = recorrer_postorden(raiz->izquierda, array, tamanio_array, contador);
	*contador = recorrer_postorden(raiz->derecha, array, tamanio_array, contador);

	if(*contador<tamanio_array){
		array[(*contador)++] = raiz->elemento;
	}
	return *contador;
}

bool abb_con_cada_elemento_preorden(nodo_abb_t *raiz, bool(*funcion)(void *, void *), 
									void *aux, size_t *contador){
	if(!raiz)
		return true;

	(*contador)++;
	if(!funcion(raiz->elemento, aux))
		return false;

	bool continuar = abb_con_cada_elemento_preorden(raiz->izquierda, funcion, aux, contador);
	if(!continuar)
		return false;

	continuar = abb_con_cada_elemento_preorden(raiz->derecha, funcion, aux, contador);
	if(!continuar)
		return false;

	return true;
}

bool abb_con_cada_elemento_inorden(nodo_abb_t *raiz, bool(*funcion)(void *, void *), 
									void *aux, size_t *contador){
	if(!raiz)
		return true;
	
	bool continuar = abb_con_cada_elemento_inorden(raiz->izquierda, funcion, aux, contador);
	if(!continuar)
		return false;

	(*contador)++;

	if(!funcion(raiz->elemento, aux))
		return false;
	
	continuar = abb_con_cada_elemento_inorden(raiz->derecha, funcion, aux, contador);
	if(!continuar)
		return false;

	return true;
}

bool abb_con_cada_elemento_postorden(nodo_abb_t *raiz, bool(*funcion)(void *, void *), 
									void *aux, size_t *contador){
	if(!raiz)
		return true;
	bool continuar = abb_con_cada_elemento_postorden(raiz->izquierda, funcion, aux, contador);
	if(!continuar)
		return false;

	continuar = abb_con_cada_elemento_postorden(raiz->derecha, funcion, aux, contador);
	if(!continuar)
		return false;

	(*contador)++;

	if(!funcion(raiz->elemento, aux))
		return false;
	
	return true;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux){
	if(!arbol || !funcion)
		return 0;
	
	size_t contador = 0;

	switch(recorrido){
		case PREORDEN:
			abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &contador);
			break;
	 	case INORDEN:
			abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &contador);
			break;
		case POSTORDEN:
			abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &contador);
			break;
		default:
			break;
	}
	
	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array){
	if(abb_vacio(arbol) || !array || tamanio_array==0)
		return 0;

	size_t contador = 0;

	switch(recorrido){
		case PREORDEN:
			contador = abb_recorrer_preorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		case INORDEN:
			contador = recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		case POSTORDEN:
			contador = recorrer_postorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		default:
			break;
	}
	return contador;
}