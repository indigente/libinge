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

#ifndef MD3MODEL_H
#define MD3MODEL_H
#include<string>
#include<vector>
#include <iostream>
#include "../../../Base/MaterialInfo.h"
#include "../../../Base/TextureArray.h" 
#include "../../../Render/Drawer.h"
#include "../../../../Math/Quaternion.h"
#include "../../IModel.h"
#include "../KeyFrame.h"
#include "../CurrentAnimInfo.h"

namespace InGE{
	using std::string;
	using std::vector;
	
	/**
	 * Struct AnimInfo
	 * Contem dados sobre o conjunto das anima�es.
	 * @author Humberto Luiz Campos Bandeira
	 */
	typedef struct sAnimInfo{
		string	name;
		string bodyPart;
		int firstFrame;
		int numFrame;
		int loopFrames;
		int fps;
		bool operator<=(const sAnimInfo *animInfo) const;
	}sAnimInfo;
	
	/**
	 * Classe Md3Model 
	 * Concrete Flyweight - contem dados de um arquivo MD3 utilizado em Quake3.
	 * @author Humberto Luiz Campos Bandeira
	 */
	class Md3Model : public InGE::IModel{
		private:
			string 	m_name;
			string	m_bodyPart;
			int	m_type;
			
			map<string, Md3Model *>				m_mapModel;
			vector<MaterialInfo *>				m_vetMaterial;
			vector<VolumeInfo *>					m_vetVolumeInfo;

			map<string, vector<KeyFrame *> >	m_mapAnim;
			map<string, CurrentAnimInfo *>	m_mapEntityAnim;

			VolumeInfo *drawFrame(CurrentAnimInfo *currAnim);

			void sphereInterpolation(int tagIndex, CurrentAnimInfo *currAnim);
			void setBodyPart(string bodyname);

		public:
			Md3Model(string bodyPart, map<string, vector<KeyFrame *> > mapAnim);
			virtual ~Md3Model();
			void setName(string name);
			string getName();
			int getType();
						
			bool attachModel(IModel *pModel);
			int getNumOfAttach();
			
			void addEntityID(string m_entityID);
			void removeEntityID(string m_entityID);
			void drawModel(string entityID);
			
			vector<VolumeInfo *> getVetVolumeInfo();

			unsigned int	getNumAnimation();
			string			getAnimation(string entityID);
// 			void				setAnimation(string entityID, string currAnim);
			void				setAnimation(string entityID, string currAnim, string nextAnim);
			
			bool getBlend();
			
			// Especializações
			string 			getBodyPart();
			unsigned int	getNumFrame(string animIndex);
			KeyFrame 		*getKeyFrame(string animIndex, int keyFrameIndex);
			
			void setDraw(string entityID,bool draw);
			void setDraw(string entityID,bool draw, string partToDraw);

};

};
#endif // MD3MODEL_H
