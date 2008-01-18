/*
  -----------------------------------------------------------------------------
  This source file is part of Indigente Game Engine
  Indigente - Interactive Digital Entertainment
  For the latest info, see http://indigente.dcc.ufba.br

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

/**
   @file Object3D.h
   @brief This file describes the class Object3d
   
*/

#ifndef INGEOBJECT3D_H
#define INGEOBJECT3D_H

#include <map>
#include "IEntity.h"
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
	   @brief This class defines a Object3D.

	   An object 3d is an entity which has a 3d model attached to it. It also has mass and volume.
	   @see IEntity
	*/
	/* XXXlucaspm: I think the inge article doesn't mention anything about audio sources... */
 class Object3D : public InGE::IEntity, public InGE::IRenderListener{
	protected :
		IModel			*m_pModel; ///< the graphical 3d model
		PhysicalGeom	*m_pPhysicalGeom; ///< the physical 3d model
		AudioSource		*m_pAudioSource; ///< the audio source 
			
		bool		m_collisionEnable; ///< It tells whether the object collides or not

		// XXXlucaspm: I don't what to do with those three!!! Someone!!
		bool		m_worldTargetCollided;
		bool		m_worldDynamicCollided;
		int 		m_objectCollided;
			
		Vector3		m_direction; ///< The direction as a Vector3 object
			
		string getModelDir(); ///< It returns the folder where models are stored
			
	public:
		Object3D(PhysicalGeom *geom=NULL); ///< Constructor
			
		~Object3D(); ///< Destructor
			
		void setDirection(const Vector3 &v); ///< It sets the direction of the object
			
		virtual void setModel(IModel *pModel); ///< It sets the graphical 3d model
		IModel *getModel(); ///< It returns the graphical 3d model
			
		void setAudioSource(AudioSource *pSource); ///< It sets the audio source
		AudioSource *getAudioSource(); ///< It gets the audio source
			
		virtual Vector3 getPosition(); ///< It gets current position
		virtual void setPosition(const Vector3 &v); ///< It sets current position
			
		virtual Vector3 getVelocity(); ///< It gets current velocity vector
		virtual void setVelocity(const Vector3 &v); ///< It sets current velocity vector
		virtual void addVelocity(const Vector3 &v); ///< It adds a velocity vector to the current velocity vector
			
		virtual Vector3 getForce(); ///< It gets the current force applied to the object
		virtual void setForce(const Vector3 &v); ///< It sets the current force vector
			
		virtual Vector3 getTargetPosition(); ///< AKA getPosition()
			
		PhysicalGeom *pGetPhysicalGeom(); ///< It gets the physical 3d model
		Vector3 getDirection(); ///< It gets the direction of this object
			
		virtual void rotate(float angle, Vector3 &axis); ///< It rotates the object
		//XXXlucaspm: Someone check this out!
		virtual float getAngleRotation(); ///< suppose a vector3 has these coordinates {x,y,z}, this function returns
		                                  ///< the angle which the direction form with {0,1,0} counterclockwise
						
		virtual void updateGeom(); // XXXlucaspm: HELP! I can't understand it!
			
		virtual void draw(); ///< It draws the graphical 3d model
			
		void enableCollision(); ///< It sets the collision mode
		void disableCollision(); ///< It unsets the collision mode
			
		bool getCollisionEnable(); ///< Is tells whether collision mode is enabled
			
		bool getBlend(); // XXXlucaspm: I can't understand it too...

		// XXXlucaspm: Someone take a look at those
		bool isWorldTargetCollided();
		bool isWorldDynamicCollided();
		bool isObjectCollided();
			
		void setWorldDynamicCollided(bool pWorldDynamicCollided);
		void setObjectCollided(bool pObjectCollided);

		// XXXlucaspm: I won't copy what I have done until I am certain
		//             it was correct (see IEntity.h)
		virtual TiXmlElement *entity2xml();
		virtual void updateFromXml(TiXmlElement *xml);
			
		virtual void onObjectCollision(Object3D* object3d = NULL, PhysicalContactPoint *contacts = NULL , unsigned int numOfContactPoints=0); ///< It process object reactions to current collisions
			
		virtual void worldTargetWithCollision(PhysicalContactPoint *moveData = NULL);
		virtual void worldDynamicWithCollision(PhysicalContactPoint *moveData = NULL);
		virtual void worldTargetWithoutCollision(PhysicalContactPoint *moveData = NULL);
		virtual void worldDynamicWithoutCollision(PhysicalContactPoint *moveData = NULL);
	};

}
#endif
