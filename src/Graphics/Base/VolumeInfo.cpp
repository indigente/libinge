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

#include "VolumeInfo.h"

using namespace InGE;

VolumeInfo::VolumeInfo(){
	m_radius = 0;
}

VolumeInfo::VolumeInfo(VolumeInfo *pVolumeInfo){
	if (!pVolumeInfo) return;
	m_minBound = pVolumeInfo->getMinBound();
	m_maxBound = pVolumeInfo->getMaxBound();
	m_origin = pVolumeInfo->getOrigin();
	m_radius = pVolumeInfo->getRadius();
}

VolumeInfo::VolumeInfo(Vector3 minBound, Vector3 maxBound, Vector3 origin,float radius){
	setVolumeInfo(minBound, maxBound, origin, radius);
}

VolumeInfo::~VolumeInfo(){
}

void VolumeInfo::setVolumeInfo(Vector3 minBound, Vector3 maxBound, Vector3 origin,float radius){
	m_minBound = minBound;
	m_maxBound = maxBound;
	m_origin = origin;
	m_radius = radius;
}

Vector3 VolumeInfo::getMinBound(){
	return m_minBound;
}

Vector3 VolumeInfo::getMaxBound(){
	return m_maxBound;
}

Vector3 VolumeInfo::getOrigin(){
	return m_origin;
}

float VolumeInfo::getRadius(){
	return m_radius;
}

/**
 * @param ConcreteMesh *pMesh - ConcreteMesh com o qual será feita a interpolação
 * @param float interpolation - Fração de interpolação entre os ConcreteMeshs
 * @return Retorna um novo ConcreteMesh interpolado
 */		
VolumeInfo *VolumeInfo::interpolate(VolumeInfo *pVolumeInfo, float interpolation){
	VolumeInfo *pNewVolumeInfo = new VolumeInfo(pVolumeInfo);
	
	pNewVolumeInfo->m_minBound += ( pNewVolumeInfo->m_minBound - this->m_minBound ) * interpolation;
	
	pNewVolumeInfo->m_maxBound += ( pNewVolumeInfo->m_maxBound - this->m_maxBound ) * interpolation;
	
	pNewVolumeInfo->m_origin += ( pNewVolumeInfo->m_origin - this->m_origin ) * interpolation;
	
	pNewVolumeInfo->m_radius += ( pNewVolumeInfo->m_radius - this->m_radius ) * interpolation;
	
	return pNewVolumeInfo;
}
