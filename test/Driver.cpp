#include "Driver.h"
#include "ArbolSintactico.h"

using namespace dcnet;

namespace aed2 {

Driver::Driver() {
    red = new Red();
    dcnet = new DCNet( *this->red );
}

//Driver::Driver(): red(Red()), dcnet(DCNet(red)) {}

Driver::~Driver() {
    delete red;
    delete dcnet;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return red->Computadoras().Longitud();
}

const Computadora Driver::IesimaComputadora(const Nat i) const {
    assert( i < CantidadComputadoras() );
    return red->Computadoras()[i].Ip();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) {
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

const Interfaz Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    return red->InterfazUsada(dameCompu(c1), dameCompu(c2));
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return red->Conectadas(dameCompu(c1), dameCompu(c2));
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    Compu c(ip);
    Conj<Interfaz>::const_Iterador it = ci.CrearIt();
    while(it.HaySiguiente()) {
        c.AgInterfaz(it.Siguiente());
        it.Avanzar();   
    }
    red->AgCompu(c);
}
    
/*    
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    // TODO
}
	
	
Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
    // TODO
    return 0;
}

const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const {
    // TODO
    return 0;
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    // TODO
    return 0;
}
	
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {
    // TODO
    return 0;
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    // TODO
}
		
void Driver::AvanzarSegundo() {
    // TODO
}
		
const Computadora& Driver::laQueMasEnvio() const {
    // TODO	
    return 0;
}

const Computadora& Driver::origen(const Paquete& p) const {
    // TODO	
    return 0;
}

const Computadora& Driver::destino(const Paquete& p) const { 
    // TODO	
    return 0;
}

Nat Driver::prioridad(const Paquete& p) const { 
    // TODO	
    return 0;
}*/
		
const Compu& Driver::dameCompu(const Computadora& c) const {
    Lista<Compu>::const_Iterador it = red->Computadoras().CrearIt();

    cout << red->Computadoras() << endl;
    cout << it.Siguiente() << endl;
    
    /*while(it.Siguiente().Ip() != c) {
        it.Avanzar();
    }*/
    return it.Siguiente();
}

} // namespace aed2

