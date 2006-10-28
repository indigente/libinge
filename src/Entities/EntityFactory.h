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
#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "IEntity.h"
#include "InfoEntity.h"
#include "Object3D.h"
#include "Avatar.h"

#include "../Audio/AudioManager.h"
#include "../Graphics/Render/RenderManager.h"
#include "../Physics/PhysicsManager.h"

#include "../Graphics/World/BspScene.h"

#include "../Graphics/Model/KFModel/KFModelFactory.h"

#include "../Network/NetClient.h"

#include <string>
#include <vector>
#include <map>
#include "../Util/TinyXML/tinyxml.h"


namespace InGE {
using std::vector;
using std::string;
using std::map;
/**
	@author Beto <nkbeto@gmail.com>
*/
class EntityFactory{
	private:
		static EntityFactory *m_pEntityFactory;
		EntityFactory();
		
		map<string, IEntity *> m_mapEntity;
		vector<InfoEntity *> m_vetInfoEntity;
		
		AudioManager		*m_pAudioManager;
		RenderManager		*m_pRenderManager;
		PhysicsManager		*m_pPhysicsManager;
		
		void addEntity(IEntity *pEntity);
		
	public:
		static	EntityFactory *getInstance();

		~EntityFactory();
		
		void setPhysicsManager(PhysicsManager *physicsManager);
		void setRenderManager(RenderManager *renderManager);
		
		PhysicsManager *getPhysicsManager();
		RenderManager *getRenderManager();

		
		void addObject3D(Object3D *pObject3D);
		void addAvatar(Avatar *pAvatar);
		void addNetAvatar(Avatar *pAvatar);
		
		void loadEntities(BspScene *scene);
		
		IEntity *loadEntity(TiXmlElement *xml);
		
		void rmEntity (IEntity *ent);
		
		unsigned int getNumOfEntity();
		
		IEntity *getEntity(string &uniqueid);
		
		void generateId(IEntity* ent);
		
		Object3D *getNewObject3D(string &uniqueid);
		Object3D *getNewObject3D();
		Avatar *getNewAvatar(string &uniqueid);
		Avatar *getNewAvatar();
		AudioSource *getNewAudioSource(string &uniqueid);
		AudioListener *getNewAudioListener(string &uniqueid);
		
		InfoEntity *pGetInfoEntity(int index);
		int 			getNumInfoEntity();
		
		void updateEntitiesAttributes();
};

}

#endif
