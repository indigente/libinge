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

#include "MeshDecorator.h"

using namespace InGE;

MeshDecorator::MeshDecorator(Mesh *pMesh){
	m_component = pMesh;
}

MeshDecorator::~MeshDecorator(){
	delete m_component;
}
/**
 * Seta o nome do MeshDecorator
 * @param string name - Nome do MeshDecorator
 */
void MeshDecorator::setName(string name){
	m_component->setName(name);
}

/**
 * Seta o modo de renderiza�o
 * @param EnumDrawer mode - Modo de renderiza�o
 */
void MeshDecorator::setDrawMode(EnumDrawer mode){
	m_component->setDrawMode(mode);
}

/**
 * Seta o modo de renderiza�o
 * @param EnumDrawer frontFace - Orienta�o das faces
 */
void MeshDecorator::setFrontFace(EnumDrawer frontFace){
	m_component->setFrontFace(frontFace);
}

/**
 * Adiciona um vertice ao ConcreteMesh
 * @param vector<Vertex> vetVertex - Vetor de v�tices a ser setado
 */
void MeshDecorator::setVertex(vector<Vertex> vetVertex){
	m_component->setVertex(vetVertex);
}
/**
 * Adiciona um vertice ao ConcreteMesh
 * @param Vertex *vetVertex - Ponteiro para o inicio do vetor de v�tices
 * @param unsigned int numVertex - Numero de v�tices
 */
void MeshDecorator::setVertex(Vertex *vetVertex, unsigned int numVertex){
	m_component->setVertex(vetVertex, numVertex);
}
/**
 * Adiciona um vertice ao ConcreteMesh
 * @param Vertex vertex - Vertice adicionado
 */
void MeshDecorator::addVertex(Vertex vertex){
	m_component->addVertex(vertex);

}
/**
 * Esvazia o vetor de v�tices
 */
void MeshDecorator::clearVertex(){
	m_component->clearVertex();
}

/**
 * Seta o m_drawIndex
 * @param vector<unsigned int> *drawIndex - Vetor de indices das faces
 */		
void MeshDecorator::setDrawIndex(vector<unsigned int> drawIndex){
	m_component->setDrawIndex(drawIndex);
}

/**
 * Seta o m_drawIndex
 * @param unsigned int *drawIndex - Ponteiro para o inicio do vetor de indices das faces
 * @param unsigned int numIndex - Numeto de indices das Faces
 */		
void MeshDecorator::setDrawIndex(unsigned int *drawIndex, unsigned int numIndex){
	m_component->setDrawIndex(drawIndex, numIndex);
}

/**
 * Adiciona um indice de face ao ConcreteMesh
 * @param unsigned int drawIndex - Indices das faces
 */		
void MeshDecorator::addDrawIndex(unsigned int drawIndex){
	m_component->addDrawIndex(drawIndex);
}
/**
 * Esvazia o vetor de �dices
 */
void MeshDecorator::clearDrawIndex(){
	m_component->clearDrawIndex();
}

/**
 * Adiciona um material ao MeshDecorator
 * @param MaterialInfo material - Novo material
 */		
void MeshDecorator::addMaterial(MaterialInfo material){
	m_component->addMaterial(material);
}
/**
 * Seta o material a ser renderisado
 * @param unsigned int index - Indice do material a ser utilizado
 */	
void MeshDecorator::setMaterial(unsigned int index){
	m_component->setMaterial(index);
}

/**
 * Calcula as Informa�es de Volume do Mesh
 */
VolumeInfo *MeshDecorator::pCalcVolumeInfo(){
	return m_component->pCalcVolumeInfo();
}

/**
 * @return Retorna o nome do MeshDecorator
 */		
string MeshDecorator::getName(){
	return m_component->getName();
}

/**
 * @return Retorna o modo de renderiza�o
 */		
EnumDrawer MeshDecorator::getDrawMode(){
	return m_component->getDrawMode();
}
/**
 * @return Retorna a orienta�o da face
 */		
EnumDrawer MeshDecorator::getFrontFace(){
	return m_component->getFrontFace();
}

/**
 * @param unsigned int index - Indice do vertice a ser retornado
 * @return Retorna um Vertex do VertexSet
 */		
Vertex *MeshDecorator::getVertex(unsigned int index){
	return m_component->getVertex(index);
}
/**
 * @return Retorna o numero de vertices
 */	
unsigned int MeshDecorator::getNumVertex(){
	return m_component->getNumVertex();
}

/**
 * @return Retorna o inicio dos indices das faces
 */	
unsigned int *MeshDecorator::getDrawIndexOffSet(){
	return m_component->getDrawIndexOffSet();
}
/**
 * @return Retorna o numero de vertices
 */	
unsigned int MeshDecorator::getNumIndex(){
	return m_component->getNumIndex();
}

/**
 * @param unsigned int index - Indice do material a ser retornado
 * @return Retorna um material
 */		
MaterialInfo MeshDecorator::getMaterial(unsigned int index){
	return m_component->getMaterial(index);
}
/**
 * @return Retorna um material
 */		
MaterialInfo MeshDecorator::getMaterial(){
	return m_component->getMaterial();
}
/**
 * @return Retorna o numero de materiais no MeshDecorator
 */	
unsigned int MeshDecorator::getNumMaterial(){
	return m_component->getNumMaterial();
}


/**
 * @return Retorna se o mesh possue blend
 */
bool MeshDecorator::getBlend(){
	return m_component->getBlend();
}

Mesh *MeshDecorator::getConcreteMesh(){
	return m_component->getConcreteMesh();
}

void MeshDecorator::render(){
	m_component->render();
}

void MeshDecorator::set(bool setup){
	m_component->set(setup);
}

void MeshDecorator::unset(){
	m_component->unset();
}

void MeshDecorator::draw(){
	this->set(0);
	this->render();
	this->unset();
}

void MeshDecorator::executeCommand(ExecuteCommandEnum e, string param){
	m_component->executeCommand(e,param);
}
