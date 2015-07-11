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
		//Lista<Compu>::Iterador it = estr.red->Computadoras().CrearIt();
		/*while(it.HaySiguiente()){ //NO ANDA EL ITERADOR DE LISTA ! ! 
			cout<<it.Siguiente().Ip()<<endl;
			//ConjLog<Paquete> cPaq;
			//estr.enEspera.definir(it.Siguiente().Ip(),cPaq);
			it.Avanzar();
		}*/
		for (Nat i = 0; i < estr.red->Computadoras().Longitud(); i++)
		{
			estr.enEspera.definir(estr.red->Computadoras()[i].Ip(),*new ConjLog<Paquete*>()); //TODO. Pierde memoria por cada creacion de un new Conj
			Nat aux =0;
			estr.cantPaquetesEnviados.definir(estr.red->Computadoras()[i].Ip(),aux);
			estr.CaminoRecorrido.definir(estr.red->Computadoras()[i].Ip(),*new DiccLog<Nat,Lista<Compu> >());
			//delete cPaq;
		}
	}
	DCNet::~DCNet(){
		//cout<<"destructor dcnet"<<endl;	
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
		DiccString<DiccLog<Nat,Lista<Compu> > >::Iterador *it = new DiccString<DiccLog<Nat,Lista<Compu> > >::Iterador(&estr.CaminoRecorrido);
		bool found = false;
		while(it->avanzar() && !found){
			DiccLog<Nat,Lista<Compu> > *paquetes = it->valorActual();
			if(paquetes->IsDefinido(p->Id())){
				found = true;
				res = paquetes->Significado(p->Id());
			}
		}
		return res;
	}

	const ConjLog<Paquete*> DCNet::EnEspera(const Compu& c){
		assert(estr.enEspera.definido(c.Ip()));
		return *estr.enEspera.obtener(c.Ip());
		//return *new ConjLog<Paquete*>();
	}

	void DCNet::CrearPaquete(Paquete* p){
		//TODO. ASSERT COMPU ORIGEN (Y DESTINO?)

		estr.enEspera.obtener(p->Origen().Ip())->Definir(p);
		estr.CaminoRecorrido.obtener(p->Origen().Ip())->Definir(p->Id(),*new Lista<Compu>());

	}


	void DCNet::AvanzarSegundo(){
		Lista<Compu>::Iterador it = estr.red->Computadoras().CrearIt();
		Lista<Buffer> buffer; 

		while( it.HaySiguiente() ) {

			ConjLog<Paquete*>* cPaq = estr.enEspera.obtener(it.Siguiente().Ip());
			if( cPaq->Cardinal() > 0 ) {
				Paquete* p = cPaq->Minimo();
				Conj<Lista<Compu> >::const_Iterador itComp = estr.red->CaminosMin(it.Siguiente(), p->Destino()).CrearIt();
				Lista<Compu> masCorto = itComp.Siguiente();
				masCorto.Fin();
				Compu pcaMover = masCorto.Primero();
				if( pcaMover == p->Destino() ) {
					cPaq->Borrar(p);
					estr.CaminoRecorrido.obtener(it.Siguiente().Ip())->Borrar(p->Id());
				} else {
					Buffer b;
					b.compu = &pcaMover;
					b.paquete = p;
					buffer.AgregarAtras( b );
					Lista<Compu> camino = estr.CaminoRecorrido.obtener(it.Siguiente().Ip())->Significado(p->Id());
					camino.AgregarAtras(pcaMover);
					estr.CaminoRecorrido.obtener(pcaMover.Ip())->Definir(p->Id(), camino);
					cPaq->Borrar(p);
					estr.CaminoRecorrido.obtener(it.Siguiente().Ip())->Borrar(p->Id());
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
			ConjLog<Paquete*> cjaMod = *estr.enEspera.obtener(itBuffer.Siguiente().compu->Ip());
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
			encontrado = estr.enEspera.obtener(it.Siguiente().Ip())->Pertenece(p);
			it.Avanzar();
		}

		return encontrado;
	}

	const Compu DCNet::LaQueMasEnvio() const{
		return estr.laQueMasEnvio.Siguiente();
	}
}
