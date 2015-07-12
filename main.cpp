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
	cout << "Creo compu 0 con interfaces 0, 1, 2, 4" << endl;
	
	//Creacion de Compus con Interfaces
	Compu* comp0 = new Compu("0");
	comp0->AgInterfaz(0);
	comp0->AgInterfaz(1);
	comp0->AgInterfaz(2);
	comp0->AgInterfaz(4);

	/** /
	cout << comp0 << endl;

	cout << "Creo una compu 1 con interfaces 0 y la asigno a la compu 0 sin delete en el operador =" << endl;

	Compu comp1("1");
	comp1.AgInterfaz(0);

	cout << comp1 << endl;

	comp0 = comp1;
	cout << comp0.Interfaces() << endl;


	cout << "listo!" << endl;
	/** /

	/**/
	cout << "Creo compu 1 con interfaces 0, 1, 2" << endl;

	Compu* comp1 = new Compu("1");
	comp1->AgInterfaz(0);
	comp1->AgInterfaz(1);
	comp1->AgInterfaz(2);

	//Consulta de una Ip de una Compu
	//cout<<"Compu: "<<comp1.Ip()<<endl;


	cout << "Creo compu 2 con interfaces 0, 1" << endl;

	Compu* comp2 = new Compu("2");
	comp2->AgInterfaz(0);
	comp2->AgInterfaz(1);

	cout << "Creo compu 3 con interfaces 0, 1" << endl;
	Compu* comp3 = new Compu("3");
	comp3->AgInterfaz(0);
	comp3->AgInterfaz(1);

	Red r;
	r.AgCompu(*comp0);
	r.AgCompu(*comp1);
	r.AgCompu(*comp2);
	r.AgCompu(*comp3);

	cout << "Imprimo la lista de compus de la red" << endl;
	cout << r.Computadoras() << endl;


	cout << "Conectando..." << endl;
	r.Conectar(*comp0 ,*comp1, 0, 0);
	r.Conectar(*comp0 ,*comp3, 1, 0);
	r.Conectar(*comp0 ,*comp2, 2, 0);
	r.Conectar(*comp1 ,*comp2, 1, 1);
	r.Conectar(*comp3 ,*comp1, 1, 2);
	cout << "Conectado !" << endl;

	cout << "Algunos caminos minimos" << endl;

	cout << r.CaminosMin(*comp1, *comp3) << endl;
	cout << r.CaminosMin(*comp0, *comp3) << endl;
	cout << r.CaminosMin(*comp1, *comp3) << endl;
	cout << r.CaminosMin(*comp2, *comp0) << endl;
	cout << r.CaminosMin(*comp1, *comp2) << endl;
	cout << r.CaminosMin(*comp3, *comp2) << endl;

	cout << "Prueba de una interfaz usada entre dos compus conectadas" << endl;

	cout << "Interfaz usada entre 0 y 1: " << r.InterfazUsada(*comp0, *comp1) << endl;

	cout << "Creando paquetes" << endl;

	Paquete *p1 = new Paquete(1,1,*comp0,*comp3); //Creacion de un nuevo paquete para la red
	Paquete *p2 = new Paquete(2,1,*comp0,*comp2); //Creacion de un nuevo paquete para la red
	Paquete *p3 = new Paquete(3,2,*comp2,*comp1); //Creacion de un nuevo paquete para la red
	
	/** /
	DCNet dcnet(r);
	dcnet.CrearPaquete(p1); //Agrego los paquetes a dcnet. Se cargan en las listas de esperas de las compus de origen
	dcnet.CrearPaquete(p2);
	dcnet.CrearPaquete(p3);
	dcnet.red(); //Se recupera la red del dcnet
	/**/

	delete comp0;
	delete comp1;
	delete comp2;
	delete comp3;

	delete p1;
	delete p2;
	delete p3;


	return 0;
}

