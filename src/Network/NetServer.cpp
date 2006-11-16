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
#include "NetServer.h"



namespace InGE
{

  //defining static class variables...
  NetServer* NetServer::m_pNetServer = NULL;

	NetServer::NetServer() {
		NetControl::startSdlNet();

		m_stopServer = false;
		m_isServerActive = false;
		m_mainThreadReady = false;
		m_pingThreadReady = false;
		m_currentScene = "";
		m_pThreadActiveServer = NULL;
		m_pThreadPingSender = NULL;
		
		UDPsocket m_sock = 0;
	}
	
  void NetServer::broadcast (UDPpacket *incoming , bool toSelf)
  {

    UDPpacket *outPacket = NULL;
    TiXmlDocument* xmlContainer = new TiXmlDocument();
    TiXmlElement* netMsg;
    int msgSource, msgDestination, entSequence;
    char* data = new char[incoming->len];
    string entId = "";

    memcpy(data, incoming->data, incoming->len);

    xmlContainer->Parse( data );

    netMsg = xmlContainer->RootElement();

    netMsg->QueryIntAttribute( "ID", &msgSource );

    if ( netMsg->Attribute("TYPE") == "ENT" )
    {
      entId = netMsg->Attribute( "UNIQUEID" );
      netMsg->QueryIntAttribute( "MSG_SEQ", &entSequence );

      map<string, int>::iterator it;
      it = m_mClientsEntitiesSequence.find(entId);

      if (it == m_mClientsEntitiesSequence.end())
        m_mClientsEntitiesSequence[entId] = 0;

      if ( entSequence < m_mClientsEntitiesSequence[entId] )
      {
        if (data) delete (data);
        if (xmlContainer) delete (xmlContainer);
        return;
      }
      else
      {
        m_mClientsEntitiesSequence[entId] = entSequence;
      }

    }

    outPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

    memcpy (outPacket->data, data, incoming->len);

    outPacket->len = incoming->len;
		
		NetControl::waitForSync();

    for (msgDestination = 0 ; msgDestination < m_vClientsAddress.size(); msgDestination++)
    {

      if ( m_vClientsLife[msgDestination] == true && 
					(msgDestination!=msgSource || toSelf)	)
      {

        outPacket->address.host = m_vClientsAddress[msgDestination].host;
        outPacket->address.port = m_vClientsAddress[msgDestination].port;

        SDLNet_UDP_Send(m_sock , -1 , outPacket);
      }

    }
		
		NetControl::postForSync();

    if (data) delete (data);
    if (xmlContainer) delete (xmlContainer);
    SDLNet_FreePacket(outPacket);

  }

