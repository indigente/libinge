/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

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

#ifndef _MOVIETEX_H_
#define _MOVIETEX_H_
#include "MeshDecorator.h"
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <smpeg/smpeg.h>
#include <string>
#include <math.h>
#include "../../Render/Drawer.h"


namespace InGE{

	using std::string;

	class MovieTex: public InGE::MeshDecorator{
		private:
			string m_filename;
			bool m_hasSound;
			int m_bpp;
			
			SDL_Surface 	*m_pSurface;
			SDL_mutex 		*m_pMut;
			unsigned int 	m_textureID;
			SMPEG 			*m_mpeg;
			SMPEG_Info 		m_info;
			int 				m_width;
			int				m_height;
			
		public:
			MovieTex(Mesh *pMesh, string filename, bool hasSound, int bpp=32);
			~MovieTex();
			
			Mesh *interpolate(Mesh *pMesh, float interpolation);
						
			static void updateTex(SDL_Surface *pImage, int x, int y, unsigned int w, unsigned int h);

			void set(bool setup);

			void executeCommand(ExecuteCommandEnum e, string param);
	};
}
#endif
