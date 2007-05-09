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
#include "MouseControl.h"
#include "ControlLayer.h"
#include <cstdio>
#include <CEGUI.h>

#define MOTION_INDEX 	10

using namespace InGE;

ControlLayer *MouseControl::m_pControlLayer = 0;
AArray *MouseControl::m_controlTab = 0;

MouseControl::MouseControl(){
	if(!MouseControl::m_controlTab)
		MouseControl::m_controlTab = new AArray();
		
	setMouseOnCenter();
}

MouseControl::MouseControl(ControlLayer *c){
	if(!MouseControl::m_controlTab)	
		MouseControl::m_controlTab = new AArray();
		
	setControlLayer(c);
	setMouseOnCenter();	
}


MouseControl::~MouseControl(){
}

void MouseControl::setControlLayer(ControlLayer *c){
	m_pControlLayer = c;
}


void MouseControl::loadTab(string filename){
	//Try to open filename
	loadDefaultTab();
}
void MouseControl::loadDefaultTab(){
	(*m_controlTab)[MOTION_INDEX] = InGE_CONTROL_LOOK;
	(*m_controlTab)[SDL_BUTTON_LEFT] = InGE_CONTROL_ACTION1;
	(*m_controlTab)[SDL_BUTTON_MIDDLE] = InGE_CONTROL_ACTION2;
	(*m_controlTab)[SDL_BUTTON_RIGHT] = InGE_CONTROL_ACTION3;
	
	(*m_controlTab)[SDL_BUTTON_WHEELUP] = InGE_CONTROL_NEXT;
	(*m_controlTab)[SDL_BUTTON_WHEELDOWN] = InGE_CONTROL_PREV;
}

void MouseControl::check(SDL_Event &event){
	ControlParam param;
	CEGUI::System &cegui = CEGUI::System::getSingleton();

    switch ( event.type ){
		case SDL_MOUSEBUTTONUP:
			switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					cegui.injectMouseButtonUp(CEGUI::LeftButton); break;
				case SDL_BUTTON_MIDDLE:
					cegui.injectMouseButtonUp(CEGUI::MiddleButton); break;
				case SDL_BUTTON_RIGHT:
					cegui.injectMouseButtonUp(CEGUI::RightButton); break;
			}
        case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					cegui.injectMouseButtonDown(CEGUI::LeftButton); break;
				case SDL_BUTTON_MIDDLE:
					cegui.injectMouseButtonDown(CEGUI::MiddleButton); break;
				case SDL_BUTTON_RIGHT:
					cegui.injectMouseButtonDown(CEGUI::RightButton); break;

				case SDL_BUTTON_WHEELDOWN:
					cegui.injectMouseWheelChange(-1); break;
				case SDL_BUTTON_WHEELUP:
					cegui.injectMouseWheelChange(+1); break;
			}

        	param.state = event.button.state;
        	param.x = event.button.x;
        	param.y = event.button.y;
			m_pControlLayer->fireEvent((*m_controlTab)[event.button.button], &param);
            break;
        case SDL_MOUSEMOTION :
			cegui.injectMousePosition(static_cast<float>(event.motion.x),
					static_cast<float>(event.motion.y));

        	if(m_keepMouseOnCenter){
        		if((event.motion.x == m_middleX) && (event.motion.y == m_middleY)) return;
				SDL_WarpMouse(m_middleX, m_middleY);
        	}
        	param.state = event.motion.state;
        	param.x = event.motion.x;
        	param.y = event.motion.y;
        	param.xRel = event.motion.xrel;
        	param.yRel = event.motion.yrel;
        	m_pControlLayer->fireEvent((*m_controlTab)[MOTION_INDEX], &param);
            break;

        default:
           	SDL_PushEvent(&event);
            break;
    } // switch

}


void MouseControl::setMouseOnCenter(){
	SDL_Surface *surface = SDL_GetVideoSurface();
	if(surface){
		m_middleX = surface->w; 
		m_middleX >>= 1;
		m_middleY = surface->h;
		m_middleY >>= 1;
	}

	m_keepMouseOnCenter = true;
}

void MouseControl::unsetMouseOnCenter(){
	m_keepMouseOnCenter = false;
}

			

