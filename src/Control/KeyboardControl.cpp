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
#include "KeyboardControl.h"
#include "ControlLayer.h"

#include <cstdio>
#include <fstream>
using namespace InGE;

ControlLayer *KeyboardControl::m_pControlLayer = 0;
AArray *KeyboardControl::m_controlTab = 0;
bool KeyboardControl::m_actived = false;

KeyboardControl::KeyboardControl(){
	if(!KeyboardControl::m_controlTab)
		KeyboardControl::m_controlTab = new AArray();
}

KeyboardControl::KeyboardControl(ControlLayer *c){
	if(!KeyboardControl::m_controlTab)	
		KeyboardControl::m_controlTab = new AArray();
		
	setControlLayer(c);
}

KeyboardControl::~KeyboardControl(){
	
}

void KeyboardControl::loadTab(string filename){
  //	ifstream keymap(filename);
	loadDefaultTab();
}

void KeyboardControl::loadDefaultTab(){

	
	(*m_controlTab)[SDLK_BACKSPACE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_TAB] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_CLEAR] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RETURN] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_PAUSE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_ESCAPE] = InGE_CONTROL_ESCAPE;
	(*m_controlTab)[SDLK_SPACE] = InGE_CONTROL_JUMP;
	(*m_controlTab)[SDLK_EXCLAIM] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_QUOTEDBL] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_HASH] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_DOLLAR] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_AMPERSAND] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_QUOTE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LEFTPAREN] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RIGHTPAREN] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_ASTERISK] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_PLUS] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_COMMA] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_MINUS] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_PERIOD] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_SLASH] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_0] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_1] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_2] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_3] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_4] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_5] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_6] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_7] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_8] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_9] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_COLON] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_SEMICOLON] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LESS] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_EQUALS] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_GREATER] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_QUESTION] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_AT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LEFTBRACKET] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_BACKSLASH] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RIGHTBRACKET] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_CARET] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_UNDERSCORE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_BACKQUOTE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_a] = InGE_CONTROL_LEFT;
	(*m_controlTab)[SDLK_b] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_c] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_d] = InGE_CONTROL_RIGHT;
	(*m_controlTab)[SDLK_e] = InGE_CONTROL_TURN_RIGHT;
	(*m_controlTab)[SDLK_f] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_g] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_h] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_i] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_j] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_k] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_l] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_m] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_n] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_o] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_p] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_q] = InGE_CONTROL_TURN_LEFT;
	(*m_controlTab)[SDLK_r] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_s] = InGE_CONTROL_BACKWARD;
	(*m_controlTab)[SDLK_t] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_u] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_v] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_w] = InGE_CONTROL_FORWARD;
	(*m_controlTab)[SDLK_x] = InGE_CONTROL_X;
	(*m_controlTab)[SDLK_y] = InGE_CONTROL_Y;
	(*m_controlTab)[SDLK_z] = InGE_CONTROL_Z;
	(*m_controlTab)[SDLK_DELETE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP0] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP1] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP2] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP3] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP4] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP5] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP6] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP7] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP8] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP9] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP_PERIOD] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP_DIVIDE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP_MULTIPLY] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP_MINUS] = InGE_CONTROL_MINUS;
	(*m_controlTab)[SDLK_KP_PLUS] = InGE_CONTROL_PLUS;
	(*m_controlTab)[SDLK_KP_ENTER] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_KP_EQUALS] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_UP] = InGE_CONTROL_FORWARD;
	(*m_controlTab)[SDLK_DOWN] = InGE_CONTROL_BACKWARD;
	(*m_controlTab)[SDLK_RIGHT] = InGE_CONTROL_TURN_RIGHT;
	(*m_controlTab)[SDLK_LEFT] = InGE_CONTROL_TURN_LEFT;
	(*m_controlTab)[SDLK_INSERT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_HOME] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_END] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_PAGEUP] = InGE_CONTROL_PREV;
	(*m_controlTab)[SDLK_PAGEDOWN] = InGE_CONTROL_NEXT;
	(*m_controlTab)[SDLK_F1] = InGE_CONTROL_F1;
	(*m_controlTab)[SDLK_F2] = InGE_CONTROL_F2;
	(*m_controlTab)[SDLK_F3] = InGE_CONTROL_F3;
	(*m_controlTab)[SDLK_F4] = InGE_CONTROL_F4;
	(*m_controlTab)[SDLK_F5] = InGE_CONTROL_F5;
	(*m_controlTab)[SDLK_F6] = InGE_CONTROL_F6;
	(*m_controlTab)[SDLK_F7] = InGE_CONTROL_F7;
	(*m_controlTab)[SDLK_F8] = InGE_CONTROL_F8;
	(*m_controlTab)[SDLK_F9] = InGE_CONTROL_F9;
	(*m_controlTab)[SDLK_F10] = InGE_CONTROL_F10;
	(*m_controlTab)[SDLK_F11] = InGE_CONTROL_F11;
	(*m_controlTab)[SDLK_F12] = InGE_CONTROL_F12;
	(*m_controlTab)[SDLK_F13] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_F14] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_F15] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_NUMLOCK] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_CAPSLOCK] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_SCROLLOCK] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RSHIFT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LSHIFT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RCTRL] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LCTRL] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RALT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LALT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RMETA] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LMETA] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_LSUPER] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_RSUPER] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_MODE] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_HELP] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_PRINT] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_SYSREQ] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_BREAK] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_MENU] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_POWER] = InGE_CONTROL_VOID;
	(*m_controlTab)[SDLK_EURO] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_NONE] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_NUM] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_CAPS] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_LCTRL] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_RCTRL] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_RSHIFT] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_LSHIFT] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_RALT] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_LALT] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_CTRL] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_SHIFT] = InGE_CONTROL_VOID;
	(*m_controlTab)[KMOD_ALT] = InGE_CONTROL_VOID;	
	
}


