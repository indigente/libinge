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
#include "QEntityParser.h"
#include <cstdio>
#include <cstring>
using namespace InGE;


QEntityParser::QEntityParser(char *entities, unsigned int len){
	m_len = len;
	m_position = 0;
	m_entities = entities;	
}

QEntity *QEntityParser::nextEntity(){
	char property[32];
	char parameter[96];
	QEntity *pEntity = NULL;
	
	string classname = "";
	string target = "";
	Vector3 origin(0.0f,0.0f,0.0f);
	Vector3 color(0.0f,0.0f,0.0f);
	float angle = 0.0f;
	float radius= 0.0f;
	int light = 0;
	float scale = 1;
	string dirName = "";
	
	
	// Procura um classname suportado
	while(classname == ""){ 	
		sscanf(&m_entities[m_position], " %127[^\n]", m_line); 
		m_position+=strlen(m_line) +1;
	
		// Condicao de contorno
		if(strncmp(m_line, "{", 1)) return NULL;
	
		// Le um entity
		while(sscanf(&m_entities[m_position], " %127[^\n]", m_line) && strncmp(m_line, "}", 1)){
			m_position += strlen(m_line) +1;	
			if(m_position >= m_len-1) return NULL;
			
			// Leitura de propriedade e parametros
			sscanf(m_line, " \"%32[^\"]\" \"%96[^\"]\" ", property, parameter );
	
			//Propriedade classname
			if(!strncmp(property, "classname", 9) ){
				//"classname" "info..."
				if(!strncmp(parameter, "info", 4)){
					classname = parameter;
					pEntity = new QEntityInfo();
					pEntity->classname = classname;
				}
				//"classname" "light..."
				else if(!strncmp(parameter, "light", 5)){
					classname = parameter;
					pEntity = new QEntityLight();
					pEntity->classname = classname;
				}
				//"classname" "unsupported"
				else{
					angle = radius = 0.0f;
					classname = target = "";
					color = origin = Vector3(0.0f,0.0f,0.0f);
					light = 0;
				}
			}
			// Propriedade "origin" "x y z"
			else if(!strncmp(property, "origin", 6)){
				sscanf(parameter, "%f %f %f", &origin[0],&origin[1],&origin[2]);
			}
			// Propriedade "target" "string"
			else if(!strncmp(property, "target", 6)){
				target = parameter;
			}
			// Propriedade "angle" "X"
			else if(!strncmp(property, "angle", 5)){
				sscanf(parameter, "%f", &angle);
			}
			// Propriedade "_color"  "X Y Z"
			else if(!strncmp(property, "_color", 6)){
				sscanf(parameter, "%f %f %f", &color[0],&color[1],&color[2]);
			}
			// Propriedade "radius"  "X"
			else if(!strncmp(property, "radius", 6)){
				sscanf(parameter, "%f", &radius);
			}
			else if(!strncmp(property, "light", 5)){
				sscanf(parameter, "%d", &light);
			}
			// "Unsupported" "unsupported"
			else if(!strncmp(property, "scale", 5)){
				sscanf(parameter, "%f", &scale);
				
			}else if(!strncmp(property, "dirName", 6)){
				dirName = parameter;
				
			}else {
			}
		}
		m_position+=2;
	}	
	
	
	
	if(pEntity->type == InGE_QENTITY_INFO){
		QEntityInfo *pEntityInfo = (QEntityInfo *) pEntity;
		pEntityInfo->origin = origin;
		pEntityInfo->target = target;
		pEntityInfo->angle = angle;
		pEntityInfo->scale = scale;
		pEntityInfo->dirName = dirName;
	}
	else if(pEntity->type == InGE_QENTITY_LIGHT){
		QEntityLight *pEntityLight = (QEntityLight *) pEntity;
		pEntityLight->origin = origin;
		pEntityLight->target = target;
		pEntityLight->color = color;
		pEntityLight->radius = radius;
		pEntityLight->light = light;
	}

		
	return pEntity;
}

QEntityParser::~QEntityParser(){
}

