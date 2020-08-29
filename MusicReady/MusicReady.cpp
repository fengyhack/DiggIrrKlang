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
	//��������
	ISoundEngine* engine = createIrrKlangDevice();
	if (engine == NULL) throw ("An error ocurred in \'createIrrKlangDevice\'");

	//��������
	ISound* music = engine->play2D(pszFileName, true, false, true, ESM_AUTO_DETECT, true);
	if (music == NULL) throw ("An error ocurred in \'play2DMusic\'");

	//��Ч
	ISoundEffectControl* fx = fx = music->getSoundEffectControl();
	if (fx == NULL) throw("This device or sound does not support sound effects.");
	//���������Ч	
	fx->enableWavesReverbSoundEffect();

	//�����̵߳ȴ�ʹ�ù����߳̿��Բ������֣�����ͻ�һ������
	//��������¿������������һЩǰ̨����������Ƶ��Ⱦ
	//���ͬʱ��һ�߳������ڲ�������
	while (true) 
	{
		char key = _getch();
		if (key == 27) break; // ����ESC�˳�ѭ��
	}

	music->drop(); // �ͷ���Դ
	engine->drop(); // ��������
}