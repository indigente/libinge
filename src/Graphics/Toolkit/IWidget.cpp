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
#include "IWidget.h"

namespace InGE{

IWidget::IWidget(){
	m_x=0;
	m_y=0;
	m_w=0.5;
	m_h=0.5;
}

void IWidget::move(float x, float y){
	 m_x = x;
	 m_y = y;
}

void IWidget::resize(float width, float height){
	 m_w = width;
	 m_h = height;
}

float IWidget::getWidth(){
	return m_w;
}

float IWidget::getHeight(){
	return m_h;
}

void IWidget::setName(string name){
	m_name = name;
}

string IWidget::getName(){
	return m_name;
}

}