#include <iostream>
#include "../aed2.h"
#include "compu.h"

using namespace aed2;

namespace dcnet{
	//Equivalente en TP a operacion Crear(ip: ip)
		Compu::Compu(const IP ip){
			estr.ip = ip; 
			estr.interfaces = Conj<Interfaz>();
		}
		/// Crea por copia una compu (operación Copiar())
  		Compu::Compu(const Compu& otra){
  			this->estr.ip = otra.estr.ip;
  			this->estr.interfaces = Conj<Interfaz>(otra.estr.interfaces);
  		}
		Compu::~Compu(){
			
		}
		const IP Compu::Ip() const{
			return this->estr.ip;
		}
		const Conj<Interfaz>& Compu::Interfaces() const{ //Se devuelve res como referencia a las interfaces pero no son modificables
			return this->estr.interfaces;
		} 
		void Compu::AgInterfaz(const Interfaz interfaz){
			this->estr.interfaces.AgregarRapido(interfaz);
		}
		/// Operacion de igualdad entre dos compus
  		bool Compu::operator==(const Compu& otra) const{
  			return this->estr.ip == otra.estr.ip;
  		}

  		bool Compu::operator!=(const Compu& otra) const{
  		  	return !(this->estr.ip == otra.estr.ip);
  		}
}
