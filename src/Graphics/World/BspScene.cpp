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
#include "BspScene.h"
#include "../../Entities/EntityFactory.h"
#define         MAX(X,Y)       X>=Y?X:Y
using namespace InGE;
using std::string;

//const float 	BspScene::m_kEpsilon = 0.03125f;
const double 	BspScene::m_kEpsilon = 1E-37;
// const float 	BspScene::m_kEpsilon = 0.1f;

BspScene::BspScene(){
	m_info.numOfNodes = 0;
	m_info.numOfLeafs = 0 ;
	m_info.numOfLeafFaces = 0;
	m_info.numOfPlanes = 0;
	m_info.numOfTextures = 0;
               
	m_info.numOfLeafBrushes = 0;
	m_info.numOfBrushes = 0;
	m_info.numOfBrushSides = 0;
                      
	m_info.numOfEntities = 0; 
               
	m_info.numOfModels = 0;
	m_info.numOfShaders = 0;
	m_info.numOfLights = 0;
        
	m_numOfMeshs = 0;
        
	m_info.pNodes = NULL;
	m_info.pLeafs = NULL;
	m_info.pPlanes = NULL;
	m_info.pLeafFaces = NULL;
	m_info.pTextures = NULL;              
	m_info.pLeafBrushes = NULL;
	m_info.pBrushes = NULL;
	m_info.pBrushSides = NULL;
               
	m_info.pEntities = NULL;
               
	m_info.pModels = NULL;
	m_info.pShaders = NULL;
	m_info.pLights = NULL;
        
	m_info.gamma = 5;      
}
BspScene::~BspScene(){
	if(m_info.pNodes) delete [] m_info.pNodes;
	if(m_info.pLeafs) delete [] m_info.pLeafs;
	if(m_info.pPlanes) delete [] m_info.pPlanes;
	if(m_info.pLeafFaces) delete [] m_info.pLeafFaces;
	if(m_info.pTextures) delete [] m_info.pTextures;
               
	if(m_info.pLeafBrushes) delete [] m_info.pLeafBrushes;
	if(m_info.pBrushes) delete [] m_info.pBrushes;
	if(m_info.pBrushSides) delete [] m_info.pBrushSides;
               
	if(m_vMeshs) delete [] m_vMeshs;
	if(m_info.pEntities) delete [] m_info.pEntities;
               
	if(m_info.pModels) delete [] m_info.pModels;
	if(m_info.pShaders) delete [] m_info.pShaders;
	if(m_info.pLights) delete [] m_info.pLights;
        
	for(unsigned int i=0; i<m_vEntityInfo.size(); i++){
		if(m_vEntityInfo[i]) delete m_vEntityInfo[i];
	}
	for(unsigned int i=0; i<m_vEntityLight.size(); i++){
		if(m_vEntityLight[i]) delete m_vEntityLight[i];
	}
}
int BspScene::findLeaf(Vector3 &vPos){
	int i = 0;
	float distance = 0.0f;
        
	while(i >=0){
		BspNode &node = m_info.pNodes[i];
		BspPlane &plane = m_info.pPlanes[node.plane];
		Vector3 normal(plane.vNormal);
               // Distancia do ponto ao plano. 
               // Para determinar do lado do plano em que se encotra o ponto
		distance = ( normal * vPos ) - plane.d;

		if(distance >= 0) i = node.front;
		else i = node.back;
               
	}
        
	return ~i;
}

void BspScene::renderLevel(Vector3 vPos, Frustum &frustum){
	int indexLeaf = this->findLeaf(vPos); // Acha em qual folhas estah a camera
	m_pFrustum = &frustum; 
	m_camera = vPos;
        
        // Armazena a cluster que estah a camera
	m_cameraCluster = m_info.pLeafs[indexLeaf].cluster;
	m_info.facesDrawn.clearAll();
        
	renderTree(0);
        
}


