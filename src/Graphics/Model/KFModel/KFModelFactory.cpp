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

#include "KFModelFactory.h"

using namespace InGE;
using namespace std;

KFModelFactory *KFModelFactory::m_pKFModelFactory = 0;

/**
 * Construtor
 */
KFModelFactory::KFModelFactory(){
 	buildNormTable();
	for (int modelIndex = 0; modelIndex < m_loadedModels.size(); modelIndex++){
		delete m_loadedModels[modelIndex];
	}
 	m_loadedModels.clear();
	m_isLoading = false;
}

/**
 * @return Retorna a classe para ser usada
 */
KFModelFactory *KFModelFactory::getInstance(){
	if(!m_pKFModelFactory)
		m_pKFModelFactory = new KFModelFactory();
		
	return m_pKFModelFactory;
}

/**
 * Destrutor
 */
KFModelFactory::~KFModelFactory(){
	if(m_pKFModelFactory) delete m_pKFModelFactory;
}


/**
 * Cria a tabela de normais para os modelos de Md3
 */
void KFModelFactory::buildNormTable(){
	double alpha, beta;
	for( int i = 0; i < 256; i++ ){
		for( int j = 0; j < 256; j++ ){
			alpha   = i * 2.0 * M_PI / 255.0;
			beta    = j * 2.0 * M_PI / 255.0;
			m_normTable[i][j][0] = (float)(cos( beta ) * sin( alpha ));
			m_normTable[i][j][1] = (float)(sin( beta ) * sin( alpha ));
			m_normTable[i][j][2] = (float)cos( alpha );
		}
	}
}


/**
 * @param string name - Nome do KFModel a ser procurado.
 * @return Retorna o indice do KFModel achado ou -1 caso n� exista.
 */
int KFModelFactory::findKFModel(string name){
	for( unsigned int i = 0; i < m_loadedModels.size(); i++ ){
		if( m_loadedModels[i]->getName() == name ){
			return i;
		}
	}
	return -1;
}


/**
 * @param string md2File - Nome do Arquivo referente ao modelo
 * @return Retorna um ponteiro para o modelo Md2 carregado
 */
 
 Md2Model* KFModelFactory::loadMd2Model(string md2File){
			
 }
 

 
 
/**
 * @param string directoryName - Endere� do diretorio com os arquivos referentes ao modelo.
 * @return Retorna um poteiro para o IModel carregado que tenha o nome filename.
 */
IModel *KFModelFactory::loadMd3(string directoryName){
	string filename = directoryName + "/lower.md3";
	int modelIndex = findKFModel(filename);
	if (modelIndex != -1){
		return m_loadedModels[modelIndex];
	} 
		
	while (m_isLoading){ //FIXME: Usar semaforo
		//Esperando qualquer thread acabar de carregar algum modelo.
	} 
	
	m_isLoading = true;
	
	Md3Model *pMd3Model;
	if (m_vetAnimInfo.size() > 0)
		m_vetAnimInfo.clear();
	
	m_directoryName = directoryName;
	
	loadMd3AnimationFile( directoryName + "/animation.cfg" );
	
	
	pMd3Model = loadMd3Model("/lower.md3", "LEGS");
	if (pMd3Model) {
		if ( pMd3Model->attachModel( loadMd3Model("/upper.md3", "TORSO") ) ){
			cout << "Model " << directoryName + "/upper.md3" << " attached to " <<  pMd3Model->getName() << endl;
		}
		
		if ( 	pMd3Model->attachModel( loadMd3Model("/head.md3", "HEAD") ) ){
			cout << "Model " << directoryName + "/head.md3" << "attached to " <<  pMd3Model->getName() << endl;
		}
	}
	m_isLoading = false;
	
	return pMd3Model;
}

/**
 * @param string md3File - Endere� do arquivo do modelo.
 * @param string bodyParty - Parte do Container referente ao modelo.
 * @return Retorna um poteiro para o Md3Model carregado.
 */
