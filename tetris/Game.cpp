
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
		&dx.pTexture[GAME_BLOCK]
	);

	//�e�g���~�m�������_��
	srand((unsigned int)time(NULL));

	//����������֐��ɂ���
	for (INT row = 0; row < 20; row++) {
		for (INT col = 0; col < 10; col++) {
			exists[row][col] = false;
		}
	}

	Phase = PROCESSING;
}

//�Q�[���̕`��Ɠ���
void Game::Process() {

	FrameCount++;

	
	//��u�ŉ��ɗ��Ƃ�����
	if (dx.KeyState[DIK_UP] == dx.PRESS) {

		block_y -= 36;

	}
	//���ړ�
	if (dx.KeyState[DIK_DOWN] == dx.PRESS) {

		block_y += 36;

	}
	//�E�ړ�
	if (dx.KeyState[DIK_RIGHT] == dx.PRESS) {

		block_x += 36;

	}
	//���ړ�
	if (dx.KeyState[DIK_LEFT] == dx.PRESS) {

		block_x -= 36;

	}

	//�Q�[�����̔w�i�`��
	Draw(0, 0, 0.0f, 0.0f, window_width, window_height, 1.0f, 1.0f, GAME_BACK);
	
	//�X�e�[�W�`��
	for (INT row = 0; row < 20; row++) {

		for (INT col = 0; col < 10; col++) {
			
			switch(color){

			case Back:
				block_tu = 0.75f;
				block_tv = 0.75f;
				exists[row][col] = false;
				break;
			case Red:
				block_tu = 0.0f;
				block_tv = 0.0f;
				exists[row][col] = true;
				break;
			case Blue:
				block_tu = 0.25f;
				block_tv = 0.0f;
				exists[row][col] = true;
				break;
			case Green:
				block_tu = 0.5f;
				block_tv = 0.0f;
				exists[row][col] = true;
				break;
			case Yellow:
				block_tu = 0.75f;
				block_tv = 0.0f;
				exists[row][col] = true;
				break;
			case White:
				block_tu = 0.0f;
				block_tv = 0.25;
				exists[row][col] = true;
				break;
			case Black:
				block_tu = 0.25f;
				block_tv = 0.25f;
				exists[row][col] = true;
				break;
			case Lightblue:
				block_tu = 0.75f;
				block_tv = 0.25f;
				exists[row][col] = true;
				break;
			default:
				block_tu = 0.75f;
				block_tv = 0.75f;
				exists[row][col] = false;
				break;
			}
			//�񎟌��z��ɂ��A�w�i�ɔ��f�������Ă���u���b�N������������Ă���


			//���W�̓����������\���̂����
			Draw(stage_x + stage_block_width * col, stage_y + stage_block_hight * row, block_tu, block_tv, stage_block_width, stage_block_hight,0.25f,0.25f, GAME_BLOCK);

		}
	}

	//�����蔻��
	Jugement();

	//�u���b�N�`��
	DrawBlocks();

	//�d��
	if (FrameCount == 60){
		// 1�b������
		FrameCount = 0;
		block_y += 36;
	}

	//���ɂ���7��ނ̕`��E�^�񒆂Ɉړ�����
	if (block_y + block_height >= window_height - 36) {

		switch (block_kind) {
		case L: 
			color = Red;
			break;
		case I:
			color = Blue;
			break;
		case J:
			color = Green;
			break;
		case S:
			color = Yellow;
			break;
		case O:
			color = White;
			break;
		case Z:
			color = Black;
			break;
		case T:
			color = Lightblue;
		}
		block_kind = rand() % 7;
		block_x = stage_x + 108;
		block_y = -144;
	}

	//debug�p
	if (dx.KeyState[DIK_RETURN] == dx.PRESS) {
		Phase = RELEASES;
	}
}

//�Q�[���̃e�N�X�`���̉��
void Game::Release() {
	//�u���b�N�ʒu�̏�����
	block_x = stage_x + 108;
	block_y = -144;

	//�e�N�X�`���̊J��
	dx.pTexture[GAME_BACK]->Release();
	dx.pTexture[GAME_BACK] = nullptr;
	dx.pTexture[GAME_BLOCK]->Release();
	dx.pTexture[GAME_BLOCK] = nullptr;

	//���U���g�V�[����
	scene = RESULT;
}

void Game::DrawBlocks() {

	/*�u���b�N�`��*/

	if (block_kind == L) {
		//L�̃u���b�N
		for (block_row = 0; block_row < 4; block_row++) {

			for (block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 1 && block_row < 3) || (block_row == 2 && block_col < 3 && block_col > 0)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.0f, 0.0f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);
					
				}
			}
		}
	}
	else if (block_kind == I) {
		//I�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if (block_col == 1) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.25f, 0.0f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);

				}
			}
		}
	}
	else if (block_kind == J) {
		//J�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 2 && block_row < 3) || (block_row == 2 && block_col < 3 && block_col >0)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.5f, 0.0f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);
				}
			}
		}
	}
	else if (block_kind == S) {
		//S�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 1 && block_row == 1) || (block_col == 2 && block_row == 1) || (block_col == 0 && block_row == 2) || (block_col == 1 && block_row == 2)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.75f, 0.0f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);

				}
			}
		}
	}
	else if (block_kind == O) {
		//O�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 1 || block_col == 2) && (block_row == 1 || block_row == 2)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.0f, 0.25f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);

				}
			}
		}
	}
	else if (block_kind == Z) {
		//Z�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 0 && block_row == 1) || (block_col == 1 && block_row == 1) || (block_col == 1 && block_row == 2) || (block_col == 2 && block_row == 2)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.25f, 0.25f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);

				}
			}
		}
	}
	else if (block_kind == T) {
		//T�̃u���b�N
		for (INT block_row = 0; block_row < 4; block_row++) {

			for (INT block_col = 0; block_col < 4; block_col++) {
				if ((block_col == 0 && block_row == 1) || (block_col == 1 && block_row == 1) || (block_col == 2 && block_row == 1) || (block_col == 1 && block_row == 2)) {

					Draw(block_x + block_width * block_col, block_y + block_height * block_row, 0.75f, 0.25f, block_width, block_height, 0.25f, 0.25f, GAME_BLOCK);

				}
			}
		}
	}
}

void Game::Jugement() {

	//�����蔻��E���EL
	if (block_x <= stage_x - stage_block_width && (block_kind == L || block_kind == I || block_kind == J || block_kind == O)) {
		block_x = stage_x - stage_block_width;
	}
	else if (block_x <= stage_x && (block_kind == S || block_kind == Z || block_kind == T)) {
		block_x = stage_x;
	}

	//�����蔻��E�E
	if (block_x >= (stage_x + stage_width) - stage_block_width * 3 && block_kind != I) {
		block_x = stage_x + stage_width - stage_block_width * 3;
	}
	else if (block_x >= (stage_x + stage_width) - stage_block_width * 2 && block_kind == I) {
		block_x = (stage_x + stage_width) - stage_block_width * 2;
	}
}