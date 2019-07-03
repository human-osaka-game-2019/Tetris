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
	enum COLOR {
		Back,
		Red,
		Blue,
		Green,
		Yellow,
		White,
		Black,
		Lightblue,
		Wall,
	};

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

	// ����
	enum DIRECTION {
		LEFT,
		RIGHT,
		DOWN
	};

	// �s�Ɨ�
	struct Cell {
		int row, col;
	};

	// ���W(pixel)
	struct Point {
		FLOAT x, y;
	};

	// uv�l
	struct UV {
		FLOAT u, v;
		void SetUV(FLOAT tu, FLOAT tv) { u = tu; v = tv; }
	};

	// ���ƍ���(pixel)
	struct Size {
		FLOAT w, h;
	};

	//�֐��̃v���g�^�C�v�錾
	void Loading();
	void Process();
	void Control();
	void Release();
	void CreateMino();
	void DrawMino();
	UV GetUV(COLOR color);
	bool CanMove(DIRECTION direction);
	bool Collides(Cell topLeft);
	void MoveDown();
	void MoveHorizontally(DIRECTION direction);
	void FixMino();

	//�E�B���h�E�̃T�C�Y
	Size windowSize = { 1280.0f, 720.0f };

	//�Q�[���X�e�[�W�̈ʒu
	Point stageTopLeft = { 460.0f, -144.0f };

	//�u���b�N��1�}�X�̑傫��
	Size blockSize = { 36.0f, 36.0f };
		   
	//�t���[���𐔂���
	INT FrameCount = 0;

	//�ړ��u���b�N�̏c�Ɖ�
	Cell blockPosition;

	// �ڒn�������ǂ���
	bool landed = false;

	// ��������mino�̐F
	COLOR minoColor = Red;

	COLOR board[25][12] = {
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Back,Back,Back,Back,Back,Back,Back,Back,Back,Back,Wall},
	{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
	};

	const int MINO_L[4][4] = {
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	const int MINO_I[4][4] = {
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
	};

	const int MINO_J[4][4] = {
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	const int MINO_S[4][4] = {
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
	};

	const int MINO_O[4][4] = {
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	const int MINO_Z[4][4] = {
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	};

	const int MINO_T[4][4] = {
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0},
	};

	int mino[4][4];
};

#endif
