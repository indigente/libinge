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
#include "Object3D.h"
#include "../Common/SceneManager.h"

using namespace InGE;

Object3D::Object3D(PhysicalGeom *geom) : IEntity("Object3D"){
	if ( geom ){
		m_pPhysicalGeom = geom;
	} else {
		m_pPhysicalGeom = new GeomSphere(22);
	}
	PhysicsManager *pPhysicsManager = SceneManager::getInstance()->getPhysicsManager();
	PhysicalBody *body = pPhysicsManager->getNewBody();
	m_pPhysicalGeom->setBody( body );
	
	m_pModel = NULL;
	m_pAudioSource = NULL;
	m_collisionEnable = true;
	m_direction.setXYZ( 0,1,0);
	
	m_objectCollided = false;
	
}


Object3D::~Object3D(){
	if(m_pPhysicalGeom) delete m_pPhysicalGeom;
// 	if(m_pAudioSource) delete m_pAudioSource;
}

Vector3 Object3D::getPosition(){
	if(m_pPhysicalGeom){
		Vector3 v = m_pPhysicalGeom->getPosition();
		if(m_pAudioSource) m_pAudioSource->setPosition(v);
		return v;
	}
	return Vector3(0,0,0);
}


void Object3D::setPosition(const Vector3 &v){
	if(m_pAudioSource) m_pAudioSource->setPosition(v);
	if(m_pPhysicalGeom) m_pPhysicalGeom->setPosition(v);
}


Vector3 Object3D::getDirection(){
	if(m_pAudioSource) m_pAudioSource->setDirection(m_direction);
	return m_direction;
}


void Object3D::setDirection(const Vector3 &v){
	if(m_pAudioSource) m_pAudioSource->setDirection(v);
	m_direction = v;
}


Vector3 Object3D::getVelocity(){
	if(m_pPhysicalGeom && m_pPhysicalGeom->getBody()){
		Vector3 linearVelocity = m_pPhysicalGeom->getBody()->getLinearVel();
		if(m_pAudioSource) m_pAudioSource->setVelocity(linearVelocity);
		return linearVelocity;
	}
	return Vector3(0,0,0);
}


void Object3D::setVelocity(const Vector3 &v){
	if(m_pAudioSource) m_pAudioSource->setVelocity(v);
	if(m_pPhysicalGeom && m_pPhysicalGeom->getBody()){
		Vector3 vel = v;
		 m_pPhysicalGeom->getBody()->setLinearVel(vel);
	}
}


Vector3 Object3D::getForce(){
	if(m_pPhysicalGeom && m_pPhysicalGeom->getBody()){
		return m_pPhysicalGeom->getBody()->getForce();
	}
	return Vector3(0,0,0);
}


void Object3D::setForce(const Vector3 &v){
	if(m_pPhysicalGeom && m_pPhysicalGeom->getBody()){
		Vector3 f = v; 
		m_pPhysicalGeom->getBody()->setForce(f);
	}
}



void Object3D::setModel(IModel *pModel){
	if (pModel){
		if (!m_pModel){
			m_pModel = pModel;
			
			m_pModel->addEntityID(m_id);
		} else if (m_pModel != pModel){
			m_pModel->removeEntityID(m_id);
			
			m_pModel = pModel;
			
			m_pModel->addEntityID(m_id);
		}
	}
}


IModel *Object3D::getModel(){
	return m_pModel;
}

PhysicalGeom *Object3D::pGetPhysicalGeom(){
	return m_pPhysicalGeom;
}

void Object3D::setAudioSource(AudioSource *source){
	m_pAudioSource = source;
}

AudioSource *Object3D::getAudioSource(){
	return m_pAudioSource;
}


