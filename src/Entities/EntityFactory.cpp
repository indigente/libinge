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
#include "EntityFactory.h"

using namespace InGE;

EntityFactory *EntityFactory::m_pEntityFactory = 0;

/**
 * Construtor
 */
EntityFactory::EntityFactory(){
	m_mapEntity.clear();
}

/**
 * @return Retorna a classe para ser usada
 */
EntityFactory *EntityFactory::getInstance(){
	if(!m_pEntityFactory)
		m_pEntityFactory = new EntityFactory();
		
	return m_pEntityFactory;
}

void EntityFactory::setPhysicsManager(PhysicsManager *physicsManager){
	if(physicsManager) m_pPhysicsManager = physicsManager;
}

void EntityFactory::setRenderManager(RenderManager *renderManager){
	if(renderManager)m_pRenderManager = renderManager;
}

RenderManager *EntityFactory::getRenderManager(){
	return m_pRenderManager;
}

PhysicsManager *EntityFactory::getPhysicsManager(){
	return m_pPhysicsManager;
}


EntityFactory::~EntityFactory(){
	m_mapEntity.clear();
}

void EntityFactory::loadEntities(BspScene *pScene){
	KFModelFactory *pModelFactory = KFModelFactory::getInstance();
	
	vector<QEntityInfo *> vetEntityInfo = pScene->getVectorOfEntityInfo();
	
	for(unsigned int i=0; i<vetEntityInfo.size(); i++){		
		if( vetEntityInfo[i]->classname == "info_player_start" ){
			InfoEntity *pInfoStart = new InfoEntity();
			pInfoStart->setPosition( vetEntityInfo[i]->origin );
			pInfoStart->setRotation(Vector4(vetEntityInfo[i]->angle, 0, 0, 1));
			pInfoStart->setClassName( vetEntityInfo[i]->classname );
			
			m_vetInfoEntity.push_back(pInfoStart);
		} else if( vetEntityInfo[i]->classname == "info_Objeto3D" ){
// 			Object3D *pEntity = new Object3D();
// 			addObject3D(pEntity);
// 			IModel *pModel = pModelFactory->loadMd3(vetEntityInfo[i]->dirName);
// //			pModel->scale(vetEntityInfo[i]->scale);
// 			pEntity->setModel( pModel );
// 
// 			
// // 			pEntity->setType( vetEntityInfo[i]->classname );
// 			Vector3 position( vetEntityInfo[i]->origin[0],vetEntityInfo[i]->origin[1],vetEntityInfo[i]->origin[2] +50  );
// 			pEntity->setPosition(position);
// 			Vector3 up(0,0,1);
// 			pEntity->rotate(vetEntityInfo[i]->angle, up);
// 			
		}
	}
}

IEntity *EntityFactory::loadEntity(TiXmlElement *xml) {
	string entType = xml->Attribute( "ENTTYPE" );
	string uniqueId = xml->Attribute( "UNIQUEID" );
	IEntity *entity = getEntity( uniqueId );
	
	if (entType.find("Object3D", 0) != string::npos){
		if (!entity)
			entity = getNewObject3D(uniqueId);
		
	} else if (entType.find("Avatar", 0) != string::npos){
		if (!entity)
			entity = getNewAvatar(uniqueId);
		
	} else if (entType.find("AudioSource", 0) != string::npos){
		if (!entity)
			entity = getNewAudioSource(uniqueId);
	} else if (entType.find("AudioListener", 0) != string::npos){
		if (!entity)
			entity = getNewAudioListener(uniqueId);
		
	}
	entity->addXML(xml);
	
	return entity; 
}

Object3D *EntityFactory::getNewObject3D(){
	
	Object3D *newObject3D = new Object3D();
	addObject3D(newObject3D);
	
	return newObject3D;
}

Object3D *EntityFactory::getNewObject3D(string &uniqueId) {
	Object3D *pObject3D = new Object3D();
	pObject3D->setId( uniqueId );
	addObject3D( pObject3D );
	return pObject3D;
}

Avatar *EntityFactory::getNewAvatar(string &uniqueId) {
	Avatar *pAvatar = new Avatar();
	pAvatar->setId( uniqueId );
	addNetAvatar( pAvatar );
	return pAvatar;
}

AudioSource *EntityFactory::getNewAudioSource(string &uniqueId) {
	AudioSource *pAudioSource = AudioManager::getInstance()->createSource();
	pAudioSource->setId( uniqueId );
// 	addAudioSource( pAudioSource ); FIXME> Nada pra fazer???
	return pAudioSource;
}

AudioListener *EntityFactory::getNewAudioListener(string &uniqueId) {
	AudioManager *pAudioManager = AudioManager::getInstance();
	AudioListener *pAudioListener = pAudioManager->getListener();
	pAudioListener->setId( uniqueId );
	
	return pAudioListener;
}


