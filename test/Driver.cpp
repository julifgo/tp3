#include "Driver.h"
#include "ArbolSintactico.h"

using namespace dcnet;

namespace aed2 {

Driver::Driver() {
    this->red = new Red();
    this->dcnet = new DCNet( *this->red );
}

Driver::~Driver() {
    delete red;
    delete dcnet;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return this->red->Computadoras().Longitud();
}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    assert( i < CantidadComputadoras() );

    return this->red->Computadoras()[i].Ip();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {

    cout << dameCompu(c) << endl;


    return dameCompu(c).Interfaces().Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, Nat i) const {
    assert(i < dameCompu(c).Interfaces().Cardinal());

    Conj<Interfaz>::const_Iterador it = dameCompu(c).Interfaces().CrearIt();
    while(i-- > 0) {
        it.Avanzar();
    }
    return it.Siguiente();
}

const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    return this->red->InterfazUsada(dameCompu(c1), dameCompu(c2));
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return this->red->Conectadas(dameCompu(c1), dameCompu(c2));
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    Compu c(ip);

    Conj<Interfaz>::const_Iterador it = ci.CrearIt();

    while(it.HaySiguiente()) {
        c.AgInterfaz(it.Siguiente());
        it.Avanzar();
    }

    this->red->AgCompu(c);
}
        
const Compu Driver::dameCompu(const Computadora& c) const {
    Nat i = 0;

    while(i < red->Computadoras().Longitud() && red->Computadoras()[i].Ip() != c) { i++; }

    return red->Computadoras()[i];
}

} // namespace aed2