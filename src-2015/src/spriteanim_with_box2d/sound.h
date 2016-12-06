#pragma once


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include<string>

using namespace std;


#include <al.h>
#include <alc.h>

#include <sndfile.h>

ALuint LoadSound(const std::string& Filename);
void init_sound();
void play_sound(string source);
void rewind_sound();
