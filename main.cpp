#include <iostream>
#include <string>
#include <cassert>
#include "aed2.h"

#include "nuestros/compu.h" 
#include "nuestros/red.h"
#include "nuestros/paquete.h"
#include "nuestros/ab.h"

#include "nuestros/ab.h"

using namespace aed2;

using namespace std;
using namespace dcnet;

int main()
{


	cout << "hola mundo";
	int variable;
	
	Lista<Nat> lista;
	lista.AgregarAtras(2);
	Nat primero = lista.Primero();
	cout<<primero<<endl;

	Dicc<Nat,String> dicc;
	dicc.Definir(1,"Uno");
	bool estaDef = dicc.Definido(5);
	cout<<"Clave definida: "<<estaDef<<endl;

	Compu comp("192.168.50.137");
	Compu comp2("192.168.0.1");
	comp.AgInterfaz(0);
	comp.AgInterfaz(36);
	comp2.AgInterfaz(2);
	cout<<"Ip creada "<<comp.Ip()<<endl;
	cout<<"Interfaz creada "<<comp.Interfaces()<<endl;
	Red r1;
	r1.AgCompu(comp);
	cout << "Primera Ip de Lista:" << r1.Computadoras().Primero().Ip() << endl;
	r1.AgCompu(comp2);
	cout<< "UsaInterfaz?:" << r1.UsaInterfaz(comp,36) << endl;
	r1.Conectar(comp,comp2,36,2);
	cout<< "UsaInterfaz ahora que conecte?:" << r1.UsaInterfaz(comp,36) << endl;
	cout<< "La Ip a la que esta conectada comp:" << r1.Vecinos(comp).CrearIt().Siguiente().Ip() << endl;
	Ab<int> bla(Ab<int>(),5,Ab<int>());
	int ble = bla.Raiz();
	cout<<ble<<endl;
	cin >> variable;



	/*

	Paquete p1 = Paquete(2, 1);

	Paquete p2 = Paquete(2, 2);

	if( p2 < p1 )
		cout << "true" << endl;
	else 
		cout << "false" << endl;

	*/

/*
	Compu c1 = Compu(1);
	Compu c2 = Compu(2);

	Paquete p1 = Paquete(1,2,c1,c2);
	//Paquete p2 = Paquete(2,1,c2,c1);

	cout << p1.prioridad() << endl;

	if(p1 == p2) {
		cout << "iguales";
	} else {
		cout << "distintos";
	}
	p1 = p2;

	if(p1 == p2) {
		cout << "iguales";
	} else {
		cout << "distintos";
	}*/

	return 0;
}