void Object3D::rotate(float angle, Vector3 &axis){
	
	Vector3 newView;
	
	Quaternion quaternion(angle, axis);
	float quat[4];
	quat[0] = quaternion.getW();
	quat[1] = quaternion.getX();
	quat[2] = quaternion.getY();
	quat[3] = quaternion.getZ();
	if(m_pPhysicalGeom) m_pPhysicalGeom->setQuaternion( quat); 
	
	// Pega o vetor de visao
	Vector3 view = this->getDirection();

	// Calcula apenas uma vez
	float cosA = cos(angle);
	float sinA = sin(angle);
	float subCosA = 1 - cosA;
	float x = axis[0];
	float y = axis[1];
	float z = axis[2];

	// Acha o nova posicao X
	newView.setX( 	( cosA + subCosA * x * x ) * view[0] + 
			( subCosA * x * y - z * sinA ) * view[1] +
			( subCosA * x * z + y * sinA ) * view[2] );
				
	// Acha o nova posicao Y
	newView.setY( 	( subCosA * x * y + z * sinA ) * view[0] +
			( cosA + subCosA * y * y ) * view[1] +
			( subCosA * y * z - x * sinA ) * view[2] );

	// Acha o nova posicao Z
	newView.setZ( 	( subCosA * x * z - y * sinA ) * view[0] +
			( subCosA * y * z + x * sinA ) * view[1] +
			( cosA + subCosA * z * z ) * view[2]);

	this->setDirection(newView);
}

void Object3D::draw(){
	if (m_pModel){
		Drawer *drawer = Drawer::getInstance();
		
		Vector3 position(getPosition());
		
		drawer->translate( position );
		
		float angle = getAngleRotation()+180;
		
		drawer->rotate( angle,0,0,1);
		
		m_pModel->drawModel( m_id );
		
		drawer->rotate( angle,0,0,-1);
		
		position *= -1;
		drawer->translate( position );
	}
}

/**
 * Liga a checagem de colisao
 */
void Object3D::enableCollision(){
	m_collisionEnable = true;
}

/**
 * Desliga a checagem de colisao
 */
void Object3D::disableCollision(){
	m_collisionEnable = false;
}

void Object3D::updateGeom(){
/*	if (m_pModel) {
	vector<VolumeInfo *> vetVolumeInfo = m_pModel->getVetVolumeInfo();
	if (m_pPhysicalGeom->getClass() == 0)
	((GeomSphere *)m_pPhysicalGeom)->setRadius(vetVolumeInfo[0]->getRadius());
		//FIXME:SÃ³ estou pegando uma esfera						
/*		for (int volumeIndex = 0; volumeIndex < vetVolumeInfo.size(); volumeIndex++){
	if (m_pPhysicalSpace[volumeIndex].getClass() == 0)
	((GeomSphere *)m_pPhysicalSpace->getGeom( volumeIndex))->setRadius( vetVolumeInfo[volumeIndex]->getRadius() );
	m_pPhysicalSpace[volumeIndex].setPosition( vetVolumeInfo[volumeIndex]->getOrigin() );FIXME
}
}*/
}

Vector3 Object3D::getTargetPosition(){
	return getPosition();
}
bool Object3D::getCollisionEnable(){
	return m_collisionEnable;
}
bool Object3D::getBlend(){
	if (m_pModel){
		return m_pModel->getBlend();
	}
	return false;		
}



void Object3D::onObjectCollision(Object3D* object3d, PhysicalContactPoint *contacts, unsigned int numOfContactPoints){
	m_objectCollided = true;
}

void Object3D::worldTargetWithCollision(PhysicalContactPoint *moveData){
	m_objectCollided = true;
	m_worldTargetCollided = true;	
}

void Object3D::worldDynamicWithCollision(PhysicalContactPoint *moveData){
	m_objectCollided = true;
	m_worldDynamicCollided = true;	
}


void Object3D::worldTargetWithoutCollision(PhysicalContactPoint *moveData){
	m_worldTargetCollided = false;	
}

void Object3D::worldDynamicWithoutCollision(PhysicalContactPoint *moveData){
	m_worldDynamicCollided = false;	
}

bool Object3D::isWorldTargetCollided() {
	
	return m_worldTargetCollided;
}

bool Object3D::isWorldDynamicCollided() {
	
	return m_worldDynamicCollided;
}

bool Object3D::isObjectCollided() {
	
	return m_objectCollided;
}

void Object3D::setWorldDynamicCollided(bool pWorldDynamicCollided) {
	
	m_worldDynamicCollided = pWorldDynamicCollided;
}

void Object3D::setObjectCollided(bool pObjectCollided) {
	
	m_objectCollided = pObjectCollided;
}

