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

#include "AudioListener.h"
#include <AL/al.h>
#include "../Math/Vector3.h"

using namespace InGE;
using namespace InGE;

AudioListener::AudioListener() : IEntity("AudioListener") {
}

AudioListener::~AudioListener() {
}

void AudioListener::setGain(float gain) {
	alListenerf(AL_GAIN, gain);
}
float AudioListener::getGain() {
	ALfloat value;
	alGetListenerf(AL_GAIN, &value);
	return value;
}
void AudioListener::setVelocity(const Vector3 &velocity) {
	alListener3f(AL_VELOCITY, velocity.getX(), velocity.getY(), velocity.getZ());
}

Vector3 AudioListener::getVelocity() {
	ALfloat v[3];
	alGetListenerfv(AL_VELOCITY, v);
	return Vector3(v);
}

void AudioListener::setPosition(const Vector3 &position) {
	alListener3f(AL_POSITION, position.getX(), position.getY(), position.getZ());
}

Vector3 AudioListener::getPosition() {
	ALfloat v[3];
	alGetListenerfv(AL_POSITION, v);
	return Vector3(v);
}

void AudioListener::setDirection(const Vector3 &orientation) {
	alListener3f(AL_ORIENTATION, orientation.getX(), orientation.getY(), orientation.getZ());
}

Vector3 AudioListener::getDirection() {
	ALfloat v[3];
	alGetListenerfv(AL_ORIENTATION, v);
	return Vector3(v);
}

TiXmlElement *AudioListener::entity2xml(){
	// TODO Implementar a serializacao dos 
	// atributos de audio para xml
	
	TiXmlElement* xmlElem = new TiXmlElement("InGENetMsg");
	Vector3 position = getPosition();
	Vector3 direction = getDirection();
	Vector3 velocity = getVelocity();
	
	xmlElem->SetAttribute( "TYPE" , "ENT" );
	xmlElem->SetAttribute( "UNIQUEID" , m_id );
	xmlElem->SetAttribute( "ENTTYPE" , m_type );	
	
	xmlElem->SetDoubleAttribute( "POS_X" , position[0] );
	xmlElem->SetDoubleAttribute( "POS_Y" , position[1] );
	xmlElem->SetDoubleAttribute( "POS_Z" , position[2] );
	
	xmlElem->SetDoubleAttribute( "DIR_X" , direction[0] );
	xmlElem->SetDoubleAttribute( "DIR_Y" , direction[1] );
	xmlElem->SetDoubleAttribute( "DIR_Z" , direction[2] );
	
	xmlElem->SetDoubleAttribute( "VEL_X" , velocity[0] );
	xmlElem->SetDoubleAttribute( "VEL_Y" , velocity[1] );
	xmlElem->SetDoubleAttribute( "VEL_Z" , velocity[2] );	
	
	return xmlElem;	
}
