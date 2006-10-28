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
#ifndef INGEAVATAR_H
#define INGEAVATAR_H

#include "Object3D.h"
#include "../Control/IControlLayerListener.h"
#include "../Graphics/Camera/CameraFP.h"
#include "../Audio/AudioListener.h"
#include "../Physics/PhysicalGeom.h"


namespace InGE {

	/**
		@author Ivan Medeiros Monteiro <fehler@gmail.com>
	*/
	class Avatar : public InGE::Object3D, public InGE::IControlLayerListener {
		protected:
			//Estados dos avatar 
			struct SMovimentState{ // Estados de Movimentacao
				bool forward;
				bool backward;
				bool strafeLeft;
				bool strafeRight;
				bool turnLeft;
				bool turnRight;
				bool jump;
			} m_movimentState;
			// Informacao associada ao deslocamento do jogador
			static float	m_moveSpeed;
			static float	m_rotateSpeed;
			static float 	m_jumpSpeed;
			
			int	m_pointerX;
			int	m_pointerY;

			Vector3 m_targetPosition;
			CameraFP m_camera;
			AudioListener *m_pAudioListener;
			
			void updateCamera();
			
		public:
			Avatar(PhysicalGeom *geom = NULL);
			
			~Avatar();
			
					
			ICamera *getCamera();
			int 	getPointerX();
			int 	getPointerY();
			void 	setPointerMiddleScreen();
			
			void 	setPosition(Vector3 &v);
			Vector3	getTargetPosition();
			void	rotate(float angle, Vector3 &axis);
			
			void	updateGeom();
			virtual void controlEventHandler(ControlEnum e, ControlParam *param);
			
			
			virtual void onObjectCollision(Object3D* object3d = NULL, PhysicalContactPoint *contacts = NULL , unsigned int numOfContactPoints=0);
			
			virtual void worldTargetWithCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldDynamicWithCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldTargetWithoutCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldDynamicWithoutCollision(PhysicalContactPoint *moveData = NULL);

			
			virtual void update();
			
			TiXmlElement *entity2xml();
			virtual void updateFromXml(TiXmlElement *xml);
	};

};

#endif
