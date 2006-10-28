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
#include "ControlLayer.h"
#include "KeyboardControl.h"
#include "MouseControl.h"
#include <cstdio>
#include <SDL/SDL.h>

using namespace InGE;

ControlLayer::ControlLayer(int activeControl){
	if(activeControl & InGE_CONTROLLAYER_PLAYER){
		m_pKeyboardControl = new KeyboardControl();
		m_pKeyboardControl->setControlLayer(this);
		m_pKeyboardControl->loadDefaultTab();

		m_pMouseControl = new MouseControl();		
		m_pMouseControl->setControlLayer(this);
		m_pMouseControl->loadDefaultTab();		
		setMouseOnCenter();		
		//grabOn();

	}
	else{
		m_pKeyboardControl = NULL;
		m_pMouseControl = NULL;
	}
	
}


ControlLayer::~ControlLayer(){
	if(m_pKeyboardControl) delete m_pKeyboardControl;
	if(m_pMouseControl) delete m_pMouseControl;
}


// Adiciona ouvidor
void ControlLayer::addListener(IControlLayerListener *l){
	m_listenerList.push_back(l);
}


// Remove ouvidor
void ControlLayer::removeListener(IControlLayerListener *l){
	list<IControlLayerListener *>::iterator it;
	
	for(it = m_listenerList.begin(); it != m_listenerList.end(); it++){
		if(l == *it) {
			m_listenerList.erase(it);
			break;
		}
	}
}


// Adiciona controlador
void ControlLayer::addControler(IControl *c){
	m_pControlList.push_back(c);
}


// Remove controlador
void ControlLayer::removeControler(IControl *c){
	list<IControl *>::iterator it;
	
	for(it = m_pControlList.begin(); it != m_pControlList.end(); it++){
		if(c == *it)
			m_pControlList.erase(it);
	}
	
}


// Dispara o evento e na lista de ouvidores
void ControlLayer::fireEvent(ControlEnum e, ControlParam *param){
	list<IControlLayerListener *>::iterator it;
	

	for(it = m_listenerList.begin(); it != m_listenerList.end(); it++)
		(*it)->controlEventHandler(e,param);
}


void ControlLayer::check(){
	list<IControl *>::iterator it;
	SDL_Event event;
	if(m_pKeyboardControl || m_pMouseControl ){	
		while(SDL_PollEvent(&event) ){
	        switch ( event.type ){
				case SDL_KEYDOWN :
				case SDL_KEYUP :
					if(m_pKeyboardControl) m_pKeyboardControl->check(event);
					break;
	            case SDL_MOUSEMOTION :
				case SDL_MOUSEBUTTONUP:
	            case SDL_MOUSEBUTTONDOWN :
	            	if(m_pMouseControl) m_pMouseControl->check(event);
	                break;
	            default:
	               	//SDL_PushEvent(&event);
	                break;
	        } // switch
	    } // while( SDL )
	}
	for(it = m_pControlList.begin(); it != m_pControlList.end(); it++){
		(*it)->check();
	}
}

void ControlLayer::setMouseOnCenter(){
	m_pMouseControl->setMouseOnCenter();
}

void ControlLayer::unsetMouseOnCenter(){
	m_pMouseControl->unsetMouseOnCenter();
}

void ControlLayer::grabOn(){
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);
}

void ControlLayer::grabOff(){
	SDL_WM_GrabInput(SDL_GRAB_OFF);
}
			
