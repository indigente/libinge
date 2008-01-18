/*
  -----------------------------------------------------------------------------
  This source file is part of Indigente Game Engine
  Indigente - Interactive Digital Entertainment
  For the latest info, see http://indigente.dcc.ufba.br

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

/**
   @file IEntity.h
   @brief This file stores the IEntity class definition
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
	   @brief An interface for entity classes.
	   
	   An entity is an object which has a defined position into the game
	   map. It also has velocity and direction. Examples:
	   - Player character
	   - Game monsters
	   - Bullets
	   - bee swarms (!)
	*/
	class IEntity {
	protected:
		string m_type; ///< Type of the entity
		string m_id; ///< Entity's identifier 
		vector<TiXmlElement *> m_vetXML; /* XXXlucaspm: xml?? Alguém pode comentar isso aqui pra mim? */
		
	public:
		IEntity(string type); ///< Class constructor (requires type as parameter)
		virtual ~IEntity(); ///< Destructor (must be defined by its derived classes)
		void	setType(string type); ///< It changes object types
		string &getType(); ///< It gets object type
		
		void setId(string id); ///< It changes the object identifier
		string &getId(); ///< It gets object identifier
		
		
		virtual Vector3 getPosition() =0; ///< It gets the object position (must be defined by its derived classes)
		virtual void setPosition(const Vector3 &v)=0; ///< It sets the object position (must be defined by its derived classes)

		virtual Vector3 getDirection() =0; ///< It gets the object direction (must be defined by its derived classes)
		virtual void setDirection(const Vector3 &v)=0; ///< It sets the object direction (must be defined by its derived classes)

		virtual Vector3 getVelocity() =0; ///< It gets the object velocity (must be defined by its derived classes)
		virtual void setVelocity(const Vector3 &v)=0; ///< It sets the object velocity (must be defined by its derived classes)
		virtual void addVelocity(const Vector3 &v)=0; ///< It adds the passed velocity to object's current velocity (must be defined by its derived classes)

		/* XXXlucaspm: warning: the following descriptions are based on my theories about them!!! Check them out!!!
		   if they are not precise, edit them! */
		virtual TiXmlElement *entity2xml()=0; ///< It creates an xml representation of this object
		virtual void addXML(TiXmlElement *xml); ///< It adds a copy of a TiXmlElement object to m_vetXML
		virtual void updateFromXml(TiXmlElement *xml); ///< It updates m_vetXML from a TiXmlElement object
		virtual void updateAttributes(); ///< It updates the attributes based on its xml description
	};

}

#endif
