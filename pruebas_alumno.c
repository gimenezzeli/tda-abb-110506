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

void prueba_simple()
{
	abb_t *abb = abb_crear(elemento_es_igual_a);
	pa2m_afirmar(abb!=NULL,"Se creo correctamente");
	void *e1 = (void*)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1),"Inserto un solo elemento");
	abb_quitar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 0), "Quito el único elemento");
	//pa2m_afirmar((abb->nodo_raiz == NULL), "Quito el único elemento");
	abb_destruir(abb);

}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	return pa2m_mostrar_reporte();
}
