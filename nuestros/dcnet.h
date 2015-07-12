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

			struct colasEspera{
				ConjLog<int> *paquetes;

				colasEspera(){
					//paquetes = new ConjLog<int>();
				}

				~colasEspera()
				{
					//return;
					cout<<"Destrucvtor colas"<<endl;
				}
			};

			struct estr{
				/*const */Red* red;
				DiccString<Nat> cantPaquetesEnviados;
				Lista<Compu>::Iterador laQueMasEnvio;
				DiccString<DiccLog<Nat,Lista<Compu> > > CaminoRecorrido;
				DiccString<ConjLog<int > > enEspera;
				//DiccString<ConjLog<Paquete* > > enEspera;1
				//DiccString<colasEspera > enEspera;

			};

			struct Buffer{
				Buffer(){};
				Compu* compu;
				Paquete* paquete;
			};

			estr estr;
			colasEspera colas;
		public:
			DCNet();
			DCNet(Red& red);//Equivalente a IniciarDCNEt
			~DCNet();
			const Red& red() const;
			Nat CantidadEnviados(const Compu& c) /*const*/; //TODO. El acceso a Dicc trie no nos deja poner const
			const Lista<Compu> CaminoRecorrido(Paquete* p);
			const ConjLog<Paquete*> EnEspera(const Compu& c);
			void CrearPaquete(Paquete* p);
			void AvanzarSegundo();
			bool IsPaqueteEnTransito(Paquete* p); //retiro const porque obtemer del dicc_trie no se lo banca
			const Compu LaQueMasEnvio() const;
	};
}
#endif