void BspScene::renderTree(int nodeIndex){
	BspNode &node = m_info.pNodes[nodeIndex];
        
	if(!m_pFrustum->isBoxInFrustum(node.min[0], node.min[1], node.min[2], 
		 node.max[0], node.max[1], node.max[2])) return;
	BspPlane &plane        = m_info.pPlanes[node.plane];
	Vector3 normal(plane.vNormal);
        
	if(normal * m_camera - plane.d > 0){ 
		if(node.front >= 0)    renderTree(node.front);
		else renderLeaf(~node.front);
                      
		if(node.back >= 0)     renderTree(node.back);
		else renderLeaf(~node.back);
               
	}
	else {
		if(node.back >= 0)     renderTree(node.back);
		else renderLeaf(~node.back);
                      
		if(node.front >= 0) renderTree(node.front);
		else renderLeaf(~node.front);
	}
        
}

void BspScene::renderLeaf(int leafIndex){
	Drawer *drawer = Drawer::getInstance();
	BspLeaf &leaf =  m_info.pLeafs[leafIndex];
	int meshCount = leaf.numOfLeafFaces;
        
	if(!isClusterVisible(m_cameraCluster, leaf.cluster)) return;
        
        
        // Verifica se a folha tem interseccao com o volume de visualizacao
	if(!m_pFrustum->isBoxInFrustum(leaf.min[0], leaf.min[1], leaf.min[2], 
		 leaf.max[0], leaf.max[1], leaf.max[2])) return;
        
	vector<Mesh *> vMeshBlend;
        // Percorre as faces da folha
	while(meshCount--){
		int meshIndex = m_info.pLeafFaces[leaf.leafFace + meshCount];
		if(!m_info.facesDrawn[meshIndex]){
			m_info.facesDrawn.set(meshIndex);
			if ( m_vMeshs[meshIndex]->getBlend() ){
				vMeshBlend.push_back(m_vMeshs[meshIndex]);
			} else {
				m_vMeshs[meshIndex]->draw();
			}
		}
               
	}
	for (int i = 0; i < vMeshBlend.size(); i++){
		m_vMeshs[i]->draw();
	}
}


int BspScene::isClusterVisible(int current, int test){
	if(!m_info.clusters.pBitsets || current < 0) return 1;
	return ( m_info.clusters.pBitsets[  current * m_info.clusters.bytesPerCluster + (test >> 3)  ]   &   (1 << (test & 7) ) ) ;
}



