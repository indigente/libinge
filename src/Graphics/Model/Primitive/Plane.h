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

#ifndef PLANE_H
#define PLANE_H
#include<string>
#include "../../Base/Mesh.h"
#include "../IModel.h"

namespace InGE{
	using std::string;
	using std::vector;

	/**
	 * Classe Plane 
	 * Concrete Flyweight - cont� dados de um cubo.
	 * @author Humberto Luiz Campos Bandeira
	 */
	class Plane : public InGE::IModel{
		private:
			string	m_name;
			Mesh	*m_pMesh;
			VolumeInfo 	*m_pVolumeInfo;
		
		public:
			Plane(Mesh *pMesh);
			virtual ~Plane();
			void setName(string name);
			string getName();
			int getType() {return 0;};
						
			bool attachModel(IModel *pModel){return false;}
			int getNumOfAttach() {return 0;}
			
			void addEntityID(string m_entityID){}
			void removeEntityID(string m_entityID){}
			void drawModel(string entityID);
			
			vector<VolumeInfo *> getVetVolumeInfo();

			unsigned int	getNumAnimation();
			string			getAnimation(string entityID){return 0;};
			void				setAnimation(string entityID, string currAnim, string nextAnim){}
			
			bool getBlend();

			void addMaterial(string filenameTex);
			
			void setDraw(string entityID,bool draw){}
			void setDraw(string entityID,bool draw, string partToDraw){}

	};

}
#endif // PLANE_H
