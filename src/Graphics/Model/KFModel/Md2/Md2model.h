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
#ifndef INGEMD2MODEL_H
#define INGEMD2MODEL_H
#include "md2Format.h"
#include "../../../Render/Drawer.h"
#include "../../../Base/MaterialInfo.h"
#include "../../../Render/IRenderListener.h"
#include "../../IModel.h"
#include "../KeyFrame.h"

namespace InGE {

/**
	@author Danton <danton@dcc.ufba.br>
*/
class Md2Model : public InGE::IModel{
	private:
		string		name;
		int             num_frames;         // number of frames
		int             num_xyz;            // number of vertices
		int             num_glcmds;         // number of opengl commands

//		vector<Mesh *>	m_vetMesh;
//		Vertex		
		vec3_t          *m_vertices;        // vertex array
		int             *m_glcmds;          // opengl command array
		int             *m_lightnormals;    // normal index array

		unsigned int    m_texid;            // texture id
		animState_t     m_anim ;             // animation
		float           m_scale;            // scale value
		
		void    Animate( float time );
		void    Interpolate( vec3_t *vertlist );
		void    RenderFrame( void );
		
		float    *shadedots;
		vec3_t   lcolor;
		
		float *m_anorms_dots;
		float *m_anorms; 
		static anim_t   m_animlist[21];
		
		vector<KeyFrame> m_vetKeyFrame;
		
	public:
		Md2Model();
		~Md2Model();
	
		bool    LoadModel(string, string);
		MaterialInfo    LoadSkin( const char *filename );

		void    DrawModel( float time );
		void    DrawFrame( int frame );

		void    SetAnim( int type );
		void    ScaleModel( float s ) { m_scale = s; }
		
		bool getBlend();
		void setWeapon(IModel*);
		void setAnimation(int);
		void drawModel();
		string getName();
		vector<VolumeInfo *> getVetVolumeInfo();

		


		/////////////////////////////////////////////////
		

};

}

#endif
