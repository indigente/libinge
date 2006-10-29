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
#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "../IScene.h"
#include "../../Render/IRenderListener.h"
#include "../../Render/Drawer.h"
#include <string>

using std::string;

namespace InGE{

struct HeightData{
	unsigned char* m_pData;	//dados de altura
	int m_size;				//tamanho do lado do mapa (elevar ao quadrado)
};

class HeightmapBase : public InGE::IScene{
  protected:
	HeightData m_heightData;	//dados de altura
	float m_heightScale;		//fator de escala da altura
	unsigned int id_texture;	//identificador da textura
		
  public:
	int m_size;			//deve ser potencia de dois (?)
	
	bool loadHeightMap(char *filename, int size);
	bool saveHeightMap(char *filename);
	bool unloadHeightMap(void);

	inline void setHeightScale(float scale)
	{	m_heightScale = scale;	}

	inline void setHeightAtPoint(unsigned char height, int x, int y)
	{	m_heightData.m_pData[(y * m_size) + x] = height;	}

	inline unsigned char getTrueHeightAtPoint(int x, int y)
	{ return (m_heightData.m_pData[(y * m_size) + x]);	}

	inline float getScaledHeightAtPoint(int x, int y)
	{ return ((m_heightData.m_pData[(y * m_size) + x]) * m_heightScale);	}
	
	void loadTexture(string path);
	
	HeightmapBase();
	~HeightmapBase();
};

};
#endif // HEIGHTMAP_H
