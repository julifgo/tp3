#include "Driver.h"
#include "mini_test.h"
#include "../aed2/Lista.h"
#include "../aed2/Conj.h"
#include "../aed2/Dicc.h"

#include <string>
#include <iostream>

using namespace aed2;

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
	
	Conj<Interfaz> conjIc1;
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
	Interfaz i3 = dcnet.IesimaInterfazDe(c1, 1);
	Interfaz i4 = dcnet.IesimaInterfazDe(c2, 1);
	
	dcnet.Conectar(c1, i1, c2, i2);
	dcnet.Conectar(c2, i3, c3, i4);
	dcnet.CrearPaquete(c1, c3, 3);
	dcnet.CrearPaquete(c3, c2, 1);
	dcnet.CrearPaquete(c3, c2, 2);
	

	ASSERT_EQ(dcnet.CantidadNodosRecorridosPor(0),1);
	ASSERT_EQ(dcnet.IesimoNodoRecorridoPor(0,0),c1);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c1),1);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c2),0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c3),2);
	ASSERT_EQ(dcnet.IesimoEnEsperaEn(c1,0),0);
	dcnet.AvanzarSegundo();

	dcnet.CrearPaquete(c3, c1, 3);
	ASSERT_EQ(dcnet.prioridad(3),3); //TODO. Descomentar cuando ande FindPaquete

	ASSERT_EQ(dcnet.CantidadNodosRecorridosPor(0),2); 
	ASSERT_EQ(dcnet.IesimoNodoRecorridoPor(0,0),c1);
	ASSERT_EQ(dcnet.IesimoNodoRecorridoPor(0,1),c2);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c1),0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c2),1);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c3),2);

	ASSERT_EQ(dcnet.CantidadEnviadosPor(c1),1);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c2),0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c3),1);

	dcnet.AvanzarSegundo();

	ASSERT_EQ(dcnet.CantidadEnviadosPor(c2),1);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c1),1);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c3),2);

	//ASSERT_EQ(dcnet.laQueMasEnvio(), c3);
	
}


void test_red() {

	Driver dr;

	ASSERT_EQ(dr.CantidadComputadoras(), 0);
	
	Computadora c0 = "192.168.0.1";
	Conj<Interfaz> i0;
	Interfaz i_0_0 = 0;
	Interfaz i_0_1 = 1;
	Interfaz i_0_2 = 2;
	i0.Agregar(i_0_0);
	i0.Agregar(i_0_1);
	i0.Agregar(i_0_2);

	Computadora c1 = "192.168.0.2";
	Conj<Interfaz> i1;
	Interfaz i_1_0 = 0;
	Interfaz i_1_1 = 1;
	Interfaz i_1_2 = 2;
	i1.Agregar(i_1_0);
	i1.Agregar(i_1_1);
	i1.Agregar(i_1_2);

	dr.AgregarComputadora(c0, i0);

	ASSERT_EQ(dr.CantidadComputadoras(), 1);

	dr.AgregarComputadora(c1, i1);

	ASSERT_EQ(dr.CantidadComputadoras(), 2);

	ASSERT_EQ(dr.CantidadInterfacesDe(c0), 3);
	ASSERT_EQ(dr.CantidadInterfacesDe(c1), 3);

	ASSERT_EQ(dr.IesimaComputadora(0), c0);
	ASSERT_EQ(dr.IesimaComputadora(1), c1);

	dr.Conectar(c0, i_0_0, c1, i_0_1);

	ASSERT(dr.conectadas(c0, c1));

	ASSERT(dr.InterfazUsada(c0, c1) == i_0_0);
	ASSERT(dr.InterfazUsada(c1, c0) == i_0_1);

	ASSERT_EQ(dr.IesimaInterfazDe(c0, 0), 0);
	ASSERT_EQ(dr.IesimaInterfazDe(c1, 0), 0);
	ASSERT_EQ(dr.IesimaInterfazDe(c0, 1), 1);
	ASSERT_EQ(dr.IesimaInterfazDe(c1, 2), 2);
}

