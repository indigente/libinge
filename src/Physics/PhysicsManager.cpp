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
#include "PhysicsManager.h"

#include <iostream>
#include <cstdio>
using namespace std;
namespace InGE {

PhysicsManager::PhysicsManager(){
	
	m_stepValue = 500.0f;
	
	m_pPhysicalWorld = new PhysicalWorld();
	
	m_pPhysicalWorld->setGravity(Vector3(0.0f,0.0f,-100.0f));
	m_lastStepTime = SDL_GetTicks();
	
}


PhysicsManager::~PhysicsManager(){
}
void PhysicsManager::quickStep(){
	Vector3 *positions = new Vector3[m_vetAvatar.size()];
	Vector3 *objectPosition = new Vector3[m_vetObject3D.size()];	

	float currentTime = SDL_GetTicks();
	float elapsedTime = currentTime - m_lastStepTime;
	
	//Armazena posicao dos Avatares e checa colisao com cenario
	for (int i=0 ; i< m_vetAvatar.size(); i++){
		m_vetAvatar[i]->update();
		checkTargetColision(m_vetAvatar[i]);
		positions[i] = m_vetAvatar[i]->getPosition();
	}

	//Armazena posicao dos Object3D
	for(int i=0; i< m_vetObject3D.size(); i++){
		objectPosition[i] = m_vetObject3D[i]->getPosition();
	}
	
	//Atualiza o mundo 	
	m_pPhysicalWorld->quickStep( elapsedTime / m_stepValue );
	

	// Checa colisao entre objetos
	for (int i= 0; i < m_vetAvatar.size(); i++){
		for (int j = 0; j < m_vetObject3D.size(); j++){
			checkObjectColision(m_vetAvatar[i], m_vetObject3D[j]);
		}
	}

	// Checa colisao do avatar com o cenario
	for (int i=0 ; i< m_vetAvatar.size(); i++){
		checkDynamicColision(m_vetAvatar[i], positions[i]);
	}
	
	// Checa colisao do object3d com o cenario
	for (int i = 0; i < m_vetObject3D.size(); i++){
		checkDynamicColision(m_vetObject3D[i], objectPosition[i] );
	}
	
	
	if(positions) delete [] positions;
	if(objectPosition) delete [] objectPosition;
	
	m_lastStepTime = currentTime;
}

	
void PhysicsManager::checkTargetColision(Object3D *object3D){
	PhysicalGeom *pGeom;
	PhysicalContactPoint moveData;
	
	if(!object3D) return;	
	if(!m_pScene) return;
	
	pGeom = object3D->pGetPhysicalGeom();
	if(!pGeom) return;
	
	Vector3 position = object3D->getPosition();
	Vector3 targetPosition = object3D->getTargetPosition();
	
	if ((object3D->getCollisionEnable())){
		moveData = m_pScene->checkMoveCollisionAndTrySlide(position, targetPosition, pGeom);
		object3D->setPosition(moveData.getPosition());

		if(!(targetPosition == object3D->getPosition()))
			object3D->worldTargetWithCollision(&moveData);
		else
			object3D->worldTargetWithoutCollision(&moveData);
	}
}

void PhysicsManager::checkDynamicColision(Object3D *object3D, Vector3 startPosition){
	PhysicalGeom *pGeom;
	PhysicalContactPoint moveData;
	
	
	if(!object3D) return;
	if(!m_pScene) return;
	
	Vector3 position = object3D->getPosition();
	
	
	pGeom = object3D->pGetPhysicalGeom();
	if(!pGeom) return;
	
	if ( (object3D->getCollisionEnable())){
		moveData = m_pScene->checkMoveCollision/*AndTrySlide*/( startPosition, position, pGeom);
		
		if(moveData.getDepth() == 1.0f){
			object3D->worldDynamicWithoutCollision( &moveData);
		}
		else{
			//object3D->setPosition(moveData.getPosition());
			object3D->setPosition(startPosition);
			object3D->worldDynamicWithCollision( &moveData);
			Vector3 v(0,0,0);
			object3D->setVelocity(v);
		}
	}
}

void PhysicsManager::checkObjectColision(Avatar *avatar, Object3D *object3D){
	if(!avatar) return;
	if(!object3D) return;
	int numOfContact = 5;
	PhysicalContactPoint *pContactPoint = new PhysicalContactPoint[numOfContact]();	


	numOfContact = PhysicalSpace::collide( *avatar->pGetPhysicalGeom(), *object3D->pGetPhysicalGeom() , pContactPoint, numOfContact);
	
	if (numOfContact > 0) {
		Vector3 v(0,0,0);
		
		object3D->setVelocity(v);
		avatar->setVelocity(v);
		avatar->onObjectCollision(object3D, pContactPoint, numOfContact);
		object3D->onObjectCollision(avatar, pContactPoint, numOfContact);
		
		
	}
	
	delete [] pContactPoint;
}
/**
 * 
 */
void PhysicsManager::updateGeom(Object3D *object3D){
	if (object3D->getModel()) {
		vector<VolumeInfo *> vetVolumeInfo = object3D->getModel()->getVetVolumeInfo();
		for (int volumeIndex = 0; volumeIndex < vetVolumeInfo.size(); volumeIndex++){
			
			
/*			if (m_pPhysicalSpace[volumeIndex].getClass() == 0)
			((GeomSphere *)m_pPhysicalSpace->getGeom( volumeIndex))->setRadius( vetVolumeInfo[volumeIndex]->getRadius() );
			m_pPhysicalSpace[volumeIndex].setPosition( vetVolumeInfo[volumeIndex]->getOrigin() );FIXME
	*/	}
	}
}


/**
 * 
 */
bool PhysicsManager::setPhysicalWorld(PhysicalWorld *pPhysicalWorld){
	if (pPhysicalWorld){
		 m_pPhysicalWorld = pPhysicalWorld;
		 return true;
	} 
	return false;
}

/**
 * 
 */
PhysicalWorld *PhysicsManager::pGetPhysicalWorld(){
	return m_pPhysicalWorld;
}

/**
 * 
 */
bool PhysicsManager::addObject3D(Object3D *object3d){
	if (object3d){
		m_vetObject3D.push_back( object3d );
		return true;
	}
	return false;
}

/**
 * 
 */
bool PhysicsManager::removeObject3D(Object3D *object3d){
	for (int i = 0; i < m_vetObject3D.size(); i++){
		if (object3d == m_vetObject3D[i]) {
			vector<Object3D *>::iterator iterator;
			iterator = m_vetObject3D.begin() + i;
			m_vetObject3D.erase(iterator);
			return true;
		}
	}
	return false;
}

bool PhysicsManager::setScene(IScene *scene){
	if (scene){
		m_pScene = scene;
		return true;
	}
	return false;
}
IScene *PhysicsManager::pGetScene(){
	return m_pScene;
}

PhysicalBody *PhysicsManager::getNewBody(){
	PhysicalBody *body = new PhysicalBody(m_pPhysicalWorld);
	PhysicalMass mass(1.0f);
	body->setMass( mass );
	return body;
}

bool PhysicsManager::addAvatar(Avatar *avatar){
	if (avatar){
		m_vetAvatar.push_back( avatar );
		return true;
	}
	return false;
}

bool PhysicsManager::removeAvatar(Avatar *avatar){
	for (int i = 0; i < m_vetAvatar.size(); i++){
		if (avatar == m_vetAvatar[i]) {
			vector<Avatar *>::iterator iterator;
			iterator = m_vetAvatar.begin() + i;
			m_vetAvatar.erase(iterator);
			return true;
		}
	}
	return false;
}

}
