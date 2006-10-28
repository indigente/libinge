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
#ifndef PHYSICALBODY_H
#define PHYSICALBODY_H
#include "../Math/Vector3.h"
#include "PhysicalWorld.h"
#include "PhysicalMass.h"
#include <ode/ode.h>


namespace InGE{	
	
class PhysicalBody{
private:
	dBodyID  m_bodyId;
	dWorldID m_worldId;			
		
public:

	PhysicalBody(PhysicalWorld *pw);
	PhysicalBody(PhysicalWorld &pw);
	~PhysicalBody();
	
	void 	setMass(PhysicalMass &mass);
	float 	getMass();
	Vector4 getCenter();
	float 	*getInertia();
	
				
	void setPosition(Vector3 &position);
	void setLinearVel(Vector3 &v);
	void setAngularVel(Vector3 &v);
	void setRotation(const float rotation[12]);
	void setQuaternion(const float quaternion[4]);
	
	Vector3 getPosition();
	Vector3 getLinearVel();
	Vector3 getAngularVel();
	const float * getRotation();
	const float * getQuaternion();
	
	dBodyID getId();
	
	
	void addForce(Vector3 &force);
	void addTorque(Vector3 &torque);
	void addRelForce(Vector3 &force);
	void addRelTorque(Vector3 &torque);
	void addForceAtPos(Vector3 &force, Vector3 &position);
	void addForceAtRelPos(Vector3 &force, Vector3 &position);
	void addRelForceAtPos(Vector3 &force, Vector3 &position);
	void addRelForceAtRelPos(Vector3 &force, Vector3 &position);
	
	
	Vector3 getForce();
	Vector3 getTorque();
	
	void setForce(Vector3 &force);
	void setTorque(Vector3 &torque);
	
	Vector3 getRelPointPos(Vector3 position);
	Vector3 getRelPointVel(Vector3 position);
	Vector3 getPointVel(Vector3 position);
	Vector3 getPosRelPoint(Vector3 position);
	Vector3 vectorToWorld(Vector3 position);
	Vector3 vectorFromWorld(Vector3 position);
	
	
	void  enable();
	void  disable();
	bool  isEnabled();
	void  setAutoDisableFlag(int autoDisable);
	int   getAutoDisableFlag();
	void  setAutoDisableLinearThreshold(float linearThreshold);
	float getAutoDisableLinearThreshold();
	void  setAutoDisableAngularThreshold(float angularThreshold);
	float getAutoDisableAngularThreshold();
	void  setAutoDisableSteps(int steps);
	int   getAutoDisableSteps();
	void  setAutoDisableTime(float time);
	float getAutoDisableTime();
	void  setAutoDisableDefaults();
	/*
	void  setAutoDisableThresholdSF1(float autoDisableThreshold);
	float getAutoDisableThresholdSF1();
	void  setAutoDisableStepSF1(int autoDisableStep);
	int   getAutoDisableStepSF1();
	*/
	//Miscellaneous Body Functions
	
	void setData(void *data);
	void *getData();
	
	void setFiniteRotationMode(int mode);
	int  getFiniteRotationMode();
	
	void setFiniteRotationAxis(Vector3 axis);
	Vector3 getFiniteRotationAxis();
	
	int getNumJoints();
	dJointID getJoint(int index);
	
	void setGravityMode(int mode);
	int getGravityMode();
	
};
};
#endif // PHYSICALBODY_H
