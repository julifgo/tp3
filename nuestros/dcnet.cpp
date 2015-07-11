#include <ostream>
#include <string>
#include "../aed2.h"
#include "paquete.h"
#include "dcnet.h"

using namespace aed2;
using namespace std;

namespace dcnet{

	DCNet::DCNet(){}
	DCNet::DCNet(const Red& red){
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
		cout<<"destructor dcnet"<<endl;
			
	}

	const Red& DCNet::red() const{
		return *estr.red; 
	}

	Nat DCNet::CantidadEnviados(const Compu& c){
		Nat res = *estr.cantPaquetesEnviados.obtener(c.Ip());
		return res;
	}

	const Lista<Compu> DCNet::CaminoRecorrido(Paquete* p) const{
		return Lista<Compu>(); //TODO. Implementar!
	}

	const ConjLog<Paquete*> DCNet::EnEspera(const Compu& c){
		assert(estr.enEspera.definido(c.Ip()));
		return *estr.enEspera.obtener(c.Ip());
	}

	void DCNet::CrearPaquete(Paquete* p){
		ConjLog<Paquete*> *cPaq = estr.enEspera.obtener(p->Origen().Ip());
		cPaq->Definir(p);
	}

	void DCNet::AvanzarSegundo(){
		cout<<"Area test provisoria"<<endl;
		cout<<"en espera iniciando bien: "<<estr.enEspera.definido("0")<<endl;
	}

	bool DCNet::IsPaqueteEnTransito(Paquete* p){
		//listo, sin testear, borrar cuando se pueda y se testee

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
