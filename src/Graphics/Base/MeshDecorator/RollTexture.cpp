/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004-2005 Indigente

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

#include "RollTexture.h"

using namespace InGE;
using namespace InGE;

RollTexture::RollTexture(Mesh *pMesh, float rollU, float rollV) : MeshDecorator(pMesh){
	m_vetRollSpeed.push_back(new Vector2(rollU, rollV));
}

RollTexture::RollTexture(Mesh *pMesh, std::vector<Vector2 *> vetRollSpeed) : MeshDecorator(pMesh){
	m_vetRollSpeed = vetRollSpeed;
}

RollTexture::~RollTexture(){
	delete m_component;
}

/**
 * @param RollTexture *pMesh - RollTexture com o qual ser� feita a interpola��o
 * @param float interpolation - Fra��o de interpola��o entre os MeshDecorators
 * @return Retorna um novo mesh interpolado
 */		
Mesh *RollTexture::interpolate(Mesh *pMesh, float interpolation){
	return new RollTexture( m_component->interpolate(pMesh, interpolation), m_vetRollSpeed );
}

void RollTexture::set(bool setup){
	Vertex *vertex;
	float tu, tv;
	for (unsigned int i = 0; i < m_component->getNumVertex(); i++){
		vertex = m_component->getVertex(i);
		tu = vertex->getTU() + m_vetRollSpeed[i % m_vetRollSpeed.size()]->getX();
		tv = vertex->getTV() + m_vetRollSpeed[i % m_vetRollSpeed.size()]->getY();
		vertex->setTexCoord(tu, tv);
	}	
	m_component->set(setup);
}

