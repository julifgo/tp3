#include <iostream>
#include "../aed2.h"
#include "compu.h"

using namespace aed2;
using namespace std;

namespace dcnet{

		//Constructores ----------------------------------

		Compu::Compu(const IP ip) {
			this->ip = ip;
			this->interfaces = new Conj<Interfaz>();
		}

  		Compu::Compu(const Compu& otra) {
  			*this = otra;
  		}

  		//Destructor -------------------------------------

		Compu::~Compu() { 
			delete this->interfaces;
		}

		//Getters ----------------------------------------

		const IP& Compu::Ip() const {
			return this->ip;
		}

		const Conj<Interfaz>& Compu::Interfaces() const {
			return *this->interfaces;
		}

		//Setters ----------------------------------------

		void Compu::AgInterfaz(const Interfaz interfaz) {
			//assert(!estr.interfaces.Pertenece(interfaz));

			this->interfaces->AgregarRapido(interfaz);
		}

		//Operadores -------------------------------------

  		Compu& Compu::operator=(const Compu& otra) {
  			this->ip = otra.Ip();

			//delete this->interfaces; //La posición pudo estar previamente seteada.
  			
  			this->interfaces = new Conj<Interfaz>(otra.Interfaces());

  			return *this;
  		}

  		bool Compu::operator==(const Compu& otra) const {
  			return this->ip == otra.Ip() && *this->interfaces == otra.Interfaces();
  		}

  		bool Compu::operator!=(const Compu& otra) const {
  		  	return !(this->ip == otra.Ip() && *this->interfaces == otra.Interfaces());
  		}

		std::ostream& operator<<(std::ostream& os, const Compu& c) {
		  	return os << c.Ip();
		}

}
