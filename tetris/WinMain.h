#include <windows.h>
#include <d3d9.h>

//�J�X�^���o�[�e�b�N�X
struct CustomVertex {
	FLOAT x, y, z, rhw;
	DWORD color;
	FLOAT tu, tv;
};

//WinMain�֐�
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);

//�E�B���h�v���V�[�W���̐���
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
