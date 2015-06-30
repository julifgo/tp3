#include "paquete.h"

namespace aed2 {

    Nat Paquete::id() const {
    	return this->_id;
    }

   	Nat Paquete::prioridad() const {
    	return this->_prioridad;
    }

    const Compu& Paquete::origen() const {
    	return *this->_origen;
    }

    const Compu& Paquete::destino() const {
    	return *this->_destino;
    }

    Paquete::Paquete(Nat id, Nat prioridad, const Compu& origen, const Compu& destino) {
    	this->_id = id;
    	this->_prioridad = prioridad;
    	*this->_origen = origen;
    	*this->_destino = destino;
    }

    Paquete::~Paquete() {

    }

    bool Paquete::operator<(const Paquete& otro) const {
    	return this->_prioridad < otro.prioridad() || this->_id < otro.id();
    }

	Paquete& Paquete::operator=(const Paquete& paquete) {
		this->_id = paquete.id();
		this->_prioridad = paquete.prioridad();
		*this->_origen = paquete.origen();
		*this->_destino = paquete.destino(); 
		return *this;
	}

	bool Paquete::operator==(const Paquete& otro) const {
		return this->_id == otro.id();
	}

}