Md3Model *KFModelFactory::loadMd3Model(string md3File, string bodyParty){
	Md3Model *md3Model = NULL;
	string filename = m_directoryName + md3File;
	int modelIndex = findKFModel(filename);
	if (modelIndex != -1)
		return (Md3Model *) m_loadedModels[modelIndex];
	
	
	FILE *file = fopen(filename.c_str(), "rb");
	if (!file){
		//cerr << "Erro ao carregar o arquivo " <<  filename << endl;
		return NULL;
	}

	md3Model = createMd3(file, bodyParty);
	md3Model->setName(filename);
	
	m_loadedModels.push_back(md3Model);
	
	fclose(file);
	
	return md3Model;
}

/**
 * @param FILE *file - Arquivo Md3.
 * @param const vector<string > &vetLowerFileTex - Vetor de endere�s de texturas referente ao modelo Md3.
 * @param vector<sAnimInfo *> vetAnimInfo - Estrutura referente as anima�es do modelo Md3.
 * @return Retorna um poteiro para o Md3Model encadeado com outros 2 carregado que tenha o nome filename.
 */
Md3Model *KFModelFactory::createMd3(FILE *file, string bodyPart){
	// Leitura do cabecalho
	sMd3Header 		header;
	fread(&header, sizeof(sMd3Header), 1, file);
	
	//BoundVolume
	sBoundVolume *psBoundVolume = new sBoundVolume[header.numBoundVolumes];
	fseek(file, header.offsetBoundVolume, SEEK_SET);
	fread(psBoundVolume, sizeof(sBoundVolume), header.numBoundVolumes, file);
	
	//Tags
	sTag *psTag = new sTag[header.numTags * header.numBoundVolumes];
	fseek(file, header.offsetTag, SEEK_SET);
	fread(psTag, sizeof(sTag), header.numTags * header.numBoundVolumes, file);
	
	//Mesh
	sMesh *psMesh = new sMesh[header.numMeshes];
	int offSet = header.offsetMesh;
	
	for (int i=0; i < header.numMeshes; i++){
		// Leitura do cabecalho do mesh
		fseek(file, offSet , SEEK_SET);
		fread(&psMesh[i].header, sizeof(sMeshHeader), 1, file);	

		//Skin 
		psMesh[i].skins = new sSkinName[psMesh[i].header.numSkins];
		fseek(file, offSet + psMesh[i].header.offsetSkins, SEEK_SET);
		fread(psMesh[i].skins, sizeof(sSkinName), psMesh[i].header.numSkins, file);
		
		//Triangle 
		psMesh[i].triangles = new sTriangle[psMesh[i].header.numTriangles];
		fseek(file, offSet + psMesh[i].header.offsetTriangles, SEEK_SET);
		fread(psMesh[i].triangles, sizeof(sTriangle), psMesh[i].header.numTriangles, file);
		
		//TexCoord 
		psMesh[i].texCoord = new sTextCoord[psMesh[i].header.numVertex];
		fseek(file, offSet + psMesh[i].header.offsetTexCoords, SEEK_SET);
		fread(psMesh[i].texCoord, sizeof(sTextCoord), psMesh[i].header.numVertex, file);

		//Vertices
		psMesh[i].vertices = new sAliasTriangle[psMesh[i].header.numVertex * psMesh[i].header.numFrames];
		fseek(file, offSet + psMesh[i].header.offsetVertex, SEEK_SET);
		fread(psMesh[i].vertices, sizeof(sAliasTriangle), psMesh[i].header.numVertex * psMesh[i].header.numFrames, file);
		offSet += psMesh[i].header.meshEnd;

	
	}
		
	unsigned int **drawIndex;
	drawIndex = new unsigned int*[header.numMeshes];
	for (int meshIndex = 0; meshIndex < header.numMeshes; meshIndex++){
		int count = 0;
		drawIndex[meshIndex]  = new unsigned int[psMesh[meshIndex].header.numTriangles * 3];

		for (int dIndex = 0; dIndex < psMesh[meshIndex].header.numTriangles; dIndex++){
			for(int vertexI = 0; vertexI < 3; vertexI++, count++){
				drawIndex[meshIndex][count] = psMesh[meshIndex].triangles[dIndex].vertex[vertexI];
			}
		}
	}
	
	Md3Model *pModel = new Md3Model( bodyPart, this->md3Setup(header, psMesh, psBoundVolume, psTag, drawIndex, bodyPart) );
	return pModel;
}

