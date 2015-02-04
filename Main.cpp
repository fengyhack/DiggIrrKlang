#include <stdio.h>
#include <stdlib.h>
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") 
#pragma warning(disable:4996)

#define PATHLEN 256

int main(void)
{
	system("color 2e");
	system("title Audio Mixer -- Archieved by IrrKlang");

	printf("Input audio file name:");
	char fileName[PATHLEN] = { 0 };
	scanf("%s", fileName);
	getchar();

	ISoundEngine* engine = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_DEFAULT_OPTIONS);
	if (engine == NULL)
	{
		printf("Failed to create the engine!\n");
		printf("Press ENTER to continue...");
		getchar();
		return -1;
	}

	ISound* sound = engine->play2D(fileName, true, true, false, ESM_AUTO_DETECT, true);
	if (sound == NULL)
	{
		printf("Failed to play \'%s\'\n", fileName);
		printf("Press ENTER to continue...");
		engine->drop();
		getchar();		
		return -2;
	}

	ISoundEffectControl* fx = sound->getSoundEffectControl();
	if (fx == NULL)
	{
		printf("Failed to get sound effect control!\n");
		sound->drop();
		engine->drop();
		getchar();
		return -3;
	}

	float volume = 0.5;
	sound->setVolume(0.8);
	sound->setIsPaused(false);	
	
	bool paused = false;
	bool efx_c = false;
	bool efx_e = false;
	bool efx_d = false;
	char key = 0;
	while (true)
	{
		system("cls");
		printf("------------------------------------------\n");
		printf("| Sound File: \'%s\'\n", fileName);
		printf("------------------------------------------\n");
		if (paused) printf("| P: Resume\n");
		else printf("|  P: Pause\n");
		if (efx_c) printf("| C: Disable Chorus Effect\n");
		else printf("|  C: Enable Chorus Effect\n");
		if (efx_e) printf("| E: Disable Echo Effect\n");
		else printf("|  E: Enable Echo Effect\n");
		if (efx_d) printf("| D: Disable Distortion Effect\n");
		else printf("|  D: Enable Distortion Effect\n");
		printf("| --- Current Volume: %.1f\n", volume);
		printf("| A: Volume +0.1 (max 1.0)\n");
		printf("| B: Volume -0.1 (min 0.1)\n");
		printf("| Q: Stop and Quit\n");
		printf("------------------------------------------\n");
		printf("Input your command:");
		key = getchar();
		getchar();
		if (key == 'q' || key == 'Q') break;
		switch (key)
		{
		case 'p':
		case 'P':
			paused =  !paused;
			sound->setIsPaused(paused);
			break;
		case 'c':
		case 'C':
			efx_c = !efx_c;
			if (efx_c)
			{
				fx->enableChorusSoundEffect();
			}
			else
			{
				fx->disableChorusSoundEffect();
			}
			break;
		case 'e':
		case 'E':
			efx_e = !efx_e;
			if (efx_e)
			{
				fx->enableEchoSoundEffect();
			}
			else
			{
				fx->disableEchoSoundEffect();
			}
			break;
		case 'd':
		case 'D':
			efx_d = !efx_d;
			if (efx_d)
			{
				fx->enableDistortionSoundEffect();
			}
			else
			{
				fx->disableDistortionSoundEffect();
			}
			break;
		case 'a':
		case 'A':
			volume += 0.1f;
			if (volume > 1.0f) volume = 1.0f;
			sound->setVolume(volume);
			break;
		case 'b':
		case 'B':
			volume -= 0.1f;
			if (volume < 0.0f) volume = 0.1f;
			sound->setVolume(volume);
			break;
		default:
			break;
		}
	}

	sound->drop();
	engine->drop();

}