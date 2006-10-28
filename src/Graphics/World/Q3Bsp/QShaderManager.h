/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente


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
#ifndef QSHADERMANAGER_H
#define QSHADERMANAGER_H
#include "QShader.h"
#include <string>
#include <map>
#include <cstdio>

namespace InGE{

	using std::string;
	using std::map;
	
	class QShaderManager{
		private:
			static QShaderManager	*m_shaderManager;
			map<string, QShader *>	m_shaders;

			char m_currentLine[1024];
			
			QShaderManager();

			bool isComment(char *str);
			bool isCull(char *str);
			bool isBlend(char *str);
			bool isMap(char *str);
			bool isClampMap(char *str);
			bool isAnimMap(char *str);
			bool isOpenK(char *str);
			bool isCloseK(char *str);
			
			void lower(char *str);
			
			bool getNewLine(FILE *fp);
			
			void setCullParameter(char *str, QShader *shader);
			void setBlendParameter(char *str, QShader *shader);
			void setMapParameter(char *str, QShader *shader);
			void setClampMapParameter(char *str, QShader *shader);
			void setAnimMapParameter(char *str, QShader *shader);
		
			
		public:
			static QShaderManager	*getInstance();
			
			bool loadShaders(string filename);
			bool parserShaders(string filename);
			void addShader(QShader *shader);
			QShader *getShader(string name);
			~QShaderManager();
	};
};

#endif // QSHADERMANAGER_H
