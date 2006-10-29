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


#ifndef QENTITY_H
#define QENTITY_H
#include "../../../Math/Vector3.h"

#include <string>

namespace InGE{
	
	using std::string;

	typedef enum EntityType{InGE_QENTITY_INFO, InGE_QENTITY_LIGHT} EntityType;
	
	class QEntity{
		public:
			EntityType type;
			string	classname;
			Vector3	origin;
			 	
			QEntity();
			virtual ~QEntity();
			
			virtual void print()=0;
	};
	
	class QEntityInfo : public InGE::QEntity {
		public:
			float angle;
			string target;
		
			string dirName;
			float scale;
			
			QEntityInfo();
			~QEntityInfo();
			
			void print();
	};
	
	class QEntityLight : public InGE::QEntity{
		public:
			int	light;
			Vector3	color;
			string 	target;
			float 	radius;
			
			QEntityLight();
			~QEntityLight();
			
			void print();
			
	};

};

#endif // QENTITY_H