void test_findPaquetes() {

	Driver dcnet;

	Computadora c0 = "0";
	Computadora c1 = "1";
	Computadora c2 = "2";
	Computadora c3 = "3";
	Computadora c4 = "4";

	Conj<Interfaz> i0;
	Conj<Interfaz> i1;
	Conj<Interfaz> i2;
	Conj<Interfaz> i3;
	Conj<Interfaz> i4;

	i0.Agregar(0); i0.Agregar(1);
	i1.Agregar(0); i1.Agregar(1); i1.Agregar(2);
	i2.Agregar(0);
	i3.Agregar(0); i3.Agregar(1); i3.Agregar(2); i3.Agregar(3);
	i4.Agregar(0); i4.Agregar(2);

	dcnet.AgregarComputadora(c0, i0);
	dcnet.AgregarComputadora(c1, i1);
	dcnet.AgregarComputadora(c2, i2);
	dcnet.AgregarComputadora(c3, i3);
	dcnet.AgregarComputadora(c4, i4);

	Interfaz _i0 = 0;
	Interfaz _i1 = 1;
	Interfaz _i2 = 2;
	Interfaz _i3 = 3;
	Interfaz _i4 = 4;

	dcnet.Conectar(c0, _i0, c1, _i0);
	dcnet.Conectar(c0, _i1, c3, _i0);
	dcnet.Conectar(c1, _i1, c4, _i0);
	dcnet.Conectar(c1, _i2, c3, _i1);
	dcnet.Conectar(c3, _i2, c2, _i0);

	dcnet.CrearPaquete(c1, c3, 3);
	dcnet.CrearPaquete(c2, c3, 3);
	dcnet.CrearPaquete(c0, c2, 1);


	//tests
	ASSERT_EQ(dcnet.prioridad(0), 3);
	ASSERT_EQ(dcnet.prioridad(1), 3);
	ASSERT_EQ(dcnet.prioridad(2), 1);
	ASSERT_EQ(dcnet.origen(0), c1);
	ASSERT_EQ(dcnet.origen(1), c2);
	ASSERT_EQ(dcnet.origen(2), c0);
	ASSERT_EQ(dcnet.destino(0), c3);
	ASSERT_EQ(dcnet.destino(1), c3);
	ASSERT_EQ(dcnet.destino(2), c2);

}

void test_dcnet_paquetes() {
	Driver dr;
	Computadora c = "192.168.0.1";
	Conj<Interfaz> i;

	i.Agregar(0);
	i.Agregar(1);
	i.Agregar(2);

	Conj<Interfaz> i2;

	i2.Agregar(0);
	i2.Agregar(1);
	i2.Agregar(2);

	Computadora c1 = "192.168.0.2";

	dr.AgregarComputadora(c, i);

	dr.AgregarComputadora(c1, i2);

	dr.CrearPaquete(c,c1,1);
	dr.CrearPaquete(c,c1,1);
	ASSERT_EQ(dr.prioridad(0),1);
	ASSERT_EQ(dr.origen(0),c);

	ASSERT_EQ(dr.CantidadComputadoras(), 2);
	ASSERT_EQ(dr.CantidadInterfacesDe(c), 3);

	ASSERT_EQ(dr.IesimaComputadora(0), c);
	ASSERT_EQ(dr.IesimaComputadora(1), c1);
	ASSERT_EQ(dr.IesimaInterfazDe(c, 0), 0);
	ASSERT_EQ(dr.IesimaInterfazDe(c1, 0), 0);
	ASSERT_EQ(dr.IesimaInterfazDe(c, 1), 1);
	ASSERT_EQ(dr.IesimaInterfazDe(c1, 0), 0);
}

