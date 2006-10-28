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
#include "InfoEntity.h"
namespace InGE{
InfoEntity::InfoEntity() : IEntity("InfoEntity"){

}

InfoEntity::~InfoEntity(){
}

void InfoEntity::setClassName(string className){
	m_className = className;
}
void InfoEntity::setPosition(const Vector3 &v){
	m_position = v;
}
void InfoEntity::setRotation(Vector4 rotation){
	m_rotation = rotation;
}

string InfoEntity::getClassName( ){
	return m_className;
}
Vector3 InfoEntity::getPosition( ){
	return m_position;
}
Vector4 InfoEntity::getRotation( ){
	return m_rotation;
}

TiXmlElement *InfoEntity::entity2xml(){
	
}
void InfoEntity::updateFromXml(TiXmlElement *xml){
	double posX, posY, posZ;
	Vector3 position;
	
	xml->Attribute( "POS_X" , &posX );
	xml->Attribute( "POS_Y" , &posY );
	xml->Attribute( "POS_Z" , &posZ );
	
	position.setXYZ(posX, posY, posZ);
	this->setPosition(position);

}


}
