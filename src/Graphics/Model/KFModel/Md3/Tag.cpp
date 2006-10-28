/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#include "Tag.h"
using namespace InGE;
using namespace InGE;
using std::string;
using std::vector;

//DEBUG
#include <iostream>
using namespace std;

Tag::Tag(string name, vec3_t position, float *rotation){
	m_name = name;
	std::transform(m_name.begin(), m_name.end(), m_name.begin(), (int(*)(int)) toupper);
	
	if ( m_name.find("TAG_", 0) == 0){
		m_name.erase(0,4);
	}
	
	m_pOrigin = new Vector3(position[0], position[1], position[2]);

	m_pRotation = new MatTransform;
	memcpy(m_pRotation->axis , rotation, sizeof(float)*9);
}

Tag::~Tag(){}

void Tag::setName(string name){
	m_name = name;
}

void Tag::setPosition(vec3_t position){
	m_pOrigin = new Vector3(position[0], position[1], position[2]);
}

void Tag::setRotation(float	*rotation){
	m_pRotation = new MatTransform;
	memcpy(m_pRotation->axis , rotation, sizeof(float)*9);
}

string Tag::getName(){
	return m_name;
}

Vector3 *Tag::getPosition(){
	return m_pOrigin;
}

MatTransform *Tag::getRotation(){
	return m_pRotation;
}
