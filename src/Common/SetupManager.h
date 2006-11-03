#ifndef STARTER_H_
#define STARTER_H_

#include <SDL/SDL.h>
#include "../Network/NetServer.h"
#include "../Network/NetClient.h"

namespace InGE{
class SetupManager{
	private:
		static SetupManager *m_setupManager;

		void setupOpenGL(int width, int height);
		SetupManager();
		
		NetServer	*m_pNetServer;
		NetClient	*m_pNetCLient;

	public:
		static SetupManager *getInstance();
		~SetupManager();
		
		int init(int width=640, int height=480, int bpp=16, bool fullscreen=true);
		
		//Setup Net
		bool setServer(int port, string scene);
		bool setClient(string name, string ip, int port);
		NetClient *getNetClient();
		NetServer *getNetServer();
		
};

}
#endif /*STARTER_H_*/
