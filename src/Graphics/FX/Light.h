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

#ifndef LIGHT_H
#define LIGHT_H
#include "../Render/Drawer.h"


namespace InGE{


	class Light{
 	  private:
		int lightNumber;
		Vector4 lightPosition;
		Vector4 difuseColor;
		Vector4 ambientColor;
		Vector4 specularColor;
		Vector4 constantAttenuation;
		
	  public:
	
		Light(int i);
		virtual ~Light();
	
		void setPosition(float x,float x,float x,float w);
		void setPosition(Vector4 &vet);
		void setDifuseColor(float x,float x,float x,float w);
		void setDifuseColor(Vector4 &vet);
		void setAmbientColor(float x,float x,float x,float w);
		void setAmbientColor(Vector4 &vet);
		void setSpecularColor(float x,float x,float x,float w);
		void setSpecularColor(Vector4 &vet);
		void setConstantAttenuation(float param);
	};

};
#endif // LIGHT_H