  void NetServer::checkVacancy (UDPpacket *incoming)
  {
    UDPpacket *outPacket;
    TiXmlDocument* xmlContainer = new TiXmlDocument();
    TiXmlElement* netMsg;
    string answer;
    char* data = new char [incoming->len];
    int vacancy;

    outPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

    memcpy (data, incoming->data, incoming->len);

    xmlContainer->Parse( data );
    netMsg = xmlContainer->RootElement();

		NetControl::waitForSync();
		
    for (vacancy = 0; vacancy < m_vClientsAddress.size() && m_vClientsLife[vacancy]; vacancy++);
		
		netMsg->SetAttribute( "ID" , vacancy );
		netMsg->SetAttribute( "TYPE" , "LGNGRA" );
		netMsg->SetAttribute( "SCENE" , m_currentScene );

		answer << *netMsg;

		memcpy (outPacket->data, answer.c_str(), answer.size() + 1);
		outPacket->len = answer.size() + 1;
		outPacket->address = incoming->address;

		SDLNet_UDP_Send (m_sock,-1,outPacket);

		
		
		
    if ( vacancy >= m_vClientsAddress.size() )
    {
      m_vClientsAddress.push_back( incoming->address );
      m_vClientsLife.push_back ( true );
      m_vClientsLastMsg.push_back ( SDL_GetTicks() );
    }
    else
    {
      m_vClientsAddress[vacancy] = incoming->address;
      m_vClientsLife[vacancy] = true;
      m_vClientsLastMsg[vacancy] = ( SDL_GetTicks() );
    }
		
		NetControl::postForSync();
		
		broadcast (outPacket);

    if (data) delete (data);
    if (xmlContainer) delete (xmlContainer);
    SDLNet_FreePacket(outPacket);
  }


int NetServer::activeServer (void *instance ){
	NetServer* pNetServer = (NetServer *) instance;

	UDPpacket *inPacket = NULL;
	TiXmlDocument* xmlContainer = new TiXmlDocument();
	TiXmlElement* netMsg;
	char* data = NULL;
	string msgType;
	int msgSource;

	inPacket = SDLNet_AllocPacket (NetControl::M_PACKET_SIZE);

	while (!pNetServer->m_stopServer){
		pNetServer->m_mainThreadReady = true;
		
		
		//       cout << "NetServer :: AGUARDANDO MENSAGEM" << endl;
		while(!SDLNet_UDP_Recv(pNetServer->m_sock, inPacket)){
			if (pNetServer->m_stopServer)
				break;
			
			pNetServer->checkClientsTimeOut();
			SDL_Delay(NetControl::M_RECEIVER_DELAY); //1/200th of a second
		}

		if (pNetServer->m_stopServer)
			break;

		//       cout << "NetServer :: REBENDO MENSAGEM" << endl;

		if (data) 
			delete (data);
		
		data = new char[inPacket->len];
		memcpy (data, inPacket->data, inPacket->len);

		xmlContainer->Clear();
		xmlContainer->Parse( data );
		netMsg = xmlContainer->RootElement();
// 		cout << "Server: \t" << *netMsg << endl;

		if ( pNetServer->handleMessage(netMsg) ) continue;

		msgType = netMsg->Attribute( "TYPE" );
		netMsg->QueryIntAttribute( "ID" , &msgSource );

		if ( msgType == "LGNREQ" )
		pNetServer->checkVacancy( inPacket );

		if (( msgType == "ENT" ) || (msgType == "RMENT") )
		pNetServer->broadcast( inPacket );

		if ( msgType == "CUS" ) {

			int toSelf;
			netMsg->Attribute( "TOSELF" , &toSelf);
			if (toSelf == 1){
				pNetServer->broadcast( inPacket , true);
			} else {
				pNetServer->broadcast( inPacket , false);
			}
				
			
		}

		if ( msgType == "CLIENT_PONG" ){
// 		cout << "NetServer :: PONG de " << msgSource << endl;
		}
		
		if ( msgType == "BYE" ){
			int id;
	
			pNetServer->broadcast( inPacket );
			netMsg->QueryIntAttribute( "ID", &id );
			pNetServer->m_vClientsLife[id] = false;
		}

		if ( pNetServer->m_vClientsLastMsg.size() > msgSource )
		pNetServer->m_vClientsLastMsg[msgSource] = SDL_GetTicks();
		
		

	}

	SDLNet_FreePacket (inPacket);
	if (xmlContainer) delete (xmlContainer);
	if (data) delete (data);

}


  int NetServer::pingSender (void *instance )
  {
    NetServer* pNetServer = (NetServer*) instance;
    while (!pNetServer->m_stopServer)
    {
			pNetServer->m_pingThreadReady = true;
      pNetServer->sendPing();
      SDL_Delay(NetControl::M_PING_PERIOD);
    }
  }


  void NetServer::sendPing()
  {
    TiXmlElement* pingMsg = new TiXmlElement("InGENetMsg");
    string pingMsgString;
    UDPpacket* pingPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

    pingMsg->SetAttribute( "ID" , -1 );
    pingMsg->SetAttribute( "TYPE" , "SERVER_PING" );

    pingMsgString << *pingMsg;

    memcpy ( pingPacket->data , pingMsgString.c_str() , pingMsgString.size() + 1);
    pingPacket->len = pingMsgString.size() + 1;

    broadcast( pingPacket );

    if (pingMsg) delete (pingMsg);
    SDLNet_FreePacket(pingPacket);
  }


 

