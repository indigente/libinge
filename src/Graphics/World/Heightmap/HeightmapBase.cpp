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
#include "HeightmapBase.h"
#include "../../Base/TextureArray.h"

#include <cstdio>

using namespace InGE;

bool HeightmapBase::loadHeightMap(char* filename, int size){
	FILE *pFile;

	pFile = NULL;
	pFile = fopen(filename,"rb");

	if (pFile == NULL){	//checa se o arquivo foi aberto corretamente
		printf("Erro ao abrir %s\n",filename);
		return false;
	}

	if (m_heightData.m_pData)	//se ja houver algum mapa carregado, descarregue-o
		unloadHeightMap();

	//alocar a memoria necessaria para o heightmap
	m_heightData.m_pData = new unsigned char[size * size];

	//checar se a memoria foi corretamente alocada
	if (m_heightData.m_pData == NULL){
		printf("Erro ao alocar memoria para %s\n",filename);
		return false;
	}

	//carregar o arquivo para a memoria, efetivamente
	fread(m_heightData.m_pData, 1, size*size, pFile);

	fclose(pFile);

	m_heightData.m_size = size;
	m_size	= size;

	printf("%s carregado com sucesso!\n", filename);
	return true;
}

bool HeightmapBase::unloadHeightMap(void){
	if (m_heightData.m_pData){
		delete[] m_heightData.m_pData;
		m_heightData.m_size = 0;
		m_size=0;
	}

	printf("HeightMap descarregado com sucesso!\n");
	return true;
}

void HeightmapBase::loadTexture(string path){
	TextureArray *textureArray = TextureArray::getInstance();
	textureArray->loadTexture(path,&id_texture);
}

HeightmapBase::HeightmapBase(){
}

HeightmapBase::~HeightmapBase(){
	this->unloadHeightMap();
}
