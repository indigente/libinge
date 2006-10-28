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
#include "HeightmapBruteForce.h"

using namespace InGE;

HeightmapBruteForce::HeightmapBruteForce(){
}

HeightmapBruteForce::~HeightmapBruteForce(){
}

void HeightmapBruteForce::renderLevel(Vector3 vPos, Frustum &frustum){
	int x,y;
	//unsigned char ucColor;
	Drawer *drawer = Drawer::getInstance();
	drawer->bindTexture(InGE_TEXTURE_2D,id_texture);
	drawer->color(1.0f,1.0f,1.0f,1.0f);
		
	for (y=0; y<m_size-1; y++){
		//drawer->begin(InGE_QUADS); 
		drawer->begin(InGE_TRIANGLE_STRIP);
		for (x=0; x<m_size-1; x++){
			//ucColor=getTrueHeightAtPoint(x,y);
			//drawer->color(ucColor,ucColor,ucColor);
			drawer->texCoord((float)x/m_size,(float)y/m_size);
			drawer->vertex(x, y, getScaledHeightAtPoint(x,y));
			
			//ucColor=getTrueHeightAtPoint(x,y+1);
			//drawer->color(ucColor,ucColor,ucColor);
			drawer->texCoord((float)x/m_size,(float)(y+1)/m_size);
			drawer->vertex(x, y+1, getScaledHeightAtPoint(x,y+1));
		}
		
		drawer->end();
	}
}
