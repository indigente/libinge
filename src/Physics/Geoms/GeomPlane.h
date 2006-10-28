/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2005 Indigente


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
#ifndef GEOMPLANE_H
#define GEOMPLANE_H

#include "../PhysicalGeom.h"
#include "../PhysicalSpace.h"
#include "../../Math/Vector4.h"
#include "../../Math/Vector3.h"

namespace InGE{
	
		
	class GeomPlane : public InGE::PhysicalGeom{
		public:
		
			GeomPlane();
			GeomPlane(Vector3 normal, float d, PhysicalSpace *ps=NULL);
			GeomPlane(Vector4 plane, PhysicalSpace *ps=NULL);
			virtual ~GeomPlane();
			
			void setParams(const Vector4 &plane);
			void setParams(const Vector3 &plane, float d);
			Vector4 getParams();
			float pointDepth(const Vector3 &point);
			void setData(void *data);
	};

};
#endif // GEOMPLANE_H
