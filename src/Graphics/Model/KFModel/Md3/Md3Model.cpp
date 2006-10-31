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

#include "Md3Model.h"

#include <iostream>
using namespace std;

namespace InGE{

bool sAnimInfo::operator<=(const sAnimInfo *animInfo) const{
	if (bodyPart == animInfo->bodyPart)
		return (firstFrame <= animInfo->firstFrame);
	return (bodyPart <= animInfo->bodyPart);
}

Md3Model::Md3Model(string bodyPart, map<string, vector<KeyFrame *> > mapAnim){
	m_type = MD3_IDENT;
	m_bodyPart = bodyPart;
	std::transform(m_bodyPart.begin(), m_bodyPart.end(), m_bodyPart.begin(), (int(*)(int)) toupper);

	m_mapAnim = mapAnim;
}


Md3Model::~Md3Model(){
}

/**
 * Seta o nome do Mesh
 * @param string name - Nome do Mesh
 */
void Md3Model::setName(string name){
	m_name = name;
}

/**
 * @return Retorna o nome do modelo.
 */
string Md3Model::getName(){
	return m_name;
}

/**
 * @return Retorna o tipo do modelo.
 */
int Md3Model::getType(){
	return m_type;
}

/**
 * Anexa um modelo ao outro atravez das tags
 * @param pModel - Ponteiro para o modelo a ser anexado
 */
bool Md3Model::attachModel(IModel *pModel){
	if (!pModel) return false;
	if (pModel->getType() != m_type) 
		return false;
	
	Md3Model *pMd3Model = (Md3Model *)pModel;
	map<string, Md3Model *>::iterator modelIt;
	modelIt = m_mapModel.find(pMd3Model->getBodyPart());
	
	if ( modelIt != m_mapModel.end() ){
		m_mapModel[pMd3Model->getBodyPart()] = pMd3Model;
		return true;
	}
 	
	map<string, vector<KeyFrame *> >::iterator animIt;
	animIt = m_mapAnim.begin();
	KeyFrame *keyFrame = animIt->second[0];

	animIt = pMd3Model->m_mapAnim.begin();
	KeyFrame *attachedKeyFrame = animIt->second[0];
	
	if (!keyFrame) return false;
	
	for (int tagIndex = 0; tagIndex < keyFrame->getNumTag(); tagIndex++){
		for (int attachedTagIndex = 0; attachedTagIndex < attachedKeyFrame->getNumTag(); attachedTagIndex++){
			if (attachedKeyFrame->pGetTag(attachedTagIndex)->getName() == keyFrame->pGetTag(tagIndex)->getName()){
				m_mapModel[pMd3Model->getBodyPart()] = pMd3Model;
				return true;
			} else if (m_mapModel.size() > 0) {
				map<string, Md3Model *>::iterator modelIt;
				for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
					if (modelIt->second){
						if ( (modelIt->second)->attachModel(pMd3Model) ){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
	
}

/**
 * @return Retorna o numero de modelos anexados
 */
int Md3Model::getNumOfAttach(){
	int numModel = m_mapModel.size();
	return numModel;
}

/**
 * Adiciona as informações de animação de uma entidade na tabela de animações do modelos. Assim podemos saber a animação, quadro chave e outras informações referentes ao modelo e a entidade que o renderiza.
 */
void Md3Model::addEntityID(string entityID){
	CurrentAnimInfo *currAnim = new CurrentAnimInfo;
	m_mapEntityAnim[entityID] = currAnim;
	map<string, vector<KeyFrame *> >::iterator	itAnim;
	itAnim = m_mapAnim.begin();
	
	currAnim->setCurrAnim( itAnim->first );
	currAnim->setNextAnim( itAnim->first );
	
	map<string, Md3Model *>::iterator modelIt;
	for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
		if (modelIt->second){
				(modelIt->second)->addEntityID(entityID);
		}
	}
}

/**
 * Adiciona uma entidade a tabela de animações do modelos. Assim podemos saber a animação, quadro chave e outras informações referentes ao modelo e a entidade que o renderiza.
 */
void Md3Model::removeEntityID(string entityID){
	//TODO mandar a recurs� para os modelos anexados
	map <string, CurrentAnimInfo *>::iterator it;
	
	it = m_mapEntityAnim.find(entityID);
	
	if (it == m_mapEntityAnim.end()){
		return;
	}

	
	CurrentAnimInfo *currAnim = m_mapEntityAnim[entityID];
	
	map<string, Md3Model *>::iterator modelIt;
	for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
		if (modelIt->second){
			modelIt->second->removeEntityID(entityID);
		}
	}

	
	delete currAnim;
	m_mapEntityAnim.erase(entityID);
}

/**
 * Renderiza o modelo na posição da Entidade
 * @param entityID - Usada para saber a animação, quadro chave e interpolação em que o modelo deve ser renderizado.
 */
void Md3Model::drawModel(string entityID){
	Drawer *drawer = Drawer::getInstance();
	
	map<string, CurrentAnimInfo *>::iterator itCurrAnim;
	itCurrAnim = m_mapEntityAnim.find(entityID);

	if(itCurrAnim == m_mapEntityAnim.end()){
		addEntityID( entityID );
		itCurrAnim = m_mapEntityAnim.find(entityID);
	}
	CurrentAnimInfo *currAnim = itCurrAnim->second;
	currAnim->linearInterpolation( getNumFrame(currAnim->getCurrAnim()) );
	
	if(m_vetVolumeInfo.size() > 0)
		m_vetVolumeInfo.clear();
	
	m_vetVolumeInfo.push_back( drawFrame(currAnim) );
	
	map<string, vector<KeyFrame *> >::iterator itVetKeyFrame;
	itVetKeyFrame = m_mapAnim.find(currAnim->getCurrAnim());
	
	if (itVetKeyFrame != m_mapAnim.end()){
		KeyFrame *keyFrame =  itVetKeyFrame->second[ currAnim->getKeyFrameIndex() ];
		
		Md3Model *pModel;
		for (int tagIndex = 0; tagIndex < keyFrame->getNumTag(); tagIndex++){
			map<string, Md3Model *>::iterator modelIt;
			modelIt = m_mapModel.find(keyFrame->pGetTag( tagIndex )->getName()); 
			pModel = modelIt->second;
			if (pModel){
				sphereInterpolation(tagIndex, currAnim);
				
				pModel->drawModel(entityID);
					
				drawer->popMatrix();
			}
		}
	}
}

/**
 * @return Retorna o VolumeInfo atual
 */
vector<VolumeInfo *> Md3Model::getVetVolumeInfo(){
	return m_vetVolumeInfo;
}

/**
 * @return Retorna o numero de anima�es
 */
unsigned int Md3Model::getNumAnimation(){
	return m_mapAnim.size();
}

/**
 * @param entityID - Usada para saber sobre qual entidade se refere a requisição.
 * @return Retorna o indice da animação atual
 */
string Md3Model::getAnimation( string entityID ){
	map<string, CurrentAnimInfo *>::iterator itC;
	itC = m_mapEntityAnim.find(entityID);
		
	if (itC == m_mapEntityAnim.end()){
		addEntityID( entityID );
		itC = m_mapEntityAnim.find(entityID);
	}
	
	return (itC->second)->getCurrAnim();
}

/**
 * @param entityID - Usada para saber sobre qual entidade se refere a requisição.
 */
void Md3Model::setAnimation( string entityID, string currAnim, string nextAnim ){
	map<string, vector<KeyFrame *> >::iterator itCurr;
	map<string, vector<KeyFrame *> >::iterator itNext;
	itCurr = m_mapAnim.find(currAnim);
	itNext = m_mapAnim.find(nextAnim);
	
	if (itCurr != m_mapAnim.end()){
		map<string, CurrentAnimInfo *>::iterator itC;
		itC = m_mapEntityAnim.find(entityID);
		
		if (itC == m_mapEntityAnim.end()){
			addEntityID( entityID );
			itC = m_mapEntityAnim.find(entityID);
		}
		
		(itC->second)->setCurrAnim(currAnim);
		
		if (itNext != m_mapAnim.end()){
			(itC->second)->setNextAnim(nextAnim);
		}
	}
	
	
	map<string, Md3Model *>::iterator modelIt;
	for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
		if(modelIt->second){
			(modelIt->second)->setAnimation(entityID, currAnim, nextAnim);
		}
	}
}

/**
 * @return Retorna o numero de Frames
 */
unsigned int Md3Model::getNumFrame(string animIndex){
	return m_mapAnim[animIndex].size();
}

/**
 * @param int animIndex - �dice da anima?o.
 * @param int keyFrameIndex - �dice do quadro chave.
 * @return Retorna um quadro chave de uma anima?o.
 */
KeyFrame *Md3Model::getKeyFrame(string animIndex, int keyFrameIndex){
	return m_mapAnim[animIndex][keyFrameIndex % m_mapAnim[animIndex].size()];
}


/**
 * @return Retorna a parte do corpo representada pelo modelo.
 */
string Md3Model::getBodyPart(){
	return m_bodyPart;
}

/**
 * @return Retorna se algum mat�ial do modelo possue canal alfa.
 */
bool Md3Model::getBlend(){ //TODO Melhorar esse metodo de Blend para checar em todos os meshs
	map<string, vector<KeyFrame *> >::iterator it;
	it = m_mapAnim.begin();
	KeyFrame *keyFrame = it->second[0];
	if (!keyFrame)
		return false;
	
	return (keyFrame->getMesh(0)->getBlend());
}


	
/**
 * @param int currentAnim - �dice da anima�o atual.
 * @param int currentKeyFrame - �dice do quadro chave atual.
 * @param int currentMaterial - �dice do material atual.
 * @param float interpolationToNextFrame - Porcentagem entre os quadro chavez na interpola?o.
 */
VolumeInfo *Md3Model::drawFrame(CurrentAnimInfo *currAnim){
	string animIndex = currAnim->getCurrAnim();
	int currkeyFrameIndex = currAnim->getKeyFrameIndex();
	int nextKeyFrameIndex = (currkeyFrameIndex + 1) % m_mapAnim[animIndex].size();
	
	KeyFrame *currKeyFrame =  m_mapAnim[animIndex][currkeyFrameIndex];
	KeyFrame *nextKeyFrame =  m_mapAnim[animIndex][nextKeyFrameIndex];
	
	KeyFrame *newFrame = currKeyFrame->interpolate(nextKeyFrame , currAnim->getInterpolation());
	
	Mesh *pMesh;
	unsigned int numOfMesh = currKeyFrame->getNumMesh();
	for (unsigned int meshI = 0; meshI < numOfMesh ; meshI++){
		if (currAnim->getIsDraw()){
			if (newFrame->getMeshDrawFlag(meshI)){
				
				pMesh = newFrame->getMesh( meshI );
				
				pMesh->draw();
			}
		}
	}
	
	VolumeInfo *volumeInfo = new VolumeInfo( newFrame->pGetVolumeInfo() );
	
	delete newFrame;
	return volumeInfo;
}

/**
 * Interpolação esferica.
 * @param int bodyParty - ?dice referente ao modelo que ser?interpolado..
 * @param int tagIndex - ?dice da tag a ser usada para a interpola?o.
 * @param float interpolationToNextFrame - Grada?o da interpola?o.
 */
void Md3Model::sphereInterpolation(int tagIndex, CurrentAnimInfo *currAnim){
	Drawer *drawer = Drawer::getInstance();
	float finalMatrix[16];
	Quaternion *quat1 = new Quaternion();
	Quaternion *quat2 = new Quaternion();
	Quaternion *finalQuat = new Quaternion();
	Tag *currentTag, *nextTag;

	int nextFrameIndex = currAnim->getKeyFrameIndex() + 1;
	nextFrameIndex  %= m_mapAnim[currAnim->getCurrAnim()].size();
	
	float interpolation = currAnim->getInterpolation();
	
	currentTag = getKeyFrame(currAnim->getCurrAnim(), currAnim->getKeyFrameIndex())->pGetTag(tagIndex);
	nextTag = getKeyFrame(currAnim->getCurrAnim(), nextFrameIndex)->pGetTag(tagIndex);

	quat1->matrixToQuaternion(*currentTag->getRotation()->axis);
	quat2->matrixToQuaternion(*nextTag->getRotation()->axis);

	finalQuat->quaternionSlerp( quat1, quat2, interpolation);
	memcpy(finalMatrix , finalQuat->quaternionToMatrix(), sizeof(finalMatrix));
	
	finalMatrix[12] = (currentTag->getPosition()->getX() + interpolation * (nextTag->getPosition()->getX() - currentTag->getPosition()->getX()));
	finalMatrix[13] = (currentTag->getPosition()->getY() + interpolation * (nextTag->getPosition()->getY() - currentTag->getPosition()->getY()));
	finalMatrix[14] = (currentTag->getPosition()->getZ() + interpolation * (nextTag->getPosition()->getZ() - currentTag->getPosition()->getZ()));
	drawer->pushMatrix();
	glMultMatrixf( finalMatrix );
	
	delete quat1;
	delete quat2;
	delete finalQuat;
}

void Md3Model::setBodyPart(string bodyname){
	m_bodyPart = bodyname;
}

void Md3Model::setDraw(string entityID,bool draw){
	map<string, CurrentAnimInfo *>::iterator it;
	it = m_mapEntityAnim.find(entityID);
	
	if (it == m_mapEntityAnim.end()){
		addEntityID( entityID );
		it = m_mapEntityAnim.find(entityID);
	}
	it->second->setIsDraw(draw);
	map<string, Md3Model *>::iterator modelIt;
	for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
		if(modelIt->second){
			(modelIt->second)->setDraw(entityID, draw);
		}
	}
	
}

void Md3Model::setDraw(string entityID,bool draw, string partToDraw){
	map<string, CurrentAnimInfo * >::iterator it;
	it = m_mapEntityAnim.find(entityID);
	
	if (it == m_mapEntityAnim.end()){
		addEntityID( entityID );
		it = m_mapEntityAnim.find(entityID);
	}
	
	if(it->first==partToDraw){//FIXME: Isso está errado, mas como fazer funcionar? Estou comparando com a ID da entidade....
		it->second->setIsDraw(draw);
	} else {
		map<string, Md3Model *>::iterator modelIt;
		for (modelIt = m_mapModel.begin(); modelIt != m_mapModel.end(); modelIt++){
			if(modelIt->second){
				(modelIt->second)->setDraw(entityID, draw, partToDraw);
			}
		}
	}
}

}