bool BspScene::load(string filename){
	FILE *fp;
	if(!(fp = fopen(filename.c_str(), "rb")))
		return false;
	BspHeader header;
	BspLump lumps[kMaxLumps];
        
        //Leitura de cabeï¿½lho
	fread(&header, 1, sizeof(BspHeader), fp);
	if((header.strID[0] != 'I') || (header.strID[1] != 'B') || (header.strID[2] != 'S') || (header.strID[3] != 'P') )
		return false;
	if(header.version != 0x2e)
		return false;
        
        //Leitura de lumps
	fread(lumps, kMaxLumps, sizeof(BspLump), fp);
        
        //Leitura de Nodos 
	if(lumps[kNodes].length){
		m_info.numOfNodes      = lumps[kNodes].length / sizeof(BspNode);
		m_info.pNodes         = new BspNode [m_info.numOfNodes];
               
		fseek(fp, lumps[kNodes].offset, SEEK_SET);
		fread(m_info.pNodes, m_info.numOfNodes, sizeof(BspNode), fp);
	}
        
        //Leitura das folhas
	if(lumps[kLeafs].length){
		m_info.numOfLeafs      = lumps[kLeafs].length / sizeof(BspLeaf);
		m_info.pLeafs         = new BspLeaf [m_info.numOfLeafs];
               
		fseek(fp, lumps[kLeafs].offset, SEEK_SET);
		fread(m_info.pLeafs, m_info.numOfLeafs, sizeof(BspLeaf), fp);
	}
        
        // Leitura de faces da folha
	if(lumps[kLeafFaces].length){
		m_info.numOfLeafFaces  = lumps[kLeafFaces].length / sizeof(BspLeafFace);
		m_info.pLeafFaces             = new BspLeafFace [m_info.numOfLeafFaces];
		fseek(fp, lumps[kLeafFaces].offset, SEEK_SET);
		fread(m_info.pLeafFaces, m_info.numOfLeafFaces, sizeof(BspLeafFace), fp);
	}
        
        // Leitura de planos
	if(lumps[kPlanes].length){
		m_info.numOfPlanes            = lumps[kPlanes].length / sizeof(BspPlane);
		m_info.pPlanes                       = new BspPlane [m_info.numOfPlanes];
		fseek(fp, lumps[kPlanes].offset, SEEK_SET);
		fread(m_info.pPlanes, m_info.numOfPlanes, sizeof(BspPlane), fp);
	}
        
        // Leitura dos Dados de visualizacao
	if(lumps[kVisData].length){
		int size;
		fseek(fp, lumps[kVisData].offset, SEEK_SET);
		fread(&(m_info.clusters.numOfClusters),       1, sizeof(int), fp);
		fread(&(m_info.clusters.bytesPerCluster), 1, sizeof(int), fp);
               
		size = m_info.clusters.numOfClusters * m_info.clusters.bytesPerCluster;
               
		m_info.clusters.pBitsets = new unsigned char [size];
		fread(m_info.clusters.pBitsets, 1, sizeof(unsigned char)*size, fp);
	}
	else m_info.clusters.pBitsets = NULL;
        
        // Leitura dos Brushes
	if(lumps[kBrushes].length){
		m_info.numOfBrushes           = lumps[kBrushes].length / sizeof(BspBrush);
		m_info.pBrushes                      = new BspBrush [m_info.numOfBrushes];
		fseek(fp, lumps[kBrushes].offset, SEEK_SET);
		fread(m_info.pBrushes, m_info.numOfBrushes, sizeof(BspBrush), fp);
	}
        
        // Leitura das folhas dos Brushes
	if(lumps[kLeafBrushes].length){
		m_info.numOfLeafBrushes        = lumps[kLeafBrushes].length / sizeof(BspLeafBrush);
		m_info.pLeafBrushes           = new BspLeafBrush[m_info.numOfLeafBrushes];
		fseek(fp, lumps[kLeafBrushes].offset, SEEK_SET);
		fread(m_info.pLeafBrushes, m_info.numOfLeafBrushes, sizeof(BspLeafBrush), fp);
	}
        
        // Leitura do BrushSide
	if(lumps[kBrushSides]. length){
		m_info.numOfBrushSides = lumps[kBrushSides]. length / sizeof(BspBrushSide);
		m_info.pBrushSides            = new BspBrushSide [m_info.numOfBrushSides];
               
		fseek(fp, lumps[kBrushSides].offset, SEEK_SET);
		fread(m_info.pBrushSides,m_info.numOfBrushSides, sizeof(BspBrushSide), fp);
	}
        
        // Leitura de entities
	if(lumps[kEntities].length){
		m_info.numOfEntities   = lumps[kEntities].length / sizeof(BspEntity);
		m_info.pEntities              = new BspEntity [m_info.numOfEntities];
		fseek(fp, lumps[kEntities].offset, SEEK_SET);
		fread(m_info.pEntities, m_info.numOfEntities, sizeof(BspEntity),fp);
               //fwrite(m_info.pEntities, m_info.numOfEntities, sizeof(BspEntity),stdout );
	}
	QEntityParser parser(m_info.pEntities, m_info.numOfEntities);
	QEntity *entity =  NULL;
	while((entity = parser.nextEntity()) != NULL){
		if(entity->type == InGE_QENTITY_INFO){
			QEntityInfo *p = (QEntityInfo *) entity;
			m_vEntityInfo.push_back(p);
		}
		else if(entity->type == InGE_QENTITY_LIGHT){
			QEntityLight *p = (QEntityLight *) entity;                   
			m_vEntityLight.push_back(p);
		}
	}
        
        // Leitura de modelos
	if(lumps[kModels].length){
		m_info.numOfModels            = lumps[kModels].length / sizeof(BspModel);
		m_info.pModels               = new BspModel[m_info.numOfModels];
		fseek(fp, lumps[kModels].offset, SEEK_SET);
		fread(m_info.pModels, m_info.numOfModels, sizeof(BspModel), fp);
	}
        
        // Leitura de Shaders
	if(lumps[kShaders].length){
		m_info.numOfShaders           = lumps[kShaders].length / sizeof (BspShader);
		m_info.pShaders                      = new BspShader [m_info.numOfShaders];
		fseek(fp, lumps[kShaders].offset, SEEK_SET);
		fread(m_info.pShaders, m_info.numOfShaders, sizeof(BspShader), fp);
	}
        
        
        // Leitura de Volume light
	if(lumps[kLightVolumes].length){
		m_info.numOfLights            = lumps[kLightVolumes].length / sizeof(BspLight);
		m_info.pLights               = new BspLight [m_info.numOfLights];
		fseek(fp, lumps[kLightVolumes].offset, SEEK_SET);
		fread(m_info.pLights, m_info.numOfLights, sizeof(BspLight), fp);
               
	}
        
	/////////////////////////////////
	// Inicio dos dados para Meshs //
	/////////////////////////////////      
	BspFace *pFaces = NULL;
        // Leitura de Faces
	if(lumps[kFaces].length){
		m_numOfMeshs   = lumps[kFaces].length / sizeof(BspFace);
		pFaces                = new BspFace [m_numOfMeshs];
		fseek(fp, lumps[kFaces].offset, SEEK_SET);
		fread(pFaces, m_numOfMeshs, sizeof(BspFace), fp);
	}
	m_vMeshs = new  Mesh * [m_numOfMeshs];
        
	int numOfVerts;
	BspVertex *pVerts = NULL;
        // Leitura de Vertices
	if(lumps[kVertices].length){
		numOfVerts     = lumps[kVertices].length / sizeof(BspVertex);
		pVerts                = new BspVertex [numOfVerts];
		fseek(fp, lumps[kVertices].offset, SEEK_SET);
		fread(pVerts, numOfVerts, sizeof(BspVertex), fp);
	}
               
        // Leitura de informacao de textura
	if(lumps[kTextures].length){
		m_info.numOfTextures   = lumps[kTextures].length / sizeof(BspTexture);
		m_info.pTextures       = new BspTexture[m_info.numOfTextures];
		fseek(fp, lumps[kTextures].offset, SEEK_SET);
		fread(m_info.pTextures, m_info.numOfTextures, sizeof(BspTexture), fp);
/*             QShaderManager *shaderManager = QShaderManager::getInstance();
		for(int i=0; i< numOfTextures; i++){
		QShader *shader = shaderManager->getShader(pTextures[i].strName);
                      //printf("%s\n", m_info.pTextures[i].strName);
		if(shader)m_vShaders.push_back(shader);
		else{
		shader = new QShader(pTextures[i].strName);
		shaderManager->addShader(shader);
		m_vShaders.push_back(shader);
	}
                      
		m_vShaders[i]->loadTextures();
	}*/
	}
        
	int numOfLightmaps;
	BspLightmap *pLightmaps = NULL;
        //Leitura de informaï¿½o de lightmap
	if(lumps[kLightmaps].length){
		numOfLightmaps = lumps[kLightmaps].length / sizeof(BspLightmap);
		pLightmaps = new BspLightmap[numOfLightmaps];
		fseek(fp, lumps[kLightmaps].offset, SEEK_SET);
		fread(pLightmaps, numOfLightmaps, sizeof(BspLightmap), fp);
		for(int i=0; i < numOfLightmaps; i++){
			this->createLightmap(i, &pLightmaps[i], 128,128);
		}
	}
	int numOfMeshVerts;
	BspMeshVertex *pMeshVerts = NULL;
        // Leitura de indice para vertices do Mesh
	if(lumps[kMeshVerts].length){
		numOfMeshVerts = lumps[kMeshVerts].length / sizeof(BspMeshVertex);
		pMeshVerts     = new BspMeshVertex [numOfMeshVerts];
		fseek(fp, lumps[kMeshVerts].offset, SEEK_SET);
		fread(pMeshVerts, numOfMeshVerts, sizeof(BspMeshVertex),fp );
	}
               
	fclose(fp);
	this->loadMeshs(pMeshVerts, pFaces, pVerts);
        
	EntityFactory *entityFactory = EntityFactory::getInstance();
	entityFactory->loadEntities(this);
        
	if (pFaces)
		delete [] pFaces;      
	if (pVerts)
		delete [] pVerts;
	if (pLightmaps)
		delete [] pLightmaps;
	if (pMeshVerts)
		delete [] pMeshVerts;
        
	return true;
}
void BspScene::loadMeshs(BspMeshVertex *pMeshVerts, BspFace *pFaces, BspVertex *pVerts){
	Vertex *pVertex;
	vector<Vector2 > vetLightmapCoord;
	BspVertex *currVertex;
	for (int j = 0; j < m_numOfMeshs; j++){
               
		m_vMeshs[j] = new ConcreteMesh();
//             vLightmapCoord = new Vector2[pFaces[j].numOfVerts];
		vetLightmapCoord.clear();
		MaterialInfo texture;
		for (int k = 0; k < pFaces[j].numOfVerts; k++){
			currVertex = &pVerts[pFaces[j].startVertIndex + k];
			vetLightmapCoord.push_back(currVertex->vLightmapCoord);
                      
			pVertex = new Vertex(currVertex->vPosition, currVertex->vNormal, currVertex->vTextureCoord);
			m_vMeshs[j]->addVertex(*pVertex);
		}

		m_vMeshs[j]->setDrawIndex( (unsigned int*) &pMeshVerts[pFaces[j].meshVertIndex], pFaces[j].numMeshVerts);
		
		texture.setTexture(m_info.pTextures[pFaces[j].textureID].strName);
		if (texture.getBlend()){
			m_vMeshs[j] = new AlphaBlend(m_vMeshs[j]);
		}
		m_vMeshs[j]->addMaterial(texture);


		if (pFaces[j].type == FACE_POLYGON){
			m_vMeshs[j]->setDrawMode(InGE_TRIANGLES);
			m_vMeshs[j] = new Lightmap(m_vMeshs[j], m_info.lightmaps[pFaces[j].lightmapID] , vetLightmapCoord);
		} else if (pFaces[j].type == BEZIER_PATCH){
			m_vMeshs[j] = new Bezier( m_vMeshs[j], pFaces[j].size, m_info.lightmaps[pFaces[j].lightmapID] , vetLightmapCoord );
		} else if (pFaces[j].type == MESH_POLYGON){
		} else if (pFaces[j].type == BILLBOARD){

                      /*m_vMeshs[j] = new BillBoard ( m_vMeshs[j] )*/;
                      
		}
	}
        
	m_info.facesDrawn.resize(m_numOfMeshs);
        
}

