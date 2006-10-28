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
#ifndef IMODEL_H
#define IMODEL_H
#include "../Base/VolumeInfo.h"
#include <string>
#include <vector>
#include <map>

namespace InGE{
	using std::string;
	using std::map;
	using std::vector;

	
	class IModel{
		public:
		
			IModel() {}
			virtual ~IModel() {}
			virtual string getName() = 0;
			virtual int getType() = 0;
						
			virtual bool attachModel(IModel *pModel) = 0;
			virtual int getNumOfAttach() = 0;
			
			virtual void addEntityID(string m_entityID) = 0;
			virtual void removeEntityID(string m_entityID) = 0;
			virtual void drawModel(string entityID) = 0;
			
			virtual vector<VolumeInfo *> getVetVolumeInfo() = 0;

			virtual unsigned int	getNumAnimation() = 0;
			virtual string			getAnimation(string entityID) = 0;
			virtual void			setAnimation(string entityID, string currAnim, string nextAnim) = 0;
			
			virtual bool getBlend() = 0;
			
			virtual void setDraw(string entityID,bool draw) = 0;
			virtual void setDraw(string entityID,bool draw, string partToDraw) = 0;
	};
};

#endif // IMODEL_H
