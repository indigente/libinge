/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

Copyright © 2004-2006 Indigente


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
#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H
#include "controlEnum.h"
#include <map>
#include <string>
#include <SDL/SDL.h>

namespace InGE{
	using std::map;
	using std::less;
	using std::string;
		
	
	class ControlLayer;
	typedef map<int, ControlEnum, less<int> > AArray;
	
	class MouseControl{
		private:
			static ControlLayer	*m_pControlLayer;
			//Liga um evento de mouse em um evento generico
			static AArray 		*m_controlTab;	
			bool			m_keepMouseOnCenter;
			int 			m_middleX;
			int			m_middleY;
			
		public:
		
			MouseControl();
			MouseControl(ControlLayer *c);
			void loadTab(string filename);
			void loadDefaultTab();
			virtual ~MouseControl();
			void setControlLayer(ControlLayer *c);
			void check(SDL_Event &event);		

			void setMouseOnCenter();
			void unsetMouseOnCenter();	
	};
};
#endif // MOUSECONTROL_H
