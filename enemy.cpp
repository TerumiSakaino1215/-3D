//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"

#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_ENEMY			"data/MODEL/carmodel2.x"	// �ǂݍ��ރ��f����
#define	ENEMY_RADIUS			(12.0f)						// ���a
#define	VALUE_MOVE_ENEMY		(0.05f)						// �����x
#define	VALUE_MOVE_MAX_ENEMY	(4.0f)						// �ō����x
#define	RATE_MOVE_ENEMY			(0.025f)					// �ړ������W��
#define	VALUE_ROTATE_ENEMY		(D3DX_PI * 0.025f)			// ��]���x
#define	RATE_ROTATE_ENEMY		(0.10f)						// ��]�����W��
#define	VALUE_MOVE_BULLET		(7.5f)						// �e�̈ړ����x



//#define COUNT_MAX				(2)						// �J�E���^�[�̃}�b�N�X�l

//#define SIDE_MOVE_ENEMY					(10.0f)	 // �v���C���[�̈ړ���
//#define SIDE_MOVE_ENEMY_MAX				(140.0f) // ���̃}�b�N�X�ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshEnemy;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffEnemy;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatEnemy;			// �������̑���

D3DXMATRIX			g_mtxWorldEnemy;			// ���[���h�}�g���b�N�X
//ENEMY				g_enemy;					// �G�l�~�[���[�N
ENEMY				g_enemy[ENEMY_MAX];				// �G�l�~�[���[�N

struct D3DXVECTOR3	playerpos;					//	�v���C���[�̈ʒu

//D3DXVECTOR3			enemypos[10]
//{
//	(0.0f, ENEMY_POS_HEIGHT, 2500.0f),
//SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 4000.0f;
//-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 6000.0f;
//};

	

//int					enemycnt;				// �G�l�~�[�̃J�E���^�[(�_�u��Ȃ��悤�ɓG�̐����Ǘ�)
//int					random;					// �����_�������̂��

