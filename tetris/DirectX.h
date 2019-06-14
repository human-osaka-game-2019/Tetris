#ifndef DirectX_H
#define DirectX_H

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <d3dx9tex.h>
#include <tchar.h>

#define TEX_MAX 10

class DirectX {
public:
	//�@Direct3D�̃C���^�[�t�F�C�X
	LPDIRECT3D9 pDirect3D;

	//�@Direct3D�̃f�o�C�X
	IDirect3DDevice9* pD3Device;

	//�@�E�B���h�E�̐ݒ�
	D3DPRESENT_PARAMETERS D3dPresentParameters;
	
	//�@DirectInput�̃L�[�{�[�h�f�o�C�X
	LPDIRECTINPUTDEVICE8 pDxIKeyDevice;

	//�@DirectInput�̃C���^�[�t�F�C�X
	LPDIRECTINPUT8 pDinput;

	//�@�e�N�X�`��
	LPDIRECT3DTEXTURE9 pTexture[TEX_MAX];

	enum KEY_STATE {
		PRESS,
		RELEASE,
		ON,
		OFF
	};

	static const int MAX_KEY = 256;
	const int MASK_NUM = 0x80;

	KEY_STATE KeyState[256];

	HRESULT BuildDxDevice(HWND hWnd, const TCHAR* FilePath);

	HRESULT InitD3Device(HWND hWnd, const TCHAR* FilePath);

	HRESULT InitDinput(HWND hWnd);

	void InitPresentParameters(HWND hWnd);

	void UpdateKeyState();

	KEY_STATE GetKeyState(INT diks);

	void All_Release();


};
#endif