void test_integral() {

	Driver dcnet;

	//test
	ASSERT_EQ(dcnet.CantidadComputadoras(), 0);

	//Creamos las computadoras

	Computadora c0 = "0";
	Computadora c1 = "1";
	Computadora c2 = "2";
	Computadora c3 = "3";
	Computadora c4 = "4";

	//Agregamos las interfaces

	Interfaz _i0 = 0;
	Interfaz _i1 = 1;
	Interfaz _i2 = 2;
	Interfaz _i3 = 3;
	Interfaz _i4 = 4;

	Conj<Interfaz> i0;
	Conj<Interfaz> i1;
	Conj<Interfaz> i2;
	Conj<Interfaz> i3;
	Conj<Interfaz> i4;

	i0.Agregar(_i0); i0.Agregar(_i1);
	i1.Agregar(_i0); i1.Agregar(_i1); i1.Agregar(_i2);
	i2.Agregar(_i0);
	i3.Agregar(_i0); i3.Agregar(_i1); i3.Agregar(_i2); i3.Agregar(_i3);
	i4.Agregar(_i0); i4.Agregar(_i2);

	//Agregamos las computadoras

	dcnet.AgregarComputadora(c0, i0);
	dcnet.AgregarComputadora(c1, i1);
	dcnet.AgregarComputadora(c2, i2);
	dcnet.AgregarComputadora(c3, i3);
	dcnet.AgregarComputadora(c4, i4);

	//Conectamos las computadoras

	dcnet.Conectar(c0, _i0, c1, _i0);
	dcnet.Conectar(c0, _i1, c3, _i0);
	dcnet.Conectar(c1, _i1, c4, _i0);
	dcnet.Conectar(c1, _i2, c3, _i1);
	dcnet.Conectar(c3, _i2, c2, _i0);

	//Creamos algunos paquetes

	aed2::Paquete p0 = 0;
	aed2::Paquete p1 = 1;

	dcnet.CrearPaquete(c1, c3, 3);
	dcnet.CrearPaquete(c2, c3, 3);

	//test
	ASSERT_EQ(dcnet.CantidadComputadoras(), 5);

	ASSERT(dcnet.InterfazUsada(c0, c1) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c0) == _i0);
	ASSERT(dcnet.InterfazUsada(c0, c3) == _i1);
	ASSERT(dcnet.InterfazUsada(c3, c0) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c4) == _i1);
	ASSERT(dcnet.InterfazUsada(c4, c1) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c3) == _i2);
	ASSERT(dcnet.InterfazUsada(c3, c1) == _i1);
	ASSERT(dcnet.InterfazUsada(c3, c2) == _i2);
	ASSERT(dcnet.InterfazUsada(c2, c3) == _i0);

	ASSERT(dcnet.conectadas(c1, c0));
	ASSERT(dcnet.conectadas(c3, c0));
	ASSERT(dcnet.conectadas(c4, c1));
	ASSERT(dcnet.conectadas(c3, c1));
	ASSERT(dcnet.conectadas(c2, c3));

	//deberia devolver la computadora de origen
	ASSERT_EQ(dcnet.IesimoNodoRecorridoPor(p0, 0), c1);
	ASSERT_EQ(dcnet.IesimoNodoRecorridoPor(p1, 0), c2);
	//deberia devolver 0 porque no se avanzó segundo
	ASSERT_EQ(dcnet.CantidadNodosRecorridosPor(p0), 1);
	ASSERT_EQ(dcnet.CantidadNodosRecorridosPor(p1), 1);

	//deberia devolver 0 porque no se avanzó segundo
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c0), 0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c1), 0);	
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c2), 0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c3), 0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c4), 0);

	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c0), 0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c1), 1);	
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c2), 1);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c3), 0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c4), 0);

	//devuelve el paquete
	ASSERT_EQ(dcnet.IesimoEnEsperaEn(c1, 0), 0);	
	ASSERT_EQ(dcnet.IesimoEnEsperaEn(c2, 0), 1);

	dcnet.AvanzarSegundo();
	/**/
	//no deberian cambiar
	ASSERT_EQ(dcnet.CantidadComputadoras(), 5);

	ASSERT(dcnet.InterfazUsada(c0, c1) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c0) == _i0);
	ASSERT(dcnet.InterfazUsada(c0, c3) == _i1);
	ASSERT(dcnet.InterfazUsada(c3, c0) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c4) == _i1);
	ASSERT(dcnet.InterfazUsada(c4, c1) == _i0);
	ASSERT(dcnet.InterfazUsada(c1, c3) == _i2);
	ASSERT(dcnet.InterfazUsada(c3, c1) == _i1);
	ASSERT(dcnet.InterfazUsada(c3, c2) == _i2);
	ASSERT(dcnet.InterfazUsada(c2, c3) == _i0);

	ASSERT(dcnet.conectadas(c1, c0));
	ASSERT(dcnet.conectadas(c3, c0));
	ASSERT(dcnet.conectadas(c4, c1));
	ASSERT(dcnet.conectadas(c3, c1));
	ASSERT(dcnet.conectadas(c2, c3));


	//deberia devolver 0 porque no se avanzó segundo
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c0), 0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c1), 1);	
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c2), 1);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c3), 0);
	ASSERT_EQ(dcnet.CantidadEnviadosPor(c4), 0);

	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c0), 0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c1), 0);	
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c2), 0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c3), 0);
	ASSERT_EQ(dcnet.CantidadEnEsperaEn(c4), 0);

	/**/
}

int main(int argc, char **argv)
{
    RUN_TEST(test_dcnet_ejemplo);
    RUN_TEST(test_dcnet_paquetes);
    RUN_TEST(test_red);
    RUN_TEST(test_findPaquetes);
    RUN_TEST(test_integral);
	/******************************************************************
	 * TODO: escribir casos de test exhaustivos para todas            *
	 * las funcionalidades del módulo.                                *
     * La interacción con el TAD DcNet se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/

	return 0;
}
