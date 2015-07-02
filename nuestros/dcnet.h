/*
/
/ Desc: Clase para representar interfaz de dcnet
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

#ifndef DC_DCNET_H_
#define DC_DCNET_H_
//#include "../aed2.h"
#include "red.h"
#include <ostream>

using namespace aed2;

namespace dcnet{

	class DCNet{
		private:
			struct estr{
				Red red;
				//DiccString<int> cantPaquetesEnviados;
				//Lista<Compu>::Iterador it;
				//TODO. Faltan elementos aun no definidos
			};
			estr estr;
		public:
			DCNet(const Red& red);//Equivalente a IniciarDCNEt
			~DCNet();
	};
}
#endif