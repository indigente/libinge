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

#ifndef KFMODELFACTORY_H
#define KFMODELFACTORY_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

#include "../IModel.h"
#include "Md2/md2Format.h"
#include "Md2/Md2model.h"
#include "Md3/md3Format.h"
#include "Md3/Md3Model.h"


namespace InGE{
	using std::string;
	using std::vector;
	
	/**
	 * Struct SkinInfo
	 * Contem dados sobre o conjunto de texturas de um modelo.
	 * @author Humberto Luiz Campos Bandeira
	 */
	struct sSkinInfo{
		char meshName[30], filename[50];
	};
	
	
	/**
	 * Classe KFModelFactory 
	 * �um FlyweightFactory/Singleton respons�el por gerenciar Modelos baseados em Quadros Chaves.
	 * Carrega modelos de md2 e md3 assegurando que nenhum modelo seja duplicada na mem�ia.
	 * @author Humberto Luiz Campos Bandeira
	 */
	class KFModelFactory{
		private:
		  	static KFModelFactory *m_pKFModelFactory;
			vector<IModel *> m_loadedModels;
			
			KFModelFactory();
			
			void buildNormTable();
			float m_normTable[256][256][3]; //FIXME: static?
			bool m_isLoading;
			
			string m_directoryName;
			vector<sAnimInfo > m_vetAnimInfo;
			int					findKFModel(string filename);
			/////////    MD2  ///////////
			Md2Model*	loadMd2Model(string md2File);
			
			/////////   MD3   /////////
			Md3Model 	*loadMd3Model(string md3File, string bodyParty);
			Md3Model		*createMd3(FILE *fp, string bodyPart);
			map<string, vector<KeyFrame *> > md3Setup(sMd3Header header, sMesh *psMesh, sBoundVolume *psBoundVolume, sTag *psTag, unsigned int **drawIndex, string bodyPart);			
		
			bool	loadMd3AnimationFile(const string& filename);


		
		public:

			static		KFModelFactory *getInstance();
			virtual		~KFModelFactory();
			
// 		IKFModel		*loadKFModel(string filename, const vector<string> &vetFileTex);
			IModel		*loadMd3(string directoryName);

			IModel		*getModel(int index);
			IModel		*getModel(string filename);
			
	};
	
};
#endif // KFMODELFACTORY_H
