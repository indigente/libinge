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

#include "AudioSource.h"

#include <AL/al.h>
#include "../Math/Vector3.h"
#include "../Entities/IEntity.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioManager.h"
#include <stdlib.h>
#include <iostream>



using namespace InGE;
using namespace std;

void erro(string s) {
	cout << s << endl;
	exit(1);
}

AudioSource::AudioSource() : IEntity("AudioSource"){
	alGenSources(1,&number);	
	alSourcef(number, AL_REFERENCE_DISTANCE, 50.0f);
	alSourcef(number, AL_MAX_DISTANCE, 200.0f);

	alGenBuffers(MAX_BUFFERS,streambuffer);
}

AudioSource::~AudioSource(){
	alDeleteSources(1,&number);
	alDeleteBuffers(MAX_BUFFERS, streambuffer);
}

void AudioSource::setBuffer(AudioBuffer &buffer){
    alSourcei(number,AL_BUFFER,((AudioBuffer &)buffer).getNumber());
   	this->buffer = &buffer;
}

AudioBuffer *AudioSource::getBuffer(){
	return buffer;
}

void AudioSource::play(){
	alSourcePlay(number);
}

void AudioSource::stop(){
	alSourceStop(number);
}




void AudioSource::setVelocity(const Vector3 &velocity) {
	alSource3f(number, AL_VELOCITY, velocity.getX(), velocity.getY(), velocity.getZ());
}

Vector3 AudioSource::getVelocity() {
	ALfloat v[3];
	alGetSourcefv(number, AL_VELOCITY, v);
	return Vector3(v);
}

void AudioSource::setPosition(const Vector3 &position) {
	alSource3f(number, AL_POSITION, position.getX(), position.getY(), position.getZ());
}

Vector3 AudioSource::getPosition() {
	ALfloat v[3];
	alGetSourcefv(number, AL_POSITION, v);
	return Vector3(v);
}

void AudioSource::setDirection(const Vector3 &direction) {
	alSource3f(number, AL_DIRECTION, direction.getX(), direction.getY(), direction.getZ());
}

Vector3 AudioSource::getDirection() {
	ALfloat v[3];
	alGetSourcefv(number, AL_DIRECTION, v);
	return Vector3(v);
}

void AudioSource::setGain(float gain) {
	alSourcef(number, AL_GAIN, gain);
}

float AudioSource::getGain() {
	float x;
	alGetSourcef(number, AL_GAIN, &x);
	return x;
}

void AudioSource::setPitch(float pitch){}
float AudioSource::getPitch(){}

void AudioSource::setMaximumDistance(float gain){}
float AudioSource::getMaximumDistance(){}
void AudioSource::setRolloffFactor(float factor){}
float AudioSource::getRolloffFactor(){}
void AudioSource::setReferenceDistance(float distance){}
float AudioSource::getReferenceDistance(){}
void AudioSource::setMinimumGain(float gain){}
float AudioSource::getMinimumGain(){}
void AudioSource::setMaximumGain(float gain){}
float AudioSource::getMaximumGain(){}
void AudioSource::setConeOuterGain(float gain){}
float AudioSource::getConeOuterGain(){}

float AudioSource::getConeInnerAngle(){}
float AudioSource::getConeOuterAngle(){}

unsigned int AudioSource::AudioSource::getBuffersQueued(){}
unsigned int AudioSource::AudioSource::getBuffersProcessed(){}

void AudioSource::setSourceRelative(bool relative){}
bool AudioSource::getSourceRelative(){}
void AudioSource::setLooping(bool loop)
{
	alSourcei(number, AL_LOOPING, loop);
}
bool AudioSource::getLooping() {
	int x;
	alGetSourcei(number, AL_LOOPING, &x);
	return x != 0;
}

bool AudioSource::isPlaying() {
	int x;
	alGetSourcei(number, AL_SOURCE_STATE, &x);
	return x == AL_PLAYING;
}

bool AudioSource::isStopped(){}
bool AudioSource::isPaused(){}

void AudioSource::pause(){}
void AudioSource::rewind(){}
void AudioSource::queueBuffer(const AudioBuffer &buffer){}
void AudioSource::unqueueBuffer(const AudioBuffer &buffer){}

TiXmlElement *AudioSource::entity2xml(){
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

bool AudioSource::playStreaming() {
	playStreaming(m_path);
}

bool AudioSource::playStreaming(string &path) {
	m_path = path;

	//para a musica e libera memoria se ja estiver tocando 
    if (isPlaying()) 
	stop(); 

	// Carrega o arquivo
    int result;       

    if(!(oggFile = fopen(path.c_str(), "rb")))
        ::erro(string("Could not open Ogg file."));
        

    if((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
    {
        fclose(oggFile);
        
        ::erro(string("Could not open Ogg stream. ") + errorString(result));
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);

    if(vorbisInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;

	// toca o arquivo

	for (int i = 0; i < MAX_BUFFERS; i++) {
    	if(!stream(streambuffer[i]))
        	return false;
	}

    alSourceQueueBuffers(this->number, MAX_BUFFERS, streambuffer);

	updateStreaming();

    play();

	AudioManager::getInstance()->addStreamingSource(this);


    return true;
}



bool AudioSource::updateStreaming() {
    int processed;        
    bool active = true;              
              
    alGetSourcei(this->number, AL_BUFFERS_PROCESSED, &processed);
    
     while(processed--)
    {                      
        ALuint buffer;
        
        vorbisInfo = ov_info(&oggStream, -1);
        vorbisComment = ov_comment(&oggStream, -1);       
        

        alSourceUnqueueBuffers(this->number, 1, &buffer);    

        check();

        active =  stream(buffer);

   
        alSourceQueueBuffers(this->number, 1, &buffer);       

        check();

    }
    
    return active;
}

bool AudioSource::stream(ALuint buffer)
{
// 	static int counter = 0;
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while(size < BUFFER_SIZE)
    {
        result = ov_read(&oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
    
        if(result > 0)
            size += result;
        else
            if(result < 0)
                ::erro(string("Result < 0 " + errorString(result)));
            else
                break;
    }
    
    if(size == 0)
        return false;
        
    alBufferData(buffer, format, pcm, size, vorbisInfo->rate); 
    check();
    
    return true;
}

void AudioSource::check()
{
	int error = alGetError();
			
    if(error != AL_NO_ERROR)
     {
      //system("pause");
	  cout << string("OpenAL error was raised.") << endl;
	cout << errorString(error) << endl;
     } 
    
}

string AudioSource::errorString(int code)
{
	char buf[10];
    switch(code)
    {
        case OV_EREAD:
            return string("Read from media.");
        case OV_ENOTVORBIS:
            return string("Not Vorbis data.");
        case OV_EVERSION:
             return string("Vorbis version mismatch.");
        case OV_EBADHEADER:
             return string("Invalid Vorbis header.");
        case OV_EFAULT:
             return string("Internal logic fault (bug or heap/stack corruption.");
        default:
		sprintf(buf,"%d", code);
                return string("Unknown Ogg error.") + string(buf);
    }
    
}

