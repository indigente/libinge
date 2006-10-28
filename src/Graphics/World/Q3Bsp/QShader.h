/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente


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
#ifndef QSHADER_H
#define QSHADER_H
#include <vector>
#include <string>
#include "../../Render/Drawer.h"


namespace InGE{

	using std::vector;
	using std::string;

	class QShader{
		private:
			int 	m_cullMode;
			int		m_blendSrc;
			int		m_blendDst;
			string  m_name;
			vector<unsigned int> m_vTextureId;
			vector<string>		m_vTextureFileName;
			
			bool	m_blendOn;
			bool	m_cullOn;
			unsigned int m_currentIndex;
			float 	m_freq;
			
			unsigned int m_lastTime;
			
		public:
		
			QShader(string name);
			~QShader();
			
			unsigned int getTextureId();
			void applyMode();
			
			void setCullMode(int cullMode);
			void setBlendFunc(int src, int dst);
			void setFreq(float freq);
			void unsetBlend();
			void unsetCull();			
			void addTextureFileName(string textureFileName);
			void loadTextures();			
			string getName();
			// TODO: void unloadTexture();
			void print();
			
			
	};

};

#endif // QSHADER_H
