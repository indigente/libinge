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
#include "QShaderManager.h"
#include <cstring>
#include <cctype>
using namespace InGE;

QShaderManager	*QShaderManager::m_shaderManager = NULL;

QShaderManager::QShaderManager(){
}

// Retorna uma Instancia de QShaderManager 
QShaderManager *QShaderManager::getInstance(){
	if(!QShaderManager::m_shaderManager){
		QShaderManager::m_shaderManager = new QShaderManager();
	}
	
	return m_shaderManager;
}

QShaderManager::~QShaderManager(){
}

bool QShaderManager::loadShaders(string filename){
	char buf[64];
	FILE *fp = fopen(filename.c_str(), "r");

	// Skip: erro ao tentar abrir arquivo
	if(!fp) return false;

	while(fscanf(fp, " %s", buf) && !feof(fp)){
		//printf("%s\n", buf);
		parserShaders(buf);
		
	}
	
	fclose(fp);

	return true;
}


// Realiza o parser do arquivo de Shaders e adiciona cada shader ao map.
bool QShaderManager::parserShaders(string filename){
	FILE *fp = fopen(filename.c_str(), "r");
	string  name;
	bool ret;
	
	// Skip: erro ao tentar abrir arquivo
	if(!fp) return false;
	
	// Cria um novo Shader
	while(getNewLine(fp) && !feof(fp)){
		name =  m_currentLine; // Nome do Shader
		QShader *shader = new QShader(name);		
		// {
		ret = getNewLine(fp); 
		if(!isOpenK(m_currentLine)) break;
		
		// Leitura dos parametro globais
		while(ret=getNewLine(fp), !isOpenK(m_currentLine) && !isCloseK(m_currentLine)){
			if(!ret) return false;
			if(isCull(m_currentLine)) setCullParameter(m_currentLine, shader);
		}



		// Verifica se ja eh o fim do shader
		if(isCloseK(m_currentLine)) continue;
		// Leitura dos parametros locais
		else if(isOpenK(m_currentLine)){
			while(ret = getNewLine(fp), !isCloseK(m_currentLine)){
				if(!ret) return false;				
				if(isMap(m_currentLine)) setMapParameter(m_currentLine, shader);
				else if(isClampMap(m_currentLine)) setClampMapParameter(m_currentLine, shader);
				else if(isAnimMap(m_currentLine)) setAnimMapParameter(m_currentLine, shader);
				else if(isBlend(m_currentLine)) setBlendParameter(m_currentLine, shader);
 			}
		}
		
		// Skip ateh o final do shader
		while(ret = getNewLine(fp), !isCloseK(m_currentLine)){
			if(!ret) return false;
			if(isOpenK(m_currentLine)){
				while(ret = getNewLine(fp), !isCloseK(m_currentLine)){
					if(!ret) return false;				
					if(isMap(m_currentLine)) setMapParameter(m_currentLine, shader);
					else if(isClampMap(m_currentLine)) setClampMapParameter(m_currentLine, shader);
					else if(isAnimMap(m_currentLine)) setAnimMapParameter(m_currentLine, shader);
					else if(isBlend(m_currentLine)) setBlendParameter(m_currentLine, shader);
	 			}
			}
		}
		
		//Inserir o Shader no map
		m_shaders[name] = shader;
	}
	
	
	fclose(fp);

	return true;
}



bool QShaderManager::isComment(char *str){
	char buf[3];
	sscanf(str, " %2s",buf);
	
	return strncmp(buf, "//", 2)? false : true;
}

bool QShaderManager::isCull(char *str){
	char buf[5];
	sscanf(str, " %4s", buf);
	
	return strncmp(buf, "cull", 4)? false : true;
}

bool QShaderManager::isBlend(char *str){
	char buf[10];
	sscanf(str, " %9s", buf);
	
	return strncmp(buf, "blendfunc", 9)? false : true;
}

bool QShaderManager::isMap(char *str){
	char buf[4];
	sscanf(str, " %3s", buf);
	
	return strncmp(buf, "map", 3)? false : true;
}

bool QShaderManager::isClampMap(char *str){
	char buf[9];
	sscanf(str, " %8s", buf);
	
	return strncmp(buf, "clampmap", 8)? false : true;
}

bool QShaderManager::isAnimMap(char *str){
	char buf[8];
	sscanf(str, " %7s", buf);
	
	return strncmp(buf, "animmap", 7)? false : true;
}

bool QShaderManager::isOpenK(char *str){
	char buf;
	sscanf(str, " %c", &buf);
	
	return buf == '{' ? true : false;
}

