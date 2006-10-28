#include "EngineLoader.h"
#include <iostream>  // NOTE: para teste
using namespace std;// NOTE: para teste
namespace InGE{
EngineLoader::EngineLoader(){
	// Pega a instancia do SceneManager
	m_pSceneManager = SceneManager::getInstance();
	
	//Instancia a camada de controlu usada pelo jogador
	m_pControlLayer = new ControlLayer();
	// Instancia o rendermanager
	m_pRenderManager = new RenderManager();
	// Instancia o mundo fisico
	m_pPhysicsManager = new PhysicsManager();
	
	AudioManager *audioManager = AudioManager::getInstance();
	audioManager->init();
	
	//SceneManager
	m_pSceneManager->setRenderManager(m_pRenderManager);
	m_pSceneManager->setPhysicsManager(m_pPhysicsManager);
	
	//Controle
	m_pControlLayer->addListener(m_pSceneManager);
//	m_pControlLayer->unsetMouseOnCenter();
//	m_pControlLayer->grabOff();
}

EngineLoader::~EngineLoader(){
	if(m_pControlLayer) delete m_pControlLayer;
	if(m_pRenderManager) delete m_pRenderManager;
	if(m_pPhysicsManager) delete m_pPhysicsManager;
	
}

void EngineLoader::createScene(string sceneFile ){
		// Instancia o cenario
	m_pScene = new BspScene();
	// Carrega o Cenario
	loadScene(sceneFile);
	// Seta o cenario utilizado pelo rendermanager
	m_pRenderManager->setScene(m_pScene);
	m_pPhysicsManager->setScene( m_pScene);
}

void EngineLoader::createPlayer(string playerModelDir, Avatar* pAvatar) {
	AudioManager *audioManager = AudioManager::getInstance();
	
	if (!pAvatar){
		pAvatar = new Avatar();
	}
	
	EntityFactory *pEntityFactory = EntityFactory::getInstance();
	pEntityFactory->addAvatar( pAvatar );
	
	if (playerModelDir != "") {
		KFModelFactory *pModelFactory = KFModelFactory::getInstance();
		IModel *pModel = pModelFactory->loadMd3(playerModelDir);
		if (pModel)
			pAvatar->setModel( pModel );
	}

	m_pPlayer = new Player(pAvatar);
	m_pSceneManager->setPlayer(m_pPlayer);
	
	// Adiciona os elementos controlados

	m_pControlLayer->addListener(pAvatar);

}


bool EngineLoader::loadScene(string sceneFile){
	bool ret = m_pScene->load(sceneFile);
	if(!ret){
		cerr << "Falha carregando Bsp..." << endl;
		exit(-1);
	}
	m_vEntityInfo = m_pScene->getVectorOfEntityInfo();
	return ret;
}

ControlLayer *EngineLoader::getControlLayer(){
	return m_pControlLayer;
}

Player *EngineLoader::getPlayer(){
	return m_pPlayer;
}

BspScene *EngineLoader::getScene(){
	return m_pScene;
}

bool EngineLoader::loadWidgets(){
// 	Window *status = new Window();
// 	//Label *label = new Label("INDIGENTE");
// 	//Label *label2 = new Label("Teste");
// 	//label->move(10, 10);
// 	//label2->move(10, 20);
// 	//status->add(label);
// 	//status->add(label2);
// 	TextureDecorator *td = new TextureDecorator("textures/showroom_misc/spearker", status);
// 	td->move(10,-10);
// 	m_pRenderManager->addWidget(td);
// 	return true;
}

void EngineLoader::setStream( AudioSource *stream ){
	if (stream)
		m_pPlayer->setStream( stream );
}

void EngineLoader::loadStream(string filename){
	AudioManager *audioManager = AudioManager::getInstance();
	AudioSource *audioSource = audioManager->createSource();
	
	audioSource->setLooping(true);
	audioSource->playStreaming(filename);
	
	if (m_pPlayer)
		m_pPlayer->setStream(audioSource);
}

}
