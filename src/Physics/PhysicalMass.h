/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004-2005 Indigente

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#ifndef PHYSICALMASS_H
#define PHYSICALMASS_H
#include "../Math/Vector4.h"
#include <ode/ode.h>

namespace InGE{
	
	class PhysicalMass{
		dMass	m_mass;
		public:

			PhysicalMass(float mass){m_mass.mass = mass;};
			PhysicalMass(float mass, Vector4 &center, float *inertia){
				setMass(mass); 
				setInertia(inertia);
				setCenter(center);
			};
						
			~PhysicalMass(){};
			
			void setMass(float mass){ m_mass.mass = mass;};
			void setCenter(Vector4 &center){ 
				m_mass.c[0] = center[0]; 
				m_mass.c[1] = center[1];
				m_mass.c[2] = center[2];
				m_mass.c[3] = center[3]; 
			};
			void setInertia(float *inertia){
				if(!inertia) return;
				m_mass.I[0] = inertia[0]; m_mass.I[1] = inertia[1];
				m_mass.I[2] = inertia[2]; m_mass.I[3] = inertia[3];
				m_mass.I[4] = inertia[4]; m_mass.I[5] = inertia[5];
				m_mass.I[6] = inertia[6]; m_mass.I[7] = inertia[7];
				m_mass.I[8] = inertia[8]; m_mass.I[9] = inertia[9];
				m_mass.I[10] = inertia[10]; m_mass.I[11] = inertia[11];																				
			};
				
			
			dMass &getMass(){return m_mass;};
	};

};

#endif // PHYSICALMASS_H
