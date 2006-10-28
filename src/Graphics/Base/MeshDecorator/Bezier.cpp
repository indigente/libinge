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

#include "Bezier.h"
using namespace InGE;
using namespace std;

/**
 * @param Mesh *pMesh - Mesh que será decorado como Bezier
 * @param int size[2] - Tamanho da malha UxV
 */
Bezier::Bezier(Mesh *pMesh, int size[2]) : MeshDecorator(pMesh){
	m_size[0] = size[0];
	m_size[1] = size[1];
	m_level = 0;
	
	for (int i = 0; i < this->getNumVertex(); i++ ){
		m_vControlVertex.push_back( Vertex(*this->getVertex(i) ) );
	}
	for (int i = 0; i < this->getNumIndex(); i++ ){
		m_vControlDrawIndex.push_back( (this->getDrawIndexOffSet()[i]) );
	}
	
	this->genBezier(8);
}

/**
 * @param Mesh *pMesh - Mesh que será decorado como Bezier
 * @param int size[2] - Tamanho da malha UxV
 * @param unsigned int pTexture - Texture para criar Lightmap
 * @param Vector2 *LightmapCoord - Coordenadas do Lightmap
 */
Bezier::Bezier(Mesh *pMesh, int size[2], unsigned int pTexture, vector<Vector2 > &vetLightmapCoord) : MeshDecorator(pMesh){
	m_size[0] = size[0];
	m_size[1] = size[1];
	m_level = 0;
	
	for (int i = 0; i < this->getNumVertex(); i++ ){
		m_vControlVertex.push_back( Vertex(*this->getVertex(i) ) );
	}
	m_vLightmapCoord = vetLightmapCoord;
	for (int i = 0; i < this->getNumIndex(); i++ ){
		m_vControlDrawIndex.push_back( (this->getDrawIndexOffSet()[i]) );
	}
	
	this->genBezier(8);
	
	m_component = new Lightmap( m_component, pTexture, m_vLightmapCoord);
}

Bezier::~Bezier(){
	delete m_component;
}

/**
 * @param Mesh *pMesh - Mesh com o qual será feita a interpolação
 * @param float interpolation - Fração de interpolação entre os MeshDecorators
 * @return Retorna um novo mesh interpolado
 */
Mesh *Bezier::interpolate(Mesh *pMesh, float interpolation){
	return new Bezier( m_component->interpolate(pMesh, interpolation), m_size );
}

void Bezier::genBezier(int level){
	if (level == m_level)
		return;

	m_level = level;
	
	unsigned int numPatchesU = (m_size[0] - 1) / 2;
	unsigned int numPatchesV = (m_size[1] - 1) / 2;
	
	SBezier *bezier;
	for (unsigned int y = 0; y < numPatchesV; ++y) {
		for (unsigned int x = 0; x < numPatchesU; ++x) {
			bezier = new SBezier;
			for (unsigned int row = 0; row < 3; ++row) {
				for (unsigned int col = 0; col < 3; ++col){
					bezier->controls[row * 3 + col] = m_vControlVertex[2 * m_size[0] * y + 2 * x + m_size[0] * row + col];
					if (m_vLightmapCoord.size() != 0){
						bezier->lightmapControls[row * 3 + col] = m_vLightmapCoord[2 * m_size[0] * y + 2 * x + m_size[0] * row + col];
					}
				}
			}
			m_vBezier.push_back(bezier);
			tesselate(m_vBezier.size() - 1);
		}
	}
	if (m_vLightmapCoord.size() != 0){
		m_vLightmapCoord.clear();
		for (unsigned int i = 0; i < m_vBezier.size(); ++i) {
			for (unsigned int j = 0; j < m_vBezier[i]->lightmapCoord.size(); ++j){
				m_vLightmapCoord.push_back(m_vBezier[i]->lightmapCoord[j]);
			}
		}
	}
		
	m_component->clearVertex();
	for (unsigned int i = 0; i < m_vBezier.size(); ++i) {
		for (unsigned int j = 0; j < m_vBezier[i]->vertices.size(); ++j){
			this->addVertex( (m_vBezier[i]->vertices[j]) );
		}
	}
	
	m_component->clearDrawIndex();
	unsigned int numPatches = numPatchesU * numPatchesV;
	unsigned int pointsPerPatch = (m_level + 1) * (m_level + 1);
	for (unsigned int counter = 0; counter < numPatches * pointsPerPatch; counter += pointsPerPatch) {
		for (unsigned int x = 0; x < m_level; ++x) {
			for (unsigned int y = 1; y <= m_level; ++y) {
				this->addDrawIndex(  x + y * (m_level + 1) + counter);
				this->addDrawIndex(  x + (y - 1) * (m_level + 1) + counter );
				this->addDrawIndex( (x + 1) + (y - 1) * (m_level + 1) + counter );
				this->addDrawIndex(  x + y * (m_level + 1) + counter );
				this->addDrawIndex( (x + 1) + (y - 1) * (m_level + 1) + counter );
				this->addDrawIndex( (x + 1) + y * (m_level + 1) + counter );
			}
		}
	}
}

