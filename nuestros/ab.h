#ifndef PAQUETE_H
#define PAQUETE_H

#include "../aed2.h"

namespace dcnet {

    template<class T>
    class Ab {
        
        public:

            //Miembros definidos en el módulo

            Ab<T>();

            ~Ab<T>();

            static const Ab<T>& Bin(const Ab<T>& i,const T e ,const Ab<T> d);

            Nat Tamano() const;

            bool IsNil() const;

            T& Raiz() const;

            const Ab& Izq() const;

            const Ab& Der() const;

        private:

            

    };

}
#endif //PAQUETE_H
