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

#ifndef BEZIER_H_
#define BEZIER_H_
#include "MeshDecorator.h"
#include "Lightmap.h"
#include <vector>

#include <iostream>

namespace InGE{
	using std::vector;
	
	class Bezier : public InGE::MeshDecorator{
		private:
			typedef struct SBezier {
				Vertex controls[9];
				Vector2 lightmapControls[9];
				
				vector<Vertex> vertices;
				vector<Vector2> lightmapCoord;
				vector<unsigned int> indices;
				
				vector<int> trisPerRow;
				vector<unsigned int *> rowIndices;
			} SBezier;
		
			int			m_size[2];
			
			vector<SBezier *>	m_vBezier;
			
			vector<Vertex >		m_vControlVertex;
			vector<Vector2 >	m_vLightmapCoord;
			vector<unsigned int>	m_vControlDrawIndex;
			
			unsigned int		m_level;
			
			void genBezier(int level);
			void tesselate(unsigned int bezierIndex);
			
		public:
			Bezier(Mesh *pMesh, int *size);
			Bezier(Mesh *pMesh, int *size, unsigned int pTexture, vector<Vector2 > &vetLightmapCoord);
			virtual ~Bezier();
			
			Mesh *interpolate(Mesh *pMesh, float interpolation);
			
			void setLevel(unsigned int level);
			
	};
};

#endif /*BEZIER_H_*/
