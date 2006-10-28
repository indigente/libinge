/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004-2005 Indigente


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
#include "QShader.h"

#include "../../Base/TextureArray.h"

using namespace InGE;

QShader::QShader(string name){
	m_name = name;
	m_currentIndex = 0;
	m_blendOn = false;
	m_cullOn = false;
	m_cullMode = InGE_BACK;
	m_blendSrc = InGE_ONE;
	m_blendDst = InGE_ZERO;
	m_freq = -1.0f;
	m_vTextureId.clear();
	m_vTextureFileName.clear();
	m_lastTime = SDL_GetTicks();
}


QShader::~QShader(){
}


unsigned int QShader::getTextureId(){
	if(m_vTextureId.size())	return m_vTextureId[m_currentIndex];
	
	return 0;
}


void QShader::applyMode(){
	unsigned int currentTime = SDL_GetTicks();
//	Drawer *drawer = Drawer::getInstance();
	
	// Cull Face
//	if(m_cullOn){
//		drawer->enable(InGE_CULL_FACE);		
//		drawer->cullFace(m_cullMode);
//	}
//	else{
//		drawer->disable(InGE_CULL_FACE);
//	}
	
	
	// Blend function
//	if(m_blendOn){
//		drawer->blendFunc(m_blendSrc, m_blendDst);
//	}
//	else{
//		drawer->blendFunc(InGE_ONE, InGE_ZERO);
//	}
	
	// Update index to animap
	if(m_vTextureId.size() > 1 && m_freq > 0.0f){
		if( (currentTime - m_lastTime)*m_freq/1000 > 1.0f){ 
			m_currentIndex = (m_currentIndex+1) %m_vTextureId.size();
			m_lastTime = SDL_GetTicks();
		}
	}
	
}


void QShader::setCullMode(int cullMode){
	m_cullOn = true;
	m_cullMode = cullMode;
}


void QShader::setBlendFunc(int src, int dst){
	m_blendOn = true;
	m_blendSrc = src;
	m_blendDst = dst;
}


void QShader::setFreq(float freq){
	m_freq = freq;
}


void QShader::unsetBlend(){
	m_blendOn = false;
}


void QShader::unsetCull(){
	m_cullOn = false;
}


void QShader::addTextureFileName(string textureFileName){
	m_vTextureFileName.push_back(textureFileName);
}

void QShader::loadTextures(){
	TextureArray *textureArray = TextureArray::getInstance();
	unsigned int textureId;

	if(m_vTextureFileName.empty()){
		textureArray->loadTexture(m_name, &textureId);
		m_vTextureId.push_back(textureId);
		return;
	}
	
	for(unsigned int i =0; i< m_vTextureFileName.size(); i++){
		if(textureArray->loadTexture(m_vTextureFileName[i], &textureId) >= 0){
			m_vTextureId.push_back(textureId);
		}
		else {
			unsigned int pos = m_vTextureFileName[i].rfind('.');
			string filename = m_vTextureFileName[i].erase(pos);
			textureArray->loadTexture(filename, &textureId);
			m_vTextureId.push_back(textureId);
		}
	}
}


void QShader::print(){
	printf("%s %d texturas:",m_name.c_str(), m_vTextureId.size());
	if(m_blendOn) printf(" blendOn %d %d :", m_blendSrc, m_blendDst);
	if(m_cullOn) printf(" cullOn %d", m_cullMode);
	printf("\n");
	for(unsigned int i =0; i< m_vTextureFileName.size(); i++){
		printf("\t%s\n", m_vTextureFileName[i].c_str());
	}
	printf("\n");
}


string QShader::getName(){
	return m_name;
}


