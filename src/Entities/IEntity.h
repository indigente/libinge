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
#ifndef IENTITY_H
#define IENTITY_H

#include <string>
#include <vector>
#include <iostream>
#include "../Math/Vector3.h"
#include "../Util/TinyXML/tinyxml.h"
#include "../Network/NetControl.h"

namespace InGE {
		
using std::string;
using std::vector;

/**
	@author Ivan Medeiros Monteiro <fehler@gmail.com>
*/
class IEntity {
	protected:
		string m_type;
		string m_id;
		vector<TiXmlElement *> m_vetXML;
		
	public:
		IEntity(string type);
		~IEntity();
		void	setType(string type);
		string &getType();
		
		void setId(string id);
		string &getId();
		
		
		virtual Vector3 getPosition() =0;
		virtual void setPosition(const Vector3 &v)=0;

		virtual Vector3 getDirection() =0;
		virtual void setDirection(const Vector3 &v)=0;

		virtual Vector3 getVelocity() =0;
		virtual void setVelocity(const Vector3 &v)=0;

		virtual TiXmlElement *entity2xml()=0;
		virtual void addXML(TiXmlElement *xml);
		virtual void updateFromXml(TiXmlElement *xml);
		virtual void updateAttributes();
};
	


}

#endif
