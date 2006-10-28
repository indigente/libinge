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
#include "NetCustomMessage.h"

namespace InGE {

NetCustomMessage::NetCustomMessage() {
	m_pCustomXmlElement = new TiXmlElement("InGENetMsg");
	m_pCustomXmlElement->SetAttribute( "TYPE" , "CUS" ); //tipo da msg: custom
	
	m_areMandatoryAttSet = false;
}


NetCustomMessage::NetCustomMessage( TiXmlElement* xml_element ) {
	m_pCustomXmlElement = (TiXmlElement *) (xml_element->Clone());
	
	m_areMandatoryAttSet = true;
}


NetCustomMessage::~NetCustomMessage()
{
	delete(m_pCustomXmlElement);
}


// void NetCustomMessage::notifyDisconnection {
// 	
// }


void NetCustomMessage::setMandatoryAttributes(int id, string& plyName) { 
	
	if (m_areMandatoryAttSet) {
		cerr << "AVISO: Atributos ID e PLYNAME estao sendo sobrescritos" << endl;
		cerr << "Novos ID, PLYNAME: " << id << ", " << plyName << endl;
	}
	
	m_pCustomXmlElement->SetAttribute( "ID" ,  id );
	m_pCustomXmlElement->SetAttribute( "PLYNAME" , plyName );
	
	m_areMandatoryAttSet = true;
}


bool NetCustomMessage::areMandatoryAttSet() {
	return m_areMandatoryAttSet;
}


bool NetCustomMessage::setAttribute (string att_name, string att_value){
	if (att_name == "TYPE" || att_name == "ID" || att_name == "PLYNAME" ) {
		cerr << "ERRO: atributos TYPE, ID e PLYNAME sao reservados." << endl;
		return false;
	}
	
	m_pCustomXmlElement->SetAttribute( att_name, att_value );
	
	return true;
}


bool NetCustomMessage::getAttribute (string att_name, string& s_return) {
	if (  m_pCustomXmlElement->Attribute( att_name.c_str() )  ==  NULL)
		return false;
	
	s_return = m_pCustomXmlElement->Attribute( att_name.c_str() );
	return true;
}


bool NetCustomMessage::setAttribute (string att_name, int att_value){
	if (att_name == "TYPE" || att_name == "ID" || att_name == "PLYNAME" ) {
		cerr << "ERRO: atributos TYPE, ID e PLYNAME sao reservados." << endl;
		return false;
	}
	
	m_pCustomXmlElement->SetAttribute( att_name, att_value );
	
	return true;
}


bool NetCustomMessage::getAttribute (string att_name, int& i_return) {
	if (m_pCustomXmlElement->QueryIntAttribute( att_name , &i_return ) == TIXML_SUCCESS)
		return true;
	else
		return false;
}


bool NetCustomMessage::setAttribute (string att_name, double att_value){
	if (att_name == "TYPE" || att_name == "ID" || att_name == "PLYNAME" ) {
		cerr << "ERRO: atributos TYPE, ID e PLYNAME sao reservados." << endl;
		return false;
	}
	
	m_pCustomXmlElement->SetDoubleAttribute( att_name.c_str() , att_value );
	
	return true;
}


bool NetCustomMessage::getAttribute (string att_name, double& d_return) {
	if (m_pCustomXmlElement->QueryDoubleAttribute( att_name , &d_return ) == TIXML_SUCCESS)
		return true;
	else
		return false;
}


bool NetCustomMessage::rmAttribute (string att_name) {
	if (att_name == "TYPE" || att_name == "ID" || att_name == "PLYNAME" ) {
		cerr << "ERRO: atributos TYPE, ID e PLYNAME sao reservados." << endl;
		return false;
	}
	
	m_pCustomXmlElement->RemoveAttribute( att_name );
	
	return true;
}


void NetCustomMessage::toString( string& s_return) {
	s_return << *m_pCustomXmlElement;
}


}
