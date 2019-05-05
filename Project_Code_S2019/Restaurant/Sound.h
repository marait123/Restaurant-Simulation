#pragma once
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
class Sound
{
public:
	Sound(void);
	static void SoundBox();
	~Sound(void);
};

