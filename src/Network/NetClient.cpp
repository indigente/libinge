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
#include "NetClient.h"

namespace InGE{

NetClient* NetClient::m_pNetClient = NULL;

int NetClient::receiver (void* instance){ /** CRITICA **/
	NetClient* pNetClient = (NetClient *) instance;

	UDPpacket* in_packet;
	TiXmlDocument* xmlcontainer = new TiXmlDocument();
	TiXmlElement* net_msg;
	string msg_type;
	int msg_id;
	string plyName;
	char* data = NULL;


	in_packet = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

	while (!pNetClient->m_stopClient){
		pNetClient->m_threadReceiverReady = true;
		while(!SDLNet_UDP_Recv(pNetClient->m_sock, in_packet)){
			pNetClient->checkServerTimeout();
			
			if (pNetClient->m_stopClient)
				break;
			
			SDL_Delay(NetControl::M_RECEIVER_DELAY); //  RECEIVER_DELAY/1000 seconds
		}

		if (pNetClient->m_stopClient)
			break;
			
			pNetClient->m_lastServerMsg = SDL_GetTicks();
	
	
		if (data)
			delete (data);

		data = new char[in_packet->len];
		memcpy (data, in_packet->data, in_packet->len);
	
		xmlcontainer->Clear();
		xmlcontainer->Parse( data );
		net_msg = xmlcontainer->RootElement();
	
	
		msg_type = net_msg->Attribute( "TYPE" );
		net_msg->QueryIntAttribute( "ID", &msg_id );
	
		if ( net_msg->Attribute( "PLYNAME" ) )
			plyName = net_msg->Attribute( "PLYNAME" );
		else
			plyName = "unnamed";
	
		NetControl::waitForSync();
		//SDL_SemWait (NetControl::m_pSemNetAndLocalSync);
		SDL_SemWait (pNetClient->m_pSemEntityValues); /** comecando a mexer nas entidades... travar acesso **/
	
	
		if (msg_type == "ENT"){ //nessa situacao, supoe-se que o cliente ja saiba da existencia
			//da origem dessa mensagem, portanto o lugar no vetor ja existe!
			EntityFactory* pEntityFactory = EntityFactory::getInstance();
	
			pNetClient->checkOtherPlayer( msg_id , plyName);
	
			IEntity* newEntity = pEntityFactory->loadEntity( net_msg );
	
			int ent_id;
			net_msg->QueryIntAttribute( "ENTID", &ent_id );
	
			while (pNetClient->m_vOthersEntities[msg_id].size() <= ent_id){
				pNetClient->m_vOthersEntities[msg_id].push_back( NULL );
			}
	
			pNetClient->m_vOthersEntities[msg_id][ent_id] = newEntity;
		}
	
	
		if (msg_type == "RMENT"){
			EntityFactory* pEntityFactory = EntityFactory::getInstance();
			string uniqueId = net_msg->Attribute( "UNIQUEID" );
			int entId;
			net_msg->Attribute( "ENTID" , &entId );
			
			pNetClient->m_vOthersEntities[msg_id][entId] = NULL;
	
			pEntityFactory->rmEntity( pEntityFactory->getEntity( uniqueId ) );
		}
	
	
		if (msg_type == "LGNGRA"){ //arranja um lugar no vetor de outras entidades para o novo vizinho
			pNetClient->checkOtherPlayer( msg_id , plyName );
		}
	
	
		if (msg_type == "BYE"){ //aqui supoe-se que ja exista a posicao msg_id no vector
			pNetClient->rmOtherPlayer( msg_id );
		}
	
	
		if (msg_type == "TIMEOUT_BYE"){ //o servidor informou que o cliente (msg_id) desconectou-se por timeout
			pNetClient->rmOtherPlayer( msg_id );
		}
	
	
		if (msg_type == "CUS"){ //mensagem personalizada
			NetCustomMessage* cus_msg = new NetCustomMessage(net_msg);
			//adiconar *net_msg a um vector (ou outro container) para uso futuro pelo usuario
			pNetClient->m_qCustomMessageQueue.push( cus_msg );
		}
	
	
		if (msg_type == "SERVER_CLOSED"){
			pNetClient->stopEverything();
			break;
		}
			
			
		if (msg_type == "SERVER_PING"){
			pNetClient->answerPing();
		}
	
	
		SDL_SemPost (pNetClient->m_pSemEntityValues); /** terminou de mexer nas entidades... liberar acesso **/
		NetControl::postForSync();
		//SDL_SemPost (NetControl::m_pSemNetAndLocalSync);
	}
	
	SDLNet_FreePacket( in_packet );
	if ( xmlcontainer ) 
		delete ( xmlcontainer );
	
	if ( data ) 
		delete ( data );
	
}



int NetClient::deadReckoning (void* instance){ /** CRITICA **/
	NetClient* pNetClient = (NetClient *) instance;

	while (!pNetClient->m_stopClient){

		SDL_Delay(NetControl::M_DEAD_RECKONING_PERIOD); //faz 50 atualizaÃ§Ãµes por deadReckoning por segundo
	
		for (int player_index = 0; player_index < pNetClient->m_vOthersEntities.size(); player_index++){
			for (int ent_index = 0; ent_index < pNetClient->m_vOthersEntities[player_index].size(); ent_index++){
				SDL_SemWait (pNetClient->m_pSemEntityValues);
				/**
				ATUALIZE A ENTIDADE DE ACORDO COM SEUS DADOS DE TIPO, VELOCIDADE, DIRECAO, ETC...
				**/
				SDL_SemPost (pNetClient->m_pSemEntityValues);
			}
		}
	}
	
	pNetClient->m_deadReckoningIsOn = false;
}



int NetClient::syncSender (void* instance){ /** OPCIONAL **/
	NetClient* pNetClient = (NetClient *) instance;

	while (!pNetClient->m_stopClient){
		SDL_Delay(NetControl::M_SYNC_SEND_PERIOD);
		pNetClient->asyncSend();
	}
	
	pNetClient->m_syncSenderIsOn = false;
}



bool NetClient::addEntityToNet(IEntity* ent){
	if (!m_clientIsOn) {
		cerr << "NetClient::addEntityToNet => ERRO: cliente nao foi startado." << endl;
		return false;
	}


	bool useVacancy = false;
	int MyEIndex;

	if (ent == NULL){
		cerr << "ERRO: A entidade foi removida da memoria antes de ser adicionada a lista do NetClient!!!" << endl;
		return false;
	}

	for (MyEIndex = 0; MyEIndex < m_vMyEntities.size(); MyEIndex++){
		if (ent == m_vMyEntities[MyEIndex]){
			cerr << "NetClient::addEntity => ERRO: a entidade ja foi adicionada a lista do cliente" << endl;
			return false;
		}
		if (m_vMyEntities[MyEIndex] == NULL){
			useVacancy = true;
			break;
		}
	}

	if (useVacancy)
		m_vMyEntities[MyEIndex] = ent;
	else
		m_vMyEntities.push_back(ent);

//     " adicionada na posicao " << MyEIndex << endl;

	return true;
}


bool NetClient::rmEntityFromNet(IEntity* ent){ //rmEntity nao desaloca nada, apenas remove da lista de entidades a serem transmitidas
	int rmIndex;
	bool exists = false;

	if (ent == NULL){
		cerr << "ERRO: A entidade foi removida da memoria antes de ser removida da lista do NetClient!!!" << endl;
		return false;
	}

	for (rmIndex = 0; rmIndex < m_vMyEntities.size(); rmIndex++){
		if (ent == m_vMyEntities[rmIndex]){
			exists = true;
			break;
		}
	}



	if (exists)	{
		TiXmlElement* netMsg = new TiXmlElement("InGENetMsg");
		string netMsgString;
		UDPpacket* outPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
	
		netMsg->SetAttribute( "ID" , m_myNetId );
		netMsg->SetAttribute( "PLYNAME" , m_myNetName );
		netMsg->SetAttribute( "TYPE" , "RMENT" );
		netMsg->SetAttribute( "ENTID" , rmIndex );
		netMsg->SetAttribute( "UNIQUEID" , ent->getId() );
	
		netMsgString << *netMsg;
	
		memcpy  ( outPacket->data , netMsgString.c_str() , netMsgString.size() + 1 );
		outPacket->len = netMsgString.size() + 1;
		outPacket->address = m_serverAddress;
	
		SDLNet_UDP_Send ( m_sock , -1 , outPacket );
	
		SDLNet_FreePacket(outPacket);
	
		if ( netMsg ) 
			delete ( netMsg );
	
		m_vMyEntities[rmIndex] = NULL;
		return true;
	}
	else
		return false;

}


void NetClient::killAllEntities(){
	EntityFactory* pEntityFactory = EntityFactory::getInstance();

	//matando a entidade dos outros
	for (int player_index = 0; player_index < m_vOthersEntities.size(); player_index++){
		for (int ent_index = 0; ent_index < m_vOthersEntities[player_index].size(); ent_index++){
			SDL_SemWait (m_pSemEntityValues);
	
			pEntityFactory->rmEntity( m_vOthersEntities[player_index][ent_index] );
	
			SDL_SemPost (m_pSemEntityValues);
		}
	}

	//matando minhas entidades
	for (int ent_index = 0; ent_index < m_vMyEntities.size(); ent_index++){
		SDL_SemWait (m_pSemEntityValues);
	
		pEntityFactory->rmEntity( m_vMyEntities[ent_index] );
	
		SDL_SemPost (m_pSemEntityValues);
	}
}


void NetClient::asyncSend(){ //manda todas as entidades a qq momento;
	m_msgSequence++;

	if (!m_isConnected){
		cerr << "ERRO: nao pode enviar mensagens quando nao conectado a um servidor!" << endl;
		return;
	}

	for (int MyEIndex = 0; MyEIndex < m_vMyEntities.size(); MyEIndex++){
		if (m_vMyEntities[MyEIndex])
			sendEntity( m_vMyEntities[MyEIndex] , MyEIndex , m_msgSequence);
	}

}


void NetClient::sendEntity(IEntity* ent , int EId , int sequence){
	
	if (!m_isConnected){
		cerr << "NetClient::sendEntity => ERRO: tentando enviar entidade quando desconectado" << endl;
		return;
	}
	
	if (ent == NULL){
		cerr << "NetClient::sendEntity => ERRO: tentando enviar entidade que nao existia mais na memoria" << endl;
		return;
	}

	string msg_string;
	TiXmlElement* net_msg = ent->entity2xml();

	UDPpacket *out_packet;

	net_msg->SetAttribute( "ID" , m_myNetId );
	net_msg->SetAttribute( "PLYNAME" , m_myNetName );
	net_msg->SetAttribute( "ENTID" , EId );
	net_msg->SetAttribute( "ENT_SEQ" , m_msgSequence );

	/**
	PEGA O TIPO DA ENTIDADE E POE EM enttype; --> o proprio metodo ent2xml faz...
	**/

	/**
	PEGA OS ATRIBUTOS DAQUELA ENTIDADE E POE NO XML net_msg; --> o proprio metodo ent2xml faz
	**/

	msg_string << *net_msg;

	out_packet = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

	memcpy (out_packet->data, msg_string.c_str(), msg_string.size() + 1);

	out_packet->address = m_serverAddress;
	out_packet->len = msg_string.size() + 1;

	SDLNet_UDP_Send(m_sock,-1,out_packet);

	SDLNet_FreePacket(out_packet);

	delete (net_msg);
}


void NetClient::startClient(){
	if (m_clientIsOn) return;
	
	if( !(m_sock=SDLNet_UDP_Open(0)) ){
		cout << "NetClient :: SDLNet_UDP_Open: " << SDLNet_GetError() << endl;
		return;
	}
	
	m_stopClient = false;
	m_pThreadClientStopper = SDL_CreateThread( clientStopper , this );

	m_pSemEntityValues = SDL_CreateSemaphore(1);
	m_clientIsOn = true;

}

void NetClient::setName(std::string name){
	m_myNetName = name;
}


int NetClient::connectToServer(string ip_address, unsigned short port){
	if (m_isConnected) return m_myNetId;

	if (!m_clientIsOn){
		cerr << "ERRO: eh necessario startar o client antes de conectar-se a um servidor" << endl;
		return -1;
	}

	TiXmlDocument* xmlcontainer = new TiXmlDocument();
	TiXmlElement* net_msg = new TiXmlElement("InGENetMsg");
	TiXmlElement* server_answer;
	string msg_string;
	string msg_type;
	UDPpacket* out_packet = NULL;
	UDPpacket* in_packet = NULL;
	char* data = NULL;
	int waitForAnswerRetries = NetControl::M_SERVER_TIMEOUT / NetControl::M_LOGIN_RETRY_DELAY; //TIMEOUT

	SDLNet_ResolveHost(&m_serverAddress, ip_address.c_str(), port);
	
	cout << "Client: tentando conectar no ip " << ip_address << ", na porta " << port << "." << endl;

	out_packet = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

	net_msg->SetAttribute( "ID", -1 );
	net_msg->SetAttribute( "PLYNAME", m_myNetName );
	net_msg->SetAttribute( "TYPE", "LGNREQ" );

	msg_string << *net_msg;

	memcpy (out_packet->data, msg_string.c_str(), msg_string.size() + 1);
	out_packet->len = msg_string.size() + 1;
	out_packet->address = m_serverAddress;

	SDLNet_UDP_Send(m_sock,-1,out_packet);


	in_packet=SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
	
	cout << "Client: esperando por resposta do servidor." << endl;

	while(!SDLNet_UDP_Recv(m_sock, in_packet)){
		if (waitForAnswerRetries <= 0) 
			return -1;
		
		waitForAnswerRetries--;
		SDL_Delay(NetControl::M_LOGIN_RETRY_DELAY); // LOGIN_RETRY_DELAY/1000 second
	}

	data = new char[in_packet->len];
	memcpy (data, in_packet->data, in_packet->len);

	xmlcontainer->Clear();
	xmlcontainer->Parse( data );

	server_answer = xmlcontainer->RootElement();


	msg_type = server_answer->Attribute( "TYPE" );

	int returnedId;

	if ( msg_type == "LGNGRA" ){
		server_answer->QueryIntAttribute( "ID", &m_myNetId );
		m_isConnected = true;
		returnedId = m_myNetId;
		m_currentScene = server_answer->Attribute( "SCENE" );
	}
	else
		returnedId = -1;

	SDLNet_FreePacket(out_packet);
	SDLNet_FreePacket(in_packet);
	if (xmlcontainer)
		delete (xmlcontainer);
	if (net_msg)
		delete (net_msg);


	NetClient* pNetClient = getInstance();
	atexit(disconnectFromServerAtExit);

	return returnedId;

}


void NetClient::startReceiver(){
	if (m_receiverIsOn) return;

	if (!m_isConnected){
		cerr << "ERRO: eh necessario conectar-se antes de receber pacotes do servidor..." << endl;
		return;
	}

	m_pThreadReceiver = SDL_CreateThread( receiver, this );
	
	while (!m_threadReceiverReady)
		SDL_Delay(333);
	
	m_receiverIsOn = true;
}


void NetClient::startSyncSender(){
	if (m_syncSenderIsOn) return;

	if (!m_isConnected){
		cerr << "ERRO: eh necessario conectar-se antes de enviar pacotes ao servidor..." << endl;
		return;
	}

	m_pThreadSyncSender = SDL_CreateThread( syncSender, this);
	m_syncSenderIsOn = true;
}


void NetClient::activateDeadReckoning(){
	if (m_deadReckoningIsOn) return;

	m_pThreadDeadReckoning = SDL_CreateThread ( deadReckoning, this);
	m_deadReckoningIsOn = true;
}


void NetClient::stopEverything(){
	m_stopClient = true;
}


int NetClient::getId(){ //retorna a m_myNetId
	return m_myNetId;
}


string NetClient::getName(){ //retorna o m_myNetName
	return m_myNetName;
}


bool NetClient::isConnected(){ //retorna m_isConnected
	return m_isConnected;
}


bool NetClient::sendCustomMessage (NetCustomMessage* cus_msg , bool toSelf){
	if (!m_isConnected){
		cerr << "ERRO: nao eh possivel enviar mensagens desconectado." << endl;
		return false;
	}

	cus_msg->setMandatoryAttributes( m_myNetId , m_myNetName );
	
	if(toSelf)
		cus_msg->setAttribute( "TOSELF" , 1 );
	else
		cus_msg->setAttribute( "TOSELF" , 0 );

	string cus_msg_string;
	cus_msg->toString( cus_msg_string );

	if (cus_msg_string.size() > (NetControl::M_PACKET_SIZE - NetControl::M_PACKET_OVERHEAD) ){
		cerr << "ERRO: sMensagem excede " << (NetControl::M_PACKET_SIZE - NetControl::M_PACKET_OVERHEAD) << " caracteres. Nao pode ser enviada" << endl;
		return false;
	}

	UDPpacket* out_packet = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);