void Bezier::tesselate(unsigned int bezierIndex){
	SBezier *bez = m_vBezier[bezierIndex];
	
	vector<Vertex> vetVertex;
	float recTess = 1 / (float)m_level;
	
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int v = 0; v <= m_level; ++v) {
			float a = v * recTess;
			float b = 1 - a;
			Vertex vert1, vert2, vert3;
			
			vert1 = bez->controls[0 + i]*(b*b);
			vert2 = bez->controls[3 + i]*(2*b*a);
			vert3 = bez->controls[6 + i]*(a*a);
			vert1 = vert1 + vert2 + vert3;

			vetVertex.push_back(vert1);
		}
	}
	for (unsigned int i = 0; i <= m_level; ++i) {
		for (unsigned int u = 0; u <= m_level; ++u) {
			float a = u * recTess;
			float b = 1 - a;
			Vertex vert1, vert2, vert3;
			
			vert1 = vetVertex[i]*(b*b);
			vert2 = vetVertex[i + (m_level + 1)]*(2*b*a);
			vert3 = vetVertex[i + 2 * (m_level + 1)]*(a*a);
			vert1 = vert1 + vert2 + vert3;

			bez->vertices.push_back(vert1);
		}
	}

	if(m_vLightmapCoord.size() != 0){
		vector<Vector2> vetLightmapCoord;
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int v = 0; v <= m_level; ++v) {
				float a = v * recTess;
				float b = 1 - a;
				Vector2 vert1, vert2, vert3;
				
				vert1 = bez->lightmapControls[0 + i]*(b*b);
				vert2 = bez->lightmapControls[3 + i]*(2*b*a);
				vert3 = bez->lightmapControls[6 + i]*(a*a);
				vert1 = vert1 + vert2 + vert3;
	
				vetLightmapCoord.push_back(vert1);
			}
		}
		for (unsigned int i = 0; i <= m_level; ++i) {
			for (unsigned int u = 0; u <= m_level; ++u) {
				float a = u * recTess;
				float b = 1 - a;
				Vector2 vert1, vert2, vert3;
				
				vert1 = vetLightmapCoord[i]*(b*b);
				vert2 = vetLightmapCoord[i + (m_level + 1)]*(2*b*a);
				vert3 = vetLightmapCoord[i + 2 * (m_level + 1)]*(a*a);
				vert1 = vert1 + vert2 + vert3;
	
				bez->lightmapCoord.push_back(vert1);
			}
		}
	}
}

void Bezier::setLevel(unsigned int level){
	m_level = level;
	for (unsigned int bezierIndex = 0; bezierIndex < m_vBezier.size(); bezierIndex++){
		this->tesselate(bezierIndex);
	}
}


