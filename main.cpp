// Tp3.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "aed2.h"

using namespace std;


int main()
{
	cout << "hola mundo";
	int variable;
	//Lista<int> abc = Lista<int>();
	int valor = 2;
	Lista<Nat> lista;
	lista.AgregarAtras(2);
	Nat primero = lista.Primero();
	cout<<primero<<endl;

	Dicc<Nat,String> dicc;
	dicc.Definir(1,"Uno");
	bool estaDef = dicc.Definido(1);
	cout<<"Clave definida: "<<estaDef<<endl;
	cin >> variable;
	return 0;
}

