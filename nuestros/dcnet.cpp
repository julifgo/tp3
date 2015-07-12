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
		estr.laQueMasEnvio = estr.red->Computadoras().CrearIt();
		/*Lista<Compu>::Iterador it = estr.red->Computadoras().CrearIt();
		while(it.HaySiguiente()){ //NO ANDA EL ITERADOR DE LISTA. VER EN MAIN QUE LISTA DE RED ANDA PERFECTO !
			cout<<it.Siguiente().Ip()<<endl;
			//ConjLog<Paquete> cPaq;
			//estr.enEspera.definir(it.Siguiente().Ip(),cPaq);
			it.Avanzar();
		}*/
		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
		{
			ConjLog<Paquete*> *cPaq = new ConjLog<Paquete*>();
			colasPaquete.AgregarAtras(cPaq);
			estr.enEspera.definir(estr.red->Computadoras()[i].Ip(),cPaq);


			Nat aux = 0;
			estr.cantPaquetesEnviados.definir(estr.red->Computadoras()[i].Ip(),aux);

			DiccLog<Nat,Lista<Compu> >*cCamino = new DiccLog<Nat,Lista<Compu> >();
			colasCaminos.AgregarAtras(cCamino);
			estr.CaminoRecorrido.definir(estr.red->Computadoras()[i].Ip(),cCamino);
		}
	}
	DCNet::~DCNet(){
		cout<<"destructor dcnet"<<endl;
		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
        {
            delete colasPaquete.operator [](i);
            delete colasCaminos.operator [](i);
        }	
	}

	const Red& DCNet::red() const{
		return *estr.red; 
	}

	Nat DCNet::CantidadEnviados(const Compu& c){
		Nat res = *estr.cantPaquetesEnviados.obtener(c.Ip());
		return res;
	}

	const Lista<Compu> DCNet::CaminoRecorrido(Paquete* p){
		Lista<Compu> res;
		DiccString<DiccLog<Nat,Lista<Compu> >* >::Iterador *it = new DiccString<DiccLog<Nat,Lista<Compu> >* >::Iterador(&estr.CaminoRecorrido);
		bool found = false;
		while(it->avanzar() && !found){
			DiccLog<Nat,Lista<Compu> > *paquetes = *it->valorActual();
			if(paquetes->IsDefinido(p->Id())){
				found = true;
				res = paquetes->Significado(p->Id());
			}
		}
		return res;
	}

	const ConjLog<Paquete*> DCNet::EnEspera(const Compu& c){
		assert(estr.enEspera.definido(c.Ip()));
		return **estr.enEspera.obtener(c.Ip());
		//return *new ConjLog<Paquete*>();
	}

	void DCNet::CrearPaquete(Paquete* p){
		//TODO. ASSERT COMPU ORIGEN (Y DESTINO?)
		DiccLog<Nat,Lista<Compu> > *dicc = *estr.CaminoRecorrido.obtener(p->Origen().Ip());
		dicc->Definir(p->Id(),*new Lista<Compu>()); //TODO. Me juego la cabeza que esto va a leakear
		//delete dicc;
	}


	void DCNet::AvanzarSegundo(){
		Lista<Compu>::Iterador it = estr.red->Computadoras().CrearIt();
		Lista<Buffer> buffer; 

		while( it.HaySiguiente() ) {

			ConjLog<Paquete*>* cPaq ;//= estr.enEspera.obtener(it.Siguiente().Ip());
			if( cPaq->Cardinal() > 0 ) {
				Paquete* p = cPaq->Minimo();
				Conj<Lista<Compu> >::const_Iterador itComp = estr.red->CaminosMin(it.Siguiente(), p->Destino()).CrearIt();
				Lista<Compu> masCorto = itComp.Siguiente();
				masCorto.Fin();
				Compu pcaMover = masCorto.Primero();
				if( pcaMover == p->Destino() ) {
					cPaq->Borrar(p);
					DiccLog<Nat,Lista<Compu> > *dicc = *estr.CaminoRecorrido.obtener(it.Siguiente().Ip());
					dicc->Borrar(p->Id());
					//delete dicc;
				} else {
					Buffer b;
					b.compu = &pcaMover;
					b.paquete = p;
					buffer.AgregarAtras( b );
					DiccLog<Nat,Lista<Compu> > *dicc = *estr.CaminoRecorrido.obtener(it.Siguiente().Ip());
					Lista<Compu> camino = dicc->Significado(p->Id());
					camino.AgregarAtras(pcaMover);
					DiccLog<Nat,Lista<Compu> > *dicc2 = *estr.CaminoRecorrido.obtener(pcaMover.Ip());
					dicc2->Definir(p->Id(), camino);
					cPaq->Borrar(p);
					dicc->Borrar(p->Id());
					//delete dicc;
					//delete dicc2;
				}
				Nat enviados = (*estr.cantPaquetesEnviados.obtener(it.Siguiente().Ip()) + 1); //?

				if(enviados > *estr.cantPaquetesEnviados.obtener(estr.laQueMasEnvio.Siguiente().Ip()) ) {
					estr.laQueMasEnvio = it;
				}
			}

			it.Avanzar();
		}

		Lista<Buffer>::const_Iterador itBuffer = buffer.CrearIt();

		while( itBuffer.HaySiguiente() ) {
			ConjLog<Paquete*> cjaMod;// = *estr.enEspera.obtener(itBuffer.Siguiente().compu->Ip());
			Paquete *paq = itBuffer.Siguiente().paquete;
			cjaMod.Definir(paq);
			itBuffer.Avanzar();
		}	
	}

	bool DCNet::IsPaqueteEnTransito(Paquete* p){
		//TODO. sin testear, borrar cuando se pueda y se testee
		Lista<Compu>::const_Iterador it = estr.red->Computadoras().CrearIt();
		bool encontrado = false;
		while ( it.HaySiguiente() && !encontrado ) {
			//encontrado = estr.enEspera.obtener(it.Siguiente().Ip())->Pertenece(p);
			it.Avanzar();
		}

		return encontrado;
	}

	const Compu DCNet::LaQueMasEnvio() const{
		return estr.laQueMasEnvio.Siguiente();
	}
}
