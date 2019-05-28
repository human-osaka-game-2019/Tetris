#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>

class Initialize {
public:
	//�@Direct3D�̃C���^�[�t�F�C�X
	LPDIRECT3D9 pDirect3D;
	//�@Direct3D�̃f�o�C�X
	IDirect3DDevice9* pD3Device;
	//�@�E�B���h�E�̐ݒ�
	D3DPRESENT_PARAMETERS D3dPresentParameters;
	//�@DirectInput�̃L�[�{�[�h�f�o�C�X
	LPDIRECTINPUTDEVICE8 pDxIKetDevice;
	//�@DirectInput�̃C���^�[�t�F�C�X
	LPDIRECTINPUT8 pDinput;
	//�@�e�N�X�`��
	LPDIRECT3DTEXTURE9 pTexture;

	struct CustomVertex {
		FLOAT x, y, z, rhw;
		DWORD color;
		FLOAT tu, tv;
	};

	BYTE KeyState[256];

	HRESULT BuildDxDevice(HWND hWnd, const TCHAR* FilePath);

	HRESULT InitD3Device(HWND hWnd, const TCHAR* FilePath);

	void InitPresentParameters(HWND hWnd);

	HRESULT InitDinput(HWND hWnd);
};