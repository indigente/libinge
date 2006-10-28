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
#include "CurrentAnimInfo.h"

namespace InGE {

CurrentAnimInfo::CurrentAnimInfo(){
	m_currAnim = "IDLE";
	m_nextAnim = "IDLE";
	m_interpolation = 0;
	m_keyFrameIndex = 0;
	m_lastDrawTime = 0;
	m_materialIndex = 0;
	m_speed = 10;
	
	m_isDraw = true;
}


CurrentAnimInfo::~CurrentAnimInfo(){
}

string CurrentAnimInfo::getCurrAnim(){
	return m_currAnim;
}

string CurrentAnimInfo::getNextAnim(){
	return m_nextAnim;
}

int CurrentAnimInfo::getKeyFrameIndex(){
	return m_keyFrameIndex;
}
int CurrentAnimInfo::getMaterialIndex(){
	return m_materialIndex;
}
float CurrentAnimInfo::getSpeed(){
	return m_speed;
}
float CurrentAnimInfo::getInterpolation(){
	return m_interpolation;
}

void CurrentAnimInfo::setCurrAnim(string currAnim){
	m_currAnim = currAnim;
}

void CurrentAnimInfo::setNextAnim(string nextAnim){
	m_nextAnim = nextAnim;
}

void CurrentAnimInfo::setKeyFrameIndex(int keyFrameIndex){
	m_keyFrameIndex = keyFrameIndex;
}
void CurrentAnimInfo::setMaterialIndex(int materialIndex){
	m_materialIndex = materialIndex;
}
void CurrentAnimInfo::setSpeed(float speed){
	m_speed = speed;
}

void CurrentAnimInfo::linearInterpolation(int maxKeyFrame){
	m_keyFrameIndex %= maxKeyFrame;
	// Tempo atual
	float currentTime = SDL_GetTicks();

	// Tempo passado entre inicio do keyframe e o tempo atual
	float elapsedTime = currentTime - m_lastDrawTime;

	if(elapsedTime < (1000.0f / m_speed)){
		// Parametro do interpolacao para o proximo frame
		m_interpolation = elapsedTime / (1000.0f / m_speed);
	} else {
		// Caso tenha passado pro proximo KeyFrame, atualiza o indice
		m_keyFrameIndex++;
		if (m_keyFrameIndex >= maxKeyFrame){
			m_keyFrameIndex %= maxKeyFrame;	
			m_currAnim = m_nextAnim;
		}
		m_lastDrawTime = currentTime;
		m_interpolation = 0;
	}
}

void CurrentAnimInfo::setIsDraw(bool m_isDraw){
	this->m_isDraw = m_isDraw;
}

bool CurrentAnimInfo::getIsDraw(){
	return m_isDraw;
}


}