bool QShaderManager::isCloseK(char *str){
	char buf;
	sscanf(str, " %c", &buf);
	
	return buf == '}' ? true : false;
}

// Passa o array de char pra minusculo
void QShaderManager::lower(char *str){
	for(;*str; *str = (char) tolower(*str), str++ );
}

bool QShaderManager::getNewLine(FILE *fp){
	do{
		if(!fscanf(fp, " %1023[^\n^\r]", m_currentLine) || feof(fp)) return false;
	 	lower(m_currentLine);
	}while(isComment(m_currentLine));
	return true;
}

void QShaderManager::setCullParameter(char *str, QShader *shader){
	char cull[5],parameter[8];
	sscanf(str, " %4s %7s", cull, parameter);
	if(!strncmp(parameter, "front", 5)) shader->setCullMode(InGE_FRONT);
	else if(!strncmp(parameter, "back", 4))shader->setCullMode(InGE_BACK);
}

void QShaderManager::setBlendParameter(char *str, QShader *shader){
	char blendfunc[10], src[32], dst[32];
	int srcMode, dstMode;
	
	if(sscanf(str, " %9s %32s %32s", blendfunc, src, dst) <3) return;
	
	if(!strncmp(src, "gl_one",6)) srcMode = InGE_ONE;
	else if(!strncmp(src, "gl_zero",7)) srcMode = InGE_ZERO;
	else if(!strncmp(src, "gl_dst_color",12)) srcMode = InGE_DST_COLOR;
	else if(!strncmp(src, "gl_one_minus_dst_color",22)) srcMode = InGE_ONE_MINUS_DST_COLOR;	
	else if(!strncmp(src, "gl_src_alpha",12)) srcMode = InGE_SRC_ALPHA;
	else if(!strncmp(src, "gl_one_minus_src_alpha",22)) srcMode = InGE_ONE_MINUS_SRC_ALPHA;
	else if(!strncmp(src, "gl_dst_alpha",12)) srcMode = InGE_DST_ALPHA;
	else if(!strncmp(src, "gl_one_minus_dst_alpha",22)) srcMode = InGE_ONE_MINUS_DST_ALPHA;
	else if(!strncmp(src, "gl_src_alpha_saturate",21)) srcMode = InGE_SRC_ALPHA_SATURATE;
	else return;
	
	if(!strncmp(dst, "gl_one",6)) dstMode = InGE_ONE;
	else if(!strncmp(dst, "gl_zero",7)) dstMode = InGE_ZERO;
	else if(!strncmp(dst, "gl_src_color",12)) dstMode = InGE_SRC_COLOR;
	else if(!strncmp(dst, "gl_one_minus_src_color",22)) dstMode = InGE_ONE_MINUS_SRC_COLOR;	
	else if(!strncmp(dst, "gl_src_alpha",12)) dstMode = InGE_SRC_ALPHA;
	else if(!strncmp(dst, "gl_one_minus_src_alpha",22)) dstMode = InGE_ONE_MINUS_SRC_ALPHA;
	else if(!strncmp(dst, "gl_dst_alpha",12)) dstMode = InGE_DST_ALPHA;
	else if(!strncmp(dst, "gl_one_minus_dst_alpha",22)) dstMode = InGE_ONE_MINUS_DST_ALPHA;
	else return;
	
	shader->setBlendFunc(srcMode, dstMode);
}

void QShaderManager::setMapParameter(char *str, QShader *shader){
	char map[4], path[64];
	
	sscanf(str, " %3s %63s", map, path);
	if(path[0] == '$') return ;
	
	shader->addTextureFileName(path);
}

void QShaderManager::setClampMapParameter(char *str, QShader *shader){
	char map[9], path[64];
	
	sscanf(str, " %8s %63s", map, path);
	if(path[0] == '$') return ;
	
	shader->addTextureFileName(path);	
}

void QShaderManager::setAnimMapParameter(char *str, QShader *shader){
	char animap[8], path[64];
	float freq;
	
	sscanf(str, " %7s %f %[^\n]", animap, &freq, str);
	
	shader->setFreq(freq);
	
	while(sscanf(str, " %63s %[^\n]", path, str) == 2){
		shader->addTextureFileName(path);	
	}
}

QShader *QShaderManager::getShader(string name){
	
	map<string, QShader* >::iterator it = m_shaders.find(name);

	return it->second;
}



void QShaderManager::addShader(QShader *shader){
	if(!shader) return;
	m_shaders[shader->getName()] = shader;
}

