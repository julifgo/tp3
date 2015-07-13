#ifndef PAQUETE_H
#define PAQUETE_H

#include "../aed2.h"
#include "compu.h"

namespace dcnet {

    class Paquete {
        
        public:

            const Nat Id() const;

            Nat Prioridad() const;

            const Compu& Origen() const;

            const Compu& Destino() const;

            Paquete(Paquete&);

            Paquete(Nat, Nat, const Compu&, const Compu&);

            ~Paquete();
           
            bool operator<(const Paquete&) const;

            bool operator>(const Paquete&) const;

            Paquete& operator=(const Paquete&);

            bool operator==(const Paquete&) const;

        private:

            Nat _id;

            Nat _prioridad;

            const Compu* _origen;

            const Compu* _destino;

    };

    std::ostream& operator<<(std::ostream&, const Paquete&);

}
#endif //PAQUETE_H
