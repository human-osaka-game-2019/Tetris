#include "Control.h"
#include "Initialize.h"
#include "WinMain.h"

#define Width 1920
#define Height 1080 
 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow) {

	const TCHAR API_NAME[] = _T("Tetris_X");
	DWORD Prev = timeGetTime();
	DWORD Curr;

	//���b�Z�[�W
	MSG msg;

	//�E�B���h�E�N���X
	WNDCLASS Wndclass;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW; //�E�B���h�E�X�^�C��
	Wndclass.lpfnWndProc = WndProc; //�E�B���h�E�v���V�[�W��
	Wndclass.cbClsExtra = 0; //�������m��
	Wndclass.cbWndExtra = 0; //�������m��
	Wndclass.hInstance = hInstance;	//�n���h���C���X�^���X
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\��
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�̃u���V,�F
	Wndclass.lpszMenuName = NULL; //���j���[��ʂ̖��O
	Wndclass.lpszClassName = API_NAME; //�A�v���P�[�V�����̖��O

	//�E�B���h�E�N���X�̓o�^
	RegisterClass(&Wndclass);

	//�E�B���h�E�n���h����createwindow�֐��ō����������
	HWND hWnd = CreateWindow(
		API_NAME,							//�N���X�̖��O
		API_NAME,							//�A�v���P�[�V�����̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,						//X�̈ʒu
		CW_USEDEFAULT,						//Y�̈ʒu
		Width,								//��
		Height,								//����
		NULL,								//�e�E�B���h�E�̃n���h��
		NULL,								//���j���[�̃n���h��
		hInstance,							//�C���X�^���X�n���h��
		NULL								//���b�Z�[�W�ɓn�����p�����[�^
	);

	ZeroMemory(&msg, sizeof(msg));


	//�E�B���h�E�����݂čX�V
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//���b�Z�[�W�ʂ̏���
	switch (msg)
	{
		//�E�B���h�E���j�󂳂ꂽ�Ƃ��̃��b�Z�[�W
	case WM_DESTROY:
		//���郁�b�Z�[�W�𑗂�
		PostQuitMessage(0);
		return 0;
		//���[�U�[�����j���[��ALT�L�[�Ɖ������������Ƃ�
	case WM_SYSKEYDOWN:
		switch (wp)
		{
		case VK_RETURN:
			return 0;
		case VK_F4:
			//���郁�b�Z�\�W
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		default:
			return 0;
		}
		return 0;
	}
	//DefaultWindowProcedure��Ԃ�(�f�t�H���g)
	return DefWindowProc(hWnd, msg, wp, lp);
}