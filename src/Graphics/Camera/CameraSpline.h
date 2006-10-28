/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2006 Indigente


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
#ifndef INGECAMERASPLINE_H
#define INGECAMERASPLINE_H
#include <SDL/SDL.h>
#include "ICamera.h"
#include "../../Math/Spline.h"
#include "../../Math/Vector3.h"

namespace InGE {
	
	/**
	@author Beto
	*/
	class CameraSpline : public InGE::ICamera{
		protected:
			Spline *m_pPositionSpline;
			Spline *m_pViewPontSpline;
		
			float m_timePosition;
			float m_timeViewPoint;
	
			float m_speed;
		
			float interpolation(bool select);
		
		public:
			CameraSpline( Spline *pPosition, Spline *pViewPoint,float speed );
			virtual ~CameraSpline();
		
			Vector3 getPosition();
			Vector3 getViewPoint();
			
			virtual void setDirection(const Vector3 &direction){};
			virtual void setStrafe(const Vector3 &strafe ){};
			virtual void setAttachPosition(const Vector3 &attach){};
			virtual void setAttachAxis(const Vector3 &attach){};
				
			// Rotacionar
			virtual void setViewByPointer(int pointerX,int pointerY) {};
			virtual void rotate(float angle, Vector3 &axis){};
			virtual void rotate( Vector4 &axis ){};
			
			// Mover
			virtual void move(const Vector3 &direction){};
		
			virtual VolumeInfo *pGetVolumeInfo() {};
			
			virtual Vector3 getDirection() {};
			virtual Vector3 getStrafe() {};
			virtual Vector3 getAttachPosition() {};
			virtual Vector3 getAttachAxis() {};	
		
	};

};

#endif