	memcpy (out_packet->data, cus_msg_string.c_str(), cus_msg_string.size() + 1);
	out_packet->len = cus_msg_string.size() + 1;
	out_packet->address = m_serverAddress;

	SDLNet_UDP_Send(m_sock,-1,out_packet);

	SDLNet_FreePacket(out_packet);
}


void NetClient::checkOtherPlayer(int id, string& name){
	vector<IEntity *> newvector;

//     cout << "NetClient::checkOtherPlayer => comecando o metodo" << endl;

	while (m_vOthersEntities.size() <= id)
		m_vOthersEntities.push_back(newvector);

	while (m_vOthersNames.size() <= id)
		m_vOthersNames.push_back("");

	m_vOthersNames[id] = "unnamed";

//     cout << "NetClient::checkOtherPlayer => terminou o metodo" << endl;
}

void NetClient::rmOtherPlayer(int id) {
	if (m_vOthersEntities.size() <= id || m_vOthersNames.size() <= id){
		cerr << "ERRO: nao pode ser removido OtherPlayer, pois sua id eh invalida" << endl;
		return;
	}

	for (int eIndex = 0; eIndex < m_vOthersEntities[id].size(); eIndex++)	{
		EntityFactory* pEntityFactory = EntityFactory::getInstance();
		
		if (m_vOthersEntities[id][eIndex]) {
			string eUniqueId = m_vOthersEntities[id][eIndex]->getId();
			pEntityFactory->rmEntity( pEntityFactory->getEntity(eUniqueId) );
		}
	
	}

	m_vOthersEntities[id].clear();
	m_vOthersNames[id] = "";

	if (m_vOthersEntities.size() == id + 1)
		m_vOthersEntities.erase (m_vOthersEntities.end());

	if (m_vOthersNames.size() == id + 1)
		m_vOthersNames.erase (m_vOthersNames.end());
	
}

