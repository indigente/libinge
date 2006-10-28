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
#include "IEntity.h"


using namespace InGE;

IEntity::IEntity(string type){
	m_type = type;
	m_id = "unknown";
}

IEntity::~IEntity(){
}

void IEntity::setType( string type ){
	m_type = type;
}

string &IEntity::getType(){
	return m_type;
}


void IEntity::setId(string id){
	m_id = id;
}


string &IEntity::getId(){
	return m_id;
}


void IEntity::updateFromXml( TiXmlElement *xml) {
	double posX, posY, posZ;
	double dirX, dirY, dirZ;
	double velX, velY, velZ;
	Vector3 position, direction, velocity;
	
// 	m_type = xml->Attribute( "ENTTYPE" );FIXME::Armengue pra o jogo em rede.
	
	xml->Attribute( "POS_X" , &posX );
	xml->Attribute( "POS_Y" , &posY );
	xml->Attribute( "POS_Z" , &posZ );
	
	xml->Attribute( "DIR_X" , &dirX );
	xml->Attribute( "DIR_Y" , &dirY );
	xml->Attribute( "DIR_Z" , &dirZ );
	
	xml->Attribute( "VEL_X" , &velX );
	xml->Attribute( "VEL_Y" , &velY );
	xml->Attribute( "VEL_Z" , &velZ );

	position.setXYZ(posX, posY, posZ);
	direction.setXYZ(dirX, dirY, dirZ);
	velocity.setXYZ(velX, velY, velZ);
	
	this->setPosition(position);
	this->setDirection(direction);
	this->setVelocity(velocity);
}

void IEntity::addXML(TiXmlElement *pXml){
	TiXmlElement *xml = new TiXmlElement(*pXml);
	m_vetXML.push_back(xml);
}

void IEntity::updateAttributes(){
	int last = m_vetXML.size() - 1;
	if (last >=0){
		updateFromXml(m_vetXML[last]);
		
		for (int index = 0; index < m_vetXML.size(); index++){
			if (m_vetXML[index])
				delete m_vetXML[index];
		}
		m_vetXML.clear();
	}
}

#if 0

/**
 * 
 * @param pw 
 * @param pModel 
 * @param pScene 
 * @return 
 */
IEntity::IEntity(PhysicalWorld *pw, IModel *pModel, IScene *pScene): PhysicalBody(pw){
	m_pModel = pModel;
	m_pScene = pScene;
	
	m_pGeom = NULL;
	
	if (m_pModel)
		this->setModel(m_pModel);
}

/**
 * Destrutor de IEntity
 */
IEntity::~IEntity(){
	delete m_pGeom;
}


/**
 * 
 * @param type 
 */
void IEntity::setType(string type){
	m_type = type;
}

/**
 * 
 * @param pScene 
 */
void IEntity::setScene(IScene *pScene){
	m_pScene = pScene;
}

/**
 * Muda o modelo da Entidade
 * @param pModel 
 */
void IEntity::setModel(IModel *pModel){
	if (!pModel) return;
	m_pModel = pModel;
	
	if (m_pGeom)
		delete m_pGeom;
	
	vector<VolumeInfo *> vetVolumeInfo = m_pModel->getVetVolumeInfo();
	if (vetVolumeInfo.size() > 1){
		PhysicalSpace *pSpace = new PhysicalSpace(InGE_SIMPLE_SPACE);
		
		for(int volumeIndex = 0; volumeIndex < vetVolumeInfo.size(); volumeIndex++){
			GeomSphere *pGeomSphere = new GeomSphere( vetVolumeInfo[volumeIndex]->getRadius() );
			pGeomSphere->setPosition( vetVolumeInfo[volumeIndex]->getOrigin() + m_position );
			pSpace->add( *pGeomSphere );
		}
		
		m_pGeom = pSpace;
		
	} else if (vetVolumeInfo.size() == 1){
		GeomSphere *pGeomSphere = new GeomSphere( vetVolumeInfo[0]->getRadius() );
		m_pGeom = pGeomSphere;
	}
}

/**
 * 
 * @return 
 */
PhysicalGeom *IEntity::pGetPhysicalGeom(){
	return m_pGeom;
}

/**
 * 
 * @return 
 */
string IEntity::getType(){
	return m_type;
}

/**
 * 
 * @return 
 */
IScene *IEntity::getScene(){
	return m_pScene;
}

/**
 * 
 * @return 
 */
IModel *IEntity::getModel(){
	return m_pModel;
}

/**
 * 
 * @return 
 */
bool IEntity::getBlend(){
	if (m_pModel){
		return m_pModel->getBlend();
	}
	return false;
}

/**
 * 
 */
void IEntity::updateGeom(){
	if (m_pModel) {
		vector<VolumeInfo *> vetVolumeInfo = m_pModel->getVetVolumeInfo();
		for (int volumeIndex = 0; volumeIndex < vetVolumeInfo.size(); volumeIndex++){
/*			if (m_pPhysicalSpace[volumeIndex].getClass() == 0)
				((GeomSphere *)m_pPhysicalSpace->getGeom( volumeIndex))->setRadius( vetVolumeInfo[volumeIndex]->getRadius() );
			m_pPhysicalSpace[volumeIndex].setPosition( vetVolumeInfo[volumeIndex]->getOrigin() );FIXME
*/		}
	}
}




#endif
