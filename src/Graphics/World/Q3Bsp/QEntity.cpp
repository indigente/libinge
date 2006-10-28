/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente


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

#include "QEntity.h"

using namespace InGE;

// Entities
QEntity::QEntity(){
}

QEntity::~QEntity(){
}


// Info Entities
QEntityInfo::QEntityInfo(){
	type = InGE_QENTITY_INFO;
}

QEntityInfo::~QEntityInfo(){
}

void QEntityInfo::print(){
	printf("EntityInfo %s\n",classname.c_str());
	printf("\tOrigin (%f, %f, %f)\n", origin[0], origin[1], origin[2]);
	printf("\tAngle %f\n", angle);
	printf("\tTarget %s\n", target.c_str());
	printf("\tdirName %s\n", dirName.c_str());
	printf("\tscale %f\n", scale);
}


// Light Entities
QEntityLight::QEntityLight(){
	type = InGE_QENTITY_LIGHT;
}

QEntityLight::~QEntityLight(){
}

void QEntityLight::print(){
	printf("EntityLight %s\n",classname.c_str());
	printf("\tOrigin (%f, %f, %f)\n", origin[0], origin[1], origin[2]);
	printf("\tTarget %s\n", target.c_str());
	printf("\tColor (%f, %f, %f)\n", color[0],color[1],color[2]);
	printf("\tLight %d\n", light );
	printf("\tRadius %f\n", radius);
}
