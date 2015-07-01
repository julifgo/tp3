/*
/ Desc: Clase para representar una computadora
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

//PASAR IMPLEMENTACIONES A CPP

#ifndef DC_COMPU_H_
#define DC_COMPU_H_

#include <ostream>
using namespace aed2;
namespace dcnet{
	typedef Nat Interfaz;
	typedef String IP;

	class Compu{
	private:
		struct estr{
			IP ip;
			Conj<Interfaz> interfaces;
		};

		estr estr;

	public:
		//Equivalente en TP a operacion Crear(ip: ip)
		Compu(const IP ip){
			estr.ip = ip; 
			estr.interfaces;
		}
		/// Crea por copia una compu (operación Copiar())
  		Compu(const Compu& otra){
  			this->estr.ip = otra.estr.ip;
  			this->estr.interfaces = Conj<Interfaz>(otra.estr.interfaces);
  		}
		~Compu(){
			//Nada?
		}
		const IP Ip() const{
			return this->estr.ip;
		}
		const Conj<Interfaz>& Interfaces() const{ //Se devuelve res como referencia a las interfaces pero no son modificables
			return this->estr.interfaces;
		} 
		void AgInterfaz(const Interfaz interfaz){
			this->estr.interfaces.AgregarRapido(interfaz);
		}
		/// Operacion de igualdad entre dos compus
  		bool operator==(const Compu& otra){
  			return this->estr.ip == otra.estr.ip;
  		}

  	
	};
}
#endif