/**
 * Collision
 * Verifica colisao no movimento pretendido
 */
PhysicalContactPoint &BspScene::checkMoveCollision(Vector3 start, Vector3 end, PhysicalGeom *geom ){
	m_moveData.setDepth(1.0f);
	m_moveData.setPosition( end );
	if ( geom == NULL ){
		m_traceType = InGE_BSP_TRACE_RAY;
		m_moveOffset = 0.0;
        
		m_startMovePosition = start;
		m_endMovePosition = end;
	} else if ( geom->getClass() == 0 ){
		m_traceType = InGE_BSP_TRACE_SPHERE;
		GeomSphere *sphere = (GeomSphere *) geom;
		m_moveOffset = sphere->getRadius();
        
		m_startMovePosition = start;
		m_endMovePosition = end;
        
	} else if ( geom->getClass() == 1 ){
		m_traceType = InGE_BSP_TRACE_BOX;
		GeomBox *box = (GeomBox *) geom;
               
		m_traceMin = box->getLengths() / -2;
		m_traceMax = box->getLengths() / 2;
		m_moveOffset = 0.0f;
               
		m_startMovePosition = start;
		m_endMovePosition = end;
               
		m_extends.setXYZ(MAX(fabs(m_traceMin[0]), fabs(m_traceMax[0])), MAX(fabs(m_traceMin[1]), fabs(m_traceMax[1])), MAX(fabs(m_traceMin[2]), fabs(m_traceMax[2])));
	}
	if(start == end) return m_moveData;
        // percorre a arvore a partir da raiz
	checkNode(0, 0.0f, 1.0f, start, end);
        
        // Se houve colisao, atualiza os valores
	if(m_moveData.getDepth() == 1.0f){
		m_moveData.setPosition( end );
	}
	else {
		Vector3 position = start + (end - start)* (m_moveData.getDepth());
		position += m_moveData.getNormal()*0.1;
	}
        
	return m_moveData;
}
/**
 * Collision
 * Verifica colisao no movimento pretendido e tenta fazer slide
 */
