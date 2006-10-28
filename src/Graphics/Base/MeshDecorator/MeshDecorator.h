/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2006 Indigente


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

#ifndef MESHDECORATOR_H_
#define MESHDECORATOR_H_
#include "../Mesh.h"
#include "ConcreteMesh.h"
#include <vector>
#include <string>

namespace InGE{
using std::string;
using std::vector;

class MeshDecorator : public InGE::Mesh {
	protected:
		Mesh *m_component;
		
	public:
		MeshDecorator(Mesh *pMesh);
		virtual ~MeshDecorator();
		//Metodos Set	
		
		void setName(string name);
		void setDrawMode(EnumDrawer mode);
		void setFrontFace(EnumDrawer frontFace);

		void setVertex(vector<Vertex> vetVertex);
		void setVertex(Vertex *vetVertex, unsigned int numVertex);
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
		
		virtual Mesh *interpolate(Mesh *pMesh, float interpolation) = 0;
				
		void draw();
		void set(bool setup);
		void unset();
		void render();

		void executeCommand(ExecuteCommandEnum e, string param);
};

};

#endif /*MESHDECORATOR_H_*/
