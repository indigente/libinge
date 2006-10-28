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
#include "MovieTex.h"
using namespace std;//FIXME: Debung
using namespace InGE;

MovieTex::MovieTex(Mesh *pMesh, string filename, bool hasSound, int bpp) : MeshDecorator(pMesh){
	Drawer *drawer = Drawer::getInstance();


	// Inicializa nulo
	m_pSurface = NULL;
	m_pMut = NULL;

	// Abre o arquivo mpeg
	m_mpeg = SMPEG_new(filename.c_str(), &m_info, hasSound );
	

	// Habilita audio e video
	if (hasSound)
		SMPEG_enableaudio(m_mpeg, m_info.has_audio);
	
	SMPEG_enablevideo(m_mpeg, m_info.has_video);

	m_width = 1 << static_cast<unsigned int> (logb(m_info.width));
	m_height = 1 << static_cast<unsigned int> (logb(m_info.height));

	// Cria um Surface vazia
	m_pSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, m_width, m_height, bpp,0,0,0,0);
	if(!m_pSurface) {
		m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, bpp,0,0,0,0);
	}
	//TODO throw NullPointerException para !m_pSurface


	// Cria a textura inicial
	drawer->enable(InGE_TEXTURE_2D);
	drawer->genTextures(1, &m_textureID);
	drawer->bindTexture(InGE_TEXTURE_2D, m_textureID);
	drawer->texParameter(InGE_TEXTURE_2D, InGE_TEXTURE_MIN_FILTER, InGE_NEAREST);
	drawer->texParameter(InGE_TEXTURE_2D, InGE_TEXTURE_MAG_FILTER, InGE_NEAREST);
		
// 	if(bpp == 32)
// 		drawer->texImage2D(InGE_TEXTURE_2D, 0, InGE_RGBA, m_width, m_height, 0, InGE_BGRA, InGE_UNSIGNED_BYTE, m_pSurface->pixels);
// 	else 
		drawer->texImage2D(InGE_TEXTURE_2D, 0, InGE_RGB, m_width, m_height, 0, InGE_BGR, InGE_UNSIGNED_BYTE, m_pSurface->pixels);


	SMPEG_setdisplay(m_mpeg, m_pSurface, m_pMut, MovieTex::updateTex);
	SMPEG_scaleXY(m_mpeg, m_width, m_height);
	SMPEG_play(m_mpeg);

}

MovieTex::~MovieTex(){
	if(m_mpeg){
		SMPEG_stop(m_mpeg);
		SMPEG_delete(m_mpeg);
	}
	if(m_pSurface)
		 SDL_FreeSurface(m_pSurface);
	if(m_pMut)
		 SDL_DestroyMutex(m_pMut);
}

void MovieTex::updateTex(SDL_Surface *pImage, int x, int y, unsigned int w, unsigned int h){
}


void MovieTex::set(bool setup){
	Drawer *drawer = Drawer::getInstance();

	drawer->activeTextureARB(InGE_TEXTURE0_ARB);
	drawer->enable(InGE_TEXTURE_2D);
	drawer->bindTexture(InGE_TEXTURE_2D, m_textureID);
	SDL_mutexP(m_pMut);
	drawer->texSubImage2D(InGE_TEXTURE_2D, 0,0,0,  m_width, m_height, InGE_BGRA, InGE_UNSIGNED_BYTE, m_pSurface->pixels);
	SDL_mutexV(m_pMut);
	
	drawer->clientActiveTextureARB(InGE_TEXTURE0_ARB);
	drawer->enableClientState(InGE_TEXTURE_COORD_ARRAY);
	drawer->texCoordPointer(2, InGE_FLOAT, sizeof(Vertex), m_component->getVertex(0)->getTextureOffset());

	m_component->set(true);	
}

void MovieTex::executeCommand(ExecuteCommandEnum e, string param){
	switch(e){
		case InGE_EXCMD_PLAY:	
			SMPEG_play(m_mpeg);
			break;
		case InGE_EXCMD_STOP:
			SMPEG_stop(m_mpeg);
			break;
		case InGE_EXCMD_REWIND:
			SMPEG_rewind(m_mpeg);
			break;	
		case InGE_EXCMD_LOOP:
			if(param =="true" || param =="1") SMPEG_loop(m_mpeg, true);
			else SMPEG_loop(m_mpeg, false);
			break;
	}		
	
}

Mesh *MovieTex::interpolate(Mesh *pMesh, float interpolation){
//	return new MovieTex( m_component->interpolate(pMesh, interpolation), m_pTexture, m_vetLightmapCoord );
}

