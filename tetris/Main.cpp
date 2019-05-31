#include "DirectX.h"
#include "Main.h"
#include "Title.h"

#define Width 1280
#define Height 720 

DirectX dx;
Title title;
 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow) {
	HWND hWnd = NULL;
	const TCHAR API_NAME[] = _T("Tetris_X");
	//���b�Z�[�W
	MSG msg;
	hWnd = GenerateWindow(&hWnd, &hInstance, API_NAME);
	dx.BuildDxDevice(hWnd,_T("Blank.jpg"));

	Mainloop(&msg);


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

HWND GenerateWindow(HWND* hWnd,HINSTANCE* hInstance,const TCHAR* API_NAME) {
	//�E�B���h�E�N���X
	WNDCLASS Wndclass;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW; //�E�B���h�E�X�^�C��
	Wndclass.lpfnWndProc = WndProc; //�E�B���h�E�v���V�[�W��
	Wndclass.cbClsExtra = 0; //�������m��
	Wndclass.cbWndExtra = 0; //�������m��
	Wndclass.hInstance = *hInstance;	//�n���h���C���X�^���X
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\��
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //�w�i�̃u���V,�F
	Wndclass.lpszMenuName = NULL; //���j���[��ʂ̖��O
	Wndclass.lpszClassName = API_NAME; //�A�v���P�[�V�����̖��O

	//�E�B���h�E�N���X�̓o�^
	RegisterClass(&Wndclass);

	//�E�B���h�E�n���h����createwindow�֐��ō����������
	return *hWnd = CreateWindow(
		API_NAME,							//�N���X�̖��O
		API_NAME,							//�A�v���P�[�V�����̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,						//X�̈ʒu
		CW_USEDEFAULT,						//Y�̈ʒu
		Width,								//��
		Height,								//����
		NULL,								//�e�E�B���h�E�̃n���h��
		NULL,								//���j���[�̃n���h��
		*hInstance,							//�C���X�^���X�n���h��
		NULL								//���b�Z�[�W�ɓn�����p�����[�^
	);
}

void Mainloop(MSG* msg) {
	SCENE scene = TITLE;

	DWORD Prev = timeGetTime();
	DWORD Curr;
	
	timeBeginPeriod(1);

	ZeroMemory(msg, sizeof(msg));
	while (msg->message != WM_QUIT) {
		if (PeekMessage(msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(msg);
			DispatchMessage(msg);
		}
		else {
			Curr = timeGetTime();
			if (Curr - Prev >= 1000 / 60) {
				dx.pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
				dx.pD3Device->BeginScene();
				//��������Q�[������
				switch (scene) {
				case TITLE:
					title.Title_Scene();
					break;
				case GAME:

					break;
				case RESULT:

					break;
				}
				dx.pD3Device->EndScene();
				dx.pD3Device->Present(NULL, NULL, NULL, NULL);

				Prev = Curr;
			}
		}
		Sleep(1);
	}
	timeEndPeriod(1);
}



