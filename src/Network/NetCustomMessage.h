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
#ifndef INGENETCUSTOMMESSAGE_H
#define INGENETCUSTOMMESSAGE_H

#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif

#include <string>

#include "../Util/TinyXML/tinyxml.h"
#include "../Util/TinyXML/tinystr.h"



namespace InGE {
	using namespace std;

/**
	@author Garou <kdubezerra@gmail.com>
*/
class NetCustomMessage{
	private:
		TiXmlElement* m_pCustomXmlElement;
		bool m_areMandatoryAttSet;

	public:
		NetCustomMessage();
		
		NetCustomMessage( TiXmlElement* xml_element );

		~NetCustomMessage();
		
// 		//seta para false o bool m_areMandatoryAttSet
// 		static void notifyDisconnection();
		
		//retorna T ou F: foi possivel setar os atributos?
		void setMandatoryAttributes(int id, string& plyName);
		
		//retorna T ou F: os atributos obrigatorios foram setados?
		bool areMandatoryAttSet();
		
		//seria melhor utilizar templates para os metodos setAttribute....
		bool setAttribute (string att_name, string att_value);
		bool getAttribute (string att_name, string& s_return);
		
		bool setAttribute (string att_name, int att_value);
		bool getAttribute (string att_name, int& i_return);
		
		bool setAttribute (string att_name, double att_value);
		bool getAttribute (string att_name, double& d_return);
		
		bool rmAttribute (string att_name);
		
		void toString (string& s_return);
};

}

#endif
