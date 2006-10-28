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
#ifndef INGENETCONTROL_H
#define INGENETCONTROL_H


#include <iostream>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

/**
#define PACKET_SIZE 2048
#define PACKET_OVERHEAD 48
#define LOGIN_RETRY_DELAY 10
#define RECEIVER_DELAY 10
#define TIMEOUT 15
//TIMEOUT in seconds
#define SYNC_SEND_PERIOD 100
#define THREAD_FINISH_WAIT_TIME 1000
**/

namespace InGE {
using namespace std;

/**
	@author Garou <kdubezerra@gmail.com>
*/
class NetControl{
	private:
		static bool m_isSdlNetOn;
	
	public:
		static const int M_PACKET_SIZE = 2048;
		static const int M_PACKET_OVERHEAD  = 48;
		static const int M_LOGIN_RETRY_DELAY = 10; //LOGIN_RETRY_DELAY in miliseconds
		static const int M_RECEIVER_DELAY = 10; //RECEIVER_DELAY in miliseconds
		static const int M_CLIENT_TIMEOUT = 30000; //CLIENT_TIMEOUT in miliseconds
		static const int M_SERVER_TIMEOUT = 30000; //TIMEOUT in miliseconds
		static const int M_SYNC_SEND_PERIOD = 30;//SYNC_SEND_PERIOD in miliseconds
		static const int M_THREAD_FINISH_WAIT_TIME = 1000; //THREAD_FINISH_WAIT_TIME in miliseconds
		static const int M_DEAD_RECKONING_PERIOD = 20;
		static const int M_PING_PERIOD = (int) (M_SERVER_TIMEOUT / 10);
		
		static SDL_sem* m_pSemNetAndLocalSync;
		
		static void waitForSync();
		static void postForSync();
		
		static void startSdlNet();
		static void quitSdlNet();
	
    NetControl();

    ~NetControl();

};

}

#endif
