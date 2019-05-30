/*
	��Y
*/

#include "DirectX.h"

#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")

HRESULT DirectX::BuildDxDevice(HWND hWnd, const TCHAR* filepath)
{
	if (FAILED(InitD3Device(hWnd, filepath))) {
		return E_FAIL;
	}

	if (FAILED(InitDinput(hWnd))) {
		return E_FAIL;
	}

	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (pDirect3D == NULL) {
		MessageBox(0, _T("Direct3D�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	pD3Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	return S_OK;
}

HRESULT DirectX::InitD3Device(HWND hWnd, const TCHAR * FilePath) {
	if (NULL == (pDirect3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		MessageBox(0, _T("Direct3D�̍쐬�Ɏ��s���܂���"), _T(""), MB_OK);
		return E_FAIL;
	}

	InitPresentParameters(hWnd);

	if (FAILED(pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&D3dPresentParameters, &pD3Device))) {

		MessageBox(0, _T("HAL���[�h��DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���\nREF���[�h�ōĎ��s���܂�"), NULL, MB_OK);
		if (FAILED(pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&D3dPresentParameters, &pD3Device))) {
			MessageBox(0, _T("DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFileEx(pD3Device, FilePath, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &pTexture[0]))) {
		MessageBox(0, _T("�e�N�X�`���̍쐬�Ɏ��s���܂���"), _T(""), MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

/*
	����
*/

HRESULT DirectX::InitDinput(HWND hWnd)
{
	HRESULT hr;

	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& pDinput, NULL)))
	{
		return hr;
	}

	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pDxIKeyDevice, NULL)))
	{
		return hr;
	}

	if (FAILED(hr = pDxIKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	if (FAILED(hr = pDxIKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	pDxIKeyDevice->Acquire();
	return S_OK;
}

void DirectX::InitPresentParameters(HWND hWnd)
{
	ZeroMemory( &D3dPresentParameters, sizeof(D3dPresentParameters));

	D3dPresentParameters.BackBufferWidth = 1280;
	D3dPresentParameters.BackBufferHeight = 720;
	D3dPresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	D3dPresentParameters.BackBufferCount = 1;
	D3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	D3dPresentParameters.MultiSampleQuality = 0;
	D3dPresentParameters.hDeviceWindow = hWnd;
	D3dPresentParameters.EnableAutoDepthStencil = FALSE;
	D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	D3dPresentParameters.Flags = 0;
	D3dPresentParameters.FullScreen_RefreshRateInHz = 0;
	D3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3dPresentParameters.Windowed = TRUE;
}

void DirectX::UpdateKeyState() {
	HRESULT hr = pDxIKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		pDxIKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);
	}
}

bool DirectX::GetKeyState(BYTE KeyNumber) {
	if (KeyState[KeyNumber] & 0x80) {
		return true;
	}
	return false;
}