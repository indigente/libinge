/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004 Indigente


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

#include "BoundVolume.h"

using namespace InGE;

BoundVolume::BoundVolume(){
}

BoundVolume::BoundVolume(sBoundVolume boundVolume){
	setBoundVolume(boundVolume);
}

BoundVolume::~BoundVolume(){
}

void BoundVolume::setBoundVolume(sBoundVolume boundVolume){
	this->m_minBound.setXYZ(boundVolume.mins[0],boundVolume.mins[1],boundVolume.mins[2]);
	this->m_maxBound.setXYZ(boundVolume.maxs[0],boundVolume.maxs[1],boundVolume.maxs[2]);
	this->m_origin.setXYZ(boundVolume.position[0],boundVolume.position[1],boundVolume.position[2]);
	this->m_radius = boundVolume.scale;
}

Vector3 BoundVolume::getMinBound(){
	return m_minBound;
}

Vector3 BoundVolume::getMaxBound(){
	return m_maxBound;
}

Vector3 BoundVolume::getOrigin(){
	return m_origin;
}

float BoundVolume::getRadius(){
	return m_radius;
}

/**
 * @param ConcreteMesh *pMesh - ConcreteMesh com o qual será feita a interpolação
 * @param float interpolation - Fração de interpolação entre os ConcreteMeshs
 * @return Retorna um novo ConcreteMesh interpolado
 */		
BoundVolume *BoundVolume::interpolate(BoundVolume *pBoundVolume, float interpolation){
	BoundVolume *pNewBoundVolume = new BoundVolume();
	
	pNewBoundVolume->m_minBound = this->m_minBound;
	pNewBoundVolume->m_minBound += ( pBoundVolume->m_minBound - this->m_minBound ) * interpolation;
	
	pNewBoundVolume->m_maxBound = this->m_maxBound;
	pNewBoundVolume->m_maxBound += ( pBoundVolume->m_maxBound - this->m_maxBound ) * interpolation;
	
	pNewBoundVolume->m_origin = this->m_origin;
	pNewBoundVolume->m_origin += ( pBoundVolume->m_origin - this->m_origin ) * interpolation;
	
	pNewBoundVolume->m_radius = this->m_radius;
	pNewBoundVolume->m_radius += ( pBoundVolume->m_radius - this->m_radius ) * interpolation;
	
	return pNewBoundVolume;
}
