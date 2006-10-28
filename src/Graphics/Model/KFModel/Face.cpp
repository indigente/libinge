/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#include "Face.h"

using namespace InGE;
using std::cerr;
using std::endl;

Face::Face(){
}

Face::~Face(){
}

void Face::calculatePlane(Vertex *v[3]){
//	plane->PlaneEq.a = v[1].y*(v[2].z-v[3].z) + v[2].y*(v[3].z-v[1].z) + v[3].y*(v[1].z-v[2].z);
	m_planeEquation.setX(v[0]->getPY()*(v[1]->getPZ()-v[2]->getPZ()) + v[1]->getPY()*(v[2]->getPZ()-v[0]->getPZ()) + v[2]->getPY()*(v[0]->getPZ()-v[1]->getPZ()));
//	plane->PlaneEq.b = v[1].z*(v[2].x-v[3].x) + v[2].z*(v[3].x-v[1].x) + v[3].z*(v[1].x-v[2].x);
	m_planeEquation.setY(v[0]->getPZ()*(v[1]->getPX()-v[2]->getPX()) + v[1]->getPZ()*(v[2]->getPX()-v[0]->getPX()) + v[2]->getPZ()*(v[0]->getPX()-v[1]->getPX()));
//	plane->PlaneEq.c = v[1].x*(v[2].y-v[3].y) + v[2].x*(v[3].y-v[1].y) + v[3].x*(v[1].y-v[2].y);
	m_planeEquation.setZ(v[0]->getPX()*(v[1]->getPY()-v[2]->getPY()) + v[1]->getPX()*(v[2]->getPY()-v[0]->getPY()) + v[2]->getPX()*(v[0]->getPY()-v[1]->getPY()));
//	plane->PlaneEq.d =-( v[1].x*(v[2].y*v[3].z - v[3].y*v[2].z) +
//					  	 v[2].x*(v[3].y*v[1].z - v[1].y*v[3].z) +
//	 					 v[3].x*(v[1].y*v[2].z - v[2].y*v[1].z) );
	m_planeEquation.setW(-(v[0]->getPX()*(v[1]->getPY()*v[2]->getPZ() - v[2]->getPY()*v[1]->getPZ()) +
						  v[1]->getPX()*(v[2]->getPY()*v[0]->getPZ() - v[1]->getPY()*v[2]->getPZ()) +
						  v[2]->getPX()*(v[0]->getPY()*v[1]->getPZ() - v[0]->getPY()*v[0]->getPZ())));
}
		
		
void Face::setConnectivity(Face *face, unsigned int currentIndex, unsigned int adjIndex){
	int currentMatchVertex[3], adjMatchVertex[3];
	int matchVertex = 0, matchIndex = 0;
	unsigned int currentVertexIndex, adjVertexIndex;
	for (currentVertexIndex = 0; currentVertexIndex < 3; currentVertexIndex++){
		if (m_neighbourFaceIndex[currentVertexIndex] == (-1)){
			for (adjVertexIndex = 0; adjVertexIndex < 3; adjVertexIndex++){
				if(m_vertexIndex[currentVertexIndex] == face->m_vertexIndex[adjVertexIndex]){
					currentMatchVertex[matchIndex] = currentVertexIndex;
					adjMatchVertex[matchIndex] = adjVertexIndex;
					matchIndex++;
				}
			}
		}
	}
	if (matchVertex == 2){
		this->m_neighbourFaceIndex[currentMatchVertex[0]] = adjIndex;
		face->m_neighbourFaceIndex[adjMatchVertex[0]] = currentIndex;
	}
}

void Face::setVertex(int vertex[3]){
	m_vertexIndex[0] = vertex[0];
	m_vertexIndex[1] = vertex[1];
	m_vertexIndex[2] = vertex[2];
}

bool Face::checkVisible(Vector4 *lightPos){
	float side =	m_planeEquation.getX() * lightPos->getX() +
					m_planeEquation.getY() * lightPos->getY() +
					m_planeEquation.getZ() * lightPos->getZ() +
					m_planeEquation.getW();
	if (side > 0){
		m_visible = 1;
	}else{
		 m_visible = 0;
	}
	return m_visible;
}

bool Face::getVisible(){
	return m_visible;
}

unsigned int Face::getVertexIndex(int index){
	return m_vertexIndex[index];
}

Vector4 Face::getPlane(){
	return m_planeEquation;
}

unsigned int Face::getNeighbourIndex(int index){
	return m_neighbourFaceIndex[index];
}
