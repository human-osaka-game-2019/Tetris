#include "Game.h"

Game::SCENE_PAHSE Phase = Game::LOAD;

//�Q�[���̃t�F�[�Y�̈ړ�
void Game::Game_Scene() {

	switch (Phase) {
	case LOAD:
		Loading();
		break;
	case PROCESSING:
		Process();
		break;
	case RELEASES:
		Release();
		Phase = LOAD;
		break;
	}
}

//�Q�[���̃e�N�X�`���̓ǂݍ���
void Game::Loading() {
	D3DXCreateTextureFromFile(
		dx.pD3Device,
		_T("Game_Back.png"),
		&dx.pTexture[GAME_BACK]
	);
	D3DXCreateTextureFromFile(
		dx.pD3Device,
		_T("Game_Stage.png"),
		&dx.pTexture[GAME_STAGE]
	);
	D3DXCreateTextureFromFile(
		dx.pD3Device,
		_T("Game_Block.png"),
		&dx.pTexture[GAME_BLOCK]
	);
	Phase = PROCESSING;
}

//�Q�[���̕`��Ɠ���
void Game::Process() {


	if (dx.GetKeyState(DIK_UP)) {

		BLOCK_y -= 36;

	}
	//���ړ�
	if (dx.GetKeyState(DIK_DOWN)) {

		BLOCK_y += 36;

	}
	//�E�ړ�
	if (dx.GetKeyState(DIK_RIGHT)) {

		BLOCK_x += 36;

	}
	//���ړ�
	if (dx.GetKeyState(DIK_LEFT)) {

		BLOCK_x -= 36;

	}

	//�Q�[�����̔w�i�`��
	dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BACK]);
	dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBack_Vertex, sizeof(CustomVertex));


	//�X�e�[�W�`��
	for (INT row = 0; row <= 20; row++) {

		for (INT col = 0; col <= 10; col++) {

			CustomVertex GameStage_Vertex[4]{
				{stage_x + stage_block_width * col                    ,stage_y + stage_block_hight * row                    ,0,1,0xffffff,0.0f,0.0f},
				{stage_x + stage_block_width + stage_block_width * col,stage_y + stage_block_hight * row                    ,0,1,0xffffff,1.0f,0.0f},
				{stage_x + stage_block_width + stage_block_width * col,stage_y + stage_block_hight + stage_block_hight * row,0,1,0xffffff,1.0f,1.0f},
				{stage_x + stage_block_width * col                    ,stage_y + stage_block_hight + stage_block_hight * row,0,1,0xffffff,0.0f,1.0f}
			};

			dx.pD3Device->SetTexture(0, dx.pTexture[GAME_STAGE]);
			dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameStage_Vertex, sizeof(CustomVertex));
		}
	}


	BLOCK_y += 1;
	
	srand((unsigned int)time(NULL));

	if (BLOCK_y + BLOCK_height >= window_height) {
		Block_Kind = rand() % 7;
		BLOCK_x = stage_x + 108;
		BLOCK_y = 0;
	}
	
		/*�u���b�N�`��*/

	if (Block_Kind == 0) {
		//L�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 1 && row < 3) || (row == 2 && col < 3 && col > 0)) {
					CustomVertex GameBlock_L_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};
					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_L_Vertex, sizeof(CustomVertex));
				}
			}
		}

	}
	else if (Block_Kind == 1) {
		//I�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if (col == 1) {
					CustomVertex GameBlock_I_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_I_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 2) {
		//J�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 2 && row < 3) || (row == 2 && col < 3 && col >0)) {
					CustomVertex GameBlock_J_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_J_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 3) {
		//S�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 1 && row == 1) || (col == 2 && row == 1) || (col == 0 && row == 2) || (col == 1 && row == 2)) {
					CustomVertex GameBlock_S_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_S_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 4) {
		//O�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 1 || col == 2) && (row == 1 || row == 2)) {
					CustomVertex GameBlock_O_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_O_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 5) {
		//Z�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 0 && row == 1) || (col == 1 && row == 1) || (col == 1 && row == 2) || (col == 2 && row == 2)) {
					CustomVertex GameBlock_Z_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Z_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 6) {
		//T�̃u���b�N
		for (INT row = 0; row < 4; row++) {

			for (INT col = 0; col < 4; col++) {
				if ((col == 0 && row == 1) || (col == 1 && row == 1) || (col == 2 && row == 1) || (col == 1 && row == 2)) {
					CustomVertex GameBlock_T_Vertex[4] = {
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height * row               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * col,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * col              ,BLOCK_y + BLOCK_height + BLOCK_height * row,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_T_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}




	if (dx.GetKeyState(DIK_RETURN)) {
		Phase = RELEASES;
	}
}

//�Q�[���̃e�N�X�`���̉��
void Game::Release() {
	dx.pTexture[GAME_BACK]->Release();
	dx.pTexture[GAME_BACK] = nullptr;
	dx.pTexture[GAME_STAGE]->Release();
	dx.pTexture[GAME_STAGE] = nullptr;
	dx.pTexture[GAME_BLOCK]->Release();
	dx.pTexture[GAME_BLOCK] = nullptr;
	scene = RESULT;
}