void EntityFactory::addObject3D(Object3D *pObject3D){
	if(!pObject3D) return;
	
	if (pObject3D->getId() == "unknown"){
		this->generateId( pObject3D );
	}
	
	m_pPhysicsManager->addObject3D( pObject3D );
	m_pRenderManager->addListener( pObject3D );
	if(pObject3D->getAudioSource()) {
// 		m_pAudioManager->addSource( pObject3D->getAudioSource() );
	}
	
	addEntity( pObject3D);
		
	NetClient* pNetClient = NetClient::getInstance();
	if ( pNetClient->isConnected() ) {
		string entId = pObject3D->getId();
		int netId = pNetClient->getId();
		
		if ( atoi( &entId[entId.size()-1] ) == netId ){
			pNetClient->addEntityToNet( (IEntity *) pObject3D );
		}
		
	}
}


void EntityFactory::addAvatar(Avatar *pAvatar){
	if(!pAvatar) return;
	
	if (pAvatar->getId() == "unknown"){
		this->generateId( pAvatar );
	}
	
	m_pPhysicsManager->addAvatar( pAvatar );
	m_pRenderManager->addListener( pAvatar );
	if(pAvatar->getAudioSource())
// 		m_pAudioManager->addSource( pAvatar->getAudioSource() );
	
	addEntity( (IEntity *) pAvatar);
	
	NetClient* pNetClient = NetClient::getInstance();
	if ( pNetClient->isConnected() ) {
		string entId = pAvatar->getId();
		int netId = pNetClient->getId();
		
		if ( atoi( &entId[entId.size()-1] ) == netId ){
			pNetClient->addEntityToNet( pAvatar );
		}
		
	}
	
}

void EntityFactory::addNetAvatar(Avatar *pAvatar){
	if(!pAvatar) return;
	
	if (pAvatar->getId() == "unknown"){
		this->generateId( pAvatar );
	}
	
	
	m_pPhysicsManager->addAvatar( pAvatar );
	m_pRenderManager->addListener( pAvatar );
	if(pAvatar->getAudioSource()) {
// 		m_pAudioManager->addSource( pAvatar->getAudioSource() );
	}
		
	addEntity( pAvatar);	
}


void EntityFactory::addEntity(IEntity *pEntity) {
	m_mapEntity[pEntity->getId()] = pEntity;
}

void EntityFactory::rmEntity (IEntity *ent) {
	if (!ent){
		cerr << "Entidade não existe" << endl;
		return;
	}
	
	NetClient* pNetClient = NetClient::getInstance();
	
	if (pNetClient->isConnected()) {
		pNetClient->rmEntityFromNet( ent );
	}
	
	if (ent->getType().find("Object3D", 0) != string::npos) {
		m_pPhysicsManager->removeObject3D( (Object3D *) ent );
		m_pRenderManager->rmListener( ent->getId() );
		
		IModel* model = ((Object3D *) ent)->getModel();
		
		if (model) {
			model->removeEntityID(ent->getId()); 
		}
		
	}
	
	if (ent->getType().find("Avatar", 0) != string::npos) {
		m_pPhysicsManager->removeAvatar( (Avatar *) ent );
		m_pRenderManager->rmListener( ent->getId() );
		
		IModel* model = ((Avatar *) ent)->getModel();
		
		if (model) {
			
			model->removeEntityID(ent->getId()); 
		}
	}
	
	if (ent->getType().find("AudioSource", 0) != string::npos) {
		//nothing to do here, right?
	}
	
	if (ent->getType().find("AudioListener", 0) != string::npos) {
		//nothing to do here, right?
	}
	
	m_mapEntity.erase( ent->getId() );
	
	delete ent;
}

unsigned int EntityFactory::getNumOfEntity(){
	return m_mapEntity.size();
}

IEntity *EntityFactory::getEntity(string &uniqueid){
	map<string, IEntity *>::iterator it;
	
	it = m_mapEntity.find(uniqueid);
	
	if (it == m_mapEntity.end())
		return NULL;
	else
		return it->second;
}

void EntityFactory::generateId(IEntity* ent){
	string newId;
	
	char* buffer = new char[50];
	
	sprintf (buffer, "%p", ent);
	
	newId = buffer;
	
	NetClient* pNetClient = NetClient::getInstance();	
	if (pNetClient->isConnected()) {
		sprintf (buffer, "%i", pNetClient->getId());
		newId += buffer;
	}
	
	ent->setId( newId );
	
	delete buffer;

}

InfoEntity *EntityFactory::pGetInfoEntity(int index){
	if (index < m_vetInfoEntity.size()){
		return m_vetInfoEntity[index];
	}else{
		index %= m_vetInfoEntity.size();
	}
	return m_vetInfoEntity[index];
}

int EntityFactory::getNumInfoEntity(){
	return m_vetInfoEntity.size();
}

void EntityFactory::updateEntitiesAttributes(){
	
 	NetControl::waitForSync();
	
	map<string, IEntity *>::iterator entityIterator;
	for (entityIterator = m_mapEntity.begin(); entityIterator != m_mapEntity.end(); entityIterator++){
		if (entityIterator->second){
			entityIterator->second->updateAttributes();
		}
	}
		
 	NetControl::postForSync();
	
}