NetCustomMessage* NetClient::nextCustomMessage(){ //apenas tira o ponteiro da fila
	if  (!m_clientIsOn)	{
		cerr << "NetClient::nextCustomMessage => ERRO: cliente precisa ser startado." << endl;
		return NULL;
	}
	
	NetControl::waitForSync();
	
	if (m_qCustomMessageQueue.empty()) {
		NetControl::postForSync();
		return NULL;
	}
	
	NetCustomMessage* msg = m_qCustomMessageQueue.front();

	m_qCustomMessageQueue.pop(); /** ISSO CAUSA SEGMENTATION FAULT???   N A O ! ! !**/
	
	NetControl::postForSync();

	return msg;
}

string NetClient::getScene(){
	if (!m_isConnected){
		cerr << "NetClient::getScene => ERRO: cliente nao esta conectado. Nao ha cenario." << endl;
		return "";
	}

	return m_currentScene;
}

void NetClient::disconnectFromServer(){
	if (!m_isConnected) return;
	//manda mensagem de desconexao
	string msg_string;
	TiXmlElement* net_msg = new TiXmlElement("InGENetMsg");
	UDPpacket *out_packet;

	net_msg->SetAttribute( "ID" , m_myNetId );
	net_msg->SetAttribute( "PLYNAME" , m_myNetName );
	net_msg->SetAttribute( "TYPE" , "BYE" );

	msg_string << *net_msg;
	out_packet = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
	memcpy (out_packet->data, msg_string.c_str(), msg_string.size() + 1);
	out_packet->address = m_serverAddress;
	out_packet->len = msg_string.size() + 1;

	SDLNet_UDP_Send(m_sock,-1,out_packet);

	SDLNet_FreePacket(out_packet);
	if (net_msg) 
		delete (net_msg);

	m_myNetId = -1;
	m_isConnected = false;
}

