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
#include "Avatar.h"
#include "../Audio/AudioManager.h"

using namespace InGE;

float Avatar::m_moveSpeed = 300.0f;
float Avatar::m_rotateSpeed = 0.01f;
float Avatar::m_jumpSpeed = 150.0f;

Avatar::Avatar(PhysicalGeom *geom) : Object3D(geom) {
	Vector3 v = getPosition();
	m_camera.setPosition( v );
	m_type = "Avatar";
	
	SDL_Surface *surface = SDL_GetVideoSurface();
	m_pointerX = surface->w >> 1;
	m_pointerY = surface->h >> 1;;
	m_pAudioListener = AudioManager::getInstance()->getListener();

	m_movimentState.forward = false;
	m_movimentState.backward = false;
	m_movimentState.strafeLeft = false;
	m_movimentState.strafeRight = false;
	m_movimentState.turnLeft = false;
	m_movimentState.turnRight = false;
	m_movimentState.jump = false;
}


Avatar::~Avatar(){
}


ICamera *Avatar::getCamera(){
	return &m_camera;
}
	
/**
 * Manipula as aÃ§Ãµes dos controles
 * @param ControlEnum e - EnumeraÃ§Ã£o dos comandos.
 * @param ControlParam *param - Parametros do comando passado.
 */
void Avatar::controlEventHandler(ControlEnum e, ControlParam *param){
	switch(e){
		case InGE_CONTROL_FORWARD:
			if(param->state){
				m_movimentState.forward = true;
			}else{
				m_movimentState.forward = false;
			}
			break;
		case InGE_CONTROL_BACKWARD:
			if(param->state){
				m_movimentState.backward = true;
			}else{
				m_movimentState.backward = false;
			}

			break;
		case InGE_CONTROL_LEFT:
			if(param->state) m_movimentState.strafeLeft = true;
			else m_movimentState.strafeLeft = false;		
			break;
		case InGE_CONTROL_RIGHT:
			if(param->state) m_movimentState.strafeRight = true;
			else m_movimentState.strafeRight = false;
			break;
		case InGE_CONTROL_TURN_LEFT:
			if(param->state) m_movimentState.turnLeft = true;
			else m_movimentState.turnLeft = false;
			break;
		case InGE_CONTROL_TURN_RIGHT:
			if(param->state) m_movimentState.turnRight = true;
			else m_movimentState.turnRight = false;
			break;
		case InGE_CONTROL_JUMP:
			if(param->state) {
				m_movimentState.jump = true;
			}
			break;
		case InGE_CONTROL_LOOK:
			m_pointerX = param->x;
			m_pointerY = param->y;
			break;
		default:
			break;
	}
}




void Avatar::rotate(float angle, Vector3 &axis){ //FIXME: Rotacionar o modelo tb.
	Object3D::rotate(angle, axis);
	m_camera.rotate( angle, axis );
}

void Avatar::updateCamera(){
	Vector3 camMove = getPosition() - m_camera.getPosition();
	m_camera.move( camMove );
	m_camera.setViewByPointer( m_pointerX, m_pointerY );
	setPointerMiddleScreen();
}


Vector3 Avatar::getTargetPosition(){
	return m_targetPosition;
}

/**
 * Checa mudanÃ§as de estado no Avatar
 */
void Avatar::update(){
	static float lastUpdateTime = 0;
	float speed = m_moveSpeed * (SDL_GetTicks() - lastUpdateTime)/1000;
	lastUpdateTime = SDL_GetTicks();
	
	//Camera
	updateCamera();
 	Vector3 up = m_camera.getUp();
 	if(m_movimentState.turnLeft){
 		rotate( (m_rotateSpeed * speed), up);
 	}
 	if(m_movimentState.turnRight){
 		rotate( -(m_rotateSpeed * speed), up);
 	}

	m_targetPosition = this->getPosition();
	
	m_direction = m_camera.getDirection();
	Vector3 strafe = m_camera.getStrafe();
	
		
	m_direction.normalize();
	strafe.normalize();
	
	if(m_movimentState.forward){
		m_targetPosition += m_direction * speed;
	}
	if(m_movimentState.backward){
		m_targetPosition -= m_direction * speed;	
	}
	if(m_movimentState.strafeLeft){
		m_targetPosition += strafe * speed;
	}
	if(m_movimentState.strafeRight){
		m_targetPosition -= strafe * speed;	
	}
	if(m_movimentState.jump){
		if(m_worldDynamicCollided){
			Vector3 v(0,0, m_jumpSpeed);
			this->setVelocity(v);
		}
		m_movimentState.jump = false;
	}
	Vector3 velocity = m_targetPosition - this->getPosition();
 	velocity[2] = 0.0f;
	velocity.normalize();
	velocity *= speed;

	m_targetPosition = velocity + this->getPosition();
	
}
	
void Avatar::setPointerMiddleScreen(){
	SDL_Surface *surface = SDL_GetVideoSurface();
	m_pointerX = surface->w >> 1;
	m_pointerY = surface->h >> 1;
}

