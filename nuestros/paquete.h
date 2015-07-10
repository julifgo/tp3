#ifndef PAQUETE_H
#define PAQUETE_H

#include "../aed2.h"
#include "compu.h"

namespace dcnet {

    class Paquete {
        
        public:

            //Miembros definidos en el módulo

            Nat Id() const;

            Nat Prioridad() const;

            const Compu& Origen() const;

            const Compu& Destino() const;

            Paquete(Nat id, Nat prioridad, const Compu& origen, const Compu& destino);

            ~Paquete();
           
            bool operator<(const Paquete& otro) const;

            bool operator>(const Paquete& otro) const;

            Paquete& operator=(const Paquete& paquete);

            //Miembros faltantes

            bool operator==(const Paquete& otro) const;

        private:

            Nat _id;

            Nat _prioridad;

            const Compu* _origen;

            const Compu* _destino;

    };

    std::ostream& operator<<(std::ostream&, const Paquete&);

}
#endif //PAQUETE_H
