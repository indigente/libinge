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
#ifndef INGEOBJECT3D_H
#define INGEOBJECT3D_H

#include "IEntity.h"
#include <map>
#include "../Graphics/Model/IModel.h"
#include "../Graphics/Render/IRenderListener.h"
#include "../Physics/PhysicalGeom.h"
#include "../Physics/Geoms/GeomSphere.h"
#include "../Audio/AudioSource.h"
#include <cmath>

using std::map;

namespace InGE {

	/**
		@author Ivan Medeiros Monteiro <fehler@gmail.com>
	*/
	class Object3D : public InGE::IEntity, public InGE::IRenderListener{
		protected :
			IModel			*m_pModel;
			PhysicalGeom	*m_pPhysicalGeom;
			AudioSource		*m_pAudioSource;
			
			bool		m_collisionEnable;
			
			bool		m_worldTargetCollided;
			bool		m_worldDynamicCollided;
			int 		m_objectCollided;
			
			Vector3		m_direction;
			
			
			string getModelDir();
			
		public:
			Object3D(PhysicalGeom *geom=NULL);
			
			~Object3D();
			
			void setDirection(const Vector3 &v);
			
			virtual void setModel(IModel *pModel);
			IModel *getModel();
			
			void setAudioSource(AudioSource *pSource);
			AudioSource *getAudioSource();
			
			virtual Vector3 getPosition();
			virtual void setPosition(const Vector3 &v);
			
			virtual Vector3 getVelocity();
			virtual void setVelocity(const Vector3 &v);
			
			virtual Vector3 getForce();
			virtual void setForce(const Vector3 &v);
			
			virtual Vector3 getTargetPosition();
			
			PhysicalGeom *pGetPhysicalGeom();
			Vector3 getDirection();
			
			virtual void rotate(float angle, Vector3 &axis);
			virtual float getAngleRotation();
						
			virtual void updateGeom();
			
			virtual void draw();
			
			void enableCollision();
			void disableCollision();
			
			bool getCollisionEnable();
			
			bool getBlend();
			
			bool isWorldTargetCollided();
			bool isWorldDynamicCollided();
			bool isObjectCollided();
			
			void setWorldDynamicCollided(bool pWorldDynamicCollided);
			void setObjectCollided(bool pObjectCollided);
			
			virtual TiXmlElement *entity2xml();
			virtual void updateFromXml(TiXmlElement *xml);
			
			virtual void onObjectCollision(Object3D* object3d = NULL, PhysicalContactPoint *contacts = NULL , unsigned int numOfContactPoints=0);
			
			virtual void worldTargetWithCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldDynamicWithCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldTargetWithoutCollision(PhysicalContactPoint *moveData = NULL);
			virtual void worldDynamicWithoutCollision(PhysicalContactPoint *moveData = NULL);
	};

};

#endif
