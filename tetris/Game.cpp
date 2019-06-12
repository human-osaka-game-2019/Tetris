
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
		_T("Game_Block.png"),
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
	for (INT row = 0; row < 20; row++) {

		for (INT col = 0; col < 10; col++) {
			
			exists[row][col] = false;

			if (BlockRow == 3&&row == 19&&row == BlockRow) {
				exists[row][col] = true;
			}
			

			if (exists[row][col] == true) {
				//�ԃu���b�N
				if (color == Red) {
					Block_tu = 0.0f;
					Block_tv = 0.0f;
				}
				//�u���b�N
				else if (color == Blue) {
					Block_tu = 0.25f;
					Block_tv = 00.f;
				}
				//�΃u���b�N
				else if (color == Green) {
					Block_tu = 0.5f;
					Block_tv = 0.0f;
				}
				//���F�u���b�N
				else if (color == Yellow) {
					Block_tu = 0.75;
					Block_tv = 0.0f;
				}
				//���F�u���b�N
				else if (color == White) {
					Block_tu = 0.0f;
					Block_tv = 0.25f;
				}
				//���F�u���b�N
				else if (color == Black) {
					Block_tu = 0.25f;
					Block_tv = 0.25f;
				}
				//���F�u���b�N
				else if (color == Lightblue) {
					Block_tu = 0.75f;
					Block_tv = 0.25f;
				}
			}
			else {
				Block_tu = 0.75f;
				Block_tv = 0.75f;
			}


			CustomVertex GameStage_Vertex[4]{
				{stage_x + stage_block_width * col                    ,stage_y + stage_block_hight * row                    ,0,1,0xffffff,Block_tu,Block_tv},
				{stage_x + stage_block_width + stage_block_width * col,stage_y + stage_block_hight * row                    ,0,1,0xffffff,Block_tu + 0.25,Block_tv},
				{stage_x + stage_block_width + stage_block_width * col,stage_y + stage_block_hight + stage_block_hight * row,0,1,0xffffff,Block_tu + 0.25,Block_tv + 0.25},
				{stage_x + stage_block_width * col                    ,stage_y + stage_block_hight + stage_block_hight * row,0,1,0xffffff,Block_tu,Block_tv + 0.25}
			};

			dx.pD3Device->SetTexture(0, dx.pTexture[GAME_STAGE]);
			dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameStage_Vertex, sizeof(CustomVertex));
		}
	}

	//�d��
	BLOCK_y += 1;
	
	srand((unsigned int)time(NULL));

	//���ɂ���7��ނ̕`��E�^�񒆂Ɉړ�����
	if (BLOCK_y + BLOCK_height >= window_height - 108) {
		//Block_Kind = rand() % 7;
		//BLOCK_x = stage_x + 108;
		BLOCK_y = window_height - 36 - 108;
	}
	
		/*�u���b�N�`��*/

	if (Block_Kind == 0) {
		//L�̃u���b�N
		for (BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 1 && BlockRow < 3) || (BlockRow == 2 && BlockCol < 3 && BlockCol > 0)) {
					
					CustomVertex  GameBlock_Vertex[4]{
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f}
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));

				}
			}
		}
	}
	else if (Block_Kind == 1) {
		//I�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if (BlockCol == 1) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 2) {
		//J�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 2 && BlockRow < 3) || (BlockRow == 2 && BlockCol < 3 && BlockCol >0)) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 3) {
		//S�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 1 && BlockRow == 1) || (BlockCol == 2 && BlockRow == 1) || (BlockCol == 0 && BlockRow == 2) || (BlockCol == 1 && BlockRow == 2)) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 4) {
		//O�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 1 || BlockCol == 2) && (BlockRow == 1 || BlockRow == 2)) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 5) {
		//Z�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 0 && BlockRow == 1) || (BlockCol == 1 && BlockRow == 1) || (BlockCol == 1 && BlockRow == 2) || (BlockCol == 2 && BlockRow == 2)) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};

					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
				}
			}
		}
	}
	else if (Block_Kind == 6) {
		//T�̃u���b�N
		for (INT BlockRow = 0; BlockRow < 4; BlockRow++) {

			for (INT BlockCol = 0; BlockCol < 4; BlockCol++) {
				if ((BlockCol == 0 && BlockRow == 1) || (BlockCol == 1 && BlockRow == 1) || (BlockCol == 2 && BlockRow == 1) || (BlockCol == 1 && BlockRow == 2)) {
					CustomVertex GameBlock_Vertex[4] = {
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,0.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height * BlockRow               ,0,1,0xffffff,1.0f,0.0f},
						{BLOCK_x + BLOCK_width + BLOCK_width * BlockCol,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,1.0f,1.0f},
						{BLOCK_x + BLOCK_width * BlockCol              ,BLOCK_y + BLOCK_height + BLOCK_height * BlockRow,0,1,0xffffff,0.0f,1.0f},
					};
					dx.pD3Device->SetTexture(0, dx.pTexture[GAME_BLOCK]);
					dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, GameBlock_Vertex, sizeof(CustomVertex));
					
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