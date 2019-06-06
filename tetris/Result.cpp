#include "Result.h"

//���U���g�̃t�F�[�Y�̐錾
Result::SCENE_PHASE Phase = Result::LOAD;

//���U���g��
void Result::Result_Scene() {

	switch (Phase) {
	case LOAD:
		Loading();
		break;
	case PROCESSING:
		Process();
		break;
	case RELEASES:
		Release();
		Phase = LOAD;
		break;
	}
}

//���U���g�̃e�N�X�`���̓ǂݍ���
void Result::Loading() {

	D3DXCreateTextureFromFile(
		dx.pD3Device,
		_T("Result_Back.png"),
		&dx.pTexture[RESULT_BACK]);
	Phase = PROCESSING;
}

//���U���g�̕`�揈��
void Result::Process() {

	//���U���g�̕`��
	dx.pD3Device->SetTexture(0, dx.pTexture[RESULT_BACK]);
	dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2,ResultBack_Vertex, sizeof(CustomVertex));

	//�G���^�[�Ń^�C�g����
	if (dx.GetKeyState(DIK_RETURN)) {
		Phase = RELEASES;
	}
}

//���U���g�̃e�N�X�`���̉��
void Result::Release() {

	dx.pTexture[RESULT_BACK]->Release();
	dx.pTexture[RESULT_BACK] = nullptr;
	scene = TITLE;
}
