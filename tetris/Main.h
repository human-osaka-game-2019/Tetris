#include <windows.h>
#include <d3d9.h>

//WinMain�֐�
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);

//�E�B���h�v���V�[�W���̐���
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//window�쐬
HWND GenerateWindow(HWND* hWnd,HINSTANCE* hInstance,const TCHAR* API_NAME);

//���C�����[�v
VOID Mainloop(MSG* msg);


	void InitPresentParameters(HWND hWnd);
