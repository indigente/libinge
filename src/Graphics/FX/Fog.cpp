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

#include "Fog.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

using namespace InGE;


Fog::Fog(): fogColor(1,1,1,1){
	Drawer *drawer = Drawer::getInstance();
	this->fogMode = InGE_EXP2;
	this->fogDensity = 0.2f;
	this->fogStart = 0.0f;
	this->fogEnd = 10.0f;
	drawer->fog(GL_FOG_MODE, fogMode);
	drawer->fog(GL_FOG_COLOR, fogColor);
	drawer->fog(GL_FOG_DENSITY, fogDensity);
	drawer->fog(GL_FOG_START, fogStart);
	drawer->fog(GL_FOG_END, fogEnd);
	drawer->fog(GL_FOG_HINT, GL_DONT_CARE);
}

Fog::~Fog(){
}

void Fog::setFogColor(float r, float g, float b, float a){
	Drawer *drawer = Drawer::getInstance();
	this->fogColor.setX(r);
	this->fogColor.setY(g);
	this->fogColor.setZ(b);
	this->fogColor.setW(a);
	drawer->fog(GL_FOG_COLOR, fogColor);
}

void Fog::setFogMode(EnumDrawer mode){
	Drawer *drawer = Drawer::getInstance();
	this->fogMode = mode;
	drawer->fog(GL_FOG_MODE, fogMode);
}

void Fog::setFogDensity(float density){
	Drawer *drawer = Drawer::getInstance();
	this->fogDensity = density;
	drawer->fog(GL_FOG_DENSITY, fogDensity);
}

void Fog::setFogStart(float start){
	Drawer *drawer = Drawer::getInstance();
	this->fogStart = start;
	drawer->fog(GL_FOG_START, fogStart);
}

void Fog::setFogEnd(float end){
	Drawer *drawer = Drawer::getInstance();
	this->fogEnd = end;
	drawer->fog(GL_FOG_END, fogEnd);
}
			  	
Vector4 Fog::getFogColor(){
	return this->fogColor;
}

EnumDrawer Fog::getFogMode(){
	return this->fogMode;
}

float Fog::getFogDensity(){
	return this->fogDensity;
}

float Fog::getFogStart(){
	return this->fogStart;
}

float Fog::getFogEnd(){
	return this->fogEnd;
}
