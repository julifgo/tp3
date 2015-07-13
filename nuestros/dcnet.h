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
#include "compu.h"
#include "paquete.h"

using namespace aed2;

namespace dcnet{

	class DCNet{ 
		private:

			

			struct estr{
				/*const */Red* red;
				DiccString<Nat> cantPaquetesEnviados;
				//Lista<Compu>::Iterador laQueMasEnvio; //ITERADOR NO FUNCIONA,SE CAMBIO POR PUNTERO A CPU
				Compu* laQueMasEnvio;
				DiccString<DiccLog<Nat,Lista<Compu>* >* > CaminoRecorrido;
				DiccString<ConjLog<Paquete* >* > enEspera;
			};

			struct Buffer{
				Compu* compu;
				Paquete* paquete;
			};

			estr estr;
			Lista<ConjLog<Paquete*>* > colasPaquete;
			Lista<DiccLog<Nat,Lista<Compu>* >* > colasCaminos;
			Lista<Lista<Compu>*> colasRecorridos;
			Lista<Paquete*> todos;
		public:
			DCNet();
			DCNet(Red& red);//Equivalente a IniciarDCNEt
			~DCNet();
			const Red* red() const;
			Nat CantidadEnviados(const Compu& c) /*const*/; //TODO. El acceso a Dicc trie no nos deja poner const
			const Lista<Compu> CaminoRecorrido(Paquete* p);
			const Lista<Compu> CaminoRecorrido(Nat id);
			const ConjLog<Paquete*>* EnEspera(const Compu& c) /*const*/; //TODO. El acceso a Dicc trie no nos deja poner const;
			void CrearPaquete(Paquete* p);
			void AvanzarSegundo();
			bool IsPaqueteEnTransito(Paquete* p); //retiro const porque obtemer del dicc_trie no se lo banca
			const Compu LaQueMasEnvio() const;
			Lista<Paquete*> TodosLosPaquetes();

	};
}
#endif
