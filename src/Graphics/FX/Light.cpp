/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004 Indigente


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

#include "Light.h"

using namespace InGE;

Light::Light(int i){
	Drawer *drawer = Drawer::getInstance();
	lightNumber = i;
	lightPosition.setXYZW(0, -1, 0, 0);
	difuseColor.setXYZW(1, 0, 0, 1);
	ambientColor.setXYZW(1, 1, 0, 1);
	specularColor.setXYZW(1,  1, 0,  1);

	drawer->enable(InGE_LIGHTING);
	drawer->enableLight(lightNumber);
	drawer->enable(InGE_COLOR_MATERIAL);
	drawer->enable(InGE_NORMALIZE);
	drawer->lightModel(InGE_LIGHT_MODEL_LOCAL_VIEWER, InGE_TRUE);
	drawer->lightModel(InGE_LIGHT_MODEL_TWO_SIDE, InGE_TRUE);
	drawer->material(InGE_FRONT_AND_BACK, InGE_AMBIENT, difuseColor);
	drawer->material(InGE_FRONT_AND_BACK, InGE_SPECULAR, specularColor);
} 

Light::~Light(){
}

void Light::setPosition(float x,float y,float z,float w){
	Drawer *drawer = Drawer::getInstance();
	lightPosition.setXYZW(x, y, z, w);
	drawer->light(GL_LIGHT0 + lightNumber,GL_POSITION, lightPosition);
}

void Light::setPosition(Vector4 &vet){
	Drawer *drawer = Drawer::getInstance();
	lightPosition = vet;
	drawer->light(GL_LIGHT0 + lightNumber,GL_POSITION, lightPosition);
}

void Light::setDifuseColor(float x,float y,float z,float w){
	Drawer *drawer = Drawer::getInstance();
	difuseColor.setXYZW(x, y, z, w);
	drawer->light(GL_LIGHT0 + lightNumber, GL_DIFFUSE, difuseColor);
}

void Light::setDifuseColor(Vector4 &vet){
	Drawer *drawer = Drawer::getInstance();
	difuseColor = vet;
	drawer->light(GL_LIGHT0 + lightNumber, GL_DIFFUSE, difuseColor);
}


void Light::setAmbientColor(float x,float y,float z,float w){
	Drawer *drawer = Drawer::getInstance();
	ambientColor.setXYZW(x, y, z, w);
	drawer->light(GL_LIGHT0 + lightNumber, GL_AMBIENT, ambientColor);
}

void Light::setAmbientColor(Vector4 &vet){
	Drawer *drawer = Drawer::getInstance();
	ambientColor = vet;
	drawer->light(GL_LIGHT0 + lightNumber, GL_AMBIENT, ambientColor);
}


void Light::setSpecularColor(float x,float y,float z,float w){
	Drawer *drawer = Drawer::getInstance();
	specularColor.setXYZW(x, y, z, w);
	drawer->light(GL_LIGHT0 + lightNumber, GL_SPECULAR, specularColor);
}

void Light::setSpecularColor(Vector4 &vet){
	Drawer *drawer = Drawer::getInstance();
	specularColor = vet;
	drawer->light(GL_LIGHT0 + lightNumber, GL_SPECULAR, specularColor);
}


void Light::setConstantAttenuation(float param){
	Drawer *drawer = Drawer::getInstance();
	drawer->light(GL_LIGHT0 + lightNumber, GL_CONSTANT_ATTENUATION, 1.0);

}
