#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "../aed2/TiposBasicos.h"
#include "../nuestros/dcnet.h"

using namespace dcnet;

namespace aed2 {

class Driver
{
    public:

        Driver();

        ~Driver();

        /// Observadores Red //////////////////////////////////////////////////////////

        Nat CantidadComputadoras() const; //listo

        const Computadora IesimaComputadora(const Nat i) const ; //listo
        
        Nat CantidadInterfacesDe(const Computadora& c) const; //listo
        
        const Interfaz IesimaInterfazDe(const Computadora& c, const Nat i) const ; //listo

        const Interfaz& InterfazUsada(const Computadora& c1, const Computadora& c2) const; //listo

        bool conectadas(const Computadora& c1, const Computadora& c2) const; //listo

        /// Armado Red ////////////////////////////////////////////////////////////////

        void AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci); //listo
        
        void Conectar(const Computadora& c1, Interfaz& i1, const Computadora& c2, Interfaz& i2); //listo
    

       /// Observadores DCNet //////////////////////////////////////////////////////////////
    
        Nat CantidadNodosRecorridosPor(const Paquete& p) const; //listo
        
        const Computadora IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const; //listo

        Nat CantidadEnviadosPor(const Computadora& c); //listo
    
        Nat CantidadEnEsperaEn(const Computadora& c); //listo
        
        const Paquete IesimoEnEsperaEn(const Computadora& c, const Nat i); //listo

        /// Acciones DCNet ////////////////////////////////////////////////////////////

        void CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad); //listo
        
        void AvanzarSegundo(); //listo
        
        const Computadora& laQueMasEnvio() const; //listo
        
        // Auxiliares para ver los paquetes
        const Computadora& origen(const Paquete& p) const; //listo
        
        const Computadora& destino(const Paquete& p) const; //listo
        
        Nat prioridad(const Paquete& p) const; //listo
        
    private:

        Red* red;
        
        DCNet* dcnet;

        Nat _id;

        const Compu& dameCompu(const Computadora& c) const;

        const dcnet::Paquete& FindPaquete(const Paquete& p) const;


        Lista<Computadora*> aBorrar;

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
