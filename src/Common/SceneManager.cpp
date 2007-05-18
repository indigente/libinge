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


/**
 * Class Constructor
 */
SceneManager::SceneManager(){
	m_state = InGE_SCENE_STARTED;
	m_pRenderManager = NULL;
	m_pPhysicsManager = NULL;
	m_pPlayer = NULL;
	
	m_isWire = false;
}

/**
 * Class Destructor
 */
SceneManager::~SceneManager(){
}

/**
 * Returns the instance
 * @return 
 */
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

/**
 * This method handles the events passed by the ControlLayer
 * @param e This is the command given by the ControlLayer
 * @param param These are the params of the command
 */
//TODO: Configuration file is needed for this commands.
void SceneManager::controlEventHandler(ControlEnum e, ControlParam *param){
	switch(e){
		case InGE_CONTROL_ESCAPE:
			if(param->state){ 
				setState( InGE_SCENE_STOPED );
			}
			break;
		case InGE_CONTROL_F11:
			if(param->state){ 
				fullScreen();
			}
			break;
		case InGE_CONTROL_F12:
			if(param->state){ 
				wireFrame();
			}
			break;
		case InGE_CONTROL_ACTION1:
			if(param->state){ 
				pick(param);
			}
			break;		
		default:
			break;
	}
}


/**
 * This method sequencially updates the modules of the engine.
 * First, it checks for player controls and change camera's position.
 * Second, make a step in the physics world and check for collisions.
 * Third, render the world and models.
 */
void SceneManager::update(){
	NetControl::waitForSync();
	//SDL_SemWait(NetControl::m_pSemNetAndLocalSync);
	
	if(m_pPlayer) m_pPlayer->update();
	
	
	//Atualizar ambiente fisico
	if(m_pPhysicsManager) m_pPhysicsManager->quickStep();
	
	
	//Atualizar render
	if(m_pRenderManager){
		if(m_pPlayer){
			m_pRenderManager->render(m_pPlayer->getCamera());
		} else {
			CameraFP camera;
			m_pRenderManager->render(&camera);
		}
	}
	
	NetControl::postForSync();
	//SDL_SemPost(NetControl::m_pSemNetAndLocalSync);
	
	AudioManager::getInstance()->update();
}

/**
 * This method make turn the aplication FullScreen if it's Windowed and Windowed if it's FullScreen.
 */
void InGE::SceneManager::fullScreen(){
	m_isFullScreen = !m_isFullScreen;
	if(m_isFullScreen)
		SDL_WM_ToggleFullScreen( SDL_GetVideoSurface() );
}

/**
 * This method make turn the aplication Wireframe if it's Filled and Filled if it's Wireframe.
 */
void InGE::SceneManager::wireFrame(){
	Drawer *drawer = Drawer::getInstance();
	m_isWire = !m_isWire;
	if(m_isWire){
		drawer->polygonMode(InGE_FRONT_AND_BACK,InGE_LINE);
	}else{
		drawer->polygonMode(InGE_FRONT_AND_BACK,InGE_FILL);
	}
}

void InGE::SceneManager::pick(ControlParam *param){
	if ( ( (m_pPlayer) && (m_pRenderManager) ) && (m_pPlayer->canPick()) ){
		m_pRenderManager->pick( m_pPlayer->getCamera(), param);
	}
}

