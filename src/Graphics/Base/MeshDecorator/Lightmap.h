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

#ifndef LIGHTMAP_H_
#define LIGHTMAP_H_
#include "MeshDecorator.h"

namespace InGE{
	class Lightmap : public InGE::MeshDecorator{
		private:
			unsigned int		m_pTexture;
			vector<Vector2 >	m_vetLightmapCoord;
			
		public:
			Lightmap(Mesh *pMesh, unsigned int pTexture, vector<Vector2 > &vetLightmapCoord);
			virtual ~Lightmap();
			
			Mesh *interpolate(Mesh *pMesh, float interpolation);
			
			void set(bool setup);
			void unset();
	};

};

#endif /*LIGHTMAP_H_*/