void KeyboardControl::setControlLayer(ControlLayer *c){
	m_pControlLayer = c;
}


void KeyboardControl::check(SDL_Event &event){
	ControlParam param;

	switch ( event.type ){
		case SDL_KEYDOWN:
			param.state = event.key.state;
			fireKeyEvent(event.key.keysym.sym);
			switch(event.key.keysym.sym){
				case SDLK_BACKSPACE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKSPACE],&param);
					break;
				case SDLK_TAB:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_TAB],&param);
					break;
				case SDLK_CLEAR:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CLEAR],&param);
					break;
				case SDLK_RETURN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RETURN],&param);
					break;
				case SDLK_PAUSE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAUSE],&param);
					break;
				case SDLK_ESCAPE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_ESCAPE],&param);
					break;
				case SDLK_SPACE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SPACE],&param);
					break;
				case SDLK_EXCLAIM:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EXCLAIM],&param);
					break;
				case SDLK_QUOTEDBL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUOTEDBL],&param);
					break;
				case SDLK_HASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HASH],&param);
					break;
				case SDLK_DOLLAR:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DOLLAR],&param);
					break;
				case SDLK_AMPERSAND:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_AMPERSAND],&param);
					break;
				case SDLK_QUOTE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUOTE],&param);
					break;
				case SDLK_LEFTPAREN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFTPAREN],&param);
					break;
				case SDLK_RIGHTPAREN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHTPAREN],&param);
					break;
				case SDLK_ASTERISK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_ASTERISK],&param);
					break;
				case SDLK_PLUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PLUS],&param);
					break;
				case SDLK_COMMA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_COMMA],&param);
					break;
				case SDLK_MINUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MINUS],&param);
					break;
				case SDLK_PERIOD:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PERIOD],&param);
					break;
				case SDLK_SLASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SLASH],&param);
					break;
				case SDLK_0:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_0],&param);
					break;
				case SDLK_1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_1],&param);
					break;
				case SDLK_2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_2],&param);
					break;
				case SDLK_3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_3],&param);
					break;
				case SDLK_4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_4],&param);
					break;
				case SDLK_5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_5],&param);
					break;
				case SDLK_6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_6],&param);
					break;
				case SDLK_7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_7],&param);
					break;
				case SDLK_8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_8],&param);
					break;
				case SDLK_9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_9],&param);
					break;
				case SDLK_COLON:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_COLON],&param);
					break;
				case SDLK_SEMICOLON:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SEMICOLON],&param);
					break;
				case SDLK_LESS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LESS],&param);
					break;
				case SDLK_EQUALS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EQUALS],&param);
					break;
				case SDLK_GREATER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_GREATER],&param);
					break;
				case SDLK_QUESTION:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUESTION],&param);
					break;
				case SDLK_AT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_AT],&param);
					break;
				case SDLK_LEFTBRACKET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFTBRACKET],&param);
					break;
				case SDLK_BACKSLASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKSLASH],&param);
					break;
				case SDLK_RIGHTBRACKET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHTBRACKET],&param);
					break;
				case SDLK_CARET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CARET],&param);
					break;
				case SDLK_UNDERSCORE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_UNDERSCORE],&param);
					break;
				case SDLK_BACKQUOTE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKQUOTE],&param);
					break;
				case SDLK_a:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_a],&param);
					break;
				case SDLK_b:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_b],&param);
					break;
				case SDLK_c:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_c],&param);
					break;
				case SDLK_d:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_d],&param);
					break;
				case SDLK_e:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_e],&param);
					break;
				case SDLK_f:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_f],&param);
					break;
				case SDLK_g:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_g],&param);
					break;
				case SDLK_h:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_h],&param);
					break;
				case SDLK_i:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_i],&param);
					break;
				case SDLK_j:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_j],&param);
					break;
				case SDLK_k:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_k],&param);
					break;
				case SDLK_l:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_l],&param);
					break;
				case SDLK_m:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_m],&param);
					break;
				case SDLK_n:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_n],&param);
					break;
				case SDLK_o:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_o],&param);
					break;
				case SDLK_p:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_p],&param);
					break;
				case SDLK_q:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_q],&param);
					break;
				case SDLK_r:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_r],&param);
					break;
				case SDLK_s:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_s],&param);
					break;
				case SDLK_t:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_t],&param);
					break;
				case SDLK_u:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_u],&param);
					break;
				case SDLK_v:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_v],&param);
					break;
				case SDLK_w:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_w],&param);
					break;
				case SDLK_x:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_x],&param);
					break;
				case SDLK_y:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_y],&param);
					break;
				case SDLK_z:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_z],&param);
					break;
				case SDLK_DELETE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DELETE],&param);
					break;
				case SDLK_KP0:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP0],&param);
					break;
				case SDLK_KP1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP1],&param);
					break;
				case SDLK_KP2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP2],&param);
					break;
				case SDLK_KP3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP3],&param);
					break;
				case SDLK_KP4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP4],&param);
					break;
				case SDLK_KP5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP5],&param);
					break;
				case SDLK_KP6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP6],&param);
					break;
				case SDLK_KP7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP7],&param);
					break;
				case SDLK_KP8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP8],&param);
					break;
				case SDLK_KP9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP9],&param);
					break;
				case SDLK_KP_PERIOD:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_PERIOD],&param);
					break;
				case SDLK_KP_DIVIDE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_DIVIDE],&param);
					break;
				case SDLK_KP_MULTIPLY:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_MULTIPLY],&param);
					break;
				case SDLK_KP_MINUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_MINUS],&param);
					break;
				case SDLK_KP_PLUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_PLUS],&param);
					break;
				case SDLK_KP_ENTER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_ENTER],&param);
					break;
				case SDLK_KP_EQUALS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_EQUALS],&param);
					break;
				case SDLK_UP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_UP],&param);
					break;
				case SDLK_DOWN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DOWN],&param);
					break;
				case SDLK_RIGHT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHT],&param);
					break;
				case SDLK_LEFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFT],&param);
					break;
				case SDLK_INSERT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_INSERT],&param);
					break;
				case SDLK_HOME:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HOME],&param);
					break;
				case SDLK_END:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_END],&param);
					break;
				case SDLK_PAGEUP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAGEUP],&param);
					break;
				case SDLK_PAGEDOWN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAGEDOWN],&param);
					break;
				case SDLK_F1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F1],&param);
					break;
				case SDLK_F2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F2],&param);
					break;
				case SDLK_F3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F3],&param);
					break;
				case SDLK_F4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F4],&param);
					break;
				case SDLK_F5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F5],&param);
					break;
				case SDLK_F6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F6],&param);
					break;
				case SDLK_F7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F7],&param);
					break;
				case SDLK_F8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F8],&param);
					break;
				case SDLK_F9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F9],&param);
					break;
				case SDLK_F10:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F10],&param);
					break;
				case SDLK_F11:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F11],&param);
					break;
				case SDLK_F12:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F12],&param);
					break;
				case SDLK_F13:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F13],&param);
					break;
				case SDLK_F14:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F14],&param);
					break;
				case SDLK_F15:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F15],&param);
					break;
				case SDLK_NUMLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_NUMLOCK],&param);
					break;
				case SDLK_CAPSLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CAPSLOCK],&param);
					break;
				case SDLK_SCROLLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SCROLLOCK],&param);
					break;
				case SDLK_RSHIFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RSHIFT],&param);
					break;
				case SDLK_LSHIFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LSHIFT],&param);
					break;
				case SDLK_RCTRL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RCTRL],&param);
					break;
				case SDLK_LCTRL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LCTRL],&param);
					break;
				case SDLK_RALT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RALT],&param);
					break;
				case SDLK_LALT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LALT],&param);
					break;
				case SDLK_RMETA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RMETA],&param);
					break;
				case SDLK_LMETA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LMETA],&param);
					break;
				case SDLK_LSUPER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LSUPER],&param);
					break;
				case SDLK_RSUPER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RSUPER],&param);
					break;
				case SDLK_MODE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MODE],&param);
					break;
				case SDLK_HELP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HELP],&param);
					break;
				case SDLK_PRINT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PRINT],&param);
					break;
				case SDLK_SYSREQ:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SYSREQ],&param);
					break;
				case SDLK_BREAK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BREAK],&param);
					break;
				case SDLK_MENU:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MENU],&param);
					break;
				case SDLK_POWER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_POWER],&param);
					break;
				case SDLK_EURO:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EURO],&param);
					break;
				default:
					break;
	        }
			break;
	
		case SDL_KEYUP :
			param.state = event.key.state;
			switch(event.key.keysym.sym){
				case SDLK_BACKSPACE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKSPACE],&param);
					break;
				case SDLK_TAB:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_TAB],&param);
					break;
				case SDLK_CLEAR:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CLEAR],&param);
					break;
				case SDLK_RETURN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RETURN],&param);
					break;
				case SDLK_PAUSE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAUSE],&param);
					break;
				case SDLK_ESCAPE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_ESCAPE],&param);
					break;
				case SDLK_SPACE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SPACE],&param);
					break;
				case SDLK_EXCLAIM:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EXCLAIM],&param);
					break;
				case SDLK_QUOTEDBL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUOTEDBL],&param);
					break;
				case SDLK_HASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HASH],&param);
					break;
				case SDLK_DOLLAR:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DOLLAR],&param);
					break;
				case SDLK_AMPERSAND:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_AMPERSAND],&param);
					break;
				case SDLK_QUOTE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUOTE],&param);
					break;
				case SDLK_LEFTPAREN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFTPAREN],&param);
					break;
				case SDLK_RIGHTPAREN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHTPAREN],&param);
					break;
				case SDLK_ASTERISK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_ASTERISK],&param);
					break;
				case SDLK_PLUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PLUS],&param);
					break;
				case SDLK_COMMA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_COMMA],&param);
					break;
				case SDLK_MINUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MINUS],&param);
					break;
				case SDLK_PERIOD:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PERIOD],&param);
					break;
				case SDLK_SLASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SLASH],&param);
					break;
				case SDLK_0:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_0],&param);
					break;
				case SDLK_1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_1],&param);
					break;
				case SDLK_2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_2],&param);
					break;
				case SDLK_3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_3],&param);
					break;
				case SDLK_4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_4],&param);
					break;
				case SDLK_5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_5],&param);
					break;
				case SDLK_6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_6],&param);
					break;
				case SDLK_7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_7],&param);
					break;
				case SDLK_8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_8],&param);
					break;
				case SDLK_9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_9],&param);
					break;
				case SDLK_COLON:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_COLON],&param);
					break;
				case SDLK_SEMICOLON:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SEMICOLON],&param);
					break;
				case SDLK_LESS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LESS],&param);
					break;
				case SDLK_EQUALS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EQUALS],&param);
					break;
				case SDLK_GREATER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_GREATER],&param);
					break;
				case SDLK_QUESTION:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_QUESTION],&param);
					break;
				case SDLK_AT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_AT],&param);
					break;
				case SDLK_LEFTBRACKET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFTBRACKET],&param);
					break;
				case SDLK_BACKSLASH:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKSLASH],&param);
					break;
				case SDLK_RIGHTBRACKET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHTBRACKET],&param);
					break;
				case SDLK_CARET:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CARET],&param);
					break;
				case SDLK_UNDERSCORE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_UNDERSCORE],&param);
					break;
				case SDLK_BACKQUOTE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BACKQUOTE],&param);
					break;
				case SDLK_a:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_a],&param);
					break;
				case SDLK_b:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_b],&param);
					break;
				case SDLK_c:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_c],&param);
					break;
				case SDLK_d:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_d],&param);
					break;
				case SDLK_e:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_e],&param);
					break;
				case SDLK_f:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_f],&param);
					break;
				case SDLK_g:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_g],&param);
					break;
				case SDLK_h:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_h],&param);
					break;
				case SDLK_i:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_i],&param);
					break;
				case SDLK_j:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_j],&param);
					break;
				case SDLK_k:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_k],&param);
					break;
				case SDLK_l:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_l],&param);
					break;
				case SDLK_m:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_m],&param);
					break;
				case SDLK_n:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_n],&param);
					break;
				case SDLK_o:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_o],&param);
					break;
				case SDLK_p:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_p],&param);
					break;
				case SDLK_q:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_q],&param);
					break;
				case SDLK_r:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_r],&param);
					break;
				case SDLK_s:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_s],&param);
					break;
				case SDLK_t:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_t],&param);
					break;
				case SDLK_u:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_u],&param);
					break;
				case SDLK_v:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_v],&param);
					break;
				case SDLK_w:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_w],&param);
					break;
				case SDLK_x:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_x],&param);
					break;
				case SDLK_y:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_y],&param);
					break;
				case SDLK_z:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_z],&param);
					break;
				case SDLK_DELETE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DELETE],&param);
					break;
				case SDLK_KP0:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP0],&param);
					break;
				case SDLK_KP1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP1],&param);
					break;
				case SDLK_KP2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP2],&param);
					break;
				case SDLK_KP3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP3],&param);
					break;
				case SDLK_KP4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP4],&param);
					break;
				case SDLK_KP5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP5],&param);
					break;
				case SDLK_KP6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP6],&param);
					break;
				case SDLK_KP7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP7],&param);
					break;
				case SDLK_KP8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP8],&param);
					break;
				case SDLK_KP9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP9],&param);
					break;
				case SDLK_KP_PERIOD:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_PERIOD],&param);
					break;
				case SDLK_KP_DIVIDE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_DIVIDE],&param);
					break;
				case SDLK_KP_MULTIPLY:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_MULTIPLY],&param);
					break;
				case SDLK_KP_MINUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_MINUS],&param);
					break;
				case SDLK_KP_PLUS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_PLUS],&param);
					break;
				case SDLK_KP_ENTER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_ENTER],&param);
					break;
				case SDLK_KP_EQUALS:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_KP_EQUALS],&param);
					break;
				case SDLK_UP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_UP],&param);
					break;
				case SDLK_DOWN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_DOWN],&param);
					break;
				case SDLK_RIGHT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RIGHT],&param);
					break;
				case SDLK_LEFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LEFT],&param);
					break;
				case SDLK_INSERT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_INSERT],&param);
					break;
				case SDLK_HOME:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HOME],&param);
					break;
				case SDLK_END:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_END],&param);
					break;
				case SDLK_PAGEUP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAGEUP],&param);
					break;
				case SDLK_PAGEDOWN:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PAGEDOWN],&param);
					break;
				case SDLK_F1:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F1],&param);
					break;
				case SDLK_F2:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F2],&param);
					break;
				case SDLK_F3:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F3],&param);
					break;
				case SDLK_F4:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F4],&param);
					break;
				case SDLK_F5:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F5],&param);
					break;
				case SDLK_F6:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F6],&param);
					break;
				case SDLK_F7:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F7],&param);
					break;
				case SDLK_F8:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F8],&param);
					break;
				case SDLK_F9:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F9],&param);
					break;
				case SDLK_F10:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F10],&param);
					break;
				case SDLK_F11:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F11],&param);
					break;
				case SDLK_F12:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F12],&param);
					break;
				case SDLK_F13:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F13],&param);
					break;
				case SDLK_F14:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F14],&param);
					break;
				case SDLK_F15:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_F15],&param);
					break;
				case SDLK_NUMLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_NUMLOCK],&param);
					break;
				case SDLK_CAPSLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_CAPSLOCK],&param);
					break;
				case SDLK_SCROLLOCK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SCROLLOCK],&param);
					break;
				case SDLK_RSHIFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RSHIFT],&param);
					break;
				case SDLK_LSHIFT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LSHIFT],&param);
					break;
				case SDLK_RCTRL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RCTRL],&param);
					break;
				case SDLK_LCTRL:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LCTRL],&param);
					break;
				case SDLK_RALT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RALT],&param);
					break;
				case SDLK_LALT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LALT],&param);
					break;
				case SDLK_RMETA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RMETA],&param);
					break;
				case SDLK_LMETA:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LMETA],&param);
					break;
				case SDLK_LSUPER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_LSUPER],&param);
					break;
				case SDLK_RSUPER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_RSUPER],&param);
					break;
				case SDLK_MODE:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MODE],&param);
					break;
				case SDLK_HELP:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_HELP],&param);
					break;
				case SDLK_PRINT:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_PRINT],&param);
					break;
				case SDLK_SYSREQ:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_SYSREQ],&param);
					break;
				case SDLK_BREAK:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_BREAK],&param);
					break;
				case SDLK_MENU:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_MENU],&param);
					break;
				case SDLK_POWER:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_POWER],&param);
					break;
				case SDLK_EURO:
					m_pControlLayer->fireEvent((*m_controlTab)[SDLK_EURO],&param);
					break;
				default: 
					break;
			}
			break;
		default:
			SDL_PushEvent(&event);
			break;
	} // switch

}


// Adiciona ouvidor
void KeyboardControl::addKeyListener(IKeyListener *l){
	std::cout << "Adicionando KeyListener ao KeyboardControl..." << std::endl;
	m_keyListenerList.push_back(l);
}


// Remove ouvidor
void KeyboardControl::removeKeyListener(IKeyListener *l){
	list<IKeyListener *>::iterator it;
	
	for(it = m_keyListenerList.begin(); it != m_keyListenerList.end(); it++){
		if(l == *it) {
			m_keyListenerList.erase(it);
			break;
		}
	}
}

// Dispara o evento e na lista de ouvidores
void KeyboardControl::fireKeyEvent(char c) {
	list<IKeyListener *>::iterator it;
	

	for(it = m_keyListenerList.begin(); it != m_keyListenerList.end(); it++)
		(*it)->keyEventHandler(c);
}
