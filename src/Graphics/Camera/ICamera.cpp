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

#include "ICamera.h"

using namespace InGE;

/**
 * Construtor padr�
 * Inicializa a camera na posi�o (0,0,0)
 * Olhando para (0,1,0), e orientado para (0,0,1)
 */
ICamera::ICamera() : IEntity("ICamera"){
	m_position.setXYZ (0.0f, 0.0f, 0.0f);
	m_up.setXYZ       (0.0f, 0.0f, 1.0f);
	m_viewPoint.setXYZ(0.0f, 1.0f, 0.0f);
	
	m_pVolumeInfo = new VolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30);
}

/**
 * Construtor
 * @param Vector3 position - Indica a posicao da camera
 * @param Vector3 viewPoint - Indica o ponto para onde a camera olha
 * @param Vector3 up - Indica a orienta�o da camera
 */
ICamera::ICamera(Vector3 position, Vector3 viewPoint, Vector3 up) : IEntity("ICamera"){
	m_position = position;
	m_viewPoint = viewPoint;
	m_up = up;
	
	m_pVolumeInfo = new VolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30);
}

/**
 * Destrutor padr�
 */
ICamera::~ICamera(){
}
	
/**
 * Seta uma posicao para a camera
 * @param Vector3 &position - Posi�o da camera
 */
void ICamera::setPosition(const Vector3 &position){
	m_position = position;
	m_pVolumeInfo->setVolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30 );
}

/**
 * Seta o ponto para o qual a camera olha
 * @param Vector3 &viewPoint - Ponto para o qual a camera olha
 */
void ICamera::setViewPoint(const Vector3 &viewPoint){
	m_viewPoint = viewPoint;
}

/** 
 * Seta orienta�o da camera
 * @param Vector3 &up - Orienta�o da camera
 */
void ICamera::setUp(const Vector3 &up){
	m_up = up;
}
	
/**
 * @return Retorna a posi�o da camera
 */
Vector3 ICamera::getPosition(){
	return m_position;
}

/**
 * @return Retorna o ponto para o qual a camera olha
 */
Vector3 ICamera::getViewPoint(){
	return m_viewPoint;
}

/**
 * @return Retorna a orienta�o da camera
 */
Vector3 ICamera::getUp(){
	return m_up;
}

TiXmlElement *ICamera::entity2xml(){
	TiXmlElement* xmlElem = new TiXmlElement("InGENetMsg");
	Vector3 camPosition = getPosition();
	Vector3 camViewPoint = getViewPoint();
	Vector3 camUp = getUp();
		
	xmlElem->SetAttribute( "TYPE" , "ENT" );
	xmlElem->SetAttribute( "UNIQUEID" , m_id );
	xmlElem->SetAttribute( "ENTTYPE" , m_type );
	
	xmlElem->SetDoubleAttribute( "POS_X" , camPosition[0] );
	xmlElem->SetDoubleAttribute( "POS_Y" , camPosition[1] );
	xmlElem->SetDoubleAttribute( "POS_Z" , camPosition[2] );
		
	xmlElem->SetDoubleAttribute( "CAMVP_X" , camViewPoint[0] );
	xmlElem->SetDoubleAttribute( "CAMVP_Y" , camViewPoint[1] );
	xmlElem->SetDoubleAttribute( "CAMVP_Z" , camViewPoint[2] );
		
	xmlElem->SetDoubleAttribute( "CAMUP_X" , camUp[0] );
	xmlElem->SetDoubleAttribute( "CAMUP_Y" , camUp[1] );
	xmlElem->SetDoubleAttribute( "CAMUP_Z" , camUp[2] );
	
	return xmlElem;
}


