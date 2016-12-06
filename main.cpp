//
//  main.cpp
//  essaiAL
//
//  Created by Guillaume on 11/05/2015.
//  Copyright (c) 2015 Guillaume. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>


#include "AL/al.h"
#include "AL/alc.h"

#import <OpenAL/al.h>
#import <OpenAL/alc.h>

#include <sndfile.h>

using namespace std;

ALuint LoadSound(const std::string& Filename)
{
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
        return 0;
    
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);
    vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
        return 0;
    sf_close(File);
    ALenum Format;
    switch (FileInfos.channels)
    {
        case 1 :  Format = AL_FORMAT_MONO16;   break;
        case 2 :  Format = AL_FORMAT_STEREO16; break;
        default : return 0;
    }
    ALuint Buffer;
    alGenBuffers(1, &Buffer);
    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
    
    if (alGetError() != AL_NO_ERROR)
        return 0;
    
    return Buffer;
}

int main(){
    ALCdevice* Device = alcOpenDevice(NULL);
    ALCcontext* Context = alcCreateContext(Device, NULL);
    alcMakeContextCurrent(Context);
        
    ALuint Source[3];
    ALuint buffer = LoadSound("/Users/bonfante/test.wav");
    ALuint buffer2 = LoadSound("/Users/bonfante/test2.wav");
    
    alGenSources(3, Source);
    
    alSourcei(Source[0], AL_BUFFER, buffer);
    alSourcei(Source[1], AL_BUFFER, buffer2);
    alSourcei(Source[2], AL_BUFFER, buffer);
    
    float x0 = -100;
    alSource3f(Source[0], AL_POSITION, x0, 0.0f, 0.0f);
    alSource3f(Source[0], AL_VELOCITY, 2.0f, 0.0f, 0.0f);
    
    alSource3f(Source[1], AL_POSITION, x0*cos(0)/2, 0.0f, x0*sin(0)/100);
    alSourcei(Source[1],AL_LOOPING, AL_TRUE);
    alSource3f(Source[2], AL_POSITION, x0/2, x0, 0.0f);
    
    ALfloat Orientation[] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
    alListenerfv(AL_ORIENTATION, Orientation);

    alSourcePlay(Source[0]);
    ALint source_state;
    
    bool done = false;
    int i = 0;
    while(true){
        i = i + 1;
        alSource3f(Source[0],AL_POSITION, x0 + 0.0001*i,0.0f,0.0f);
        alSource3f(Source[1],AL_POSITION, x0*cos(0.000001*i)/2, 0.0f, x0*sin(0.000001*i)/100);
        alSource3f(Source[2],AL_POSITION, x0/2, x0 + 0.00001*i,0.0f);
        
        
        if (!done){
           alGetSourcei(Source[0], AL_SOURCE_STATE, &source_state);
            if (source_state != AL_PLAYING){
                done = true;
                alSourcePlay(Source[1]);
                alSourcePlay(Source[2]);
            }
        }
    }
    printf("end pos = %f",(x0+ 0.00001*i));
}
