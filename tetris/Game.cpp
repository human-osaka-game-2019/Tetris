
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
	CreateMino();

	Phase = PROCESSING;
}

//�Q�[���̕`��Ɠ���
void Game::Process() {
	FrameCount++;

	Control();
	
	//�Q�[�����̔w�i�`��
	Draw(0, 0, 0.0f, 0.0f, windowSize.w, windowSize.h, 1.0f, 1.0f, GAME_BACK);
	
	//�X�e�[�W�`��
	for (INT row = 4; row < 25; row++) {
		for (INT col = 0; col < 12; col++) {
			UV uv = GetUV(board[row][col]);

			//�񎟌��z��ɂ��A�w�i�ɔ��f�������Ă���u���b�N������������Ă���
					 	//���W�̓����������\���̂����
			FLOAT x = stageTopLeft.x + blockSize.w * col;
			FLOAT y = stageTopLeft.y + blockSize.h * row;
			Draw(x, y, uv.u, uv.v, blockSize.w, blockSize.h, 0.25f, 0.25f, GAME_BLOCK);
		}
	}

	//�~�m�`��
	DrawMino();

	//���ɂ���7��ނ̕`��E�^�񒆂Ɉړ�����
	if (landed) {
		FixMino();
		CreateMino();
	}

	//debug�p
	if (dx.KeyState[DIK_RETURN] == dx.PRESS) {
		Phase = RELEASES;
	}
}

void Game::Control()
{
	//��u�ŉ��ɗ��Ƃ�����
	if (dx.KeyState[DIK_UP] == dx.PRESS) {
		//block_y -= 36;
	}
	//���ړ�
	if (dx.KeyState[DIK_DOWN] == dx.PRESS){
		MoveDown();
	}
	//�E�ړ�
	if (dx.KeyState[DIK_RIGHT] == dx.PRESS){
		MoveHorizontally(RIGHT);
	}
	//���ړ�
	if (dx.KeyState[DIK_LEFT] == dx.PRESS) {
		MoveHorizontally(LEFT);
	}

	//�d��
	if (FrameCount == 60){
		// 1�b������
		FrameCount = 0;
		MoveDown();
	}
}

void Game::MoveDown()
{
	if (CanMove(DOWN)) {
		++blockPosition.row;
	} else {
		landed = true;
	}
}

void Game::MoveHorizontally(DIRECTION direction)
{
	if(CanMove(direction)) {
		blockPosition.col += (direction == LEFT ? -1 : 1);
	}
}

void Game::FixMino()
{
	int col = blockPosition.col;
	int row = blockPosition.row;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (mino[y][x] != 0) {
				board[row + y][col + x] = minoColor;
			}
		}
	}
}

//�Q�[���̃e�N�X�`���̉��
void Game::Release() {
	//�e�N�X�`���̊J��
	dx.pTexture[GAME_BACK]->Release();
	dx.pTexture[GAME_BACK] = nullptr;
	dx.pTexture[GAME_BLOCK]->Release();
	dx.pTexture[GAME_BLOCK] = nullptr;

	//���U���g�V�[����
	scene = RESULT;
}

void Game::CreateMino() {
	const INT(*tmpl)[4];

	switch (rand() % 7) {
	case L:
		minoColor = Red;
		tmpl = MINO_L;
		break;
	case I:
		minoColor = Blue;
		tmpl = MINO_I;
		break;
	case J:
		minoColor = Green;
		tmpl = MINO_J;
		break;
	case S:
		minoColor = Yellow;
		tmpl = MINO_S;
		break;
	case O:
		minoColor = White;
		tmpl = MINO_O;
		break;
	case Z:
		minoColor = Black;
		tmpl = MINO_Z;
		break;
	case T:
		minoColor = Lightblue;
		tmpl = MINO_T;
		break;
	default:
		return;
	}

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			mino[y][x] = tmpl[y][x];
		}
	}

	blockPosition.col = 3;
	blockPosition.row = 0;
	landed = false;
}

void Game::DrawMino() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (mino[y][x]) {
				FLOAT left = stageTopLeft.x + blockSize.w * (blockPosition.col + x);
				FLOAT top = stageTopLeft.y + blockSize.h * (blockPosition.row + y);
				UV uv = GetUV(minoColor);
				Draw(left, top, uv.u, uv.v, blockSize.w, blockSize.h, 0.25f, 0.25f, GAME_BLOCK);
			}
		}
	}
}

Game::UV Game::GetUV(COLOR color)
{
	UV uv;
	switch (color) {
	case Red:
		uv.SetUV(0.0f, 0.0f);
		break;
	case Blue:
		uv.SetUV(0.25f, 0.0f);
		break;
	case Green:
		uv.SetUV(0.5f, 0.0f);
		break;
	case Yellow:
		uv.SetUV(0.75f, 0.0f);
		break;
	case White:
		uv.SetUV(0.0f, 0.25f);
		break;
	case Black:
		uv.SetUV(0.5f, 0.25f);
		break;
	case Lightblue:
		uv.SetUV(0.75f, 0.25f);
		break;
	case Wall:
		uv.SetUV(0.25f, 0.5f);
		break;
	default:
		uv.SetUV(0.75f, 0.75f);
		break;
	}

	return uv;
}

bool Game::CanMove(DIRECTION direction)
{
	// �Փ˔���̊�_�ƂȂ�Cell
	Cell topLeft = blockPosition;

	switch (direction) {
	case Game::LEFT:
	case Game::RIGHT:
		// �~�m�����E�ɓ��������ꏊ�ŏՓ˂��Ă��邩���`�F�b�N����
		topLeft.col += (direction == RIGHT ? 1 : -1);
		break;
	case Game::DOWN:
		// �~�m�����ɓ��������ꏊ�ŏՓ˂��Ă��邩���`�F�b�N����
		++topLeft.row;
		break;
	default:
		return false;
	}

	if (Collides(topLeft)) {
		return false;
	}

	return true;
}

bool Game::Collides(Cell topLeft)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (mino[y][x] == Back) {
				continue;
			}

			if (board[topLeft.row + y][topLeft.col + x] != Back) {
				return true;
			}
		}
	}

	return false;
}
