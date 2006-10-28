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

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "MaterialInfo.h"
#include "TextureArray.h" 
#include "Vertex.h"
#include "VolumeInfo.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector3.h"
#include "../Render/Drawer.h"

	
namespace InGE{
	using std::string;
	using std::vector;
	
	enum ExecuteCommandEnum {
		InGE_EXCMD_PLAY,
		InGE_EXCMD_STOP,
		InGE_EXCMD_SKIP,
		InGE_EXCMD_LOOP,
		InGE_EXCMD_REWIND
	};
	
	/** 
	 * Classe Mesh 
	 * Possui a estrutura b�ica para um objeto 3d.
	 * As faces s� armazenadas, ligando cada pol�ono a
	 * v�ices e coordenadas de textura
	 */
	class Mesh{
	  public:
	
		Mesh() {}
		virtual ~Mesh() {}

		//Metodos Set	
		
		virtual void setName(string name) = 0;
		virtual void setDrawMode(EnumDrawer mode) = 0;
		virtual void setFrontFace(EnumDrawer frontFace) = 0;

		virtual void setVertex(vector<Vertex> vetVertex) = 0;
		virtual void setVertex(Vertex * vetVertex, unsigned int numVertex) = 0;
		virtual void addVertex(Vertex vertex) = 0;
		virtual void clearVertex() = 0;
		
		virtual void setDrawIndex(vector<unsigned int> drawIndex) = 0;
		virtual void setDrawIndex(unsigned int *drawIndex, unsigned int numIndex) = 0;
		virtual void addDrawIndex(unsigned int drawIndex) = 0;
		virtual void clearDrawIndex() = 0;
		
		virtual void addMaterial(MaterialInfo material) = 0;
		virtual void setMaterial(unsigned int index) = 0;
		
		virtual VolumeInfo *pCalcVolumeInfo() = 0;
		
		//Metodos Get	
		virtual string getName() = 0;
		virtual EnumDrawer getDrawMode() = 0;
		virtual EnumDrawer getFrontFace() = 0;

		virtual Vertex *getVertex(unsigned int index) = 0;
		virtual unsigned int getNumVertex() = 0;
		
		virtual unsigned int *getDrawIndexOffSet() = 0;
		virtual unsigned int getNumIndex() = 0;
		
		virtual MaterialInfo getMaterial(unsigned int index) = 0;
		virtual MaterialInfo getMaterial() = 0;
		virtual unsigned int getNumMaterial() = 0;
		
		virtual Mesh *getConcreteMesh() = 0;
		
		//Metodos de renderiza�o
		virtual bool getBlend() = 0;

		virtual Mesh *interpolate(Mesh *pMesh, float interpolation) = 0;

		
		
		virtual void draw() = 0;
		virtual void set(bool setup) = 0;
		virtual void unset() = 0;
		virtual void render() = 0;

		virtual void executeCommand(ExecuteCommandEnum e, string param)=0;
	};

};
#endif // MESH_H