//int					llusefrag;				// ���t�g���[���g�p�t���O
//int					clusefrag;				// �Z���^�[���[���g�p�t���O
//int					rlusefrag;				// ���C�g���[���g�p�t���O

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &g_enemy[0];

	// �����_���ɂ������Ƃ���
	//for (int i = 0; i < ENEMY_MAX; i++)							// �悤�킩���
	//{
	//	enemy = &g_enemy[i];
	//	enemy->pos = D3DXVECTOR3(enemypos[i]){
	//		(0.0f, ENEMY_POS_HEIGHT, 2500.0f),
	//		(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 4000.0f),
	//		(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 6000.0f)
	//	}	
	//}

	//for (int i = 0; i < ENEMY_MAX; i++)
	//{
		// �S������w

	enemy = &g_enemy[0];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 2500.0f); // z�l 2500
	enemy = &g_enemy[1];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 3500.0f); // 4000
	enemy = &g_enemy[2];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 5000.0f); // 6000
	enemy = &g_enemy[3];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 6500.0f); // 6000
	enemy = &g_enemy[4];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 7000.0f); // 6000
	enemy = &g_enemy[5];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 8000.0f); // 6000
	enemy = &g_enemy[6];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 9000.0f); // 6000
	enemy = &g_enemy[7];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 10000.0f); // 6000
	enemy = &g_enemy[8];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 11000.0f); // 6000
	enemy = &g_enemy[9];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 12000.0f); // 6000
	enemy = &g_enemy[10];
	enemy->pos = D3DXVECTOR3(0, ENEMY_POS_HEIGHT, 13000.0f); // 6000
	enemy = &g_enemy[11];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 14000.0f); // 6000
	enemy = &g_enemy[12];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 15000.0f); // 6000
	enemy = &g_enemy[13];
	enemy->pos = D3DXVECTOR3(0, ENEMY_POS_HEIGHT, 16000.0f); // 6000
	enemy = &g_enemy[14];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 16500.0f);


	enemy = &g_enemy[0];
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		g_pD3DTextureEnemy = NULL;
		g_pMeshEnemy = NULL;
		g_pD3DXMatBuffEnemy = NULL;

		//enemy->pos = D3DXVECTOR3(0.0f, 20.0f, (i + 1) * 1500.0f);
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->rot = D3DXVECTOR3(0.0f, 9.45f, 0.0f);
		enemy->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->fRadius = ENEMY_RADIUS;

		enemy->use = true;

		enemy->move.z = VALUE_MOVE_MAX_ENEMY;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_ENEMY,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXMatBuffEnemy,
			NULL,
			&g_nNumMatEnemy,
			&g_pMeshEnemy)))
		{
			return E_FAIL;
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,		// �t�@�C���̖��O
			&g_pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif

		// �e�̐ݒ�
		enemy->nIdxShadow = SetShadow(enemy->pos, enemy->fRadius * 2.0f, enemy->fRadius * 2.0f);		// �e�̐ݒ�
	}

	//enemycnt = 0;
	//random    = 0;

	//llusefrag = false;
	//clusefrag = false;
	//rlusefrag = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_pD3DTextureEnemy != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureEnemy->Release();
			g_pD3DTextureEnemy = NULL;
		}

		if (g_pMeshEnemy != NULL)
		{// ���b�V���̊J��
			g_pMeshEnemy->Release();
			g_pMeshEnemy = NULL;
		}

		if (g_pD3DXMatBuffEnemy != NULL)
		{// �}�e���A���̊J��
			g_pD3DXMatBuffEnemy->Release();
			g_pD3DXMatBuffEnemy = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &g_enemy[0]; // �|�C���^�[�̏�����


	/*
	if () // �����_������ enemy[0]�̏ꍇ
	{
		// enemy[1]=�g�p ���� enemy[2]=�g�p �ȊO�̂Ƃ������_���ŏo�� �݂�����

		// true�ɂ���R�[�h������
	}

	// enemy[1]�̏ꍇ...
	// enemy[2]�̏ꍇ...
	*/

	// ��L�ł͂Ȃ��A�A�A
	// �V���v���ɃJ�E���^�[�Ő��䂵�����������̂ł͂Ȃ����Ƃ������Ƃ�����


	//enemy = &g_enemy[0]; // �|�C���^�[�̏�����
	
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		//if (enemy->use == false && enemycnt < COUNT_MAX) // ���̃G�l�~�[�������Ƃ��g���ĂȂ��Ƃ�
		//{// �����_������
		//	random = rand() % 90;
		//	if (random == 0)
		//	{
		//		enemy->use = true;
		//		playerpos = GetPositionPlayer();
		//		enemy->pos.z = playerpos.z + 2000.0f;
		//		enemycnt++;
		//	}
		//}

		if (enemy->use == true) // �G�l�~�[���g���Ă�Ƃ�
		{
			// �ړ�����
			enemy->pos.z += enemy->move.z;		// �ړ����x�𔽉f

			// �v���C���[�̈ʒu�擾
			playerpos = GetPositionPlayer();
			if (enemy->pos.z <= playerpos.z - 100.0f) // �v���C���[�����(��ʊO)�ɍs������
			{// ���g�p��Ԃɂ��Ĉʒu��������
				enemy->use = false;
				enemy->pos.z = 30000.0f;
				//enemycnt--;
			}
		}

		// �e�̈ʒu�ݒ�
		SetPositionShadow(enemy->nIdxShadow, D3DXVECTOR3(enemy->pos.x, 0.1f, enemy->pos.z));

		float fSizeX = 20.0f + (enemy->pos.y - 10.0f) * 0.05f;
		if (fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (enemy->pos.y - 10.0f) * 0.05f;
		if (fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(enemy->nIdxShadow, fSizeX, fSizeY);

		float colA = (200.0f - (enemy->pos.y - 10.0f)) / 400.0f;
		if (colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(enemy->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));


		if ((enemy->move.x * enemy->move.x
			+ enemy->move.y * enemy->move.y
			+ enemy->move.z * enemy->move.z) > 1.0f)
		{
			D3DXVECTOR3 pos;

			pos.x = enemy->pos.x + sinf(enemy->rot.y) * 10.0f;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z + cosf(enemy->rot.y) * 10.0f;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);
		}













	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	ENEMY *enemy = &g_enemy[0]; // �|�C���^�[�̏�����
	
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy->pos.x, enemy->pos.y, enemy->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemy);

				// �`��
				g_pMeshEnemy->DrawSubset(nCntMat);
			}
		}

		{// �}�e���A�����f�t�H���g�ɖ߂�
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			pDevice->SetMaterial(&mat.MatD3D);
		}
	}
}

//=============================================================================
// �G�l�~�[���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_enemy[0];
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(void)
{
	return g_enemy->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(void)
{
	return g_enemy->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(void)
{
	return g_enemy->rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMoveEnemy(void)
{
	return g_enemy->move;
}

//int GetEnemyCounter(void)
//{
//	return enemycnt;
//}

void SetEnemyPos(void)
{
	ENEMY *enemy = &g_enemy[0];

	enemy = &g_enemy[0];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 2500.0f); // z�l 2500
	enemy = &g_enemy[1];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 3500.0f); // 4000
	enemy = &g_enemy[2];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 5000.0f); // 6000
	enemy = &g_enemy[3];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 6500.0f); // 6000
	enemy = &g_enemy[4];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 7000.0f); // 6000
	enemy = &g_enemy[5];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 8000.0f); // 6000
	enemy = &g_enemy[6];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 9000.0f); // 6000
	enemy = &g_enemy[7];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 10000.0f); // 6000
	enemy = &g_enemy[8];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 11000.0f); // 6000
	enemy = &g_enemy[9];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 12000.0f); // 6000
	enemy = &g_enemy[10];
	enemy->pos = D3DXVECTOR3(0, ENEMY_POS_HEIGHT, 13000.0f); // 6000
	enemy = &g_enemy[11];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 14000.0f); // 6000
	enemy = &g_enemy[12];
	enemy->pos = D3DXVECTOR3(SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 16000.0f); // 6000
	enemy = &g_enemy[13];
	enemy->pos = D3DXVECTOR3(0, ENEMY_POS_HEIGHT, 18000.0f); // 6000
	enemy = &g_enemy[14];
	enemy->pos = D3DXVECTOR3(-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 20250.0f);
}