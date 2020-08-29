#include <conio.h> //_getch
#include <stdio.h>
#include <stdlib.h>
#include <irrKlang.h>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

void IrrKlangPlayMusic(const char* pszFileName);

int main(int argc, const char** argv)
{
	try
	{
		IrrKlangPlayMusic("Assets/Background.mp3");
	}
	catch (char* pszExcept)
	{
		puts(pszExcept);
	}
	system("pause");
	return 0;
}

void IrrKlangPlayMusic(const char* pszFileName)
{
	//启动引擎
	ISoundEngine* engine = createIrrKlangDevice();
	if (engine == NULL) throw ("An error ocurred in \'createIrrKlangDevice\'");

	//播放声音
	ISound* music = engine->play2D(pszFileName, true, false, true, ESM_AUTO_DETECT, true);
	if (music == NULL) throw ("An error ocurred in \'play2DMusic\'");

	//音效
	ISoundEffectControl* fx = fx = music->getSoundEffectControl();
	if (fx == NULL) throw("This device or sound does not support sound effects.");
	//激活回响音效	
	fx->enableWavesReverbSoundEffect();

	//让主线程等待使得工作线程可以播放音乐，否则就会一闪而过
	//正常情况下可以在这里进行一些前台工作比如视频渲染
	//与此同时另一线程则用于播放声音
	while (true) 
	{
		char key = _getch();
		if (key == 27) break; // 按下ESC退出循环
	}

	music->drop(); // 释放资源
	engine->drop(); // 撤出引擎
}