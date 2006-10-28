/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#ifndef FOG_H
#define FOG_H

#include <string>
#include "../Render/Drawer.h"
#include "../Render/enumDrawer.h"
#include "../../Math/Vector4.h"


namespace InGE{
using std::string;


	class Fog{
	  private:
		Vector4 fogColor;
		EnumDrawer fogMode;
		float fogDensity;
		float fogStart;
		float fogEnd;

	  public:
	  	Fog();
	  	virtual ~Fog();
	  	
	  	void setFog();
	  	
		void setFogColor(Vector4 *color);
		void setFogColor(float r, float g, float b, float a);
		void setFogMode(EnumDrawer mode);
		void setFogDensity(float density);
		void setFogStart(float start);
		void setFogEnd(float end);
			  	
	  	Vector4 getFogColor();
		EnumDrawer getFogMode();
		float getFogDensity();
		float getFogStart();
		float getFogEnd();
	};

};
#endif // FOG_H
