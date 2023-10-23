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

void crear_abb()
{
	abb_t *abb = abb_crear(elemento_es_igual_a);
	pa2m_afirmar(abb != NULL, "El abb se creo correctamente");
	pa2m_afirmar(abb_tamanio(abb) == 0, "El abb vacio tiene tamanio cero");
	abb_t *abb_null = abb_crear(NULL);
	pa2m_afirmar(abb_null == NULL,
		     "No se puede crear un abb con comparador NULL");
	abb_destruir(abb);
	abb_destruir_todo(abb_null, NULL);
}

void insertar_en_abb()
{
	abb_t *abb = abb_crear(elemento_es_igual_a);
	void *e1 = (void *)2;
	abb_insertar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 1), "Inserto un solo elemento");
	void *e2 = (void *)5;
	abb_insertar(abb, e2);
	pa2m_afirmar((abb_tamanio(abb) == 2), "Inserto el 2do elemento");
	void *e3 = (void *)10;
	abb_insertar(abb, e3);
	pa2m_afirmar((abb_tamanio(abb) == 3), "Inserto el 3er elemento");
	void *e4 = (void *)7;
	abb_insertar(abb, e4);
	pa2m_afirmar((abb_tamanio(abb) == 4), "Inserto el 4to elemento");
	void *e5 = (void *)15;
	abb_insertar(abb, e5);
	pa2m_afirmar((abb_tamanio(abb) == 5), "Inserto el 5to elemento");
	void *e6 = NULL;
	abb_insertar(abb, e6);
	pa2m_afirmar((abb_tamanio(abb) == 6),
		     "Se puede insertar un elemento NULL");
	pa2m_afirmar((abb_tamanio(abb) == 6),
		     "Se insertaron todos los elementos");
	abb_destruir_todo(abb, NULL);
}

void quitar_elementos()
{
	abb_t *abb = abb_crear(elemento_es_igual_a);
	void *e1 = (void *)2;
	abb_insertar(abb, e1);
	void *e2 = (void *)5;
	abb_insertar(abb, e2);
	void *e3 = (void *)10;
	abb_insertar(abb, e3);
	void *e4 = (void *)7;
	abb_insertar(abb, e4);
	void *e5 = (void *)15;
	abb_insertar(abb, e5);
	pa2m_afirmar((abb_tamanio(abb) == 5),
		     "Se insertaron todos los elementos");
	abb_quitar(abb, e2);
	pa2m_afirmar((abb_tamanio(abb) == 4),
		     "Se elimino correctamente un elemento");
	abb_quitar(abb, e1);
	pa2m_afirmar((abb_tamanio(abb) == 3),
		     "Se elimino correctamente otro elemento");
	abb_insertar(abb, e2);
	pa2m_afirmar((abb_tamanio(abb) == 4),
		     "Se inserto de nuevo el elemento eliminado");
	abb_quitar(abb, e4);
	abb_quitar(abb, e3);
	abb_quitar(abb, e5);
	abb_quitar(abb, e2);
	pa2m_afirmar(abb_vacio(abb), "Abb vacia despues de borrar todo");
	abb_destruir_todo(abb, NULL);
}

void buscar_elementos()
{
	abb_t *abb = abb_crear(elemento_es_igual_a);
	void *e1 = (void *)2;
	abb_insertar(abb, e1);
	void *e2 = (void *)5;
	abb_insertar(abb, e2);
	void *e3 = (void *)10;
	abb_insertar(abb, e3);
	void *e4 = (void *)7;
	abb_insertar(abb, e4);
	void *e5 = (void *)15;
	void *e6 = (void *)6;
	abb_insertar(abb, e5);
	abb_buscar(abb, e3);
	pa2m_afirmar(abb_buscar(abb, e5) == e5, "Se encontro el elemento");
	pa2m_afirmar(abb_buscar(abb, e2) == e2, "Se encontro otro elemento");
	abb_quitar(abb, e1);
	pa2m_afirmar(!abb_buscar(abb, e1),
		     "No se encontro el elemento borrado");
	pa2m_afirmar(!abb_buscar(abb, e6),
		     "No se encontro un elemento inexistente");
	pa2m_afirmar(!abb_buscar(abb, NULL), "No se encontro un elemento NULL");
	abb_destruir_todo(abb, NULL);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== MIS PRUEBAS ========================");
	crear_abb();
	pa2m_nuevo_grupo("\n=== Insertar ===");
	insertar_en_abb();
	pa2m_nuevo_grupo("\n=== Quitar ===");
	quitar_elementos();
	pa2m_nuevo_grupo("\n=== Busqueda ===");
	buscar_elementos();

	return pa2m_mostrar_reporte();
}
