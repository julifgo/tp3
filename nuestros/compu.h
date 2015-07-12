/*
/ Desc: Clase para representar una computadora
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

#ifndef DC_COMPU_H_
#define DC_COMPU_H_

#include <ostream>

using namespace aed2;

namespace dcnet{

	typedef Nat Interfaz;
	typedef String IP;

	class Compu{

		private:

			IP ip;

			Conj<Interfaz>* interfaces;

		public:

			Compu(const IP);
			
			Compu(const Compu&);
			
			~Compu();
			
			const IP& Ip() const;
			
			const Conj<Interfaz>& Interfaces() const;
			
			void AgInterfaz(const Interfaz);
			
			Compu& operator=(const Compu&);
			
			bool operator==(const Compu&) const;
			
			bool operator!=(const Compu&) const;
	
	};

	std::ostream& operator<<(std::ostream&, const Compu&);

}

#endif
