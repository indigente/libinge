/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright ï¿½ 2004-2005 Indigente

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

#ifndef KFMODEL_H
#define KFMODEL_H
#include <string>
#include <vector>
#include "../../Base/VolumeInfo.h"

namespace InGE{
	using std::string;
	using std::vector;
	/**
	 * Classe Abistrata KFModel 
	 * Flyweight utilisado para a abistração entre modelos carregados.
	 * @author Humberto Luiz Campos Bandeira
	 */
	class IKFModel{//FIXME: IKFMoldel deveria herdar de IModel, para isso as informações sobre amimação e frame deveriam estar na Entidade.
		public:

			IKFModel() {}
			virtual ~IKFModel() {}
			virtual string getName() = 0;
			virtual vector<VolumeInfo *> getVetVolumeInfo() = 0;
			virtual VolumeInfo *drawModel(int currentAnimIndex, int currentKeyFrameIndex, int currentMaterialIndex, float interpolationToNextFrame) = 0;
			};
	
};
#endif // KFMODEL_H
