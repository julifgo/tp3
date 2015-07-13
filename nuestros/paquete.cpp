#include "paquete.h"

namespace dcnet {

    //Constructores ----------------------------------
    
    Paquete::Paquete(Paquete& otro) {
        *this = otro;
    }

    Paquete::Paquete(Nat id, Nat prioridad, const Compu& origen, const Compu& destino) {
        //Nosotros guardamos referencias de las computadoras, no tiene sentido que exista un paquete cuyo origen y destino no existe.
    	this->_id = id;
    	this->_prioridad = prioridad;
    	this->_origen = &origen;
    	this->_destino = &destino;
    }

    //Destructor -------------------------------------

    Paquete::~Paquete() {

    }
    
    //Getters ----------------------------------------

    const Nat Paquete::Id() const {
        return this->_id;
    }

    Nat Paquete::Prioridad() const {
        return this->_prioridad;
    }

    const Compu& Paquete::Origen() const {
        return *this->_origen;
    }

    const Compu& Paquete::Destino() const {
        return *this->_destino;
    }

    //Operadores -------------------------------------

    bool Paquete::operator<(const Paquete& otro) const {
    	return this->_prioridad < otro.Prioridad() || this->_id < otro.Id();
    }

    bool Paquete::operator>(const Paquete& otro) const {
        return !(this->_prioridad < otro.Prioridad() || this->_id < otro.Id()) && !(otro == *this);
    }

    Paquete& Paquete::operator=(const Paquete& paquete) {
        //Incluso en el operador de copia del paquete, se copian el id y la prioridad a nuevas posiciones de memoria, pero los campos para origen y destino siguen guardando referencias a las computadoras originales.
		this->_id = paquete.Id();
		this->_prioridad = paquete.Prioridad();
		this->_origen = paquete._origen;
		this->_destino = paquete._destino;
		return *this;
	}

	bool Paquete::operator==(const Paquete& otro) const {
		return this->_id == otro.Id() && this->_prioridad == otro.Prioridad() && *this->_origen == otro.Origen() && *this->_destino == otro.Destino();
	}

    std::ostream& operator<<(std::ostream& os, const Paquete& p) {
        return os << p.Id() << " " << p.Prioridad() << " " << p.Origen() << " " << p.Destino();
    }

}