/**
 * @param sMd3Header header
 * @param sMesh *psMesh
 * @param sBoundVolume *psBoundVolume
 * @param sTag *psTag
 * @param unsigned int **drawIndex
 * @return Retorna um vetor de KeyFrame para ser adicionado ao Md3Model
 */
map<string, vector<KeyFrame *> > KFModelFactory::md3Setup(sMd3Header header, sMesh *psMesh, sBoundVolume *psBoundVolume, sTag *psTag, unsigned int **drawIndex, string bodyPart){
	map<string, vector<KeyFrame *> > mapAnim;
	if (m_vetAnimInfo.size() > 0){
		for (int animIndex = 0; animIndex < m_vetAnimInfo.size(); animIndex++){
			if ( ( (m_vetAnimInfo[animIndex].bodyPart == bodyPart) || (m_vetAnimInfo[animIndex].bodyPart == "BOTH") ) && (bodyPart != "HEAD")  ) { 
				vector<KeyFrame *> vetKeyFrame;
				for (int frameIndex = m_vetAnimInfo[animIndex].firstFrame; frameIndex < (m_vetAnimInfo[animIndex].numFrame + m_vetAnimInfo[animIndex].firstFrame); frameIndex++){
					KeyFrame *currentKeyFrame = new KeyFrame();
					currentKeyFrame->setName(m_vetAnimInfo[animIndex].name);
					for (int tagIndex = 0; tagIndex < header.numTags; tagIndex++){
						currentKeyFrame->addTag(new Tag(psTag[tagIndex].name, psTag[(frameIndex * header.numTags) + tagIndex].position, (float *)psTag[(frameIndex * header.numTags) + tagIndex].rotation));
					}
					Vector3 *pPosition, *pNormal;
					Vector2 *pTexCood;
					sAliasTriangle *psVertex;
					for (int meshIndex=0; meshIndex < header.numMeshes; meshIndex++){
						Mesh *pMesh = new ConcreteMesh();
						
						pMesh->setName(psMesh[meshIndex].header.name);
						pMesh->setFrontFace(InGE_CW);
						
						for (int texIndex = 0; texIndex < psMesh[meshIndex].header.numSkins; texIndex++){
							MaterialInfo material;
							material.setTexture( psMesh[meshIndex].skins[texIndex].name );
							pMesh->addMaterial( material );
						}
						for (int vIndex = 0; vIndex < psMesh[meshIndex].header.numVertex; vIndex++){
							
							psVertex = &( psMesh[meshIndex].vertices[ vIndex + (frameIndex * psMesh[meshIndex].header.numVertex)  ] );
							
							pPosition = new Vector3((psVertex->vertex[0]) / 64.0f,
															 (psVertex->vertex[1]) / 64.0f,
															 (psVertex->vertex[2]) / 64.0f);
							
							pNormal = new Vector3(	m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][0],
															m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][1],
															m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][2]);
							
							pTexCood = new Vector2( psMesh[meshIndex].texCoord[ vIndex ].s,
															psMesh[meshIndex].texCoord[ vIndex ].t );
							
							pMesh->addVertex( Vertex( *pPosition, *pNormal, *pTexCood ) );
							
						}
						
						pMesh->setDrawIndex( drawIndex[meshIndex], psMesh[meshIndex].header.numTriangles * 3 );
						
						currentKeyFrame->addMesh( pMesh );
					}
					currentKeyFrame->setVolumeInfo( psBoundVolume[frameIndex] );
					vetKeyFrame.push_back( currentKeyFrame );
				}
				mapAnim[m_vetAnimInfo[animIndex].name] = vetKeyFrame;
			}
		}
	}
	if ((m_vetAnimInfo.size() == 0) || (mapAnim.size() == 0)){
		
		vector<KeyFrame *> vetKeyFrame;
		KeyFrame *currentKeyFrame;
		for (int frameIndex = 0; frameIndex < header.numBoundVolumes; frameIndex++){
			currentKeyFrame = new KeyFrame();

			for (int j = 0; j < header.numTags; j++){
				currentKeyFrame->addTag(new Tag(psTag[j].name, psTag[(frameIndex * header.numTags) + j].position, (float *)psTag[(frameIndex * header.numTags) + j].rotation));
			}

			Vector3 *pPosition, *pNormal;
			Vector2 *pTexCood;
			sAliasTriangle *psVertex;
		
			for (int meshIndex=0; meshIndex < header.numMeshes; meshIndex++){
				Mesh *pMesh = new ConcreteMesh();
											
				pMesh->setName(psMesh[meshIndex].header.name);
				pMesh->setFrontFace(InGE_CW);
				
				for (int texIndex = 0; texIndex < psMesh[meshIndex].header.numSkins; texIndex++){
					MaterialInfo material;
					material.setTexture( psMesh[meshIndex].skins[texIndex].name );
					pMesh->addMaterial( material );
				}
				
			
				for (int vIndex = 0; vIndex < psMesh[meshIndex].header.numVertex; vIndex++){
					psVertex = &( psMesh[meshIndex].vertices[ vIndex + (frameIndex * psMesh[meshIndex].header.numVertex) ] );
				
					pPosition = new Vector3( (psVertex->vertex[0]) / 64.0f,
													  (psVertex->vertex[1]) / 64.0f,
													  (psVertex->vertex[2]) / 64.0f);
					pNormal = new Vector3(	m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][0],
													m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][1],
													m_normTable[psVertex->lightNormalIndex[0]][psVertex->lightNormalIndex[1]][2]);
				
					pTexCood = new Vector2(	psMesh[meshIndex].texCoord[ vIndex + (0 * psMesh[meshIndex].header.numVertex) ].s,
													psMesh[meshIndex].texCoord[ vIndex + (0 * psMesh[meshIndex].header.numVertex) ].t );

					pMesh->addVertex( Vertex( *pPosition, *pNormal, *pTexCood ) );
				}
			
				pMesh->setDrawIndex( drawIndex[meshIndex], psMesh[meshIndex].header.numTriangles * 3 );

				currentKeyFrame->addMesh(pMesh);	
			}
			currentKeyFrame->setVolumeInfo( psBoundVolume[frameIndex] );
			vetKeyFrame.push_back(currentKeyFrame);
		}
		mapAnim["IDLE"] = vetKeyFrame;
	}
	
	return mapAnim;
}



