#include "Title.h"

//�^�C�g���̃t�F�[�Y�̐錾
Title::SCENE_PHASE Phase = Title::LOAD;

//�^�C�g���̃t�F�[�Y�̈ړ�
void Title::Title_Scene() {

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

//�^�C�g���̃e�N�X�`���̓ǂݍ���
void Title::Loading() {
			D3DXCreateTextureFromFile(
			dx.pD3Device,
			_T("Title_Back.png"),
			&dx.pTexture[TITLE_BACK]);
		Phase = PROCESSING;
}

//�^�C�g���̕`�揈��
void Title::Process() {

	//�^�C�g���̕`��
	Draw(0, 0, 0.0f, 0.0f, window_width, window_height,1.0f,1.0f,TITLE_BACK);

	//�G���^�[�ŃQ�[����
	if (dx.KeyState[DIK_RETURN] == dx.PRESS) {
		Phase = RELEASES;
	}
}

//�^�C�g���̃e�N�X�`���̉��
void Title::Release() {

	for (int i = 0; i < TEX_MAX; i++) {
		if (dx.pTexture[i] != nullptr) {
			dx.pTexture[i]->Release();
			dx.pTexture[i] = nullptr;
		}
	}
	scene = GAME;

}
