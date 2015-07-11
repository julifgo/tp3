#include <iostream>
#include <string>
#include <cassert>
#include "aed2.h"

#include "nuestros/compu.h" 
#include "nuestros/red.h"
#include "nuestros/paquete.h"
#include "nuestros/dcnet.h"

using namespace aed2;
using namespace std;
using namespace dcnet;

int main()
{
	
	/**/
	cout << "Creo compu 0 con interfaces 0" << endl;
	
	//Creacion de Compus con Interfaces
	Compu comp0("0");
	comp0.AgInterfaz(0);
	comp0.AgInterfaz(1);
	comp0.AgInterfaz(2);
	comp0.AgInterfaz(4);

	cout << "Creo compu 1 con interfaces 0" << endl;

	Compu comp1("1");
	comp1.AgInterfaz(0);
	comp1.AgInterfaz(1);
	comp1.AgInterfaz(2);
	//Consulta de una Ip de una Compu
	cout<<"Compu: "<<comp1.Ip()<<endl;
	

	Compu comp2("2");
	comp2.AgInterfaz(0);
	comp2.AgInterfaz(1);

	Compu comp3("3");
	comp3.AgInterfaz(0);
	comp3.AgInterfaz(1);

	Red r;
	r.AgCompu(comp0);
	r.AgCompu(comp1);
	r.AgCompu(comp2);
	r.AgCompu(comp3);

	cout << "Conectando..." << endl;
	r.Conectar(comp0 ,comp1, 0, 0);
	r.Conectar(comp0 ,comp3, 1, 0);
	r.Conectar(comp0 ,comp2, 2, 0);
	r.Conectar(comp1 ,comp2, 1, 1);
	r.Conectar(comp3 ,comp1, 1, 2);
	cout << "Conectado !" << endl;

	cout << "Algunos caminos minimos" << endl;

	cout << r.CaminosMin(comp1, comp3) << endl;
	cout << r.CaminosMin(comp0, comp3) << endl;
	cout << r.CaminosMin(comp1, comp3) << endl;
	cout << r.CaminosMin(comp2, comp0) << endl;
	cout << r.CaminosMin(comp1, comp2) << endl;
	cout << r.CaminosMin(comp3, comp2) << endl;

	//Prueba de una interfaz usada entre dos compus conectadas
	Interfaz inter = r.InterfazUsada(comp0,comp1);
	cout<<"Interfaz usada entre 0 y 1: "<<inter<<endl;
	DCNet dcnet(r);
	Paquete *p1 = new Paquete(1,1,comp0,comp3); //Creacion de un nuevo paquete para la red
	Paquete *p2 = new Paquete(2,1,comp0,comp2); //Creacion de un nuevo paquete para la red
	Paquete *p3 = new Paquete(3,2,comp2,comp1); //Creacion de un nuevo paquete para la red
	dcnet.CrearPaquete(p1); //Agrego los paquetes a dcnet. Se cargan en las listas de esperas de las compus de origen
	dcnet.CrearPaquete(p2);
	dcnet.CrearPaquete(p3);
	dcnet.red(); //Se recupera la red del dcnet
	

	return 0;
}