PhysicalContactPoint &BspScene::checkMoveCollisionAndTrySlide(Vector3 start, Vector3 end, PhysicalGeom *geom){
	m_moveData.setDepth( 1.0f );
	m_moveData.setPosition( end );
	if ( geom == NULL ){
		m_traceType = InGE_BSP_TRACE_RAY;
		m_moveOffset = 0.0;
        
		m_startMovePosition = start;
		m_endMovePosition = end;
	}else if ( geom->getClass() == 0 ) {
		m_traceType = InGE_BSP_TRACE_SPHERE;
		GeomSphere *sphere = (GeomSphere *) geom;
		m_moveOffset = sphere->getRadius();
        
		m_startMovePosition = start;
		m_endMovePosition = end;
               
	} else if ( geom->getClass() == 1 ) {
		m_traceType = InGE_BSP_TRACE_BOX;
		GeomBox *box = (GeomBox *) geom;
               
		m_traceMin = box->getLengths() / -2;
		m_traceMax = box->getLengths() / 2;
		m_moveOffset = 0.0f;
               
		m_startMovePosition = start;
		m_endMovePosition = end;
               
		m_extends.setXYZ(MAX(fabs(m_traceMin[0]), fabs(m_traceMax[0])), MAX(fabs(m_traceMin[1]), fabs(m_traceMax[1])), MAX(fabs(m_traceMin[2]), fabs(m_traceMax[2])));
        
	} else if ( geom->getClass() == 8 ) {
		PhysicalSpace *space = (PhysicalSpace *)geom;
//                    for (int i = 0; space->getNumGeom(); i++){
//                           checkMoveCollisionAndTrySlide(start, end, space->getGeom( i ));
	}
	if(start == end)
		return m_moveData;
        // percorre a arvore a partir da raiz
	checkNode(0, 0.0f, 1.0f, start, end);
        
        // Se houve colisao, atualiza os valores
	if(m_moveData.getDepth() == 1.0f)
		m_moveData.setPosition( end );
	else{
		Vector3 slideStartPoint, position;
		slideStartPoint = position = start + (end - start)* m_moveData.getDepth();
		Vector3 v1 = (start - end)* (1.0f - m_moveData.getDepth());
		m_moveData.getNormal().normalize();
		Vector3 v2 =  m_moveData.getNormal() * (v1 * m_moveData.getNormal());
		position += (v2-v1);

		position += m_moveData.getNormal()*0.1;
		

		m_moveData.setPosition( position );
		checkMoveCollisionAndTrySlide(slideStartPoint, m_moveData.getPosition(), geom);
	}
        
	return m_moveData;
}
/**
 * Percorre a arvore(bsp) para ateh achar as folhas para verificar colisao
 */
