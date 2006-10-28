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
#include "CameraFP.h"

using namespace InGE;
using namespace std;
CameraFP::CameraFP(){
	m_position.setXYZ (0.0f, 0.0f, 0.0f);
	m_up.setXYZ       (0.0f, 0.0f, 1.0f);
	m_viewPoint.setXYZ(0.0f, 1.0f, 0.0f);
	
	m_pVolumeInfo = new VolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30);
}

CameraFP::CameraFP(Vector3 position, Vector3 viewPoint, Vector3 up){
	m_position = position;
	m_viewPoint = viewPoint;
	m_up = up;
	
	m_pVolumeInfo = new VolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30);
}

CameraFP::~CameraFP(){
}


/** 
 * Seta dire�o da camera
 * @param Vector3 &direction - Dire�o da camera
 */
void CameraFP::setDirection(const Vector3 &direction){
	Vector3 dir = direction;
	dir.normalize();
	m_viewPoint = m_position + dir;

}

/** 
 * Seta deslocamento lateral da camera
 * @param Vector3 &strafe - Deslocamento lateral da camera
 */
void CameraFP::setStrafe(const Vector3 &strafe ){
	m_viewPoint = m_position + strafe.cross(m_up);
}



/** 
 * Seta posi�o de conex� da camera
 * @param Vector3 &attachPosition - Posi�o de conex� da camera
 */
void CameraFP::setAttachPosition(const Vector3 &attachPosition){
	m_position = attachPosition;
	m_viewPoint = m_position + Vector3(0,1,0);
}

/** 
 * Seta eixo de conex� da camera
 * @param Vector3 &attachAxis - Eixo de conex� da camera
 */
void CameraFP::setAttachAxis(const Vector3 &attachAxis){
	m_up = attachAxis;
}

/**
 *  Rotaciona o ponto de vista da camera
 * @param Vector4 &axis - Ângulo e Eixo de rota�o
 */
void CameraFP::rotate( Vector4 &axis){
	Vector3 newView;

	// Pega o vetor de visao
	Vector3 view = this->getDirection();
	// Calcula apenas uma vez
	float cosA = cos(axis[0]);
	float sinA = sin(axis[0]);
	float subCosA = 1 - cosA;
	float x = axis[1];
	float y = axis[2];
	float z = axis[3];

	// Acha o nova posicao X
	newView.setX( ( cosA + subCosA * x * x ) * view[0] + 
		      ( subCosA * x * y - z * sinA ) * view[1] +
		      ( subCosA * x * z + y * sinA ) * view[2] );
				
	// Acha o nova posicao Y
	newView.setY( ( subCosA * x * y + z * sinA ) * view[0] +
		      ( cosA + subCosA * y * y ) * view[1] +
		      ( subCosA * y * z - x * sinA ) * view[2] );

	// Acha o nova posicao Z
	newView.setZ( ( subCosA * x * z - y * sinA ) * view[0] +
		      ( subCosA * y * z + x * sinA ) * view[1] +
		      ( cosA + subCosA * z * z ) * view[2]);

	
	this->setDirection(newView);
}

/**
 *  Rotaciona o ponto de vista da camera
 * @param float angle - �gulo de rota�o em graus
 * @param Vector3 &axis - Eixo de rota�o
 */
void CameraFP::rotate(float angle, Vector3 &axis){
	Vector4 v(angle, axis[0], axis[1], axis[2]);
	this->rotate( v );
}

/**
 *  Move a camera
 * @param Vector3 direction - Indica a dire�o a qual a camera deve se deslocar
 */
void CameraFP::move(const Vector3 &target){
 	Vector3 newPosition;
	newPosition = this->checkColision(m_position, target);

	m_viewPoint += newPosition;
	m_position += newPosition;
}
/**
 *  Desloca a camera
 * @param Vector3 direction - Indica a dire�o a qual a camera deve se deslocar
 */
void CameraFP::setPosition(const Vector3 &position){
	Vector3 direction = getDirection();
	m_position = position;
	setDirection( direction );
}

/**
 * @return Retorna o vetor de dire�o
 */
Vector3 CameraFP::getDirection(){
	Vector3 direction = m_viewPoint - m_position;
	direction.normalize();
	return direction;
}

/**
 * @return Retorna o vetor de deslocamento lateral
 */
Vector3 CameraFP::getStrafe(){
	Vector3 strafe = m_up.cross( m_viewPoint - m_position );;
	strafe.normalize();
	return strafe;
}

/**
 * @return Retorna o vetor de posi�o do eixo
 */
Vector3 CameraFP::getAttachPosition(){
	return m_position;
}

/**
 * @return Retorna o vetor de eixo
 */
Vector3 CameraFP::getAttachAxis(){
	return m_up;
}

/**
 * Checa colis� com o IScene
 * @return Retorna o vetor com a posi�o final
 */
Vector3 CameraFP::checkColision(const Vector3 &start,const Vector3 &target){
	return target;
}


/**
 * @return Retorna as informa�es do Volume da camera
 */
VolumeInfo *CameraFP::pGetVolumeInfo(){
	return m_pVolumeInfo;
}

void CameraFP::setViewByPointer(int pointerX,int pointerY){
	int middleX = 320, middleY = 240;
	float angleY = 0.0f , angleZ = 0.0f; 
	SDL_Surface *surface = SDL_GetVideoSurface();
	static float currentRotX = 0.0f;

	if(surface){
		middleX = surface->w >> 1;
		middleY = surface->h >> 1;
	}
	
	if((middleX == pointerX) && (middleY == pointerY)) return ;
	
	angleY =    (middleX - pointerX)/400.0f ;
	angleZ =  - (middleY - pointerY)/400.0f;

	currentRotX -= angleZ ;

	Vector3 up = this->getUp();
 	Vector3 strafe = this->getStrafe();
	
	if(currentRotX > 1.0f){
		currentRotX = 1.0f;
		this->rotate(angleY, up);		
	}
	else if(currentRotX < -1.0f){
		currentRotX = -1.0f;
		this->rotate(angleY, up);
	}
	else{ 
		this->rotate(angleZ, strafe);
		this->rotate(angleY, up);
	}
}
