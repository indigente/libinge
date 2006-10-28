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
#ifndef _IWIDGET_H_
#define _IWIDGET_H_

#include <string>

namespace InGE{
using std::string;
class IWidget{
	protected:
		string m_name;
		float m_x, m_y;
		float m_w, m_h;
	public:
		IWidget();
		virtual ~IWidget() {}
		virtual void draw(float x, float y, float width, float height)=0;
		
		virtual void setName(string name);
		virtual string getName();
		
		virtual void move(float x, float y);
		virtual void resize(float width, float height);
		
		virtual float getWidth();
		virtual float getHeight();
};

};

#endif //_IWIDGET_H_
