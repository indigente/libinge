#ifndef ENGINELOADER_H_
#define ENGINELOADER_H_

#include "SceneManager.h"
#include "Player.h"
#include "../Audio/AudioManager.h"
#include "../Graphics/World/BspScene.h"
#include "../Graphics/Camera/ICamera.h"
#include "../Control/ControlLayer.h"
#include "../Graphics/World/Q3Bsp/QEntity.h"
#include "../Graphics/Camera/CameraFP.h"
#include "../Entities/EntityFactory.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace InGE{

/**
 * Must be instantied after calling SetupManager::init()
 */
class EngineLoader{
	private:
		BspScene			*m_pScene;

		ICamera				*m_pCamera;
		Player				*m_pPlayer;
		
		ControlLayer 			*m_pControlLayer;
		RenderManager 			*m_pRenderManager;
		SceneManager			*m_pSceneManager;
		PhysicsManager			*m_pPhysicsManager;
		vector<QEntityInfo *> 	m_vEntityInfo;

		
		bool loadScene(string sceneFile);
		void loadModels();
		
	public:
		EngineLoader();
		virtual ~EngineLoader();
		Player *getPlayer();
		BspScene *getScene();
		ControlLayer *getControlLayer();
		bool loadWidgets();
		bool createScene(string sceneFile);
		void createPlayer(string playerModelDir, Avatar* pAvatar = NULL);

		void setStream(AudioSource *stream);
		void loadStream(string filename);
		
		// factory methods
		virtual ControlLayer *createControlLayer();
		virtual RenderManager *createRenderManager();
		virtual PhysicsManager *createPhysicsManager();
};
}
#endif /*ENGINELOADER_H_*/
