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

#include "ConcreteMesh.h"

using namespace InGE;
using namespace std;

/**
 * Construtor
 */
ConcreteMesh::ConcreteMesh(){
	this->m_name = "";
	m_drawMode = InGE_TRIANGLES;
	m_cullFace = false;

	m_currMaterial = 0;
}

/**
 * Construtor
 */
ConcreteMesh::ConcreteMesh(ConcreteMesh *pMesh){
	this->m_name = pMesh->m_name;
	this->m_drawMode = pMesh->m_drawMode;

	this->m_cullFace = pMesh->m_cullFace;
	this->m_frontFace = pMesh->m_frontFace;
	
	this->m_vetVertex = pMesh->m_vetVertex;
	this->m_drawIndex = pMesh->m_drawIndex;

	this->m_vetMaterial = pMesh->m_vetMaterial;
	this->m_currMaterial = pMesh->m_currMaterial;

}

ConcreteMesh::~ConcreteMesh(){
}

/**
 * Seta o nome do ConcreteMesh
 * @param string name - Nome do ConcreteMesh
 */
void ConcreteMesh::setName(string name){
	m_name = name;
}

/**
 * Seta o modo de renderiza�o
 * @param EnumDrawer mode - Modo de renderiza�o
 */
void ConcreteMesh::setDrawMode(EnumDrawer mode){
	m_drawMode = mode;
}

/**
 * Seta o modo de renderiza�o
 * @param EnumDrawer frontFace - Orienta�o das faces
 */
void ConcreteMesh::setFrontFace(EnumDrawer frontFace){
	m_frontFace = frontFace;
	m_cullFace = true;
}

/**
 * Adiciona um vertice ao ConcreteMesh
 * @param vector<Vertex> vetVertex - Vetor de v�tices a ser setado
 */
void ConcreteMesh::setVertex(vector<Vertex> vetVertex){
	m_vetVertex = vetVertex;
}
/**
 * Adiciona um vertice ao ConcreteMesh
 * @param Vertex *vetVertex - Ponteiro para o inicio do vetor de v�tices
 * @param unsigned int numVertex - Numero de v�tices
 */
void ConcreteMesh::setVertex(Vertex * vetVertex, unsigned int numVertex){
	for (int i = 0; i < numVertex; i++){
		m_vetVertex.push_back( vetVertex[i] );
	}
}
/**
 * Adiciona um vertice ao ConcreteMesh
 * @param Vertex vertex - Vertice adicionado
 */
void ConcreteMesh::addVertex(Vertex vertex){
	m_vetVertex.push_back( vertex );

}
/**
 * Esvazia o vetor de v�tices
 */
void ConcreteMesh::clearVertex(){
	m_vetVertex.clear();
}

/**
 * Seta o m_drawIndex
 * @param vector<unsigned int> *drawIndex - Vetor de indices das faces
 */		
void ConcreteMesh::setDrawIndex(vector<unsigned int> drawIndex){
	m_drawIndex = drawIndex;
}

/**
 * Seta o m_drawIndex
 * @param unsigned int *drawIndex - Ponteiro para o inicio do vetor de indices das faces
 * @param unsigned int numIndex - Numeto de indices das Faces
 */
void ConcreteMesh::setDrawIndex(unsigned int *drawIndex, unsigned int numIndex){
	for (int i = 0; i < numIndex; i++){
		m_drawIndex.push_back( drawIndex[i] );
	}
}

/**
 * Calcula as Informa�es de Volume do Mesh
 */
VolumeInfo *ConcreteMesh::pCalcVolumeInfo(){
	Vector3 min, max, orig;
	float radius = 0;
	min = m_vetVertex[0].getPosition();
	max = m_vetVertex[0].getPosition();
	
	for (int vertexIndex = 1; vertexIndex < m_vetVertex.size(); vertexIndex++){
		if (m_vetVertex[vertexIndex].getPX() < min.getX()) {
			min.setX( m_vetVertex[vertexIndex].getPX() );
		} else if (m_vetVertex[vertexIndex].getPX() > max.getX() ){
			max.setX( m_vetVertex[vertexIndex].getPX() );
		}
		
		if (m_vetVertex[vertexIndex].getPY() < min.getY()) {
			min.setY( m_vetVertex[vertexIndex].getPY() );
		} else if (m_vetVertex[vertexIndex].getPY() > max.getY() ){
			max.setY( m_vetVertex[vertexIndex].getPY() );
		}
		
		if (m_vetVertex[vertexIndex].getPZ() < min.getZ()) {
			min.setZ( m_vetVertex[vertexIndex].getPZ() );
		} else if (m_vetVertex[vertexIndex].getPZ() > max.getZ() ){
			max.setZ( m_vetVertex[vertexIndex].getPZ() );
		}
	}
	orig = ((max - min) / 2.0f) + min;
	radius = (orig - min).getNorma();
	
	VolumeInfo *pVolumeInfo = new VolumeInfo(min, max, orig, radius);
	return pVolumeInfo;
}

/**
 * Adiciona um indice de face ao ConcreteMesh
 * @param unsigned int drawIndex - Indices das faces
 */		
void ConcreteMesh::addDrawIndex(unsigned int drawIndex){
	m_drawIndex.push_back( drawIndex );
}
/**
 * Esvazia o vetor de �dices
 */
void ConcreteMesh::clearDrawIndex(){
	m_drawIndex.clear();
}

/**
 * Adiciona um material ao ConcreteMesh
 * @param MaterialInfo material - Novo material
 */		