int Avatar::getPointerX(){
	return m_pointerX;
}
int Avatar::getPointerY(){
	return m_pointerY;
}

void Avatar::updateGeom(){
	Object3D::updateGeom();
		
}

void Avatar::setPosition(Vector3 &v){
	Object3D::setPosition( v );
	m_camera.setPosition( v );
}



void Avatar::onObjectCollision(Object3D* object3d, PhysicalContactPoint *contacts, unsigned int numOfContactPoints){
	
}

void Avatar::worldTargetWithCollision(PhysicalContactPoint *moveData){
	Object3D::worldTargetWithCollision(moveData);
}

void Avatar::worldDynamicWithCollision(PhysicalContactPoint *moveData){
	Object3D::worldDynamicWithCollision(moveData);
}


void Avatar::worldTargetWithoutCollision(PhysicalContactPoint *moveData){
	Object3D::worldTargetWithoutCollision(moveData);
}

void Avatar::worldDynamicWithoutCollision(PhysicalContactPoint *moveData){
	Object3D::worldDynamicWithoutCollision(moveData);
}

TiXmlElement *Avatar::entity2xml(){
	TiXmlElement* xmlElem = new TiXmlElement("InGENetMsg");
	Vector3 position = getPosition();
	Vector3 direction = getDirection();
	Vector3 velocity = getVelocity();
	
	xmlElem->SetAttribute( "TYPE" , "ENT" );
	xmlElem->SetAttribute( "UNIQUEID" , m_id );
	xmlElem->SetAttribute( "ENTTYPE" , m_type );	
	
	xmlElem->SetDoubleAttribute( "POS_X" , position[0] );
	xmlElem->SetDoubleAttribute( "POS_Y" , position[1] );
	xmlElem->SetDoubleAttribute( "POS_Z" , position[2] );
	
	xmlElem->SetDoubleAttribute( "DIR_X" , direction[0] );
	xmlElem->SetDoubleAttribute( "DIR_Y" , direction[1] );
	xmlElem->SetDoubleAttribute( "DIR_Z" , direction[2] );
	
	xmlElem->SetDoubleAttribute( "VEL_X" , velocity[0] );
	xmlElem->SetDoubleAttribute( "VEL_Y" , velocity[1] );
	xmlElem->SetDoubleAttribute( "VEL_Z" , velocity[2] );
	
	if (m_pModel)
		xmlElem->SetAttribute( "ANIM" , m_pModel->getAnimation( m_id) );
	
	Vector3 camPosition = m_camera.getPosition();
	Vector3 camViewPoint = m_camera.getViewPoint();
	Vector3 camUp = m_camera.getUp();
	
	xmlElem->SetDoubleAttribute( "CAMPOS_X" , camPosition[0] );
	xmlElem->SetDoubleAttribute( "CAMPOS_Y" , camPosition[1] );
	xmlElem->SetDoubleAttribute( "CAMPOS_Z" , camPosition[2] );
	
	xmlElem->SetDoubleAttribute( "CAMVP_X" , camViewPoint[0] );
	xmlElem->SetDoubleAttribute( "CAMVP_Y" , camViewPoint[1] );
	xmlElem->SetDoubleAttribute( "CAMVP_Z" , camViewPoint[2] );
	
	xmlElem->SetDoubleAttribute( "CAMUP_X" , camUp[0] );
	xmlElem->SetDoubleAttribute( "CAMUP_Y" , camUp[1] );
	xmlElem->SetDoubleAttribute( "CAMUP_Z" , camUp[2] );
	
	if (m_pModel)
		xmlElem->SetAttribute( "MODEL_DIR" , getModelDir() );
		
	
	return xmlElem;
}

void Avatar::updateFromXml(TiXmlElement *xml) {
	Object3D::updateFromXml(xml);
	
	Vector3 camPosition;
	Vector3 camViewPoint;
	Vector3 camUp;
		
		
	double tCamPos[3];
	double tCamVp[3];
	double tCamUp[3];
		
	xml->Attribute( "CAMPOS_X", &tCamPos[0] );
	xml->Attribute( "CAMPOS_Y", &tCamPos[1] );
	xml->Attribute( "CAMPOS_Z", &tCamPos[2] );
		
	xml->Attribute( "CAMVP_X", &tCamVp[0] );
	xml->Attribute( "CAMVP_Y", &tCamVp[1] );
	xml->Attribute( "CAMVP_Z", &tCamVp[2] );
		
	xml->Attribute( "CAMUP_X", &tCamUp[0] );
	xml->Attribute( "CAMUP_Y", &tCamUp[1] );
	xml->Attribute( "CAMUP_Z", &tCamUp[2] );
		
	camPosition.setXYZ( tCamPos[0], tCamPos[1], tCamPos[2]);
	camViewPoint.setXYZ( tCamVp[0], tCamVp[1], tCamVp[2]);
	camUp.setXYZ( tCamUp[0], tCamUp[1], tCamUp[2]);
	
	m_camera.setPosition( camPosition);
	m_camera.setViewPoint( camViewPoint);
	m_camera.setUp(camUp);
}

