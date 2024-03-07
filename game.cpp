//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
//#include "meshwall.h"
#include "player.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
//#include "life.h"
//#include "timer.h"
#include "score.h"
//#include "item.h"
#include "sound.h"

#include "enemy.h"
#include "input.h"
#include "fade.h"
#include "pause.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 128, 6000.0f, 640.0f);

	// �ǂ̏�����
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									//D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);

	// ��(�����p)
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// �e�̏�����
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	// �G�l�~�[�̏�����
	InitEnemy();
	
	// �e�̏�����
	InitBullet();

	// �����̏�����
	InitExplosion();

	// �G�t�F�N�g�̏�����
	InitEffect();

	//// ���C�t�̏�����
	//InitLife();

	//// �^�C�}�[�̏�����
	//InitTimer();
	//ResetTimer(5);

	// �X�R�A�̏�����
	InitScore();

//	// �A�C�e���̏�����
//	InitItem();
//	for(int nCntCoin = 0; nCntCoin < 40; nCntCoin++)
//	{
//		float fPosX, fPosY, fPosZ;
//
//		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;
////		fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;
//		fPosY = 40.0f;
//		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
//		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN); 
//	}

	// BGM�Đ�
	//PlaySound(SOUND_LABEL_BGM000);

	// �|�[�Y�̏�����
	InitPause();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitMeshField();

	// �ǂ̏I������
	//UninitMeshWall();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �e�̏I������
	UninitBullet();

	// �����̏I������
	UninitExplosion();

	// �G�t�F�g�̏I������
	UninitEffect();

	//// ���C�t�̏I������
	//UninitLife();

	//// �^�C�}�[�̏I������
	//UninitTimer();

	//// �X�R�A�̏I������
	//UninitScore();

	//// �A�C�e���̏I������
	//UninitItem();

	// BGM��~
	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	// �J�����X�V
	UpdateCamera();

	// �n�ʏ����̍X�V
	UpdateMeshField();

	// �Ǐ����̍X�V
	//UpdateMeshWall();

	// �e�����̍X�V
	UpdateShadow();

	// �v���C���[�����̍X�V
	UpdatePlayer();

	// �G�l�~�[�̏����̍X�V
	UpdateEnemy();

	// �e�����̍X�V
	UpdateBullet();

	// ���������̍X�V
	UpdateExplosion();

	// �G�t�F�N�g�����̍X�V
	UpdateEffect();

	//// ���C�t�����̍X�V
	//UpdateLife();

	//// �^�C�}�[�����̍X�V
	//UpdateTimer();

	// �X�R�A�����̍X�V
	UpdateScore();

	//// �A�C�e�������̍X�V
	//UpdateItem();

	// �|�[�Y���
	UpdatePause();
	
	if (GetKeyboardTrigger(DIK_F1))
	{
		// �Q�[����ʂ̏I������
		UninitGame();

		SetMode(MODE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �n�ʏ����̕`��
	DrawMeshField();

	// �e�����̕`��
	DrawShadow();

	// �v���C���[�����̕`��
	DrawPlayer();

	// �G�l�~�[�̏����̕`��
	DrawEnemy();

	//// �A�C�e�������̕`��
	//DrawItem();

	// �e�����̕`��
	DrawBullet();

	// �Ǐ����̕`��
	//DrawMeshWall();

	// ���������̕`��
	DrawExplosion();

	// �G�t�F�N�g�����̕`��
	DrawEffect();

	//// ���C�t�����̕`��
	//DrawLife();

	//// �^�C�}�[�����̕`��
	//DrawTimer();

	// �X�R�A�����̕`��
	DrawScore();
}

