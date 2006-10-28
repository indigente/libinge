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
#ifndef INGENETCLIENT_H
#define INGENETCLIENT_H

#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif

#include <queue>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

#include "../Util/TinyXML/tinyxml.h"
#include "../Util/TinyXML/tinystr.h"

#include "NetControl.h"
#include "NetCustomMessage.h"
#include "../Entities/IEntity.h"
#include "../Entities/EntityFactory.h"

namespace InGE {
	using namespace std;

/**
	@author Garou <kdubezerra@gmail.com>
*/
class NetClient{
	private:
		static NetClient* m_pNetClient;
		
		SDL_Thread* m_pThreadReceiver;
		SDL_Thread* m_pThreadDeadReckoning;
		SDL_Thread* m_pThreadSyncSender;
		SDL_Thread* m_pThreadClientStopper;
			
		bool m_clientIsOn;
		bool m_isConnected;
		bool m_receiverIsOn;
		bool m_syncSenderIsOn;
		bool m_deadReckoningIsOn;
		bool m_threadReceiverReady;
		
		bool m_stopClient;
				
		UDPsocket m_sock;
		IPaddress m_serverAddress;
		int m_myNetId;		
		string m_myNetName;
		string m_currentScene;
		
		SDL_sem* m_pSemEntityValues;
		
		int m_msgSequence;
		
		unsigned int m_lastServerMsg;
		
		queue<NetCustomMessage *> m_qCustomMessageQueue;
		
		vector<IEntity *> m_vMyEntities; //my[x] = minha entidade x
		vector< vector<IEntity *> > m_vOthersEntities; //others[x][y] = entidade y do player x
		vector<string> m_vOthersNames;
		
		static int receiver (void* instance);/** CRITICA **/
		static int deadReckoning (void* instance);/** CRITICA **/
		static int syncSender (void* instance);/** OPCIONAL **/
		static int clientStopper (void* instance); /** thread que monitora a vida do cliente **/
		
		static void disconnectFromServerAtExit();
		
		void sendEntity(IEntity* ent , int EId , int sequence);
		
		void checkOtherPlayer(int id, string& name);
		void rmOtherPlayer(int id);
		
		void checkServerTimeout();
		
		void killAllEntities();
		
		void answerPing();
		
		NetClient();
	public:
		
		static NetClient* getInstance();
		~NetClient();
		
		
		/** INTERFACE PRINCIPAL (DEVE SER CHAMADO NESSA ORDEM) : **/
		
		void startClient(); //abre o socket, basicamente
		
		int connectToServer(string ip_address, unsigned short port); //retorna o ID
		
		void startReceiver(); //inicializa a thread de recebimento
		
		/* PODE-SE ESCOLHER ENTRE ENVIO SINCRONO, ASSINCRONO, OU AMBOS :) */
		void startSyncSender(); //inicializa a thread de envio sincrono
		void asyncSend(); //manda todas as entidades a qq momento
		
		void disconnectFromServer();
		
		void stopEverything(); //para tudo, deixando o client "zerado", como recem-instanciado		
		
		
		/** PEGAR E SETAR ATRIBUTOS E ESTADOS : **/
		
		void setName(std::string name); //o jogador define seu nome na net
		
		int getId(); //retorna a m_myNetId		
		
		string getName(); //retorna o m_myNetName
		
		string getScene(); //retorna o cenario que o servidor lhe deu, quando conectou
		
		bool isConnected(); //retorna m_isConnected
		
		
		/** INTERFACE PARA USO E ENVIO E RECEBIMENTO DE CUSTOM MESSAGES : **/
		
		bool sendCustomMessage (NetCustomMessage* cus_msg , bool toSelf=false);
		
		NetCustomMessage* nextCustomMessage(); //por enquanto, o metodo nao deleta
																	 //a msg, apenas remove do vetor 
		
		
		/** METODOS QUE PROVAVELMENTE TORNEM-SE PRIVADOS : **/
		bool addEntityToNet(IEntity* ent); //verificar pro cara nao inserir duas vezes. 
		bool rmEntityFromNet(IEntity* ent);  //retorna true se removeu, false se por algum motivo nao
		
		
		/** METODOS QUE PROVAVELMENTE TORNEM-SE INEXISTENTES... : **/
		void activateDeadReckoning(); //ativa o deadReckoning
		
    
		
		

};

}

#endif
