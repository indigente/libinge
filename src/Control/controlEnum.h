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
#ifndef CONTROLENUM_H
#define CONTROLENUM_H


namespace InGE{
	enum ControlEnum{
		/* Move */
		InGE_CONTROL_UP=0,
		InGE_CONTROL_DOWN,
		InGE_CONTROL_LEFT,
		InGE_CONTROL_RIGHT,
		InGE_CONTROL_FORWARD,
		InGE_CONTROL_BACKWARD,
		InGE_CONTROL_STEP_LEFT,
		InGE_CONTROL_STEP_RIGHT,
		InGE_CONTROL_TURN_LEFT,
		InGE_CONTROL_TURN_RIGHT,
		InGE_CONTROL_JUMP,
		InGE_CONTROL_CROUCH,
		/* Look */
		InGE_CONTROL_LOOK,
		InGE_CONTROL_LOOK_UP,
		InGE_CONTROL_LOOK_DOWN,
		InGE_CONTROL_CENTER_VIEW,
		InGE_CONTROL_ZOOM,
		/* ATTACK */ 
		InGE_CONTROL_ACTION1,
		InGE_CONTROL_ACTION2,
		InGE_CONTROL_ACTION3,
		InGE_CONTROL_ATTACK1,
		InGE_CONTROL_ATTACK2,
		InGE_CONTROL_PREV_WEAPON,
		InGE_CONTROL_NEXT_WEAPON,
		InGE_CONTROL_WEAPON1,
		InGE_CONTROL_WEAPON2,	
		InGE_CONTROL_WEAPON3,
		InGE_CONTROL_WEAPON4,
		InGE_CONTROL_WEAPON5,
		InGE_CONTROL_WEAPON6,
		InGE_CONTROL_WEAPON7,
		InGE_CONTROL_WEAPON8,
		InGE_CONTROL_WEAPON9,
		InGE_CONTROL_WEAPON10,
		/* MISC */
		InGE_CONTROL_F1,
		InGE_CONTROL_F2,
		InGE_CONTROL_F3,
		InGE_CONTROL_F4,
		InGE_CONTROL_F5,
		InGE_CONTROL_F6,
		InGE_CONTROL_F7,
		InGE_CONTROL_F8,
		InGE_CONTROL_F9,
		InGE_CONTROL_F10,
		InGE_CONTROL_F11,
		InGE_CONTROL_F12,
		InGE_CONTROL_PREV,
		InGE_CONTROL_NEXT,
		InGE_CONTROL_VOID,
		InGE_CONTROL_ESCAPE,
		InGE_CONTROL_USE_ITEM,
		InGE_CONTROL_SHOW_SCORE,
		InGE_CONTROL_SHOW_MENU,
		InGE_CONTROL_GESTURE,
		InGE_CONTROL_CHAT,
		InGE_CONTROL_SAVE_GAME,
		InGE_CONTROL_LOAD_GAME,
		InGE_CONTROL_PRINT_SCREEN,
		InGE_CONTROL_HANDLE,
		InGE_CONTROL_X,
		InGE_CONTROL_Y,
		InGE_CONTROL_Z,
		InGE_CONTROL_MINUS,
		InGE_CONTROL_PLUS,
		InGE_MAX_CONTROL_ENUM
	};

};

#endif

