/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004 Indigente


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.BEZIER_PATCH

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef ISCENE_H
#define ISCENE_H
#include "../../Math/Vector3.h"
#include "../../Physics/PhysicalSpace.h"
#include "../../Physics/PhysicalGeom.h"
#include "../../Physics/PhysicalContactPoint.h"
#include "../Render/Frustum.h"
#include <vector>


namespace InGE{	
	using std::vector;

	struct MoveData{
		Vector3 endPoint;
		Vector3	normal;
		float 	depth;
		bool allSolid;
		bool startOut;
	};
	
	class IScene{
		public:
			IScene(){};
			virtual ~IScene(){};
			virtual void renderLevel(Vector3 camera, Frustum &frutum) = 0;
			
			virtual PhysicalContactPoint &checkMoveCollision(Vector3 start, Vector3 end, PhysicalGeom *geom = NULL) = 0;
			virtual PhysicalContactPoint &checkMoveCollisionAndTrySlide(Vector3 start, Vector3 end, PhysicalGeom *geom = NULL) = 0;
		
	};

};

#endif // ISCENE_H
