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

#ifndef PRIMITIVEFACTORY_H
#define PRIMITIVEFACTORY_H
#include <string>
#include <vector>
#include "../../Base/MeshDecorator/ConcreteMesh.h"
#include "../../Base/MeshDecorator/DecoratorList.h"
#include "PrimitiveEnum.h"
#include "Box.h"
#include "Plane.h"
//#include "Sphere.h"



namespace InGE{

	/**
	 * Classe PrimitivesFactory 
	 * �um FlyweightFactory/Singleton respons�vel por gerenciar Modelos Primitivos.
	 * Carrega modelos primitivos de acordo com nomes assegurando que nenhum modelo seja duplicada na mem�ia.
	 * @author Humberto Luiz Campos Bandeira
	 */
	class PrimitiveFactory{
		private:
		  	static PrimitiveFactory *m_pPrimitiveFactory;
			std::vector<IModel *> m_loadedPrimitives;
			
			PrimitiveFactory();
			int findPrimitiveFactory(std::string name);
 
 			Box *loadBox(std::string name, float scale, std::string filenameTex);
 			Plane *loadPlane(std::string name, float scale, std::string filenameTex);
 				
		public:

			static	PrimitiveFactory *getInstance();
			virtual	~PrimitiveFactory();
			
			IModel 	*loadPrimitive(std::string name, int shape, float scale, std::string filenameTex);

			IModel	*getPrimitive(int index);
			IModel	*getPrimitive(std::string name);
			void		rmPrimitive(int index);
			void		rmPrimitive(std::string name);
	};
	
};
#endif // PRIMITIVEFACTORY_H