/**
 * @param string confFilename - Endere� do arquivo texto referente as anima�es do modelo.
 * @param int numFrame - Numero de frames do modelo, usado para checagem de erros.
 * @return - Retorna um poteiro para um vetor de sAnimInfo contendo informa�es sobre as anima�es de um modelo.
 */
bool KFModelFactory::loadMd3AnimationFile(const string& confFilename){
	FILE *confFile;
	confFile = fopen(confFilename.c_str(), "rb"); 
	if(!confFile) {
		cerr << "Erro carregando o arquivo "<< confFilename << endl;
		return false;
	}

	char currentWord[15];
	char currentLine[50];
	char *name;
	char *bodyPart;
	
	
	while(!feof(confFile)){
		fscanf(confFile, " %s " , currentWord);
		if(!isdigit( currentWord[0] )){
			fscanf(confFile,"%[^\n] ",currentLine);
		} else {
			
			sAnimInfo animInfo;
			animInfo.firstFrame = atoi(currentWord);
			name = new char[20];
			bodyPart = new char[20];
			fscanf(confFile," %d %d %d // %[^_] _ %[^\n] ",&animInfo.numFrame,&animInfo.loopFrames,&animInfo.fps,bodyPart, name, currentLine);
			animInfo.name = name;
			animInfo.bodyPart = bodyPart;
			std::transform(animInfo.bodyPart.begin(), animInfo.bodyPart.end(), animInfo.bodyPart.begin(), (int(*)(int)) toupper);
			
			
			m_vetAnimInfo.push_back(animInfo);
		}
	}
			
 	fclose(confFile);
	return true;
}


