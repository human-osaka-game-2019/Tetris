#ifndef TITLE_H
#define TITLE_H

#include "DirectX.h"
#include "Main.h"

class Title {
public:

	void Title_Scene();

	enum SCENE_PHASE {
		LOAD,
		PROCESSING,
		RELEASES
	};

private:

	//�E�B���h�E�̃T�C�Y
	FLOAT window_width = 1280;
	FLOAT window_height = 720;

	//�v���g�^�C�v�錾
	void Loading();
	void Process();
	void Release(); 
	
};

#endif