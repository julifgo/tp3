/*
/
/ Desc: Clase para representar interfaz de dcnet
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

#ifndef DC_DCNET_H_
#define DC_DCNET_H_
#include "../aed2.h"
#include "red.h"
#include "paquete.h"
#include "diccLog.h"
#include "conjLog.h"
#include <ostream>

using namespace aed2;

namespace dcnet{

	class DCNet{ //TODO. Ver diferencia entre in dcnet e inout dcnet
		private:
			struct estr{
				const Red* red;
				DiccString<Nat> cantPaquetesEnviados;
				Lista<Compu>::Iterador laQueMasEnvio;
				DiccString<DiccLog<Nat,Lista<Compu>>> CaminoRecorrido;
				DiccString<ConjLog<Paquete>> enEspera;
			};
			estr estr;
		public:
			DCNet();
			DCNet(const Red& red);//Equivalente a IniciarDCNEt
			~DCNet();
			const Red& red() const;
			Nat CantidadEnviados(const Compu& c) /*const*/; //TODO. El acceso a Dicc trie no nos deja poner const
			const Lista<Compu> CaminoRecorrido(const Paquete& p) const;
			const ConjLog<Paquete> EnEspera(const Compu& c);
			void CrearPaquete(const Paquete& p);
			void AvanzarSegundo();
			bool IsPaqueteEnTransito(const Paquete& p); //retiro const porque obtemer del dicc_trie no se lo banca
			const Compu LaQueMasEnvio() const;
	};
}
#endif
