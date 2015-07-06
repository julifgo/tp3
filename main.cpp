#include <iostream>
#include <string>
#include <cassert>
#include "aed2.h"

#include "nuestros/compu.h" 
#include "nuestros/red.h"
#include "nuestros/paquete.h"
#include "nuestros/ab.h"

//#include "nuestros/diccLog.h"

using namespace aed2;

using namespace std;
using namespace dcnet;

int main()
{

	/*
	Lista<Nat> lista;
	lista.AgregarAtras(2);
	Nat primero = lista.Primero();
	cout<<primero<<endl;
	*/

	/*
	Dicc<Nat,String> dicc;
	dicc.Definir(1,"Uno");
	bool estaDef = dicc.Definido(5);
	cout<<"Clave definida: "<<estaDef<<endl; */

	Compu comp1("0");
	comp1.AgInterfaz(0);
	comp1.AgInterfaz(36);

	Compu comp2("1");
	comp2.AgInterfaz(2);

	//cout<<"Ip creada "<<comp1.Ip()<<endl;
	//cout<<"Interfaz creada "<<comp1.Interfaces()<<endl;

	Red r;
	r.AgCompu(comp1);
	r.AgCompu(comp2);
	r.Conectar(comp1 ,comp2, 36, 2);

	//cout << "Primera Ip de Lista:" << r1.Computadoras().Primero().Ip() << endl;
	//cout<< "UsaInterfaz?:" << r1.UsaInterfaz(comp,36) << endl;
	//cout<< "UsaInterfaz ahora que conecte?:" << r1.UsaInterfaz(comp,36) << endl;
	//cout<< "La Ip a la que esta conectada comp:" << r1.Vecinos(comp).CrearIt().Siguiente().Ip() << endl;
	//cout<<comp<<endl;
	/*DiccLog<int,int> diccionario;
	diccionario.Definir(1,10);
	Ab<int> arbolIzq(Ab<int>(),10,Ab<int>());
	Ab<int> arbolDer(Ab<int>(),20,Ab<int>());
	Ab<int> arbol(arbolIzq,5,arbolDer);
	Ab<int> izq = arbol.Izq();
	cout<<"raiz: "<<izq.Raiz()<<endl;
	//cout<<"cardinal arbol: "<<arbol.Tamano()<<endl;
	//cout<<"cardinal arbol izquiwerdo: "<<arbol.Izq().Tamano()<<endl;
	//cin >> variable;

*/

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
		cout << "igualeshttps://www.google.com.ar/search?client=ubuntu&channel=fs&q=c%2B%2B+double+free+or+coruption&ie=utf-8&oe=utf-8&gfe_rd=cr&ei=2ceZVf_MI_Cp8we5o4HQAQ";
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

