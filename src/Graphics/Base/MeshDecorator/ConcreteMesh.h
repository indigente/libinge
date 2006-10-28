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

#ifndef CONCRETEMESH_H_
#define CONCRETEMESH_H_
#include "../Mesh.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

namespace InGE{
using std::string;
using std::vector;

class ConcreteMesh : public InGE::Mesh {
	private:
		string			m_name;	// Nome do Mesh
		EnumDrawer		m_drawMode;
		
		bool			m_cullFace;
		EnumDrawer		m_frontFace;
		
		vector<Vertex>		m_vetVertex;
		vector<unsigned int>	m_drawIndex;	// Indices das faces, numero de faces = m_numIndex / 3
		vector<MaterialInfo >	m_vetMaterial;	// Informa�es das texturas

		VolumeInfo		*m_pVolumeInfo;
		
		unsigned int m_currMaterial;
		void renderNormals();
		
	public:
		ConcreteMesh();
		ConcreteMesh(ConcreteMesh *pMesh);
		virtual ~ConcreteMesh();
		//Metodos Set	
		
		void setName(string name);
		void setDrawMode(EnumDrawer mode);
		void setFrontFace(EnumDrawer frontFace);

		void setVertex(vector<Vertex> vetVertex);
		void setVertex(Vertex * vetVertex, unsigned int numVertex);
		void addVertex(Vertex vertex);
		void clearVertex();
		
		void setDrawIndex(vector<unsigned int> drawIndex);
		void setDrawIndex(unsigned int *drawIndex, unsigned int numIndex);
		void addDrawIndex(unsigned int drawIndex);
		void clearDrawIndex();
		
		void addMaterial(MaterialInfo material);
		void setMaterial(unsigned int index);

		VolumeInfo *pCalcVolumeInfo();
		
		//Metodos Get	
		string getName();
		EnumDrawer getDrawMode();
		EnumDrawer getFrontFace();

		Vertex *getVertex(unsigned int index);
		unsigned int getNumVertex();
		
		unsigned int *getDrawIndexOffSet();
		unsigned int getNumIndex();
		
		MaterialInfo getMaterial(unsigned int index);
		MaterialInfo getMaterial();
		unsigned int getNumMaterial();
		
		Mesh *getConcreteMesh();
				
		//Metodos de renderiza�o
		bool getBlend();
		
		Mesh *interpolate(Mesh *pMesh, float interpolation);
		
		void draw();
		void set(bool setup);
		void unset();
		void render();

		void executeCommand(ExecuteCommandEnum e, string param);
};

};

#endif /*CONCRETEMESH_H_*/
