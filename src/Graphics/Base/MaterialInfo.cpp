/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2006 Indigente


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

#include "MaterialInfo.h"
#include "TextureArray.h"

using namespace InGE;

#include <iostream>
using namespace std;

/**
 * Construtor
 */
MaterialInfo::MaterialInfo(){
	m_alpha = false;
}

/**
 * Destrutor
 */
MaterialInfo::~MaterialInfo(){
}

/**
 * Seta a textura que deverá ser utilizada por esse material
 * A textura será carregada, caso ainda não esteja carregada.
 * @param string filename - Indica o arquivo que contem a textura que será associada a este material.
 */
void MaterialInfo::setTexture(string filename){
	TextureInfo *info = TextureArray::getInstance()->getInfo(filename);
	m_filename = filename;
	m_textureId = info->textureID;
	m_alpha = info->alpha;
}

/**
 * Seta o identificador de textura
 * @param int id - Identificador de textura
 */
void MaterialInfo::setId(int id){
	m_textureId = id;
}


/**
 * @return Retorna o nome do arquivo que contém a textura
 */
string MaterialInfo::getFileName(){
	return m_filename;
}

/**
 * @return Retorna o ID da textura
 */
int MaterialInfo::getId(){
	return m_textureId;;
}
/**
 * @return Retorna se existe o canal alfa no material
 */
bool MaterialInfo::getBlend(){
	return m_alpha;
}
