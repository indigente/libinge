/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004 Indigente


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

#include "Plane.h"

namespace InGE{

Plane::Plane(Mesh * pMesh){
	if (pMesh){
		m_pMesh = pMesh;
		m_pVolumeInfo = pMesh->pCalcVolumeInfo();
		m_name = m_pMesh->getName();
	} else {
		m_pMesh = NULL;
		m_pVolumeInfo = NULL;
	}
}

Plane::~Plane(){
	delete m_pMesh;
	delete m_pVolumeInfo;
}

void Plane::setName(std::string name){
	m_name = name;
}

void Plane::addMaterial(string filenameTex){
	MaterialInfo texture;
	texture.setTexture(filenameTex);
	m_pMesh->addMaterial(texture);
}

std::string Plane::getName(){
	return m_name;
}
bool Plane::getBlend(){
	return m_pMesh->getBlend();
}
void Plane::drawModel(string entityID){
	Drawer *drawer = Drawer::getInstance();

	m_pMesh->draw();
	
}

vector<VolumeInfo *> Plane::getVetVolumeInfo(){
	if (!m_pVolumeInfo)
		m_pVolumeInfo = m_pMesh->pCalcVolumeInfo();
	vector<VolumeInfo *> vetVolumeInfo;
	vetVolumeInfo.push_back( m_pVolumeInfo );
	return vetVolumeInfo;
}

unsigned int	Plane::getNumAnimation(){ 
	return 1;
}

}
