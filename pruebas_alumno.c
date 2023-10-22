#include "pa2m.h"
#include "./src/abb.h"

int elemento_es_igual_a(void *_a, void *_b)
{
	void *a = _a;
	void *b = _b;

	if (a && b && a == b)
		return 0;

	return -1;
}

void crear_abb(){
	abb_t *abb = abb_crear(elemento_es_igual_a);
	pa2m_afirmar(abb!=NULL,"Se creo correctamente");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto un solo elemento");
	abb_quitar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 0), "Quito el único elemento");
	abb_destruir(abb);
}

void insertar_en_abb(){
	abb_t *abb = abb_crear(elemento_es_igual_a);
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto un solo elemento");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto el 2do elemento");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto el 3er elemento");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto el 4to elemento");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto el 5to elemento");
	abb_destruir_todo(abb, NULL);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	return pa2m_mostrar_reporte();
}
