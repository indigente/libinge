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
#ifndef CONTROLLAYER_H
#define CONTROLLAYER_H
#include "IControlLayerListener.h"
#include "controlEnum.h"
#include "IControl.h"
#include "MouseControl.h"
#include "KeyboardControl.h"

#include <list>
#include <iostream>

#define		InGE_CONTROLLAYER_PLAYER	1
#define 	InGE_CONTROLLAYER_AI		2
#define 	InGE_CONTROLLAYER_NET		4

namespace InGE{
	using std::list;

	class IControl;
	typedef struct ControlParam ControlParam;

	class ControlLayer{
		private:
			//Lista da Controles
			KeyboardControl		*m_pKeyboardControl;
			MouseControl		*m_pMouseControl;
			
			int			m_middleX;
			int			m_middleY;
			
			list<IControl *>	m_pControlList;
			
			// Lista de ouvidores do controle
			list<IControlLayerListener *>	m_listenerList;
			
		public:

			ControlLayer(int activeControl = InGE_CONTROLLAYER_PLAYER);
			virtual ~ControlLayer();
			
			// Adiciona ouvidor
			void addListener(IControlLayerListener *l);
			// Remove ouvidor
			void removeListener(IControlLayerListener *l);
			// Adiciona controlador
			void addControler(IControl *c);
			// Remove controlador
			void removeControler(IControl *c);
			// Dispara o evento e na lista de ouvidores
			void fireEvent(ControlEnum e, ControlParam *param);
			// Checa controles
			void check();
			
			KeyboardControl *getKeyboardControl() { return m_pKeyboardControl; }
			
			void setMouseOnCenter();
			void unsetMouseOnCenter();
					
			void grabOn();
			void grabOff();
			
			
	};


	
};

#endif // CONTROLLAYER_H
