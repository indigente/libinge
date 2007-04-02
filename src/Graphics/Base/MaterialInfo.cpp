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
	m_emissive = false;
		
	m_face = InGE_FRONT_AND_BACK;
	
	m_color.setXYZW(1.0,1.0,1.0,1.0);				// Cor do objeto
	m_specular.setXYZW(1.0,1.0,1.0,1.0);
	m_shininess = 64;
	m_emissiveColor.setXYZW(1.0,1.0,1.0,1.0);

}

/**
 * Destrutor
 */
MaterialInfo::~MaterialInfo(){
}

/**
 * Seta a textura que dever�ser utilizada por esse material
 * A textura ser�carregada, caso ainda n� esteja carregada.
 * @param string filename - Indica o arquivo que contem a textura que ser�associada a este material.
 */
void MaterialInfo::setTexture(string filename){
	TextureInfo *info = TextureArray::getInstance()->getInfo(filename);
	if(info) {
		m_filename = filename;
		m_textureId = info->textureID;
		m_alpha = info->alpha;
    }
}

/**
 * Seta o identificador de textura
 * @param int id - Identificador de textura
 */
void MaterialInfo::setId(int id){
	m_textureId = id;
}


/**
 * @return Retorna o nome do arquivo que cont� a textura
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


Vector4 MaterialInfo::getColor() const{
  return m_color;
}


void MaterialInfo::setColor(const Vector4& theValue){
  m_color = theValue;
}


bool MaterialInfo::getEmissive() const{
  return m_emissive;
}


void MaterialInfo::setEmissive(bool theValue){
  m_emissive = theValue;
}


EnumDrawer MaterialInfo::getFace() const{
  return m_face;
}


void MaterialInfo::setFace(const EnumDrawer& theValue){
  m_face = theValue;
}


Vector4 MaterialInfo::getSpecular() const{
  return m_specular;
}


void MaterialInfo::setSpecular(const Vector4& theValue){
  m_specular = theValue;
}


int MaterialInfo::getShininess() const{
  return m_shininess;
}


void MaterialInfo::setShininess(const int& theValue){
  m_shininess = theValue;
}

void MaterialInfo::apply(EnumDrawer textureChannel){
	Drawer *drawer = Drawer::getInstance();
		
	drawer->activeTextureARB(textureChannel);
	drawer->enable(InGE_TEXTURE_2D);
	drawer->bindTexture(InGE_TEXTURE_2D, m_textureId );

	drawer->material(m_face, InGE_AMBIENT_AND_DIFFUSE, m_color);
	drawer->material(m_face, InGE_SPECULAR, m_specular);
	drawer->material(m_face, InGE_SHININESS, m_shininess);
	if(m_emissive)
		drawer->material(m_face, InGE_EMISSION, m_emissiveColor);
}