  /*NetServer::NetServer(Uint16 port)
  {
  	NetServer();
  	openServer(port);	
  }*/

  void NetServer::openServer(unsigned short int port)
  {
    if(!(m_sock=SDLNet_UDP_Open(port)))
    {
      cerr << "NetServer :: SDLNet_UDP_Open: " << SDLNet_GetError() << endl;
      return;
    }	else
			cout << "NetServer :: Porta " << port << " aberta." << endl;

    m_stopServer = false;

    m_pThreadActiveServer = SDL_CreateThread( activeServer, this );
    m_pThreadPingSender = SDL_CreateThread( pingSender , this);
		
		while (!m_mainThreadReady || !m_pingThreadReady)
			SDL_Delay(333);

		cout << "Servidor aberto na porta " << port << endl;
		
    m_isServerActive = true;

    atexit(warnClientsAboutClosureAtExit);
  }

  void NetServer::setScene (string sceneName)
  {
    m_currentScene = sceneName;
  }

 void NetServer::closeServer() {

    m_stopServer = true;
    SDL_Delay(NetControl::M_THREAD_FINISH_WAIT_TIME);
    warnClientsAboutClosureAtExit();
	 if (m_pThreadActiveServer)
    	SDL_KillThread( m_pThreadActiveServer );
	 if (m_pThreadPingSender)
	 	SDL_KillThread( m_pThreadPingSender );
// 	 if (m_sock != 0)
// 	 	SDLNet_UDP_Close(m_sock);
	 m_vClientsLastMsg.clear();
	 m_vClientsAddress.clear();
	 m_vClientsLife.clear();
	 m_mClientsEntitiesSequence.clear();
	 m_isServerActive = false;
}


void NetServer::checkClientsTimeOut(){

    for (int cIndex = 0; cIndex < m_vClientsLastMsg.size(); cIndex++)
    {
      if (m_vClientsLife[cIndex] &&
          SDL_GetTicks() >
          m_vClientsLastMsg[cIndex] + NetControl::M_CLIENT_TIMEOUT)
      {
        killClient( cIndex );
      }
    }

  }


  void NetServer::killClient( int clientId )
  {
    TiXmlElement* netMsg = new TiXmlElement("InGENetMsg");
    UDPpacket* outPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
    string msgString;

    netMsg->SetAttribute( "ID" , clientId );
    netMsg->SetAttribute( "TYPE" , "TIMEOUT_BYE" );

    msgString << *netMsg;

    memcpy (outPacket->data, msgString.c_str(), msgString.size() + 1);
    outPacket->len = msgString.size() + 1;
    outPacket->address = m_vClientsAddress[clientId];

    broadcast( outPacket );

    m_vClientsLife[clientId] = false;

    SDLNet_FreePacket (outPacket);
  }


  void NetServer::warnClientsAboutClosureAtExit()
  {
    NetServer* pNetServer = NetServer::getInstance();
    UDPpacket* outPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
    TiXmlElement* closureMsg = new TiXmlElement( "InGENetMsg" );
    string closureMsgString;

    closureMsg->SetAttribute( "ID" , -1 );
    closureMsg->SetAttribute( "TYPE" , "SERVER_CLOSED" );

    closureMsgString << *closureMsg;

    memcpy ( outPacket->data , closureMsgString.c_str() , closureMsgString.size() + 1 );
    outPacket->len = closureMsgString.size() + 1;

    pNetServer->broadcast( outPacket );

    SDLNet_FreePacket( outPacket );
    if (closureMsg) delete (closureMsg);
  }


	bool NetServer::handleMessage(TiXmlElement* msg) {
		return false;
	} 
	
	
	bool NetServer::isServerActive() {
		return m_isServerActive;
	}


  NetServer* NetServer::getInstance()
  {
    if (!m_pNetServer)
      m_pNetServer = new NetServer();
    return m_pNetServer;
  }

  NetServer::~NetServer()
{}

}