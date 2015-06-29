#include <stdio.h>
#include <iostream>
#include <fstream>
#include "aed2.h"
//#include "dicc_trie.h"
#include "nuestros/compu.h" 

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
	cout<<"Ip creada "<<comp.Ip()<<endl;

	cin >> variable;
	return 0;
}

