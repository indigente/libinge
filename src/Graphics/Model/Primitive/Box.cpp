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

#include "Box.h"

namespace InGE{

Box::Box(Mesh *pMesh){
	if (pMesh){
		m_pMesh = pMesh;
		m_pVolumeInfo = pMesh->pCalcVolumeInfo();
		m_name = m_pMesh->getName();
	} else {
		m_pMesh = NULL;
		m_pVolumeInfo = NULL;
	}

}

Box::~Box(){}

void Box::setName(std::string name){
	m_name = name;
}

void Box::addMaterial(string filenameTex){
	MaterialInfo texture;
	texture.setTexture(filenameTex);
	m_pMesh->addMaterial(texture);
}

std::string Box::getName(){
	return m_name;
}
bool Box::getBlend(){
	return m_pMesh->getBlend();
}


void Box::drawModel(string entityID){
	Drawer *drawer = Drawer::getInstance();

	m_pMesh->draw();

}



vector<VolumeInfo *> Box::getVetVolumeInfo(){
	if (!m_pVolumeInfo)
		m_pVolumeInfo = m_pMesh->pCalcVolumeInfo();
	vector<VolumeInfo *> vetVolumeInfo;
	vetVolumeInfo.push_back( m_pVolumeInfo );
	return vetVolumeInfo;
}

unsigned int	Box::getNumAnimation(){ 
	return 1;
}

void Box::setDraw(string entityID,bool draw) {
  0;
  //Falta alquem implementar...
}


void Box::setDraw(string entityID,bool draw, string partToDraw){
  0;
  //Falta alquem implementar...
}

}