TiXmlElement *Object3D::entity2xml(){
	TiXmlElement* xmlElem = new TiXmlElement("InGENetMsg");
	Vector3 position = getPosition();
	Vector3 direction = getDirection();
	Vector3 velocity = getVelocity();
	
	xmlElem->SetAttribute( "TYPE" , "ENT" );
	
	xmlElem->SetAttribute( "UNIQUEID" , m_id );
	xmlElem->SetAttribute( "ENTTYPE" , m_type );	
	
	string strue = "1";
	string sfalse = "0";
	
	if (m_objectCollided) {
		xmlElem->SetAttribute("OBJECT_COLLIDED", strue);
		
	} else {
		
		xmlElem->SetAttribute("OBJECT_COLLIDED", sfalse);
	}
	
	if (m_worldDynamicCollided) {
		xmlElem->SetAttribute("WORLD_DYNAMIC", strue);
		
	} else {
		
		xmlElem->SetAttribute("WORLD_DYNAMIC", sfalse);
	}
	
	xmlElem->SetDoubleAttribute( "POS_X" , position[0] );
	xmlElem->SetDoubleAttribute( "POS_Y" , position[1] );
	xmlElem->SetDoubleAttribute( "POS_Z" , position[2] );
	
	xmlElem->SetDoubleAttribute( "DIR_X" , direction[0] );
	xmlElem->SetDoubleAttribute( "DIR_Y" , direction[1] );
	xmlElem->SetDoubleAttribute( "DIR_Z" , direction[2] );
	
	xmlElem->SetDoubleAttribute( "VEL_X" , velocity[0] );
	xmlElem->SetDoubleAttribute( "VEL_Y" , velocity[1] );
	xmlElem->SetDoubleAttribute( "VEL_Z" , velocity[2] );
	
	if (getModel())
		xmlElem->SetAttribute( "ANIM" , m_pModel->getAnimation(m_id) );
	
	if (getModel()){
		xmlElem->SetAttribute( "MODEL_DIR" , getModelDir() );
	}
	return xmlElem;
}

void Object3D::updateFromXml(TiXmlElement *xml) {
	IEntity::updateFromXml(xml);
	
	string modelDir = "";
	if (xml->Attribute( "MODEL_DIR" )){
		modelDir = xml->Attribute( "MODEL_DIR" );

		if (modelDir != ""){
			KFModelFactory *pModelFactory = KFModelFactory::getInstance();
			IModel *pModel = pModelFactory->loadMd3( modelDir );
		
			if (pModel) {
				this->setModel( pModel );
				this->getModel()->setAnimation(getId() , xml->Attribute( "ANIM" ) , xml->Attribute( "ANIM" ));
			}
		}
	}	
	int attWorldDynamicCollided; 
	xml->Attribute( "WORLD_DYNAMIC", &attWorldDynamicCollided );
	int attObjectCollided; 
	xml->Attribute( "OBJECT_COLLIDED", &attObjectCollided );
// 		const char* attObjectCollided2 = xml->Attribute("OBJECT_COLLIDED");
		//cerr << attObjectCollided << "    -     " << attWorldDynamicCollided << endl;
// 		string attWorldDynamicCollided = attWorldDynamicCollided2;
// 		string attObjectCollided =/* */attObjectCollided2;
		
	if (attWorldDynamicCollided == 1) {
		
		this->setWorldDynamicCollided(true);
		
	} else {
		
		this->setWorldDynamicCollided(false); 
	}
	
	if (attObjectCollided == 1) {
		this->setObjectCollided(true); 
		
	} else {
		
		this->setObjectCollided(false); 
	}
}


string Object3D::getModelDir() {
	if (!getModel()) return "";
	
	string modelName = getModel()->getName();
	
	string modelDir = modelName.substr( 0 , modelName.find_last_of('/') );
	
	return modelDir;
}

/**
 *@return float retorna o angulo entre o vertor direï¿½o e o vetor (0,1,0)
*/
float Object3D::getAngleRotation(){
	static float rat = 180/3.1415926535897932; 
	float angle;
	angle=acos((m_direction[1])/(sqrt(pow(m_direction[0],2)+pow(m_direction[1],2))));
	angle *= rat;
	
 	if(m_direction[0]>0){
 		angle +=(360-2*angle);
 	}
	return angle;

}


