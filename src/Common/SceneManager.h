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

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Control/ControlLayer.h"
#include "../Entities/EntityFactory.h"
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalContactPoint.h"
#include "../Graphics/Render/RenderManager.h"
#include "../Graphics/Render/Drawer.h"
#include "../Network/NetControl.h"
#include "Player.h"

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

#define InGE_SCENE_STOPED	0
#define InGE_SCENE_STARTED	1
#define InGE_SCENE_PLAYING	2

namespace InGE{
	
	class SceneManager : public InGE::IControlLayerListener{
		private:
			static SceneManager	*m_pSceneManager;
			
			PhysicsManager		*m_pPhysicsManager;
			RenderManager		*m_pRenderManager;
			
			Player				*m_pPlayer;
			
			int m_state;
			bool m_isWire;
			bool m_isFullScreen;
			
			SceneManager();
			
			
		public:
		
			virtual ~SceneManager();
			static SceneManager *getInstance();
			
			void setPhysicsManager(PhysicsManager *physicsManager);
			void setRenderManager(RenderManager *renderManager);
			void setPlayer(Player *player);
			void setState(int state);
	
			
			PhysicsManager *getPhysicsManager();
			RenderManager *getRenderManager();
			Player *getPlayer();
			int getState();
	
			void controlEventHandler(ControlEnum e, ControlParam *param);
			
			void update();
			
			
	};

};
#endif // SCENEMANAGER_H
