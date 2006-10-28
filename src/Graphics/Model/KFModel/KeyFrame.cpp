/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004 Indigente


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

#include "KeyFrame.h"

using namespace InGE;
using std::vector;

KeyFrame::KeyFrame(){
}

KeyFrame::~KeyFrame(){
	for (int i = 0; i < m_vetTag.size(); i++ ){
		delete m_vetTag[i];
	}
	for (int i = 0;i<m_vetMesh.size();i++ ){
		delete m_vetMesh[i];
	}

	m_vetTag.clear();
	m_vetMesh.clear();
	m_vetDrawFlag.clear();
	
}

void KeyFrame::setName(string name){
	m_name = name;
}

void KeyFrame::addTag(Tag *pTag){
	m_vetTag.push_back(pTag);
}

void KeyFrame::addMesh(Mesh *mesh){
	if(!mesh) return;
	m_vetMesh.push_back(mesh);
	m_vetDrawFlag.push_back(true);
}

void KeyFrame::setVolumeInfo(sBoundVolume &boundVolume){
	Vector3 min(boundVolume.mins);
	Vector3 max(boundVolume.maxs);
	Vector3 orig(boundVolume.position);
	float radius = boundVolume.scale;
	
	m_volumeInfo.setVolumeInfo( min, max, orig, radius );
}

void KeyFrame::setVolumeInfo(VolumeInfo volumeInfo){
	memcpy(&m_volumeInfo , &volumeInfo, sizeof(VolumeInfo));
}

string KeyFrame::getName(){
	return m_name;
}

Tag *KeyFrame::pGetTag(int index){
	return m_vetTag[index];
}

unsigned int KeyFrame::getNumTag(){
	return m_vetTag.size();
}

unsigned int KeyFrame::getNumMesh(){
	return m_vetMesh.size();
}
bool KeyFrame::getMeshDrawFlag(int index){
	return m_vetDrawFlag[index];
}

Mesh *KeyFrame::getMesh(int index){
	return m_vetMesh[index];
}

VolumeInfo *KeyFrame::pGetVolumeInfo(){
	return &m_volumeInfo;
}

KeyFrame *KeyFrame::interpolate(KeyFrame *nextFrame, float interpolationToNextFrame){
	KeyFrame *newKeyFrame = new KeyFrame();
	for (unsigned int meshI = 0; meshI < m_vetMesh.size(); meshI++){
		Mesh *currMesh, *nextMesh, *pMesh;
		currMesh = this->getMesh(meshI);
		nextMesh = nextFrame->getMesh(meshI);
	
		pMesh = currMesh->interpolate(nextMesh, interpolationToNextFrame);
		newKeyFrame->addMesh( pMesh );
// 		newKeyFrame->addMesh( currMesh );
	}
	
	VolumeInfo *currVolume, *nextVolume, *pVolumeInfo;
	currVolume = this->pGetVolumeInfo();
	nextVolume = nextFrame->pGetVolumeInfo();
	
	pVolumeInfo = currVolume->interpolate( nextVolume, interpolationToNextFrame);

	newKeyFrame->setVolumeInfo(pVolumeInfo);
// 	newKeyFrame->setVolumeInfo(currVolume);
	
	return newKeyFrame;
}
