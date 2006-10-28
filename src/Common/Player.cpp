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
#include "Player.h"

using namespace InGE;

using namespace std;

/**
 * Contrutor de Player
 * @param PhysicalWorld *pw -Mundo Fisico onde o Corpo ser�inserido
 * @param  IModel *pModel - Modelo do Player
 * @param  IScene *pScene - Scenario onde o Player ser�inserido
 * @param  ICamera *pCamera - Camera do Player
 */
Player::Player(Avatar *avatar, ICamera *pCamera){
	m_pAvatar = avatar;
	m_pAudioListener = AudioManager::getInstance()->getListener();
	m_pStream = NULL;
	
	
	if (pCamera){
		m_pCamera = pCamera;
	} else {
		if ( m_pAvatar ){
			m_pCamera = m_pAvatar->getCamera();
		} else {
			m_pCamera = NULL;
		}
	}
}


/**
 * Destrutor de Player
 */
Player::~Player(){
	if (m_pAudioListener)
		EntityFactory::getInstance()->rmEntity( m_pAudioListener );
	if (m_pAvatar)
		EntityFactory::getInstance()->rmEntity( m_pAvatar );
	if (m_pCamera)
		EntityFactory::getInstance()->rmEntity( m_pCamera );
	if (m_pStream)
		EntityFactory::getInstance()->rmEntity( m_pStream );
}



void Player::update(){//FIXME: Vai bugar se a camera do player for diferente da do avatar

	if (m_pCamera){
		if ( m_pAudioListener )
			m_pAudioListener->setPosition( m_pCamera->getPosition() );
		
		if ( m_pStream )
			m_pStream->setPosition( m_pCamera->getPosition() );
	}
}

void Player::setAvatar(Avatar *pAvatar){
	if (pAvatar)
		m_pAvatar = pAvatar;
}
Avatar *Player::getAvatar(){
	return m_pAvatar;
}

void Player::setAudioListener(AudioListener *pListener){
	if (pListener)
		m_pAudioListener = pListener;
}

AudioListener *Player::getAudioListener(){
	return m_pAudioListener;

}

void Player::setCamera(ICamera *pCamera){
	if (pCamera)
		m_pCamera = pCamera;
}

ICamera *Player::getCamera(){
	return m_pCamera;
}

void Player::rotate(float angle, Vector3 &axis){
	if (m_pAvatar->getCamera() == m_pCamera){
		m_pAvatar->rotate(angle, axis);
	} else {
		m_pCamera->rotate( angle, axis );
	}
}

void Player::setStream(AudioSource *stream){
	if (!stream) return;
	
	m_pStream = stream;
	m_pStream->setPosition( m_pAvatar->getPosition() );
}

AudioSource *Player::getStream(){
	return m_pStream;
}
