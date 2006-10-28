/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

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
#include "Lightmap.h"
using namespace InGE;

Lightmap::Lightmap(Mesh *pMesh, unsigned int pTexture, vector<Vector2 > &vetLightmapCoord) : MeshDecorator(pMesh){
	m_pTexture = pTexture;
	m_vetLightmapCoord = vetLightmapCoord;
}

Lightmap::~Lightmap(){
	delete m_component;
}

Mesh *Lightmap::interpolate(Mesh *pMesh, float interpolation){
	return new Lightmap( m_component->interpolate(pMesh, interpolation), m_pTexture, m_vetLightmapCoord );
}

void Lightmap::set(bool setup){
	Drawer *drawer = Drawer::getInstance();
	m_component->set(setup);
	
	drawer->enable(InGE_BLEND);
	
	drawer->activeTextureARB(InGE_TEXTURE1_ARB);
	drawer->enable(InGE_TEXTURE_2D);
	drawer->bindTexture(InGE_TEXTURE_2D, m_pTexture );
	
	drawer->clientActiveTextureARB(InGE_TEXTURE1_ARB);
	drawer->enableClientState(InGE_TEXTURE_COORD_ARRAY);
	drawer->texCoordPointer(2, InGE_FLOAT, sizeof(Vector2), &m_vetLightmapCoord[0]);
}

void Lightmap::unset(){
	Drawer *drawer = Drawer::getInstance();
	
	drawer->disable(InGE_BLEND);
	
	drawer->activeTextureARB(InGE_TEXTURE1_ARB);
	drawer->disable(InGE_TEXTURE_2D);
	
	drawer->clientActiveTextureARB(InGE_TEXTURE1_ARB);
	drawer->disableClientState(InGE_TEXTURE_COORD_ARRAY);
	
	m_component->unset();
}

