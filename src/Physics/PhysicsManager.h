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
#ifndef INGEPHYSICSMANAGER_H
#define INGEPHYSICSMANAGER_H
#include "PhysicalWorld.h"
#include "../Entities/Object3D.h"
#include "../Entities/Avatar.h"
#include "../Graphics/World/IScene.h"
#include <vector>


namespace InGE {
using std::vector;

/**
	@author Beto <nkbeto@gmail.com>
*/
class PhysicsManager{
private:
	PhysicalWorld		*m_pPhysicalWorld;
	float 			m_stepValue;
	vector<Object3D *>	m_vetObject3D;
	vector<Avatar *>	m_vetAvatar;
	IScene			*m_pScene;
	
	float	m_lastStepTime;
	
	void	checkTargetColision(Object3D *object3d);
	void	checkDynamicColision(Object3D *object3d, Vector3 startPosition);
	void	checkObjectColision(Avatar *avatar, Object3D *object3d);
	
	void	updateGeom(Object3D *object3d);

public:
	PhysicsManager();

	~PhysicsManager();

	bool setPhysicalWorld(PhysicalWorld *pPhysicalWorld);
	PhysicalWorld *pGetPhysicalWorld();
	
	bool addAvatar(Avatar *avatar);
	bool removeAvatar(Avatar *avatar);
	
	bool addObject3D(Object3D *object3d);
	bool removeObject3D(Object3D *object3d);
	
	
	
	bool setScene(IScene *scene);
	IScene *pGetScene();
		
	PhysicalBody *getNewBody();
	
	void quickStep();
	
};

}

#endif
