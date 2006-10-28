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
#ifndef INGENETSERVER_H
#define INGENETSERVER_H

#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

#include "../Util/TinyXML/tinyxml.h"
#include "../Util/TinyXML/tinystr.h"

#include "NetControl.h"

namespace InGE
{
  using namespace std;
  /**
  	@author Garou <kdubezerra@gmail.com>
  */
  class NetServer
  {
  protected:

    static NetServer* m_pNetServer;

	bool m_mainThreadReady;
	bool m_pingThreadReady;
		
    bool m_isServerActive;

    bool m_stopServer;

    string m_currentScene;

    //thread que rodará para retransmitir os pacotes recebidos em broadcast, EXCETO para a origem
    SDL_Thread* m_pThreadActiveServer;
    SDL_Thread* m_pThreadPingSender;

    //socket que irá enviar e receber os pacotes pela rede
    UDPsocket m_sock;

    //vetor dos clientes, seus endereços e suas respectivas (in)atividades
    vector<IPaddress> m_vClientsAddress;
    vector<bool> m_vClientsLife;
    vector<unsigned int> m_vClientsLastMsg;
    map<string, int> m_mClientsEntitiesSequence;

    //mandar para todos os clientes, o UDPpacket *incoming
    void broadcast (UDPpacket *incoming , bool toSelf=false);

    //verificar se o pedido de login feito atraves do UDPpacket *incoming pode ser atendido
    void checkVacancy (UDPpacket *incoming);

    //função executada pela thread principal da classe
    static int activeServer (void *instance );
    static int pingSender (void *instance );

    void checkClientsTimeOut();

    void sendPing();

    static void warnClientsAboutClosureAtExit();

	virtual bool handleMessage(TiXmlElement* msg);

    NetServer();

  public:
    static NetServer* getInstance();

    void openServer(unsigned short int port);

    bool isServerActive();

    void killClient(int clientId);

    void closeServer();

    //seta o cenario a ser usado
    void setScene (string sceneName);

    ~NetServer();

  };



}

#endif
