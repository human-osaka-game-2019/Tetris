/*
	��Y
*/

#include "DirectX.h"
#include "Main.h"

#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")

HRESULT Init::BuildDxDevice(HWND hWnd, const TCHAR* filepath)
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

HRESULT Init::InitD3Device(HWND hWnd, const TCHAR * FilePath) {
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
}
/*
	����
*/

HRESULT Init::InitDinput(HWND hWnd)
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
