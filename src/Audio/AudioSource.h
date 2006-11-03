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

#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../Math/Vector3.h"
#include "AudioBuffer.h"
#include "../Entities/IEntity.h"

#include <AL/al.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#define MAX_BUFFERS 4
#define BUFFER_SIZE (4096 * 4)

namespace InGE{

class AudioManager;

class AudioSource : public InGE::IEntity {
private:
	ALuint number;

	// ogg vorbis, streaming
	FILE*           oggFile;
	OggVorbis_File  oggStream;
	vorbis_info*    vorbisInfo;
	vorbis_comment* vorbisComment;
	ALenum format;  //marcos- mono ou stereo
	string m_path;

protected:
	AudioSource();

public:
	friend class InGE::AudioManager;
	AudioBuffer *buffer;  // Especifico para OpenAL

	// buffers para streaming
	//AudioBuffer *streambuffer[2];
	ALuint streambuffer[MAX_BUFFERS];

	
	virtual ~AudioSource();

	virtual void setPitch(float pitch);
	virtual float getPitch();
	virtual void setGain(float gain);
	virtual float getGain();
	virtual void setMaximumDistance(float gain);
	virtual float getMaximumDistance();
	virtual void setRolloffFactor(float factor);
	virtual float getRolloffFactor();
	virtual void setReferenceDistance(float distance);
	virtual float getReferenceDistance();
	virtual void setMinimumGain(float gain);
	virtual float getMinimumGain();
	virtual void setMaximumGain(float gain);
	virtual float getMaximumGain();
	virtual void setConeOuterGain(float gain);
	virtual float getConeOuterGain();

	virtual float getConeInnerAngle();
	virtual float getConeOuterAngle();

	virtual unsigned int getBuffersQueued();
	virtual unsigned int getBuffersProcessed();

	/* Estes metodos agora sao herdados de IEntity */
	virtual void setVelocity(const Vector3 &velocity);
	virtual Vector3 getVelocity();
	virtual void setPosition(const Vector3 &position);
	virtual Vector3 getPosition();
	virtual void setDirection(const Vector3 &direction);
	virtual Vector3 getDirection();
	/* */

	virtual void setSourceRelative(bool relative);
	virtual bool getSourceRelative();
	virtual void setLooping(bool loop);
	virtual bool getLooping(); // deprecated. Use isLooping() instead.
	virtual bool isLooping();
	virtual void setBuffer(AudioBuffer &buffer);
	virtual void clearBuffers();
	virtual AudioBuffer *getBuffer();

	virtual bool isPlaying();
	virtual bool isStopped();
	virtual bool isPaused();

	// falta getState

	virtual void play();
	virtual void pause();
	virtual void stop();
	virtual void rewind();
	virtual void queueBuffer(const AudioBuffer &buffer);
	virtual void unqueueBuffer(const AudioBuffer &buffer);
	
	// streaming
	bool playStreaming(string &path);
	bool playStreaming();
	bool stream(ALuint buffer);
	void check();
	bool updateStreaming();
	string errorString(int code);

	// xml
	TiXmlElement *entity2xml();
};

};

#endif // AUDIOSOURCE_H