void BspScene::checkNode(int nodeIndex, double startFraction, double endFraction, Vector3 start, Vector3 end){
	if(m_moveData.getDepth() <= startFraction)
		return;

	//Se o noh eh folha
	if(nodeIndex<0)        {
		BspLeaf &leaf = m_info.pLeafs[~nodeIndex];

		for (int i = 0; i < leaf.numOfLeafBrushes; i++){
			BspBrush &brush = m_info.pBrushes[m_info.pLeafBrushes[leaf.leafBrush + i]];
			// Checa se o brush eh valido e  material pra colisao
			if((brush.numOfBrushSides > 0) && (((m_info.pTextures[brush.textureID].contents)&1)||((m_info.pTextures[brush.textureID].contents)&0x10000))){
				checkBrush(brush);
			}

		}
		return;
	}

	BspNode        &node = m_info.pNodes[nodeIndex];
	BspPlane &plane = m_info.pPlanes[node.plane];
	Vector3  normal(plane.vNormal);

	double startDistance = (normal * start) - plane.d;
	double endDistance = (normal * end) - plane.d;
	if(m_traceType == InGE_BSP_TRACE_BOX) m_moveOffset = fabs(m_extends[0]*normal[0])+fabs(m_extends[1]*normal[1])+fabs(m_extends[2]*normal[2]);

        // Se ambos os pontos estaum na frente do plano, vai pra filho da frente
	if((startDistance >= m_moveOffset) && (endDistance >= m_moveOffset)){
		checkNode(node.front, startFraction, endFraction, start, end);
	}
        // Se ambos os pontos estaum atras do plano, vai pra filho de tras
	else if((startDistance < -m_moveOffset) && (endDistance < -m_moveOffset)){
		checkNode(node.back, startFraction, endFraction, start, end);  
	}
        // Caso contrario, split e vai pra os dois filhos.

	else{
               // Indice do noh para o ponto inicial e final
		int sideIndex1, sideIndex2;
               // Percentual a ser movido pelo ponto inicial e final
		double fraction1, fraction2;
               // Ponto de split
		Vector3 middle;

               // Ajusta Indices e Percentuais
		if(startDistance < endDistance){
			sideIndex1 = node.back;
			sideIndex2 = node.front;

			double inverseDiff = 1.0f / (startDistance - endDistance);
			fraction1 = (startDistance - m_kEpsilon - m_moveOffset) * inverseDiff;
			fraction2 = (startDistance + m_kEpsilon + m_moveOffset) * inverseDiff;               
		}
		else if(startDistance > endDistance){
			sideIndex1 = node.front;
			sideIndex2 = node.back;

			double inverseDiff = 1.0f / (startDistance - endDistance);
			fraction1 = (startDistance + m_kEpsilon + m_moveOffset) * inverseDiff;
			fraction2 = (startDistance - m_kEpsilon - m_moveOffset) * inverseDiff;
		}
		else {
			sideIndex1 = node.front;
			sideIndex2 = node.back;
			fraction1 = 1.0f;
			fraction2 = 0.0f;
		}

               // Valida Percentuais
		if(fraction1 < 0.0f) fraction1 = 0.0f;
		else if (fraction1 > 1.0f) fraction1 = 1.0f;
		if(fraction2 < 0.0f) fraction2 = 0.0f;
		else if (fraction2 > 1.0f) fraction2 = 1.0f;

               // definindo ponto de split a partir do ponto inicial
		middle = start + (end - start) * fraction1;
               // define o percentual do ponto inicial ateh o ponto de split                
		double middleFraction = startFraction + (endFraction - startFraction) * fraction1;
               //checagem no noh do ponto inicial
		checkNode(sideIndex1, startFraction, middleFraction, start, middle);

               // definindo ponto de split a partir do ponto final
		middle =  start + (end - start) * fraction2;
               // define o percentual do ponto final ateh o ponto de split                  
		middleFraction = startFraction + (endFraction - startFraction) * fraction2;
               //checagem no noh do ponto final
		checkNode(sideIndex2, middleFraction, endFraction, middle, end);
	}
}

