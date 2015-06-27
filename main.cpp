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
	//abc.AgregarAdelante(valor);
	//int test = abc.Primero();
	//cout << test;
	cin >> variable;
	return 0;
}