void ConcreteMesh::addMaterial(MaterialInfo material){
	m_vetMaterial.push_back(material);
}
/**
 * Seta o material a ser renderisado
 * @param unsigned int index - Indice do material a ser utilizado
 */	
void ConcreteMesh::setMaterial(unsigned int index){
	m_currMaterial = index;
}

/**
 * @return Retorna o nome do ConcreteMesh
 */		
string ConcreteMesh::getName(){
	return m_name;
}

/**
 * @return Retorna o modo de renderiza�o
 */		
EnumDrawer ConcreteMesh::getDrawMode(){
	return m_drawMode;
}
/**
 * @return Retorna a orienta�o da face
 */		
EnumDrawer ConcreteMesh::getFrontFace(){
	return m_frontFace;
}
/**
 * @param unsigned int index - Indice do vertice a ser retornado
 * @return Retorna um Vertex do VertexSet
 */		
Vertex *ConcreteMesh::getVertex(unsigned int index){
	return &m_vetVertex[index];
}
/**
 * @return Retorna o numero de vertices
 */	
unsigned int ConcreteMesh::getNumVertex(){
	return m_vetVertex.size();
}

/**
 * @return Retorna o inicio dos indices das faces
 */	
unsigned int *ConcreteMesh::getDrawIndexOffSet(){
	return &m_drawIndex[0];
}
/**
 * @return Retorna o numero de vertices
 */	
unsigned int ConcreteMesh::getNumIndex(){
	return m_drawIndex.size();
}

/**
 * @param unsigned int index - Indice do material a ser retornado
 * @return Retorna um material
 */		
MaterialInfo ConcreteMesh::getMaterial(unsigned int index){
	return m_vetMaterial[index];
}

/**
 * @return Retorna o material atual
 */		
MaterialInfo ConcreteMesh::getMaterial(){
	return m_vetMaterial[m_currMaterial];
}
/**
 * @return Retorna o numero de materiais no ConcreteMesh
 */	
unsigned int ConcreteMesh::getNumMaterial(){
	return m_vetMaterial.size();
}


/**
 * @return Retorna se o mesh possue blend
 */
bool ConcreteMesh::getBlend(){
	return false;
}

Mesh *ConcreteMesh::getConcreteMesh(){
	return this;
}

/**
 * @param ConcreteMesh *pMesh - ConcreteMesh com o qual ser�feita a interpola�o
 * @param float interpolation - Fra�o de interpola�o entre os ConcreteMeshs
 * @return Retorna um novo ConcreteMesh interpolado
 */		
Mesh *ConcreteMesh::interpolate(Mesh *pMesh, float interpolation){
	ConcreteMesh *pConcreteMesh = (ConcreteMesh *)pMesh->getConcreteMesh();
	ConcreteMesh *newMesh = new ConcreteMesh(this);
	
	for (unsigned int i = 0; i < m_vetVertex.size(); i++){
		newMesh->m_vetVertex[i] += ( pConcreteMesh->m_vetVertex[i] - m_vetVertex[i] ) * interpolation;
	}
	
	return newMesh;
}

/**
 * Renderiza o mesh
 */	
void ConcreteMesh::draw(){
	this->set(false);
	this->render();
	this->unset();
}

void ConcreteMesh::set(bool setup){
	Drawer *drawer = Drawer::getInstance();
	if (m_cullFace) {
		drawer->frontFace( m_frontFace );
	} else {
		drawer->disable(InGE_CULL_FACE);
	}

	if (!setup){
		drawer->activeTextureARB(InGE_TEXTURE0_ARB);
		drawer->enable(InGE_TEXTURE_2D);
		drawer->bindTexture(InGE_TEXTURE_2D, m_vetMaterial[m_currMaterial].getId() );
		
		drawer->clientActiveTextureARB(InGE_TEXTURE0_ARB);
		drawer->enableClientState(InGE_TEXTURE_COORD_ARRAY);
		drawer->texCoordPointer(2, InGE_FLOAT, sizeof(Vertex), m_vetVertex[0].getTextureOffset());
	}
}

void ConcreteMesh::unset(){
	Drawer *drawer = Drawer::getInstance();
	if (!m_cullFace)
		drawer->enable(InGE_CULL_FACE);
}

void ConcreteMesh::render(){
	Drawer *drawer = Drawer::getInstance();

	drawer->vertexPointer(3, InGE_FLOAT, sizeof(Vertex), m_vetVertex[0].getPositionOffset());
	drawer->normalPointer(InGE_FLOAT, sizeof(Vertex), m_vetVertex[0].getNormalOffset());

	drawer->drawElements(m_drawMode, m_drawIndex.size(), InGE_UNSIGNED_INT, &m_drawIndex[0]);
	
//	renderNormals(); TODO:Testar isso
}

void ConcreteMesh::executeCommand(ExecuteCommandEnum e, string param){
}

void ConcreteMesh::renderNormals(){
	Drawer *drawer = Drawer::getInstance();
	drawer->begin(InGE_LINE);
	
	Vertex *pVertex;
	Vector3 pos1, pos2;
	for (int i=0; i < m_vetVertex.size(); i++){
		pVertex = &m_vetVertex[i];
		
		pos1 = pVertex->getPosition();
		pos2 = pVertex->getNormal();
		pos2 += pos1;
		drawer->vertex( pos1 );
		drawer->vertex( pos2 );

	}
	
	
	drawer->end();
}
