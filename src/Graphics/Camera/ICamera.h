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

#ifndef ICAMERA_H
#define ICAMERA_H
#include <SDL/SDL.h>
#include "../../Math/Vector3.h" 
#include "../../Math/Vector4.h" 
#include "../../Control/IControlLayerListener.h"
#include "../../Control/controlEnum.h"
#include "../Base/VolumeInfo.h"
#include "../../Entities/IEntity.h"

namespace InGE{

	/**
	* Classe ICamera 
	* Representa Camera.
	* @author Ivan Medeiros Monteiro
	*/
	class ICamera : public InGE::IEntity{
		protected:
			Vector3		m_position;		// Posicao da camera 
			Vector3		m_viewPoint;		// Ponto de visao da camera
			Vector3		m_up;			// Vetor cabeca da camera
			
			VolumeInfo 	*m_pVolumeInfo;		// Informa�o sobre o volume da camera
			
		public:
			ICamera();
			ICamera(Vector3 position, Vector3 viewPoint, Vector3 up);
			virtual ~ICamera();
			
			//Metodos Set
			virtual void setPosition(const Vector3 &position);
			virtual void setVelocity(const Vector3 &v) {}; // de IEntity
			virtual void setViewPoint(const Vector3 &viewPoint);
			virtual void setUp(const Vector3 &up);
			
			virtual void setDirection(const Vector3 &direction) = 0;
			virtual void setStrafe(const Vector3 &strafe ) = 0;
			virtual void setAttachPosition(const Vector3 &attach) = 0;
			virtual void setAttachAxis(const Vector3 &attach) = 0;
			
			virtual void setViewByPointer(int pointerX,int pointerY) = 0;
			// Rotacionar
			virtual void rotate(float angle, Vector3 &axis) = 0;
			virtual void rotate( Vector4 &axis ) = 0;
			
			// Mover
			virtual void move(const Vector3 &direction) = 0;
		
			//Metodos Get
			virtual Vector3 getPosition();
			virtual Vector3 getViewPoint();
			virtual Vector3 getUp();
			
			virtual VolumeInfo *pGetVolumeInfo() = 0;
			
			virtual Vector3 getVelocity() {}; // de IEntity
			virtual Vector3 getDirection() = 0;
			virtual Vector3 getStrafe() = 0;
			virtual Vector3 getAttachPosition() = 0;
			virtual Vector3 getAttachAxis() = 0;
			
			TiXmlElement *entity2xml();
	};

};
#endif // CAMERA_H
