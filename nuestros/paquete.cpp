#include "paquete.h"

namespace dcnet {

    Nat Paquete::Id() const {
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

    Paquete::Paquete(Nat id, Nat prioridad, const Compu& origen, const Compu& destino) {
    	this->_id = id;
    	this->_prioridad = prioridad;
    	this->_origen = &origen;
    	this->_destino = &destino;
    }

    Paquete::~Paquete() {
    }

    bool Paquete::operator<(const Paquete& otro) const {
    	return this->_prioridad < otro.Prioridad() || this->_id < otro.Id();
    }

	Paquete& Paquete::operator=(const Paquete& paquete) {
		this->_id = paquete.Id();
		this->_prioridad = paquete.Prioridad();
		this->_origen = paquete._origen;
		this->_destino = paquete._destino;
		return *this;
	}

	bool Paquete::operator==(const Paquete& otro) const {
		return this->_id == otro.Id();
	}

    std::ostream& operator<<(std::ostream& os, const Paquete& p) {
        os << p.Id() << " " << p.Prioridad() << " " << p.Origen() << " " << p.Destino(); 
        return os;
    }

}