/**
 * Faz checagem de colisao com um Brush especifico
 */
 
void BspScene::checkBrush(BspBrush &brush){
	float startFraction= -1.0f;
	float endFraction = 1.0f;
	bool  startOut = false;
	bool  endOut   = false;

        // Candidato a vetor normal
	Vector3 vCandidateToHitNormal; 

        // Varre os lados do Brush verificando colisao
	for(int i = 0 ; i < brush.numOfBrushSides; i++){
		BspBrushSide &brushSide = m_info.pBrushSides[brush.brushSide + i];
		BspPlane &plane = m_info.pPlanes[brushSide.plane];

		Vector3 normal(plane.vNormal);
		float startDistance;
		float endDistance;


		if(m_traceType == InGE_BSP_TRACE_BOX){ // Box
			Vector3 offset( normal[0] < 0 ? m_traceMax[0] : m_traceMin[0], 
								 normal[1] < 0 ? m_traceMax[1] : m_traceMin[1],
								 normal[2] < 0 ? m_traceMax[2] : m_traceMin[2]);

			startDistance = normal * (m_startMovePosition + offset) - plane.d;
			endDistance = normal * (m_endMovePosition + offset) - plane.d;        
		}
		else { // Ray and Sphere
			startDistance = normal * m_startMovePosition - plane.d - m_moveOffset;
			endDistance = normal * m_endMovePosition - plane.d - m_moveOffset;            
		}
                             
		if(startDistance > 0) startOut = true;
		if(endDistance > 0) endOut = true;
               
               // Se os dois pontos estaum fora, nao ha colisao
		if((startDistance > 0) && (endDistance > 0)) return; 
               // Se os dois pontos estaum atras, testar com outro plano
		else if((startDistance <= 0) && (endDistance <= 0)) continue;
               
               
               // Faz startDistance tender ao ponto final e endDistance tender ao inicial
               // se ele se cruzarem, entaum naum houve colisao
		if(startDistance > endDistance){
			float fraction = (startDistance - m_kEpsilon) / (startDistance - endDistance);
			if(fraction > startFraction){
				startFraction = fraction;
				vCandidateToHitNormal = normal;
			}
		}
		else{
			float fraction = (startDistance + m_kEpsilon) / (startDistance - endDistance);
			if(fraction < endFraction)     endFraction = fraction;
		}
	}
	
	if(!startOut){ // inicia dentro do brush
	//	m_moveData.startOut = false;
	//	if(!endOut) m_moveData.allSolid = true;
		return;
	}

	if(startFraction < endFraction){
		if((startFraction > -1.0f) && (startFraction < m_moveData.getDepth())){
			if(startFraction < 0) 
				startFraction = 0;
                      
			m_moveData.setDepth( startFraction );
			m_moveData.setNormal( vCandidateToHitNormal );
		}
	}
        
}

