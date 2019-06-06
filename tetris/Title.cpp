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
	dx.pD3Device->SetTexture(0, dx.pTexture[TITLE_BACK]);
	dx.pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TitleBack_Vertex, sizeof(CustomVertex));

	//�G���^�[�ŃQ�[����
	if (dx.GetKeyState(DIK_RETURN)) {
		Phase = RELEASES;
	}
}

//�^�C�g���̃e�N�X�`���̉��
void Title::Release() {

	dx.pTexture[TITLE_BACK]->Release();
	dx.pTexture[TITLE_BACK] = nullptr;
	scene = GAME;

}
