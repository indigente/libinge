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

#ifndef ALPHABLEND_H_
#define ALPHABLEND_H_
#include "MeshDecorator.h"

namespace InGE{

	class AlphaBlend : public InGE::MeshDecorator{
	public:
		AlphaBlend(Mesh *pMesh);
		virtual ~AlphaBlend();
		
		bool getBlend();
		
		Mesh *interpolate(Mesh *pMesh, float interpolation);
		
		void set(bool setup);
		void unset();
	};
};
#endif /*ALPHABLEND_H_*/
