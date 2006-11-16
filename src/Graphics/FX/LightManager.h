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
#ifndef INGELIGHTMANAGER_H
#define INGELIGHTMANAGER_H
#include <vector>
#include "Light.h"
#include "../Render/enumDrawer.h"
#include "../Render/Drawer.h"
#include "../../Math/Vector4.h"
		
namespace InGE {
using namespace std;
/**
	@author Humberto Bandeira <nkbeto@gmail.com>
*/
class LightManager{
	private:
		//Global configuration
		Vector4 m_ambientColor;
		bool m_localViewer;
		bool m_twoSidedLight;
		EnumDrawer m_separateSpecularColor;
		
		//Lights
		vector<Light *> m_vStaticLight;
		vector<Light *> m_vDinamicLight;
		
	public:
		LightManager();
	
		~LightManager();

		void setAmbientColor(const Vector4& theValue);
		void setLocalViewer(bool theValue);
		void setTwoSidedLight(bool theValue);
		void setSeparateSpecularColor(const EnumDrawer& theValue);
		void addStaticLight(Light *light);
		void addDinamicLight(Light *light);
		
		Vector4 getAmbientColor() const;
		bool getLocalViewer() const;
		bool getTwoSidedLight() const;
		EnumDrawer getSeparateSpecularColor() const;
		Light *getStaticLight(int index);
		Light *getDinamicLight(int index);
	
};

}

#endif
