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

#include "TextureArray.h"
#include "../Render/Drawer.h"
#include <iostream>  //DEBUG

using namespace InGE;

using std::cerr;	//debug
using std::endl; 	//debug

TextureArray *TextureArray::textureArray = 0;

/**
 * Construtor
 */
TextureArray::TextureArray() {
	Drawer *drawer = Drawer::getInstance();

	SDL_Surface	*pImage = SDL_CreateRGBSurface(SDL_HWSURFACE, 2,2, 32, 0,0,0,0);
	m_defaultTexture.width = 2;
	m_defaultTexture.height = 2;

	//Gerando indice de textura
	drawer->genTextures(1, &m_defaultTexture.textureID);
	//Atribuindo como textura alvo
	drawer->bindTexture(InGE_TEXTURE_2D, m_defaultTexture.textureID);

	drawer->texImage2D(InGE_TEXTURE,0, InGE_RGBA, 2,2,0,InGE_BGRA, InGE_UNSIGNED_BYTE, pImage->pixels);
	
	SDL_FreeSurface(pImage);
	
}

/**
 * @return Retorna a classe para ser usada
 */
TextureArray *TextureArray::getInstance(){
	if(!textureArray)
		textureArray = new TextureArray();
		
	return textureArray;
}

/**
 * Destrutor
 */
TextureArray::~TextureArray(){
	if(textureArray) delete textureArray;
}


TextureInfo* TextureArray::getInfo(const string &filename) {
	map<const string, TextureInfo>::iterator it = m_textures.find(filename);
	
	if( it != m_textures.end() ) {
		//++it->second.ref_count; //FIXME: funcionar o ref_count;
		return &(it->second);
	} else {
		try {
			m_textures[filename] = loadFile(filename);
			return &(m_textures.find(filename)->second);
		} catch(string s) {
			return &m_defaultTexture;
		}
	}
}

string TextureArray::findTextureExtension(string strName){
	FILE *fp;
	string filename;

	//Sem extensao
	filename = strName;
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}
	
	//TGA	
	filename = strName;
	filename += ".tga";
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}
	
	//JPG
	filename = strName;
	filename += ".jpg";
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}

	//BMP
	filename = strName;
	filename += ".bmp";
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}

	//PNG
	filename = strName;
	filename += ".png";
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}

	//PCX
	filename = strName;
	filename += ".pcx";
	if((fp = fopen(filename.c_str(), "r"))){
		fclose(fp);
		return filename;
	}
	
	return string();	
}

TextureInfo TextureArray::loadFile(const string &filename){
	unsigned int textureID, width, height;
	bool alpha = false;
	SDL_Surface	*pImage;
	Drawer *drawer = Drawer::getInstance();
	
	string filename_ext = findTextureExtension(filename);
	if (filename_ext.empty()) {
		//cerr << "ERRO no nome do arquivo: " << filename << endl;
		throw string("No such file");
	}
	
	//Carregando bitmap
	pImage = IMG_Load(filename_ext.c_str());
	//checagem de erro ao carregar bitmap
	if(pImage == NULL){
		cerr << " Failed loading " << filename_ext << " : " << SDL_GetError() << endl;
		throw string("SDL ERROR: failed loading");
	}

	
	//Gerando indice de textura
	drawer->genTextures(1, &textureID);
	//Atribuindo como textura alvo
	drawer->bindTexture(InGE_TEXTURE_2D, textureID);

	drawer->texParameter(InGE_TEXTURE_2D, InGE_TEXTURE_MAG_FILTER, InGE_LINEAR);
	drawer->texParameter(InGE_TEXTURE_2D, InGE_TEXTURE_MIN_FILTER, InGE_LINEAR_MIPMAP_NEAREST);
	drawer->texEnv( InGE_TEXTURE_ENV, InGE_TEXTURE_ENV_COLOR, InGE_BLEND );


	width  = pImage -> w;
	height = pImage -> h;
	unsigned char * data = (unsigned char *) (pImage->pixels);         // the pixel data

	int bytesPerPixel = pImage->format->BytesPerPixel;


	unsigned char *pixels = new unsigned char[width * height * bytesPerPixel];
	int count = 0;

	if(pImage->format->BytesPerPixel == 4){
		char r,g,b,a;
		unsigned int *data = (unsigned int *) (pImage->pixels);
		
		for(unsigned int i = 0; i < (width * height); ++i){
			unsigned int pixelValue=data[i];

			SDL_GetRGBA(pixelValue, pImage->format, (Uint8 *)&r, (Uint8 *)&g, (Uint8 *)&b, (Uint8 *)&a);
			
			pixels[count++] = r;
			pixels[count++] = g;
			pixels[count++] = b;
			pixels[count++] = a;
			
			if ((int ) a != -1 );
				alpha = true;
		}
		
		drawer->build2DMipmaps(InGE_TEXTURE_2D,  InGE_RGBA, width, height, InGE_RGBA, InGE_UNSIGNED_BYTE, pixels);
		
	} else if(pImage->format->BytesPerPixel == 3) {
		char r,g,b;

		unsigned char *data = (unsigned char *) (pImage->pixels);		

		for(unsigned int i = 0; i < (width * height); ++i){
			unsigned int pixelValue=0;

			for(int j = bytesPerPixel - 1 ; j >=0; --j){
				pixelValue <<= 8;     
				pixelValue |=  data[ (i * bytesPerPixel) + j ];  
			}                                                    

			SDL_GetRGB(pixelValue, pImage->format, (Uint8 *)&r, (Uint8 *)&g, (Uint8 *)&b);
			
			pixels[count++] = r;
			pixels[count++] = g;
			pixels[count++] = b;
		}
		
		drawer->build2DMipmaps(InGE_TEXTURE_2D,  InGE_RGB, width, height, InGE_RGB, InGE_UNSIGNED_BYTE, pixels);
		
	} else {
		cerr << "Texture: " << filename << " - Invalid pImage->format->BytesPerPixel" << endl;
		throw string("Formato invalido na textura");
	}


	SDL_FreeSurface(pImage);
	//if(pixels) delete [] pixels;
	
	return TextureInfo(textureID, width, height, alpha);
}

int TextureArray::loadTexture(const string &filename, unsigned int *id, bool *alpha){
	TextureInfo *info = getInfo(filename);
	if (info == NULL) return -1;
	if (id) *id = info->textureID;
	if (alpha) *alpha = info->alpha;
	return 0;
}
