#include <ostream>
#include <string>
#include "../aed2.h"
#include "paquete.h"
#include "dcnet.h"

using namespace aed2;
using namespace std;
namespace dcnet{

	DCNet::DCNet(){}
	DCNet::DCNet(Red& red){
		estr.red = &red;
		if(estr.red->Computadoras().Longitud()>0)
			estr.laQueMasEnvio = new Compu(estr.red->Computadoras().Primero());
		else
			estr.laQueMasEnvio = NULL;

		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
		{
			ConjLog<Paquete*> *cPaq = new ConjLog<Paquete*>();
			colasPaquete.AgregarAtras(cPaq);
			estr.enEspera.definir(estr.red->Computadoras()[i].Ip(),cPaq);


			Nat aux = 0;
			estr.cantPaquetesEnviados.definir(estr.red->Computadoras()[i].Ip(),aux);

			DiccLog<Nat,Lista<Compu>* >*cCamino = new DiccLog<Nat,Lista<Compu>* >();
			colasCaminos.AgregarAtras(cCamino);
			estr.CaminoRecorrido.definir(estr.red->Computadoras()[i].Ip(),cCamino);
		}
	}
	DCNet::~DCNet(){
		//cout<<"destructor dcnet"<<endl;
		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
        {
            delete colasPaquete.operator [](i);
            delete colasCaminos.operator [](i);
        }
		for (Nat i = 0; i < colasRecorridos.Longitud(); i++)
		{
			delete colasRecorridos.operator [](i);
		}
		delete estr.laQueMasEnvio;
	}

	const Red* DCNet::red() const{
		return estr.red; 
	}

	Nat DCNet::CantidadEnviados(const Compu& c){
		Nat res = *estr.cantPaquetesEnviados.obtener(c.Ip());
		return res;
	}

	const Lista<Compu> DCNet::CaminoRecorrido(Paquete* p){
		Lista<Compu> res;
		DiccString<DiccLog<Nat,Lista<Compu>* >* >::Iterador *it = new DiccString<DiccLog<Nat,Lista<Compu>* >* >::Iterador(&estr.CaminoRecorrido);
		bool found = false;
		DiccLog<Nat,Lista<Compu>* > *paquetesPc0 = *it->valorActual();
		if(paquetesPc0->IsDefinido(p->Id())){
			found = true;
			res = *paquetesPc0->Significado(p->Id());
		}
		while(it->avanzar() && !found){
			DiccLog<Nat,Lista<Compu>* > *paquetes = *it->valorActual();
			if(paquetes->IsDefinido(p->Id())){
				found = true;
				res = *paquetes->Significado(p->Id());
			}
		}
		delete it;
		return res;
	}

	const Lista<Compu> DCNet::CaminoRecorrido(Nat id){
		Lista<Compu> res;
		DiccString<DiccLog<Nat,Lista<Compu>* >* >::Iterador *it = new DiccString<DiccLog<Nat,Lista<Compu>* >* >::Iterador(&estr.CaminoRecorrido);
		bool found = false;
		DiccLog<Nat,Lista<Compu>* > *paquetesPc0 = *it->valorActual();
		if(paquetesPc0->IsDefinido(id)){
			found = true;
			res = *paquetesPc0->Significado(id);
		}
		while(it->avanzar() && !found){
			DiccLog<Nat,Lista<Compu>* > *paquetes = *it->valorActual();
			if(paquetes->IsDefinido(id)){
				found = true;
				res = *paquetes->Significado(id);
			}
		}
		delete it;
		return res;
	}

	const ConjLog<Paquete*>* DCNet::EnEspera(const Compu& c){
		assert(estr.enEspera.definido(c.Ip()));
		return *estr.enEspera.obtener(c.Ip());
	}

