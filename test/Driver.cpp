#include "Driver.h"
#include "ArbolSintactico.h"

using namespace dcnet;

namespace aed2 {

Driver::Driver(){
    red = new Red();
    dcnet = new DCNet(*red);
}

//Driver::Driver(): red(Red()), dcnet(DCNet(red)) {}

Driver::~Driver() {
    // TODO
    //acá iria el destructor de red y/o dcnet entre otras cosas
}

// TAD RED
/*Nat Driver::CantidadComputadoras() const {
    return red->Computadoras().Longitud();
}*/

/*const Computadora Driver::IesimaComputadora(const Nat i) const {
    assert( i < CantidadComputadoras() );
    return red->Computadoras()[i].Ip();
}*/
        
/*Nat Driver::CantidadInterfacesDe(const Computadora& c) {
    return dameCompu(c).Interfaces().Cardinal();
}*/

//const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, /*const*/ Nat i) const{ //Error decrement of readonly parameter
/*    assert(i < dameCompu(c).Interfaces().Cardinal());
    //Conj<Compu>::const_Iterador it = dameCompu(c).Interfaces().CrearIt(); //Interfaces es de tipo Interfaz
    Conj<Interfaz>::const_Iterador it = dameCompu(c).Interfaces().CrearIt();
    while(i-- > 0) {
        it.Avanzar();
    }
    return it.Siguiente();
} */

///*const*/ Interfaz Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) /*const*/ {
  //  return red->InterfazUsada(dameCompu(c1), dameCompu(c2));
//}

/*bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return red->Conectadas(dameCompu(c1), dameCompu(c2));
}*/

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    // TODO
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    // TODO
}
	
	
/*Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
    // TODO
    return 0;
}*/

/*const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const {
    // TODO
}*/

/*Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    // TODO
    return 0;
}*/
	
/*Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}*/

/*const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {
    // TODO
    return 0;
}*/

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    // TODO
}
		
void Driver::AvanzarSegundo() {
    // TODO
}
		
/*const Computadora& Driver::laQueMasEnvio() const {
    // TODO	
    return "0";
}*/

/*const Computadora& Driver::origen(const Paquete& p) const {
    // TODO	
    return 0;
} */

/*const Computadora& Driver::destino(const Paquete& p) const { 
    // TODO	
    return 0;
}*/

/*Nat Driver::prioridad(const Paquete& p) const { 
    // TODO	
    return 0;
}*/
		
const Compu& Driver::dameCompu(const Computadora& c) const{
    Lista<Compu>::const_Iterador it = red->Computadoras().CrearIt();
    while(it.Siguiente().Ip() != c) {
        it.Avanzar();   
    }
    return it.Siguiente();
}

} // namespace aed2