void NetClient::disconnectFromServerAtExit(){
	m_pNetClient->disconnectFromServer();
}

NetClient* NetClient::getInstance(){
	if (!m_pNetClient)
		m_pNetClient = new NetClient();
	
	return m_pNetClient;
}

NetClient::NetClient(){ // rever isso -> NetControl.cpp?
	NetControl::startSdlNet();

	m_pThreadReceiver = NULL;
	m_pThreadDeadReckoning = NULL;
	m_pThreadSyncSender = NULL;
	m_pThreadClientStopper = NULL;

	m_clientIsOn = false;
	m_receiverIsOn = false;
	m_syncSenderIsOn = false;
	m_isConnected = false;
	m_deadReckoningIsOn = false;
	m_threadReceiverReady = true;

	m_currentScene = "";

	m_stopClient = false;

	m_pSemEntityValues = NULL;

	m_msgSequence = 0;

	m_sock = NULL;
	m_myNetId = -1;
	m_myNetName = "Unnamed";
}
	
	
int NetClient::clientStopper (void* instance) {
	NetClient* pNetClient = (NetClient*) instance;
	
	while (!pNetClient->m_stopClient)
		SDL_Delay (1000);
	
	SDL_Delay ( NetControl::M_THREAD_FINISH_WAIT_TIME );

	if (pNetClient->m_deadReckoningIsOn){
		SDL_KillThread( pNetClient->m_pThreadDeadReckoning );
		pNetClient->m_deadReckoningIsOn = false;
	}

	if (pNetClient->m_syncSenderIsOn){
		SDL_KillThread( pNetClient->m_pThreadSyncSender );
		pNetClient->m_syncSenderIsOn = false;
	}

	if (pNetClient->m_receiverIsOn){
		SDL_KillThread( pNetClient->m_pThreadReceiver );
		pNetClient->m_receiverIsOn = false;
		
		SDL_SemPost (pNetClient->m_pSemEntityValues); /** terminou de mexer nas entidades... liberar acesso **/
		NetControl::postForSync(); /** terminou de mexer nas entidades. pode liberar para o SceneManager::update() **/
	}

	if (pNetClient->m_isConnected)
		pNetClient->disconnectFromServer();

	pNetClient->killAllEntities();
	
	if (pNetClient->m_clientIsOn){
		SDLNet_UDP_Close(pNetClient->m_sock);

		if (pNetClient->m_pSemEntityValues != NULL){
			SDL_DestroySemaphore(pNetClient->m_pSemEntityValues);
			pNetClient->m_pSemEntityValues = NULL;
		}

		pNetClient->m_clientIsOn = false;
	}

	//PIPOCA todas as entidades um dia instanciadas		
	/**
	REMOVER  T O D A S  AS ENTIDADES DO JOGO[?]
		**/

	//limpar lista de entidades
	pNetClient->m_vMyEntities.clear();
	pNetClient->m_vOthersNames.clear();
	for (int vRunner = 0; vRunner < pNetClient->m_vOthersEntities.size(); vRunner++){
		pNetClient->m_vOthersEntities[vRunner].clear();
	}

	//limpar fila de NetCustomMessages recebidas
	while ( !pNetClient->m_qCustomMessageQueue.empty() ){
		delete ( pNetClient->m_qCustomMessageQueue.front() );
		pNetClient->m_qCustomMessageQueue.pop();
	}
}
	
	
void NetClient::checkServerTimeout() {
	if (SDL_GetTicks() > m_lastServerMsg + NetControl::M_SERVER_TIMEOUT) {
		cout << "NetClient :: SERVIDOR PARECE ESTAR INATIVO. TIMEOUT." << endl;
		stopEverything();
	}
}
	
	
void NetClient::answerPing() {
	TiXmlElement* pongMsg = new TiXmlElement("InGENetMsg");
	string pongMsgString;
	UDPpacket* pongPacket = SDLNet_AllocPacket(NetControl::M_PACKET_SIZE);
	
	pongMsg->SetAttribute( "ID" , m_myNetId );
	pongMsg->SetAttribute( "PLYNAME" , m_myNetName );
	pongMsg->SetAttribute( "TYPE" , "CLIENT_PONG" ),
	
	pongMsgString << *pongMsg;
	
	memcpy (pongPacket->data , pongMsgString.c_str() , pongMsgString.size() + 1);
	pongPacket->len = pongMsgString.size() + 1;
	pongPacket->address = m_serverAddress;
	
	SDLNet_UDP_Send(m_sock , -1 , pongPacket);
			
	SDLNet_FreePacket(pongPacket);
	if (pongMsg)
		delete (pongMsg);
}


NetClient::~NetClient(){ // rever isso -> NetControl.cpp?
	NetControl::quitSdlNet();
}




}
