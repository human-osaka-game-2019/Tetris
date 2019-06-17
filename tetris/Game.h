#ifndef GAME_H
#define GAME_H

#include "DirectX.h"
#include "Main.h"
#include <time.h>

class Game {
public:

	void Game_Scene();

	enum SCENE_PAHSE {
		LOAD,
		PROCESSING,
		RELEASES
	};

	Game::SCENE_PAHSE Phase = Game::LOAD;

private:

	//�E�B���h�E�̃T�C�Y
	FLOAT window_height = 720;
	FLOAT window_width = 1280;

	//�Q�[���X�e�[�W�̈ʒu
	FLOAT stage_x = 460;
	FLOAT stage_y = 0;
	FLOAT stage_width = 360;
	FLOAT stage_height = 720;

	//�X�e�[�W��1�}�X�̑傫��
	FLOAT stage_block_width = 36;
	FLOAT stage_block_hight = 36;

	//�ړ��u���b�N�̈ʒu
	FLOAT block_x = stage_x + 108;
	FLOAT block_y = -144;

	//�u���b�N��1�}�X�̑傫��
	FLOAT block_width = 36;
	FLOAT block_height = 36;
		   
	//�t���[���𐔂���
	INT FrameCount = 0;

	//�u���b�N�̎��
	INT block_kind = 0;

	//�ړ��u���b�N�̏c�Ɖ�
	INT block_row = 0;
	INT block_col = 0;

	//�u���b�N��tu��tv
	FLOAT block_tu = 0.5f;
	FLOAT block_tv = 0.5f;
	
	//�X�e�[�W�̃t���O
	bool exists[20][10];

	//�֐��̃v���g�^�C�v�錾
	void Loading();
	void Process();
	void Release();
	void DrawBlocks();
	void Jugement();

	//
	enum COLOR {
		Back,
		Red,
		Blue,
		Green,
		Yellow,
		White,
		Black,
		Lightblue
	};

	COLOR color = Back;

	//�u���b�N�̎��
	enum BLOCK_KIND {
		L,
		I,
		J,
		S,
		O,
		Z,
		T
	};
};

#endif
