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
#include "LightManager.h"

namespace InGE {

LightManager::LightManager(){
	m_ambientColor.setXYZW( 0.2, 0.2, 0.2, 1.0);
	m_localViewer = false;
	m_twoSidedLight = false;
	m_separateSpecularColor = InGE_SINGLE_COLOR;

}


LightManager::~LightManager(){
}


Vector4 LightManager::getAmbientColor() const{
  return m_ambientColor;
}


void LightManager::setAmbientColor(const Vector4& light){
	Drawer *drawer = Drawer::getInstance();
	m_ambientColor = light;
	
	drawer->light(GL_AMBIENT, InGE_LIGHT_MODEL_AMBIENT, m_ambientColor);
}

bool LightManager::getLocalViewer() const {
	return m_localViewer;
}


void LightManager::setLocalViewer(bool theValue) {
	Drawer *drawer = Drawer::getInstance();
	m_localViewer = theValue;
	
	drawer->lightModel(InGE_LIGHT_MODEL_LOCAL_VIEWER, m_localViewer);
}


bool LightManager::getTwoSidedLight() const {
    return m_twoSidedLight;
}


void LightManager::setTwoSidedLight(bool theValue) {
	Drawer *drawer = Drawer::getInstance();
	m_twoSidedLight = theValue;
	
	drawer->lightModel(InGE_LIGHT_MODEL_TWO_SIDE, m_twoSidedLight);
}

void LightManager::setSeparateSpecularColor(const EnumDrawer& theValue) {
	Drawer *drawer = Drawer::getInstance();
	m_separateSpecularColor = theValue;
	
	drawer->lightModel(InGE_LIGHT_MODEL_COLOR_CONTROL, m_separateSpecularColor);
}

EnumDrawer LightManager::getSeparateSpecularColor() const {
    return m_separateSpecularColor;
}


Light *LightManager::getStaticLight(int index) {
	if (index >= m_vStaticLight.size())
		return NULL;
	
	return m_vStaticLight[index];
}


void LightManager::addStaticLight(Light *theValue) {
    m_vStaticLight.push_back(theValue);
}

Light *LightManager::getDinamicLight(int index) {
	if (index >= m_vDinamicLight.size())
		return NULL;
	
	return m_vDinamicLight[index];
}


void LightManager::addDinamicLight(Light *theValue) {
    m_vDinamicLight.push_back(theValue);
}

}

