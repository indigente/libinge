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

#include "AudioManager.h"

#include <AL/alut.h>
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "AudioBuffer.h"
#include "AudioSource.h"

using namespace InGE;

AudioManager *AudioManager::instance = 0;

AudioManager::AudioManager()
{
	listener = 0;
	
	alutGetError();	
	alutInit(0, (char **)0);	
	AudioManager::checkALUTError();
}

AudioManager::~AudioManager() {
	alutGetError();	
	alutExit();	
	AudioManager::checkALUTError();
}

AudioManager *AudioManager::getInstance() {
	if (AudioManager::instance == 0)
		AudioManager::instance = new AudioManager();
	return AudioManager::instance;
}

void AudioManager::init(){
	// inicializacao movida para o construtor.
	puts("AudioManager::init() is deprecated and shouldn't be used anymore.");
}

AudioSource *AudioManager::createSource() {
	return new AudioSource();
}

AudioBuffer *AudioManager::createBuffer() {
	return new AudioBuffer();
}

AudioListener *AudioManager::getListener() {
	if (listener == 0)
		listener = new AudioListener();
	return listener;
}

void AudioManager::addStreamingSource(AudioSource *source) {
	streamingSources.push_back(source);
}

void AudioManager::update() {
	bool isActive = false;
	vector<AudioSource *>::iterator it;
	for(it = streamingSources.begin(); it != streamingSources.end(); it++) {
		AudioSource *source = *it;
		isActive = source->updateStreaming();
		if (!isActive) {
			source->stop();
			source->clearBuffers();
			if (!source->getLooping())
				streamingSources.erase(it);
			break;
		}
		if (source->getLooping() && !source->isPlaying()) {
			source->playStreaming();
			break;
		}
	}
}
	
void AudioManager::checkALError() {
	ALenum errcode = alGetError();
	if (errcode != AL_NO_ERROR) {
		switch(errcode)
		{
			case AL_INVALID_NAME:
				throw string("AL_INVALID_NAME: Invalid Name parameter passed to AL call.");
				break;
			case AL_INVALID_ENUM:
				throw string("AL_INVALID_ENUM: Invalid parameter passed to AL call.");
				break;
			case AL_INVALID_VALUE:
				throw string("AL_INVALID_VALUE: Invalid enum parameter value.");
				break;
			case AL_INVALID_OPERATION:
				throw string("AL_INVALID_OPERATION: Illegal call.");
				break;
			case AL_OUT_OF_MEMORY:
				throw string("AL_OUT_OF_MEMORY: No mojo.");
				break;
			default:
				throw string("Unknown OpenAL error.");
		};
	}
}

void AudioManager::checkALUTError() {
	ALenum errcode = alutGetError();
	if (errcode != ALUT_ERROR_NO_ERROR)
		throw string(alutGetErrorString(errcode));
}
	
// void addSource(AudioSource *audioSource){
// 	m_
// }
