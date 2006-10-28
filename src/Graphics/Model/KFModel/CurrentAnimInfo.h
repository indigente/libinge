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
#ifndef INGECURRENTANIMINFO_H
#define INGECURRENTANIMINFO_H
#include <SDL/SDL.h>
#include <iostream>
#include <string>

namespace InGE {
using std::string;
/**
	@author Beto <nkbeto@gmail.com>
*/
class CurrentAnimInfo{
	private:
		string	m_currAnim;
		string	m_nextAnim;
		int		m_keyFrameIndex;
		int		m_materialIndex;
		float		m_speed;
		
		float		m_lastDrawTime;
		float 	m_interpolation;
		
		bool		m_isDraw;

	public:
    CurrentAnimInfo();

    ~CurrentAnimInfo();
		
	 string getCurrAnim();
	 string getNextAnim();
	 int getKeyFrameIndex();
	 int getMaterialIndex();
	 float getSpeed();
	 float getInterpolation();
	 
	 void setCurrAnim(string currAnim);
	 void setNextAnim(string nextAnim);
	 void setKeyFrameIndex(int keyFrameIndex);
	 void setMaterialIndex(int materialIndex);
	 void setSpeed(float speed);
	 
	 void linearInterpolation(int maxKeyFrame);
	 
	 void setIsDraw(bool);
	 bool getIsDraw();
};

}

#endif
