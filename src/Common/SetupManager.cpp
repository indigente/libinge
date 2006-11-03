#include "../Graphics/Render/Drawer.h"
#include "SetupManager.h"
#include<iostream>

using namespace InGE;
using std::cerr;
using std::endl;

SetupManager *SetupManager::m_setupManager = NULL;
SDL_Surface *g_screen = NULL;

void SetupManager::setupOpenGL(int width, int height){
	Drawer *drawer = Drawer::getInstance();
	float ratio = (float) width / (float) height;

	/* Shading model-Gouraud (smooth) */
	drawer->shadeModel(InGE_SMOOTH);
	drawer->enable(InGE_TEXTURE_2D);
	
	drawer->clearDepth(1.0f);
	drawer->enable(InGE_DEPTH_TEST);
	drawer->depthFunc(InGE_LEQUAL);
	
	drawer->enable(InGE_BLEND);
	
	drawer->clearColor(0,0,0,1);
	drawer->viewport(0,0,width, height);

	drawer->hint(InGE_PERSPECTIVE_CORRECTION_HINT, InGE_NICEST);
	drawer->matrixMode(InGE_PROJECTION);
	drawer->loadIdentity();

	drawer->perspective(70.0f,ratio, 0.1f ,10000.0f);
	
	drawer->enable(InGE_CULL_FACE);
	drawer->cullFace(InGE_FRONT);
	
	drawer->matrixMode(GL_MODELVIEW);
	drawer->loadIdentity();
	
}

int SetupManager::init(int width, int height, int bpp, bool fullscreen){
	int videoFlags=SDL_OPENGL;
	if (fullscreen)
		videoFlags |= SDL_FULLSCREEN;
	const SDL_VideoInfo	*info = NULL;
	
	// Inicializando Subsistema de video da SDL
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cerr << "Falha inicializando SDL video..." << endl;
		return 1;
	}
	
	// Notificando chamada de SDL_Quit ao sair
	atexit(SDL_Quit);

	// Consultando informacao de video
	if(!(info = SDL_GetVideoInfo())){
		cerr << "Falha ao consultar informacao de video..." << endl;
		return 1;
	}

	// Profundidade de cor atual
//	bpp = info->vfmt->BitsPerPixel;


	// Verifica possibilidade de criar surface em hardware
    if(info->hw_available) videoFlags |= SDL_HWSURFACE ;
	else videoFlags |= SDL_SWSURFACE;
		
	// Verifica a possibilidade de aceleracao
	if(info->blit_hw) videoFlags |= SDL_HWACCEL;
	
	// Definindo atributo para OpenGL	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp);
				  
	// Definindo um modo de video
	if(!(g_screen = SDL_SetVideoMode(width, height, bpp, videoFlags))){
		cerr << "Falha ao tentar estabelecer modo de video..." << endl;
		return 1;
	}
	setupOpenGL(width, height);

	return 0;
}

SetupManager *SetupManager::getInstance(){
	if(!m_setupManager) m_setupManager = new SetupManager();
	
	return m_setupManager;
}


SetupManager::SetupManager(){
}

SetupManager::~SetupManager(){
	
}

bool SetupManager::setServer(int port, string scene){
	m_pNetServer = NetServer::getInstance();
	m_pNetServer->openServer( port );
	m_pNetServer->setScene( scene );
}

bool SetupManager::setClient(string name, string ip, int port){
	
 	/*m_pNetCLient->delay(1000); */
	
	m_pNetCLient = NetClient::getInstance();
	m_pNetCLient->startClient();
	
	m_pNetCLient->setName(name);
	m_pNetCLient->connectToServer(ip, port);
	
	if ( m_pNetCLient->getId() == -1) {
		cerr << "ERRO: NAO FOI POSSIVEL CONECTAR" << endl;
		return (1);
	}
	
}

NetClient *SetupManager::getNetClient(){
	return m_pNetCLient;
}

NetServer *SetupManager::getNetServer(){
	return m_pNetServer;
}
