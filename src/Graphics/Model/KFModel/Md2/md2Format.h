/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004 Indigente


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

#ifndef MD2FORMAT_H
#define MD2FORMAT_H

namespace InGE{

// magic number "IDP2" or 844121161
#define MD2_IDENT                (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')
// number of precalculated normals
#define NUMVERTEXNORMALS        162

#define MD2_VERSION		8

// number of precalculated normals
#define NUMVERTEXNORMALS        162

// number of precalculated dot product results (for lighting)
#define SHADEDOT_QUANT          16

#define MAX_MD2_VERTS	2048

typedef float vec3_t[3];

// precalculated normal vectors

/////////////////////////////////////////////////

	
// Estrutura Md2Header
// - Armazena informacoes do cabecalho md2
// md2 header
typedef struct
{
	int     ident;              // magic number. must be equal to "IPD2"
	int     version;            // md2 version. must be equal to 8

	int     skinwidth;          // width of the texture
	int     skinheight;         // height of the texture
	int     framesize;          // size of one frame in bytes

	int     num_skins;          // number of textures
	int     num_xyz;            // number of vertices
	int     num_st;             // number of texture coordinates
	int     num_tris;           // number of triangles
	int     num_glcmds;         // number of opengl commands
	int     num_frames;         // total number of frames

	int     ofs_skins;          // offset to skin names (64 bytes each)
	int     ofs_st;             // offset to s-t texture coordinates
	int     ofs_tris;           // offset to triangles
	int     ofs_frames;         // offset to frame data
	int     ofs_glcmds;         // offset to opengl commands
	int     ofs_end;            // offset to end of file

} sMd2Header;

	// Usado para Armazenar vertices lido do frame atual
	typedef struct{
		unsigned char vertex[3];
		unsigned char lightNormalIndex;
	}vertex_t;
	
	// This stores UV coordinates
	typedef struct{
		short s;
		short t;
	}texCoord_t;
	
	// This stores the animation scale, translation and name information for a frame, plus verts
	typedef struct{
		float scale[3];
		float translate[3];
		char name[16];
		vertex_t    verts[1];       // first vertex of this frame
	}frame_t;
	
	// triangle
	typedef struct
	{
		short   index_xyz[3];    // indexes to triangle's vertices
		short   index_st[3];     // indexes to vertices' texture coorinates
	} triangle_t;

	// animation
	typedef struct
	{
		int     first_frame;            // first frame of the animation
		int     last_frame;             // number of frames
		int     fps;                    // number of frames per second

	} anim_t;
	
	// animation state
	typedef struct
	{
		int     startframe;              // first frame
		int     endframe;                // last frame
		int     fps;                     // frame per second for this animation

		float   curr_time;               // current time
		float   old_time;                // old time
		float   interpol;                // percent of interpolation

		int     type;                    // animation type

		int     curr_frame;              // current frame
		int     next_frame;              // next frame

	} animState_t;

	// Armazena indice dentro do vetor de coordenadas de vertices e texturas
	typedef struct Face{
		short vertexIndices[3];
		short textureIndices[3];
	}Face;

	// This stores the frames vertices after they have been transformed
	typedef struct Frame{
		char strName[16];
		triangle_t *pVertices;
	}Frame;
	
	typedef char Skin [64];
	
	// animation list
	typedef enum {
		STAND,
		RUN,
		ATTACK,
		PAIN_A,
		PAIN_B,
		PAIN_C,
		JUMP,
		FLIP,
		SALUTE,
		FALLBACK,
		WAVE,
		POINT,
		CROUCH_STAND,
		CROUCH_WALK,
		CROUCH_ATTACK,
		CROUCH_PAIN,
		CROUCH_DEATH, 
		DEATH_FALLBACK,
		DEATH_FALLFORWARD,
		DEATH_FALLBACKSLOW,
		BOOM,

		MAX_ANIMATIONS

	} animType_t;

};
#endif  //MD2FORMAT_H
