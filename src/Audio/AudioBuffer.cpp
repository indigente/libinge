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

#include <stdlib.h>
#include "AudioBuffer.h"
#include <AL/al.h>
#include <AL/alut.h>
#include <iostream>
#include "AudioManager.h"

using namespace InGE;
using namespace std;

AudioBuffer::AudioBuffer()
{
	alGetError();
	alGenBuffers(1, &number);
	try {
		AudioManager::checkALError();
	} catch (string e) {
		number = 0;
		throw;
	}
}

AudioBuffer::~AudioBuffer()
{
	if (number != 0)
		alDeleteBuffers(1, &number);
}

//void OpenAlBuffer::setData(void *data)=0;
void AudioBuffer::loadFile(char *filename) {
	ALsizei size;
	ALfloat freq;
	ALenum format;
	ALvoid *data;
	ALboolean al_bool;

	alutGetError();
	data = alutLoadMemoryFromFile(filename,&format,&size,&freq);
	if (!data) {
		cerr << "Error while loading file " << filename << endl;
		AudioManager::checkALUTError();
	}
	else {
		alGetError();
		alBufferData(number,format,data,size,(ALsizei)freq);
		AudioManager::checkALError();
		free(data);
	}
}

void AudioBuffer::setData(void *data) {}

unsigned int AudioBuffer::getFrequency() {
	ALint value;
	alGetBufferi(number, AL_FREQUENCY, &value);
	return value;
}
unsigned int AudioBuffer::getBitDepth() {
	ALint value;
	alGetBufferi(number, AL_BITS, &value);
	return value;
}
unsigned int AudioBuffer::getChannels() {
	ALint value;
	alGetBufferi(number, AL_CHANNELS, &value);
	return value;
}
unsigned int AudioBuffer::getSize() {
	ALint value;
	alGetBufferi(number, AL_SIZE, &value);
	return value;
}
