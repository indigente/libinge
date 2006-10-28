/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2005 Indigente

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

#include "Mask.h"
using namespace InGE;

Mask::Mask(Mesh *pMesh, MaterialInfo mask) : MeshDecorator(pMesh){
	m_mask = mask;
}

Mask::~Mask(){
	delete m_component;
}

/**
 * @return Retorna se o mesh possue blend
 */
bool Mask::getBlend(){
	return true;
}

Mesh *Mask::interpolate(Mesh *pMesh, float interpolation){
	return new Mask( m_component->interpolate(pMesh, interpolation), m_mask );
}

void Mask::set(bool setup){
	Drawer *drawer = Drawer::getInstance();

	drawer->enable(InGE_BLEND);
	
	drawer->blendFunc( InGE_DST_COLOR, InGE_ZERO );

	drawer->activeTextureARB(InGE_TEXTURE0_ARB);
	drawer->enable(InGE_TEXTURE_2D);
	drawer->bindTexture( InGE_TEXTURE_2D, m_mask.getId() );
	
	drawer->clientActiveTextureARB(InGE_TEXTURE0_ARB);
	drawer->enableClientState(InGE_TEXTURE_COORD_ARRAY);
	drawer->texCoordPointer(2, InGE_FLOAT, sizeof(Vertex), m_component->getVertex(0)->getTextureOffset());
	
	drawer->enableClientState(InGE_NORMAL_ARRAY);
	drawer->normalPointer(InGE_FLOAT, sizeof(Vertex), m_component->getVertex(0)->getNormalOffset());

	drawer->enableClientState(InGE_VERTEX_ARRAY);
	drawer->vertexPointer(3, InGE_FLOAT, sizeof(Vertex), m_component->getVertex(0)->getPositionOffset());

	
	drawer->drawElements(m_component->getDrawMode(), m_component->getNumIndex(), InGE_UNSIGNED_INT, m_component->getDrawIndexOffSet());

	drawer->blendFunc( InGE_ONE, InGE_ONE_MINUS_CONSTANT_COLOR );

	m_component->set(setup);
}

void Mask::unset(){
	Drawer *drawer = Drawer::getInstance();
	
	drawer->disable(InGE_BLEND);
	m_component->unset();
}
