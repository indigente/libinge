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
#ifndef INFOENTITY_H
#define INFOENTITY_H

#include "IEntity.h"
#include "../Math/Vector4.h"

namespace InGE{
/**
	@author Ivan Medeiros Monteiro <fehler@gmail.com>
*/
class InfoEntity :  public InGE::IEntity{
	private:
		string m_className;
		Vector3 m_position;
		Vector4 m_rotation;
	
	
	public:
   	InfoEntity();

		~InfoEntity();
		
		void setClassName(string className);
		void setPosition(const Vector3 &v);
		void setRotation(Vector4 rotation);
		
		string getClassName( );
		Vector3 getPosition( );
		Vector4 getRotation( );
		
		virtual Vector3 getDirection(){};
		virtual void setDirection(const Vector3 &v){};
		virtual Vector3 getVelocity(){};
		virtual void setVelocity(const Vector3 &v){};

		virtual TiXmlElement *entity2xml();
		virtual void updateFromXml(TiXmlElement *xml);

};
}
#endif
