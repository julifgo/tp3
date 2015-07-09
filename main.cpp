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

	/**/

	cout << "Creo compu 0 con interfaces 0, 1, 2" << endl;
	
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

	cout << "Creo compu 2 con interfaces 0" << endl;

	Compu comp2("2");
	comp2.AgInterfaz(0);
	comp2.AgInterfaz(1);

	cout << "Creo compu 3 con interfaces 0" << endl;

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

	cout << "Algunos caminos minimos" << endl;

	cout << r.CaminosMin(comp1, comp3) << endl;
	cout << r.CaminosMin(comp0, comp3) << endl;
	cout << r.CaminosMin(comp1, comp3) << endl;
	cout << r.CaminosMin(comp2, comp0) << endl;
	cout << r.CaminosMin(comp1, comp2) << endl;
	cout << r.CaminosMin(comp3, comp2) << endl;

	/**/

	/** /

	Ab<int> *arbolIzq = new Ab<int>(NULL,10,NULL);
	Ab<int> *arbolDer = new Ab<int>(NULL,20,NULL);
	Ab<int> arbol(arbolIzq,5,arbolDer);
	Ab<int> izq = *arbol.izq();
	//cout<<"raiz: "<<izq.raiz()<<endl;
	Red r1;
	Compu c1("1");
	c1.AgInterfaz(0);
	Compu c2("2");
	c2.AgInterfaz(0);
	c2.AgInterfaz(1);
	Compu c3("3");
	c3.AgInterfaz(0);
	r1.AgCompu(c1);
	r1.AgCompu(c2);
	r1.AgCompu(c3);
	r1.Conectar(c1,c2,0,0);
	r1.Conectar(c2,c3,1,0);
	Paquete paq(1,2,c1,c2);
	//cout << "Primera Ip de Lista:" << r1.Computadoras().Primero().Ip() << endl;

	//r.Conectar(comp0 ,comp2, 2, 0);

	//Conj<Lista<Compu> > Red::CaminosMin(const Compu& c1,const Compu& c2)
	//cout << r1.CaminosMin(c3, c1) << endl;
	//cout << r.CaminosMin(comp0, comp1) << endl;

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
	cout<<"raiz: "<<izq.Raiz()<<endl;*/
	//cout<<"cardinal arbol: "<<arbol.Tamano()<<endl;
	//cout<<"cardinal arbol izquiwerdo: "<<arbol.Izq().Tamano()<<endl;
	//cin >> variable;

	/**/

	return 0;
}

