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

#ifndef BSPFORMAT_H
#define BSPFORMAT_H
#include "../../../Math/Vector2.h"
#include "../../../Math/Vector3.h"

#define BSP_FACE_POLYGON	1
#define BSP_BEZIER_PATCH    2
#define BSP_MESH_POLYGON    3
#define BSP_BILLBOARD       4

namespace InGE{

	using namespace InGE;


	enum eLumps {
		kEntities = 0,		// Stores player/object positions, etc...
		kTextures,		// Stores texture information
		kPlanes,		// Stores the splitting planes
		kNodes,			// Stores the BSP nodes
		kLeafs,			// Stores the leafs of the nodes
		kLeafFaces,		// Stores the leaf's indices into the faces
		kLeafBrushes,		// Stores the leaf's indices into the brushes
		kModels,		// Stores the info of world models
		kBrushes,		// Stores the brushes info (for collision)
		kBrushSides,		// Stores the brush surfaces info
		kVertices,		// Stores the level vertices
		kMeshVerts,		// Stores the model vertices offsets
		kShaders,		// Stores the shader files (blending, anims..)
		kFaces,			// Stores the faces for the level
		kLightmaps,		// Stores the lightmaps for the level
		kLightVolumes,		// Stores extra world lighting information
		kVisData,		// Stores PVS and cluster info (visibility)
		kMaxLumps		// A constant to store the number of lumps
	};


	// Cabecalho do BSP 
	struct BspHeader {
		char strID[4];		// This should always be 'IBSP'
		int version;		// This should be 0x2e for Quake 3 files
	}; 
	

	
	// Estrutura de BSP lump
	struct BspLump {
		int offset;		 	// Inicio do lump
		int length;			// Tamanho do lump
	};
	
	

	// Estrutura de Vertices BSP
	struct BspVertex {
		Vector3 vPosition;		// (x, y, z) position.
		Vector2 vTextureCoord;	// (u, v) texture coordinate
		Vector2 vLightmapCoord;	// (u, v) lightmap coordinate
		Vector3 vNormal;		// (x, y, z) normal vector
		unsigned char color[4];	// RGBA color for the vertex 
		
		BspVertex &operator+=(BspVertex &vert){
			vPosition += vert.vPosition;
			vTextureCoord += vert.vTextureCoord;						
			vLightmapCoord += vert.vLightmapCoord;
			vNormal += vert.vNormal;						
			return *this;
		};
		BspVertex &operator*=(float f){
			vPosition *= f;
			vTextureCoord *= f;						
			vLightmapCoord *= f;
			vNormal *= f;						
			return *this;
		};		
		BspVertex operator+(BspVertex &vert){
			BspVertex vertRet;
			vertRet = *this;
			vertRet.vPosition += vert.vPosition;
			vertRet.vTextureCoord += vert.vTextureCoord;						
			vertRet.vLightmapCoord += vert.vLightmapCoord;
			vertRet.vNormal += vert.vNormal;						
			return vertRet;
		};
		BspVertex operator*(float f){
			BspVertex vertRet;
			vertRet = *this;
			vertRet.vPosition *= f;
			vertRet.vTextureCoord *= f;						
			vertRet.vLightmapCoord *= f;
			vertRet.vNormal *= f;						
			return vertRet;
		};
	};

	
	
	// Estruturas de faces BSP
	struct BspFace {
		int textureID;		// The index into the texture array 
		int effect;			// The index for the effects (or -1 = n/a) 
		int type;			// 1=polygon, 2=patch, 3=mesh, 4=billboard 
		int startVertIndex;	// The starting index into this face's first vertex 
		int numOfVerts;		// The number of vertices for this face 
		int meshVertIndex;	// The index into the first meshvertex 
		int numMeshVerts;	// The number of mesh vertices 
		int lightmapID;		// The texture index for the lightmap 
		int lMapCorner[2];	// The face's lightmap corner in the image 
		int lMapSize[2];	// The size of the lightmap section 
		Vector3 lMapPos;	// The 3D origin of lightmap.
		float lMapVecs[3][2];	// The 3D space for s and t unit vectors.  
		Vector3 vNormal;	// The face normal.
		int size[2];		// The bezier patch dimensions. 
	};
	

	
	// This is our BSP texture structure
	struct BspTexture {
		char strName[64];   // The name of the texture w/o the extension 
		int flags;			// The surface flags (unknown) 
		int contents;		// The content flags (unknown)
	};



	struct BspLightmap {
		unsigned char imageBits[128][128][3];   // The RGB data in a 128x128 image
	};	



	struct BspNode {
		int plane;					// The index into the planes array 
		int front;					// The child index for the front node 
		int back;					// The child index for the back node 
		int min[3];				// The bounding box min position. 
		int max[3];				// The bounding box max position. 
	};
	


	struct BspLeaf {
		int cluster;				// The visibility cluster 
		int area;					// The area portal 
		int min[3];				// The bounding box min position 
		int max[3];				// The bounding box max position 
		int leafFace;				// The first index into the face array 
		int numOfLeafFaces;			// The number of faces for this leaf 
		int leafBrush;				// The first index for into the brushes 
		int numOfLeafBrushes;		// The number of brushes for this leaf 
	};
	



	struct BspPlane {
		Vector3 vNormal;			// Plane normal.
		float d;					// The plane distance from origin 
	};



	struct BspVisData {
		int numOfClusters;			// The number of clusters
		int bytesPerCluster;		// The amount of bytes (8 bits) in the cluster's bitset
		unsigned char *pBitsets;	// The array of bytes that holds the cluster bitsets				
	};


		
	struct BspBrush {
		int brushSide;           // The starting brush side for the brush
		int numOfBrushSides;     // Number of brush sides for the brush
		int textureID;           // The texture index for the brush
	};		



	struct BspBrushSide {
		int plane;		// The plane index
		int textureID;	// The texture index
	};


	struct BspModel {
		float min[3];           // The min position for the bounding box
		float max[3];           // The max position for the bounding box. 
		int faceIndex;          // The first face index in the model 
		int numOfFaces;         // The number of faces in the model 
		int brushIndex;         // The first brush index in the model 
		int numOfBrushes;       // The number brushes for the model
	}; 

	struct BspShader {
		char strName[64];     // The name of the shader file 
		int brushIndex;       // The brush index for this shader 
		int unknown;          // This is 99% of the time 5
	}; 
	
	struct BspLight {
		unsigned char  ambient[3];     // This is the ambient color in RGB
		unsigned char  directional[3]; // This is the directional color in RGB
		unsigned char  direction[2];   // The direction of the light: [phi,theta] 
	}; 

	typedef int  BspLeafFace;
	typedef int  BspLeafBrush;
	typedef char BspEntity ;
	typedef int  BspMeshVertex;

};

#endif