vector<QEntityInfo *>& BspScene::getVectorOfEntityInfo(){
	return m_vEntityInfo;
}
vector<QEntityLight *>& BspScene::getVectorOfEntityLight(){
	return m_vEntityLight; 
}
 
void BspScene::createLightmap(int index, BspLightmap *pImageBits, int width, int height){
	Drawer *drawer = Drawer::getInstance();
        
	drawer->genTextures(1, &m_info.lightmaps[index]);
	drawer->pixelStore(InGE_UNPACK_ALIGNMENT,1);
        
	drawer->bindTexture(InGE_TEXTURE_2D, m_info.lightmaps[index]);
        
	this->changeGamma((unsigned char *)pImageBits, width*height*3, m_info.gamma);
        
//      drawer->texImage2D( InGE_TEXTURE_2D, 0, InGE_RGB, width, height, 0, InGE_RGB, InGE_UNSIGNED_BYTE, pImageBits );
	drawer->build2DMipmaps(InGE_TEXTURE_2D, 3, width, height, InGE_RGB, InGE_UNSIGNED_BYTE, pImageBits);
        
	drawer->texParameter(InGE_TEXTURE_2D, InGE_TEXTURE_MAG_FILTER, InGE_LINEAR);
	drawer->texParameter(GL_TEXTURE_2D, InGE_TEXTURE_MIN_FILTER, InGE_LINEAR_MIPMAP_NEAREST);
	drawer->texEnv(InGE_TEXTURE_ENV, InGE_TEXTURE_ENV_MODE, InGE_MODULATE);
}
void BspScene::changeGamma(unsigned char *pImage, unsigned int size, float factor){
	for(unsigned int i = 0; i < size / 3; i++, pImage += 3){
		float scale = 1.0f, temp = 0.0f;
		float r = 0, g = 0, b = 0;
		r = (float)pImage[0];
		g = (float)pImage[1];
		b = (float)pImage[2];
		r *= factor / 255.0f;
		g *= factor / 255.0f;
		b *= factor / 255.0f;
		if(r > 1.0f && (temp = (1.0f/r)) < scale) scale=temp;
		if(g > 1.0f && (temp = (1.0f/g)) < scale) scale=temp;
		if(b > 1.0f && (temp = (1.0f/b)) < scale) scale=temp;
		scale*=255.0f;
		r*=scale;   g*=scale;   b*=scale;
		pImage[0] = (unsigned char)r;
		pImage[1] = (unsigned char)g;
		pImage[2] = (unsigned char)b;
	}
}
