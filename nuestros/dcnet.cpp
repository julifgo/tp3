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
		//estr.cantPaquetesEnviados = DiccString<Nat>(); //TODO. Revisar esto con profe.
	}
	DCNet::~DCNet(){
			//TODO. IMPLEMENTAR.
	}

	const Red& DCNet::red() const{
		return *estr.red; 
	}

	Nat DCNet::CantidadEnviados(const Compu& c){
		Nat res = *estr.cantPaquetesEnviados.obtener(c.Ip());
		return res;
	}

	const Lista<Compu> DCNet::CaminoRecorrido(const Paquete& p) const{
		return Lista<Compu>(); //TODO. Implementar!
	}

	const Conj<Paquete> DCNet::EnEspera(const Compu& c) const{
		return Conj<Paquete>(); //TODO. Implementar!
	}

	void DCNet::CrearPaquete(const Paquete& p){

	}

	void DCNet::AvanzarSegundo(){

	}

	bool DCNet::IsPaqueteEnTransito(const Paquete& p) const{
		return true;
	}

	const Compu DCNet::LaQueMasEnvio() const{
		return estr.laQueMasEnvio.Siguiente();
	}
}
