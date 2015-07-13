#include "Driver.h"
#include "ArbolSintactico.h"

using namespace dcnet;

namespace aed2 {

Driver::Driver(): red(new Red()), dcnet(NULL), _id(0) {}

Driver::~Driver() {
    delete dcnet;
    delete red;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return this->red->Computadoras().Longitud();
}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    assert( i < CantidadComputadoras() );
    const Computadora *res = new Computadora(red->Computadoras()[i].Ip());
   // aBorrar.AgregarAdelante(res); TODO: CHECKLEAK
    return *res;
 //   return red->Computadoras()[i].Ip();
}
     
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    return dameCompu(c).Interfaces().Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, Nat i) const {
    assert(i < dameCompu(c).Interfaces().Cardinal());

    Conj<Interfaz>::const_Iterador it = dameCompu(c).Interfaces().CrearIt();
  //  dameCompu(c).Interfaces().Pertenece(i); PERTENECE PERO ME DEVUELVE BASURA, FALLA ITERADOR
    while(i-- > 0) {
        it.Avanzar();
    }
    return it.Siguiente();
}

const Interfaz& Driver::InterfazUsada(const Computadora& c1, const Computadora& c2) const {
    return this->red->InterfazUsada(dameCompu(c1), dameCompu(c2));
}

void Driver::Conectar(const Computadora& c1, Interfaz& i1, const Computadora& c2, Interfaz& i2){
    this->red->Conectar(dameCompu(c1),dameCompu(c2),i1,i2);
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return this->red->Conectadas(dameCompu(c1), dameCompu(c2));
}



// TAD DCNET
Nat Driver::CantidadEnviadosPor(const Computadora& c){
     return dcnet->CantidadEnviados(c);
}

Nat Driver::CantidadEnEsperaEn(const Computadora& c){
    const ConjLog<dcnet::Paquete*>* paquetesEnEspera = dcnet->EnEspera(c);
    return paquetesEnEspera->Cardinal();
}

const Paquete Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i){
       const ConjLog<dcnet::Paquete*>* paquetesEnEspera = dcnet->EnEspera(c);
       assert(i < paquetesEnEspera->Cardinal());
       ConjLog<dcnet::Paquete*> paquetes = *paquetesEnEspera; //TODO. Asegurarse que esto este haciendo una copia.
       Nat j = 0;
       while(j<i){
            dcnet::Paquete* paq = paquetes.Minimo();
            paquetes.Borrar(paq);
            j++;
       }
       dcnet::Paquete paqReturn = *paquetes.Minimo();
       return paqReturn.Id();
}

void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    Compu c(ip);

    Conj<Interfaz>::const_Iterador it = ci.CrearIt();

    while(it.HaySiguiente()) {
        c.AgInterfaz(it.Siguiente());
        it.Avanzar();
    }

    this->red->AgCompu(c);
}

Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
    assert(dcnet != NULL);
    
    return this->dcnet->CaminoRecorrido(p).Longitud();
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    if (this->dcnet == NULL) {
        this->dcnet = new DCNet(*red);
    }

    dcnet::Paquete* p = new dcnet::Paquete(_id, prioridad, dameCompu(origen), dameCompu(destino));

    this->dcnet->CrearPaquete( p );
    _id++;
}

const Computadora& Driver::laQueMasEnvio() const {
    return this->dcnet->LaQueMasEnvio().Ip();
}

Nat Driver::prioridad(const Paquete& p) const {
	 assert(dcnet != NULL);
	 return FindPaquete(p).Prioridad();
}

const Computadora& Driver::origen(const Paquete& p) const {
	 assert(dcnet != NULL);
	 return FindPaquete(p).Origen().Ip();
}

const Computadora& Driver::destino(const Paquete& p) const {
	 assert(dcnet != NULL);
	 return FindPaquete(p).Destino().Ip();
}

const Compu Driver::dameCompu(const Computadora& c) const {
    Nat i = 0;

    while(i < red->Computadoras().Longitud() && red->Computadoras()[i].Ip() != c) { i++; }

    return red->Computadoras()[i];
}

void Driver::AvanzarSegundo(){
	if (this->dcnet == NULL) {
		this->dcnet = new DCNet(*red);
	}
	dcnet->AvanzarSegundo();
}

const dcnet::Paquete& Driver::FindPaquete(const Paquete& p) const {
    assert(dcnet != NULL);
    Lista<Compu>::const_Iterador it1 = red->Computadoras().CrearIt();
    while (it1.HaySiguiente()) {
        ConjLog<dcnet::Paquete*> conjLog = *dcnet->EnEspera(it1.Siguiente());
        //Conj<paquete>::const_Iterador it2 = cola.CrearIt();
        while (conjLog.Cardinal()>0) {
            if (conjLog.Minimo()->Id() == p) {
                return *conjLog.Minimo();
            }
            conjLog.Borrar(conjLog.Minimo());
        }
        it1.Avanzar();
    }
}


} // namespace aed2
