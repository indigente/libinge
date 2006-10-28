/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H
#include <string>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



#define MAX_TEXTURE		1024


namespace InGE{

	using std::string;
	using std::map;

	class TextureInfo {
		private:
			unsigned int ref_count;
		public:
			unsigned int textureID, width, height;
			bool alpha;
			TextureInfo(){}
			TextureInfo(unsigned int i, unsigned int w, unsigned int h, bool a=false)
				: ref_count(1), textureID(i), width(w), height(h), alpha(a) { }
	};

	/**
	 * Classe TextureArray 
	 * Singleton respons�vel por gerenciar texturas
	 * Carrega textura e assegura que nenhuma textura seja
	 * duplicada na mem�ria.
	 * @author Ivan Medeiros Monteiro
	 */
	class TextureArray{
	  private:
		TextureInfo m_defaultTexture;
  		map<const string, TextureInfo> m_textures;
	  	static TextureArray *textureArray;
		TextureArray();
		
		TextureInfo loadFile(const string &filename);
		string findTextureExtension(string strName);
		
	  public:
		static TextureArray *getInstance();
		~TextureArray();
		
		TextureInfo* getInfo(const string &filename);
		void unload(unsigned int textureID); //FIXME: este nome? garbage collector

		//DEPRECIADO
		int loadTexture(const string &filename, unsigned int *id = 0, bool *alpha = 0);		
	};
	
};
#endif // TEXTUREARRAY_H
