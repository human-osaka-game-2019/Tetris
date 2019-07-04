#include "Result.h"

//���U���g�̃t�F�[�Y�̈ړ�
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
	Draw(0, 0, 0.0f, 0.0f, window_width, window_height, 1.0f,1.0f,RESULT_BACK);

	//�G���^�[�Ń^�C�g����
	if (dx.KeyState[DIK_RETURN] == dx.PRESS) {
		Phase = RELEASES;
	}
}

//���U���g�̃e�N�X�`���̉��
void Result::Release() {

	for (int i = 0; i < TEX_MAX;i++) {
		if (dx.pTexture[i] != nullptr) {
			dx.pTexture[i]->Release();
			dx.pTexture[i] = nullptr;
		}
	}
	scene = TITLE;
}
