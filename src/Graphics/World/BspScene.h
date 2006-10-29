/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004 Indigente


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
#ifndef BSPSCENE_H
#define BSPSCENE_H

#include "IScene.h"

#include "../../Util/BitSet.h"
#include "../../Math/Vector3.h"

#include "../Render/Frustum.h"

#include "../Base/Mesh.h"
#include "../Base/MeshDecorator/DecoratorList.h" 

#include "../../Physics/PhysicalSpace.h"
#include "../../Physics/PhysicalGeom.h"
#include "../../Physics/PhysicalContactPoint.h"
#include "../../Physics/Geoms/GeomPlane.h"
#include "../../Physics/Geoms/GeomSphere.h"
#include "../../Physics/Geoms/GeomBox.h"

#include "Q3Bsp/bspFormat.h"
#include "Q3Bsp/QEntityParser.h"
#include "Q3Bsp/QShaderManager.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#define FACE_POLYGON    1
#define BEZIER_PATCH    2
#define MESH_POLYGON    3
#define BILLBOARD       4

namespace InGE{
	enum BspTraceType{
		InGE_BSP_TRACE_RAY, InGE_BSP_TRACE_SPHERE,InGE_BSP_TRACE_BOX
	};
	
	struct BspInfo{
		BspTexture		*pTextures;
		int 			numOfTextures;

		BspNode			*pNodes;
		int 			numOfNodes;
		
		BspLeaf			*pLeafs;
		int 			numOfLeafs;
		
		BspLeafFace		*pLeafFaces;
		int 			numOfLeafFaces;
		
		BspPlane		*pPlanes;
		int 			numOfPlanes;
		
		BspLeafBrush		*pLeafBrushes;
		int 			numOfLeafBrushes;
		
		BspBrush		*pBrushes;
		int 			numOfBrushes;
		
		BspBrushSide		*pBrushSides;
		int 			numOfBrushSides;
			
		BspEntity		*pEntities;
		int 			numOfEntities; 
		
		BspModel		*pModels;
		int 			numOfModels;
		
		BspShader		*pShaders;
		int 			numOfShaders;
		
		BspLight		*pLights;	
		int 			numOfLights;	
		
		BspVisData		clusters;
		BitSet			facesDrawn;
		
		
		
		unsigned int		lightmaps[MAX_TEXTURE];
		float 			gamma;
	};
	
	
	
	class BspScene : public InGE::IScene{
	   private:
		// Informacoes do arquivo Bsp
		BspInfo 		m_info;
		
		// Posicao da camera
		Vector3			m_camera;
		
		// Cluster onde a camera estah
		int			m_cameraCluster;
		
		// Volume de visualizacao
		Frustum			*m_pFrustum;
		
		// Mesh 
		Mesh 			**m_vMeshs;
		int			m_numOfMeshs;
			
		// Colision Data
		PhysicalContactPoint	m_moveData;
		BspTraceType		m_traceType;
		Vector3				m_startMovePosition;
		Vector3				m_endMovePosition;
		float					m_moveOffset;
		
		Vector3				m_extends;
		Vector3				m_traceMax;
		Vector3				m_traceMin;
		
		static const double 	m_kEpsilon;
		
		// TODO: Entities 
		vector<QEntityInfo *>	m_vEntityInfo;
		vector<QEntityLight *>	m_vEntityLight;
		
		/////////////////////
		/* Private Methods */
		////////////////////
		
	  	// Achar o indice do nodo folha
		int findLeaf(Vector3 &vPos);
		
	  	// Renderizar cen�io
		void renderTree(int nodeIndex);
		
		void renderLeaf(int nodeIndex);
		
		int isClusterVisible(int current, int test);
	  	
	  	// Metodos de colisao
		void checkNode(int indexNode, double startFraction, double endFraction, Vector3 start, Vector3 end);
		
		void checkBrush(BspBrush &brush);		
		
		
		void createLightmap(int index, BspLightmap *pImageBits, int width, int height);
		void changeGamma(unsigned char *pImage, unsigned int size, float factor);
		
		void loadMeshs(BspMeshVertex *pMeshVerts, BspFace *pFaces, BspVertex *pVerts);
		
	  public:
		BspScene(); 
		~BspScene();
		
		
		bool 	load(string filename);
		
		void 	renderLevel(Vector3 vPos, Frustum &frustum);
		
		// Colisao 
		PhysicalContactPoint &checkMoveCollision(Vector3 start, Vector3 end, PhysicalGeom *geom = NULL);
		PhysicalContactPoint &checkMoveCollisionAndTrySlide(Vector3 start, Vector3 end, PhysicalGeom *geom = NULL);
		
		// Entity
		std::vector<QEntityInfo *>& getVectorOfEntityInfo();
		std::vector<QEntityLight *>& getVectorOfEntityLight();
				
	
	};

};
#endif
