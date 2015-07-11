#include <iostream>
#include <string>
#include <cassert>
#include "aed2.h"

#include "nuestros/compu.h" 
#include "nuestros/red.h"
#include "nuestros/paquete.h"
#include "nuestros/ab.h"
#include "nuestros/dcnet.h"
#include "nuestros/conjLog.h"

//#include "nuestros/diccLog.h"

using namespace aed2;

using namespace std;
using namespace dcnet;

int main()
{
	
	/**/
	cout << "Creo compu 0 con interfaces 0" << endl;
	
	Compu comp0("0");
	comp0.AgInterfaz(0);
	comp0.AgInterfaz(1);
	comp0.AgInterfaz(2);
	comp0.AgInterfaz(4);

	cout << "Creo compu 1 con interfaces 0" << endl;

	Compu comp1("1");
	comp1.AgInterfaz(0);
	cout<<"Compu: "<<comp1.Ip()<<endl;
	comp1.AgInterfaz(1);
	comp1.AgInterfaz(2);

	//cout << "Creo compu 2 con interfaces 0" << endl;

	Compu comp2("2");
	comp2.AgInterfaz(0);
	comp2.AgInterfaz(1);

	//cout << "Creo compu 3 con interfaces 0" << endl;

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


	Interfaz inter = r.InterfazUsada(comp0,comp1);
	cout<<"Interfaz usada entre 0 y 1: "<<inter<<endl;
	DCNet dcnet(r);
	//dcnet.AvanzarSegundo();

	Paquete *p = new Paquete(1,1,comp0,comp3);
	dcnet.CrearPaquete(p);
	//dcnet.IsPaqueteEnTransito(p);
	//ConjLog<Paquete*> enEspera = dcnet.EnEspera(comp0);
	//delete p;
	//ConjLog<Paquete*> conj;
	//conj.Definir(p);
	//cout<<conj.Cardinal()<<endl;


	return 0;
}

