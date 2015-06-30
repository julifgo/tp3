#include "compu.h"

namespace aed2 {

	Nat Compu::ip() const {
		return this->_ip;
	}

	const Conj<Nat>& Compu::interfaces() const {
		return *this->_interfaces;
	}

	Compu::Compu(Nat const& ip) {
		this->_ip = ip;
		this->_interfaces = new Conj<Nat>();
	}

	Compu::~Compu() {

	}

	void Compu::agInterfaz(Nat const& interfaz) {
		this->_interfaces->AgregarRapido(interfaz);
	}

	bool Compu::operator==(const Compu& otro) const {
		return this->_ip == otro.ip();
	}

	Compu& Compu::operator=(const Compu& compu) {
		*this->_interfaces = compu.interfaces();
		this->_ip = compu.ip();
		return *this;
	}


}