#ifndef PAQUETE_H
#define PAQUETE_H

#include "../aed2/TiposBasicos.h"
#include "compu.h"

namespace aed2 {

    class Paquete {
        
        public:

            //Miembros definidos en el módulo

            Nat id() const;

            Nat prioridad() const;

            const Compu& origen() const;

            const Compu& destino() const;

            Paquete(Nat id, Nat prioridad, const Compu& origen, const Compu& destino);

            ~Paquete();
           
            bool operator<(const Paquete& otro) const;

            Paquete& operator=(const Paquete& paquete);

            //Miembros faltantes

            bool operator==(const Paquete& otro) const;

        private:

            Nat _id;

            Nat _prioridad;

            Compu* _origen;

            Compu* _destino;

    };

}
#endif //PAQUETE_H
