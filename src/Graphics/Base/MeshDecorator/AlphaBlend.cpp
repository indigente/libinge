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

#include "AlphaBlend.h"
using namespace InGE;

AlphaBlend::AlphaBlend(Mesh *pMesh) : MeshDecorator(pMesh){
}

AlphaBlend::~AlphaBlend(){
	delete m_component;
}

/**
 * @return Retorna se o mesh possue blend
 */
bool AlphaBlend::getBlend(){
	return true;
}

/**
 * @param Mesh *pMesh - Mesh com o qual será feita a interpolação
 * @param float interpolation - Fração de interpolação entre os MeshDecorators
 * @return Retorna um novo mesh interpolado
 */		
Mesh *AlphaBlend::interpolate(Mesh *pMesh, float interpolation){
	return new AlphaBlend( m_component->interpolate(pMesh, interpolation) );
}

void AlphaBlend::set(bool setup){
	Drawer *drawer = Drawer::getInstance();
	
	drawer->enable(InGE_BLEND);
	drawer->blendFunc( InGE_SRC_ALPHA, InGE_ONE_MINUS_SRC_ALPHA );
	
	m_component->set(setup);
}

void AlphaBlend::unset(){
	Drawer *drawer = Drawer::getInstance();
	
	drawer->disable(InGE_BLEND);

	m_component->unset();
}
