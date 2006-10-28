/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2005 Indigente


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
#ifndef CAMERAFP_H_
#define CAMERAFP_H_

#include "ICamera.h"

namespace InGE{

	class CameraFP : public InGE::ICamera{
		private:
			Vector3 checkColision(const Vector3 &start,const Vector3 &target);
		
		public:
			CameraFP();
			CameraFP(Vector3 position, Vector3 viewPoint, Vector3 up);
			~CameraFP();
			void setDirection(const Vector3 &direction);
			void setStrafe(const Vector3 &strafe );
			void setAttachPosition(const Vector3 &attach);
			void setAttachAxis(const Vector3 &attach);
		
			// Rotacionar
			void setViewByPointer(int pointerX,int pointerY);
			void rotate(float angle, Vector3 &axis);
			void rotate( Vector4 &axis );
			// Mover
			void setPosition(const Vector3 &position);
			void move(const Vector3 &target);
			
			Vector3 getDirection();
			Vector3 getStrafe();
			Vector3 getAttachPosition();
			Vector3 getAttachAxis();
			
			VolumeInfo *pGetVolumeInfo();
			
	};

};
#endif /*CAMERAFP_H_*/
