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
#include "SceneManager.h"


using namespace InGE;


SceneManager *SceneManager::m_pSceneManager = 0;


SceneManager::SceneManager(){
	m_state = InGE_SCENE_STARTED;
	m_pRenderManager = NULL;
	m_pPhysicsManager = NULL;
	m_pPlayer = NULL;
	
	m_isWire = false;
}


SceneManager::~SceneManager(){
}

SceneManager *SceneManager::getInstance(){
	if(!m_pSceneManager){
		m_pSceneManager = new SceneManager();
	}
	return m_pSceneManager;	
}

void SceneManager::setPhysicsManager(PhysicsManager *physicsManager){
	if(physicsManager){
		m_pPhysicsManager = physicsManager;
		EntityFactory::getInstance()->setPhysicsManager( physicsManager );
	}
}

void SceneManager::setRenderManager(RenderManager *renderManager){
	if(renderManager){
		m_pRenderManager = renderManager;
		EntityFactory::getInstance()->setRenderManager( renderManager );
	}
}

void SceneManager::setPlayer(Player *player){
	if(player)m_pPlayer = player;
}

RenderManager *SceneManager::getRenderManager(){
	return m_pRenderManager;
}

PhysicsManager *SceneManager::getPhysicsManager(){
	return m_pPhysicsManager;
}

Player *SceneManager::getPlayer(){
	return m_pPlayer;
}

int SceneManager::getState(){
	return m_state;
}			

void SceneManager::setState(int state){
	m_state = state;
}			

void SceneManager::controlEventHandler(ControlEnum e, ControlParam *param){
	Drawer *drawer = Drawer::getInstance();
	switch(e){
		case InGE_CONTROL_ESCAPE:
			if(param->state){ 
				m_state = InGE_SCENE_STOPED;
			}
			break;
		case InGE_CONTROL_F11:
			if(param->state){ 
				m_isFullScreen = !m_isFullScreen;
				if(m_isFullScreen) SDL_WM_ToggleFullScreen( SDL_GetVideoSurface() );
			}
			break;
		case InGE_CONTROL_F12:
			if(param->state){ 
				m_isWire = !m_isWire;
				if(m_isWire) drawer->polygonMode(InGE_FRONT_AND_BACK,InGE_LINE);
				else drawer->polygonMode(InGE_FRONT_AND_BACK,InGE_FILL);
			}
			break;
			
		case InGE_CONTROL_ACTION1:
			if(param->state){ 
			//	m_pRenderManager->pick(param);
			}
			break;		
		default:
			break;
	}
}


void SceneManager::update(){
	NetControl::waitForSync();
	//SDL_SemWait(NetControl::m_pSemNetAndLocalSync);
	
	if(m_pPlayer) m_pPlayer->update();
	
	
	//Atualizar ambiente fisico
	if(m_pPhysicsManager) m_pPhysicsManager->quickStep();
	
	
	//Atualizar render
	if(m_pRenderManager) m_pRenderManager->render(m_pPlayer->getCamera());
	
	NetControl::postForSync();
	//SDL_SemPost(NetControl::m_pSemNetAndLocalSync);
	
	AudioManager::getInstance()->update();
}