	void DCNet::CrearPaquete(Paquete* p){
		//TODO. ASSERT COMPU ORIGEN (Y DESTINO?)
		ConjLog<Paquete*>* conj = *estr.enEspera.obtener(p->Origen().Ip());
		conj->Definir(p);
		DiccLog<Nat,Lista<Compu>* > *dicc = *estr.CaminoRecorrido.obtener(p->Origen().Ip());
		Lista<Compu>* camino = new Lista<Compu>();
		colasRecorridos.AgregarAtras(camino);
		todos.AgregarAtras(p);
		camino->AgregarAdelante(p->Origen());
		dicc->Definir(p->Id(),camino); //TODO. Me juego la cabeza que esto va a leakear//LEAK: ES FIX Sacar el NEW? TODO:TESTEAR
		//delete dicc;
	}


	void DCNet::AvanzarSegundo(){
		//Lista<Compu>::Iterador it = estr.red->Computadoras().CrearIt();
		Lista<Buffer> buffer; 

		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
			{
			IP ipActual = estr.red->Computadoras()[i].Ip();
			ConjLog<Paquete*>* cPaq = *estr.enEspera.obtener(ipActual);
			if( cPaq->Cardinal() > 0 ) {
				Paquete* p = cPaq->Minimo();
				Conj<Lista<Compu> > conjCortos = estr.red->CaminosMin(estr.red->Computadoras()[i], p->Destino());
				Lista<Compu> masCorto = conjCortos.CrearIt().Siguiente();
				masCorto.Fin();
				Compu pcaMover = masCorto.Primero();
				if( pcaMover == p->Destino() ) {
					cPaq->Borrar(p);
					DiccLog<Nat,Lista<Compu>* > *dicc = *estr.CaminoRecorrido.obtener(ipActual);
					dicc->Borrar(p->Id());
					//delete dicc;
				} else {
					Buffer b;
					b.compu = &pcaMover;
					b.paquete = p;
					buffer.AgregarAtras( b );
					DiccLog<Nat,Lista<Compu>* > *dicc = *estr.CaminoRecorrido.obtener(ipActual);
					Lista<Compu>* camino = dicc->Significado(p->Id());
					camino->AgregarAtras(pcaMover);
					DiccLog<Nat,Lista<Compu>* > *dicc2 = *estr.CaminoRecorrido.obtener(pcaMover.Ip());
					dicc2->Definir(p->Id(), camino);
					cPaq->Borrar(p);
					dicc->Borrar(p->Id());
					//delete dicc;
					//delete dicc2;
				}
				Nat enviados = (*estr.cantPaquetesEnviados.obtener(ipActual) + 1); //?
				estr.cantPaquetesEnviados.definir(ipActual,enviados);

				if(enviados > *estr.cantPaquetesEnviados.obtener(estr.laQueMasEnvio->Ip()) ) {
					if (estr.laQueMasEnvio == NULL){
						estr.laQueMasEnvio = new Compu(estr.red->Computadoras()[i]);
					}
					else{
						*estr.laQueMasEnvio = estr.red->Computadoras()[i];
					}
				}
			}
		}

		Lista<Buffer>::const_Iterador itBuffer = buffer.CrearIt();

		while( itBuffer.HaySiguiente() ) {
			ConjLog<Paquete*> *cjaMod = *estr.enEspera.obtener(itBuffer.Siguiente().compu->Ip());
			Paquete *paq = itBuffer.Siguiente().paquete;
			cjaMod->Definir(paq);
			itBuffer.Avanzar();
		}	
	}

	bool DCNet::IsPaqueteEnTransito(Paquete* p){
		//Lista<Compu>::const_Iterador it = estr.red->Computadoras().CrearIt(); //No anda el iterador de la list
		bool encontrado = false;
		Nat i = 0;
		while(i < estr.red->Computadoras().Longitud() && !encontrado)
		//for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
		{
			ConjLog<Paquete* >*conj  = *estr.enEspera.obtener(estr.red->Computadoras()[i].Ip());
			encontrado = conj->Pertenece(p);
			i++;
			//it.Avanzar();
		}

		return encontrado;
	}

	const Compu DCNet::LaQueMasEnvio() const{
		return *estr.laQueMasEnvio;
	}

	Lista<Paquete*> DCNet::TodosLosPaquetes(){
		return todos;
	}
}
