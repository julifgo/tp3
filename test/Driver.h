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

        Nat CantidadComputadoras() const;

        const Computadora& IesimaComputadora(const Nat i) const ;
        
        Nat CantidadInterfacesDe(const Computadora& c) const;
        
        const Interfaz& IesimaInterfazDe(const Computadora& c, const Nat i) const ;

        const Interfaz& IntefazUsada(const Computadora& c1, const Computadora& c2) const;

        bool conectadas(const Computadora& c1, const Computadora& c2) const;

        /// Armado Red ////////////////////////////////////////////////////////////////

        void AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci);
        
        void Conectar(const Computadora& c1, Interfaz& i1, const Computadora& c2, Interfaz& i2);
    

       /// Observadores DCNet //////////////////////////////////////////////////////////////
    
        Nat CantidadNodosRecorridosPor(const Paquete& p) const;
        
        const Computadora& IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const;

        Nat CantidadEnviadosPor(const Computadora& c) const;
    
        Nat CantidadEnEsperaEn(const Computadora& c) const;
        
        const Paquete& IesimoEnEsperaEn(const Computadora& c, const Nat i) const;

        /// Acciones DCNet ////////////////////////////////////////////////////////////

        void CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad);
        
        void AvanzarSegundo();
        
        const Computadora& laQueMasEnvio() const;
        
        // Auxiliares para ver los paquetes
        const Computadora& origen(const Paquete& p) const; 
        
        const Computadora& destino(const Paquete& p) const; 
        
        Nat prioridad(const Paquete& p) const; 
        
    private:

        Red* red;
        
        DCNet* dcnet;

        const Compu dameCompu(const Computadora& c) const;

        Lista<Computadora*> aBorrar;

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
