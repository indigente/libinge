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
#ifndef MD3FORMAT_H
#define MD3FORMAT_H

namespace InGE{

	// número de vetóres normais pre-calculados
	#define NUMVERTEXNORMALS		162

	// identificador "IDP3" ou 860898377
	#define MD3_IDENT				(('3'<<24) + ('P'<<16) + ('D'<<8) + 'I')

	// número de versão
	#define	MD3_VERSION				15

	// número maximal de sommet par mesh
	#define MD3_MAX_VERTICES		8192
	
		
	// vecteur 3D
	typedef float vec3_t[3];
	
		
	// Estrutura Md3Header
	// - Armazena informacoes do cabecalho md3
	typedef struct{ 
		int		ident;			// identificateur fichier MD3 : "IDP3"
		int		version;		// version du format : 15
		char		filename[68];		// nome du fichier
		int		numBoundVolumes;	// número de frames
		int		numTags;		// número de tags
		int		numMeshes;		// número de meshes
		int		numMaxSkins;		// número de textures
		int		offsetBoundVolume;	// taille du md3_header_t (en octets)
		int		offsetTag;		// offset dï¿½but donnï¿½es tags
		int		offsetMesh;		// offset fin donnï¿½es tags
		int		offsetEnd;		// taille du fichier (en octets)
	} sMd3Header;
	
	
	// Usado para Armazenar vertices lido do frame atual
	typedef struct{
		signed short		vertex[3];				// coord. (x,y,z) du vertex
		unsigned char	lightNormalIndex[2];	// index normale
	} sAliasTriangle;
	
	
	// triangle
	typedef struct{
		int		vertex[3];	// indices des sommets
	} sTriangle;
	
	
	// texture
	typedef struct{
		char name[68];
	} sSkinName;
	
	
	// coord. texture (s,t)
	typedef struct{
		float	s;
		float	t;
	} sTextCoord;
	
	
	// header mesh
	typedef struct{
		int		ident;				// identifiant : "IDP3"
		char		name[68];			// nome do mesh
		int		numFrames;			// número de frames
		int		numSkins;			// número de textures
		int		numVertex;			// número de vertices de um frame
		int		numTriangles;		// número de triangles
		int		offsetTriangles;		// offset dos triangulos
		int		offsetSkins;			// offset das skins (108 octets)
		int		offsetTexCoords;		// offset das coord. texturas
		int		offsetVertex;		// offset dos vertices
		int		meshEnd;				// final do mesh (em octetos)
	} sMeshHeader;
	
	
	// mesh
	typedef struct{
		sMeshHeader			header;			// header do mesh 
		sSkinName			*skins;			// skins
		sTriangle			*triangles;		// index triangulos
		sTextCoord			*texCoord;		// coordenadas de texture
		sAliasTriangle		*vertices;		// vertices e indices da normais
		int					texId;			// id texture du mesh
	} sMesh;
	
	
	// frame
	typedef struct{
		vec3_t	mins;
		vec3_t	maxs;
		vec3_t	position;
		float	scale;
		char	creator[16];
	} sBoundVolume;
		
	
	// tag
	typedef struct{
		char	name[64];
		vec3_t	position;
		float	rotation[3][3];
	} sTag;
	
		
	// animation
	typedef struct{
		int		curr_frame;		// frame courante
		int		next_frame;		// frame suivante
		float	interp;			// proucentage d'interpolation
	} sAnimation;


};
#endif  //MD2FORMAT_H
