#include "Driver.h"
#include "mini_test.h"
#include "../aed2.h"
//#include "../aed2/Conj.h"
//#include "../aed2/Dicc.h"

#include "../nuestros/paquete.h"
#include "../nuestros/compu.h"

#include <string>
#include <iostream>

using namespace aed2;
using namespace dcnet;

/** 
 * Imprime un elemento a un string, en vez de a una pantalla, 
 * a través del operador << 
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan 
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename S::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
	it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

	while( it1.HaySiguiente() )
	{
		bool esta = false;
		it2 = s.CrearIt();

		while( it2.HaySiguiente() ) {
		  if ( it1.Siguiente() == it2.Siguiente() ) {
			esta = true;
			break;
		  }
		  it2.Avanzar();
		}

		if ( !esta ) {
			return false;
		}
			
		it1.Avanzar();
	}
  
  return true;
}


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
 
void test_dcnet_ejemplo() {
	/*Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	
	conjIc1.Agregar(1);
	conjIc1.Agregar(2);
	conjIc1.Agregar(3);
	
	conjIc2.Agregar(1);
	conjIc2.Agregar(2);
	conjIc2.Agregar(3);
	
	conjIc3.Agregar(1);
	conjIc3.Agregar(2);
	
	Computadora c1 = "dc.uba.ar";
	Computadora c2 = "uba.ar";
	Computadora c3 = "dm.uba.ar";
	
	Driver dcnet;
	
	dcnet.AgregarComputadora(c1, conjIc1);
	dcnet.AgregarComputadora(c2, conjIc2);
	dcnet.AgregarComputadora(c3, conjIc3);
	
	// ejemplo - Indexado en 0 
	Interfaz i1 = dcnet.IesimaInterfazDe(c1, 0); 
	Interfaz i2 = dcnet.IesimaInterfazDe(c2, 2);
	
	dcnet.Conectar(c1, i1, c2, i2);
	dcnet.CrearPaquete(c1, c2, 3);
	dcnet.AvanzarSegundo();	

	ASSERT_EQ(dcnet.laQueMasEnvio(), c1);*/
		
}

//
//TESTS PAQUETE

void test_paquete_id() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p(id, prioridad, c1, c2);

	ASSERT_EQ(to_str(p.Id()), to_str(id));

}

void test_paquete_prioridad() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p(id, prioridad, c1, c2);

	ASSERT_EQ(to_str(p.Prioridad()), to_str(prioridad));

}

void test_paquete_origen() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p(id, prioridad, c1, c2);

	ASSERT_EQ(to_str(p.Origen()), to_str(c1));

}

void test_paquete_destino() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p(id, prioridad, c1, c2);

	ASSERT_EQ(to_str(p.Destino()), to_str(c2));

}

void test_paquete_equal() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p1(id, prioridad, c1, c2);
	Paquete p2(id, prioridad, c1, c2);

	ASSERT_EQ(to_str(p1 == p2), to_str(true));

}

void test_paquete_assign() {

	ID id = 1;
	Prioridad prioridad = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p1(id, prioridad, c1, c2);
	Paquete p2 = p1;

	ASSERT_EQ(to_str(p2), to_str(p1));

}

void test_paquete_lower_by_prioridad() {

	ID id1 = 0;
	ID id2 = 1;
	Prioridad prioridad1 = 0;
	Prioridad prioridad2 = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p1(id1, prioridad1, c1, c2);
	Paquete p2(id2, prioridad2, c1, c2);

	ASSERT_EQ(to_str(p1 < p2), to_str(true));
	ASSERT_EQ(to_str(p2 < p1), to_str(false));

}

void test_paquete_lower_by_id() {

	ID id1 = 0;
	ID id2 = 1;
	Prioridad prioridad1 = 1;
	Prioridad prioridad2 = 1;
	Compu c1("192.168.0.1");
	Compu c2("192.168.0.2");

	Paquete p1(id1, prioridad1, c1, c2);
	Paquete p2(id2, prioridad2, c1, c2);

	ASSERT_EQ(to_str(p1.Prioridad() == p2.Prioridad()), to_str(true));
	ASSERT_EQ(to_str(p1 < p2), to_str(true));
	ASSERT_EQ(to_str(p2 < p1), to_str(false));

}

//
//TESTS COMPU


int main(int argc, char **argv)
{
	//RUN_TEST(test_dcnet_ejemplo);

	//test paquete
	RUN_TEST(test_paquete_id);
	RUN_TEST(test_paquete_prioridad);
	RUN_TEST(test_paquete_origen);
	RUN_TEST(test_paquete_destino);
	RUN_TEST(test_paquete_equal);
	RUN_TEST(test_paquete_assign);
	RUN_TEST(test_paquete_lower_by_prioridad);
	RUN_TEST(test_paquete_lower_by_id);


	/******************************************************************
	 * TODO: escribir casos de test exhaustivos para todas            *
	 * las funcionalidades del módulo.                                *
     * La interacción con el TAD DcNet se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/

	return 0;
}
