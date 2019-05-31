#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <d3d9.h>

#include "DirectX.h"

//�J�X�^���o�[�e�b�N�X
struct CustomVertex {
	FLOAT x, y, z, rhw;
	DWORD color;
	FLOAT tu, tv;
};

extern DirectX dx;

//WinMain�֐�
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);

//�E�B���h�v���V�[�W���̐���
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//window�쐬
HWND GenerateWindow(HWND* hWnd,HINSTANCE* hInstance,const TCHAR* API_NAME);

//���C�����[�v
void Mainloop(MSG* msg);

enum TEX_NO {
	TITLE_BACK,
	TITLE_FONT,
	GAME_BACK,
	GAME_STAGE,
	GAME_BLOCK,
	RESULT_BACK,
	RESULT_FONT
};

enum SCENE {
	TITLE,
	GAME,
	RESULT
};

#endif
