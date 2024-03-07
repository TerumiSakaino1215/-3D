//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"

#include "enemy.h"
//#include "meshfield.h"
#include "explosion.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER			"data/MODEL/carmodel.x"	// �ǂݍ��ރ��f����
#define	PLAYER_RADIUS			(12.0f)						// ���a
#define	VALUE_MOVE_PLAYER		(0.3f)						// �����x
#define	VALUE_MOVE_MAX_PLAYER	(45.0f)						// �ō����x
#define	RATE_MOVE_PLAYER		(0.025f)					// �ړ������W��
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.025f)			// ��]���x
#define	RATE_ROTATE_PLAYER		(0.10f)						// ��]�����W��
#define	VALUE_MOVE_BULLET		(7.5f)						// �e�̈ړ����x

#define SIDE_MOVE_PLAYER					(14.0f)	 // �v���C���[�̈ړ���
//#define SIDE_MOVE_PLAYER_MAX				(140.0f) // ���̃}�b�N�X�ړ���
//#define SIDE_MOVE_PLAYER_MAX_LEFT			(100.f)  // �v���C���[��������ő�l
//#define SIDEMOVE_PLAYER_MAX_RIGHT		(380.f)  // �v���C���[��������ő�l

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshPlayer;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffPlayer;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer;			// �������̑���

D3DXMATRIX			g_mtxWorldPlayer;			// ���[���h�}�g���b�N�X
PLAYER				g_player;					// �v���C���[���[�N

bool				moveflag;					// �ړ��t���O
bool				moveflag_left;				// ��ړ��t���O
bool				moveflag_right;				// ���ړ��t���O

float				moveamount;					// �ړ���

bool				leftlineflag;				// �����[���ɂ��邩
bool				rightlineflag;				// �E���[���ɂ��邩
bool				centerlineflag;				// �������[���ɂ��邩

int					counter;
int					effectcounter;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pD3DTexturePlayer		= NULL;
	g_pMeshPlayer			= NULL;
	g_pD3DXMatBuffPlayer	= NULL;

	g_player.pos			= D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot			= D3DXVECTOR3(0.0f, 9.45f, 0.0f);
	g_player.rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius		= PLAYER_RADIUS;

	g_player.use			= true;
	//g_player.draw			= true;
	
	centerlineflag			= true;
	leftlineflag			= false;				// �����[���ɂ��邩
	rightlineflag			= false;				// �E���[���ɂ��邩
	moveflag				= false;
	moveflag_left			= false;
	moveflag_right			= false;

	moveamount				= 0.0f;
	counter					= 0;
	effectcounter			= 0;

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(MODEL_PLAYER,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&g_pD3DXMatBuffPlayer,
								NULL,
								&g_nNumMatPlayer,
								&g_pMeshPlayer)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&g_pD3DTexturePlayer);	// �ǂݍ��ރ������[
#endif

	// �e�̐ݒ�
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);		// �e�̐ݒ�


	//D3DXVECTOR3 rotCamera;
	//// �J�����̌����擾
	//rotCamera = GetRotCamera();
	//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// ����(�O)


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if(g_pD3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	if(g_pMeshPlayer != NULL)
	{// ���b�V���̊J��
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	if(g_pD3DXMatBuffPlayer != NULL)
	{// �}�e���A���̊J��
		g_pD3DXMatBuffPlayer->Release();
		g_pD3DXMatBuffPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_player.use == true)
	{
		// ���s���x
		if (g_player.move.z <= VALUE_MOVE_MAX_PLAYER)
		{
			g_player.move.z += VALUE_MOVE_PLAYER;
		}
		//else
		//{
		//	g_player.move.z = VALUE_MOVE_MAX_PLAYER;
		//}

		// �L�[�{�[�h���͂ňړ�
		if (moveflag == false && centerlineflag == true)	// �������[���ɂ���Ƃ�
		{
			if (GetKeyboardTrigger(DIK_A) || IsButtonTriggered(0, BUTTON_LEFT))
			{
				moveflag = true;
				moveflag_left = true;
				centerlineflag = false;
				leftlineflag = true;
			}
			else if (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(0, BUTTON_RIGHT))
			{
				moveflag = true;
				moveflag_right = true;
				centerlineflag = false;
				rightlineflag = true;
			}
		}



		if (moveflag == false && leftlineflag == true)								// �����[���ɂ���Ƃ�
		{
			if (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(0, BUTTON_RIGHT))
			{
				moveflag = true;
				moveflag_right = true;
				leftlineflag = false;
				centerlineflag = true;
			}
		}



		if (moveflag == false && rightlineflag == true)								// �E���[���ɂ���Ƃ�
		{
			if (GetKeyboardTrigger(DIK_A) || IsButtonTriggered(0, BUTTON_LEFT))
			{
				moveflag = true;
				moveflag_left = true;
				rightlineflag = false;
				centerlineflag = true;
			}
		}


		//D3DXVECTOR3 rotCamera;
		//float fDiffRotY;

		//// �J�����̌����擾
		//rotCamera = GetRotCamera();

		// �ړ�
		if (moveflag == true)
		{
			if (moveflag_left == true)
			{
				g_player.pos.x -= SIDE_MOVE_PLAYER;
				moveamount += SIDE_MOVE_PLAYER;

				////g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f; // ����(���O)

				if (moveamount >= SIDE_MOVE_PLAYER_MAX)
				{
					moveflag = false;
					moveflag_left = false;
					moveamount = 0.0f;

					//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// ����(�O)
				}
			}
			else if (moveflag_right == true)
			{
				g_player.pos.x += SIDE_MOVE_PLAYER;
				moveamount += SIDE_MOVE_PLAYER;

				//g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f; // ����(�E�O)

				if (moveamount >= SIDE_MOVE_PLAYER_MAX)
				{
					moveflag = false;
					moveflag_right = false;
					moveamount = 0.0f;

					//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// ����(�O)
				}
			}
		}

















		//D3DXVECTOR3 rotCamera;
		//float fDiffRotY;

		//// �J�����̌����擾
		//rotCamera = GetRotCamera();


		//// �e����
		//if (GetKeyboardTrigger(DIK_SPACE))
		//{
		//	D3DXVECTOR3 pos;
		//	D3DXVECTOR3 move;

		//	pos.x = g_player.pos.x - sinf(g_player.rot.y) * 10.0f;
		//	pos.y = g_player.pos.y;
		//	pos.z = g_player.pos.z - cosf(g_player.rot.y) * 10.0f;

		//	move.x = -sinf(g_player.rot.y) * VALUE_MOVE_BULLET;
		//	move.y = 0.0f;
		//	move.z = -cosf(g_player.rot.y) * VALUE_MOVE_BULLET;

		//	SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

		//	// SE�Đ�
		//	//PlaySound(SOUND_LABEL_SE_SHOT);
		//}

		//// �ړI�̊p�x�܂ł̍���
		//fDiffRotY = g_player.rotDest.y - g_player.rot.y;
		//if(fDiffRotY > D3DX_PI)
		//{
		//	fDiffRotY -= D3DX_PI * 2.0f;
		//}
		//if(fDiffRotY < -D3DX_PI)
		//{
		//	fDiffRotY += D3DX_PI * 2.0f;
		//}

		//// �ړI�̊p�x�܂Ŋ�����������
		//g_player.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;
		//if(g_player.rot.y > D3DX_PI)
		//{
		//	g_player.rot.y -= D3DX_PI * 2.0f;
		//}
		//if(g_player.rot.y < -D3DX_PI)
		//{
		//	g_player.rot.y += D3DX_PI * 2.0f;
		//}

		///// �ʒu�ړ�
		//g_player.pos.x += g_player.move.x;
		//g_player.pos.y += g_player.move.y;
		g_player.pos.z += g_player.move.z;

		//if(g_player.pos.x < -630.0f)
		//{
		//	g_player.pos.x = -630.0f;
		//}
		//if(g_player.pos.x > 630.0f)
		//{
		//	g_player.pos.x = 630.0f;
		//}
		//if(g_player.pos.y < 10.0f)
		//{
		//	g_player.pos.y = 10.0f;
		//}
		//if(g_player.pos.y > 150.0f)
		//{
		//	g_player.pos.y = 150.0f;
		//}
		//if(g_player.pos.z > 630.0f)
		//{
		//	g_player.pos.z = 630.0f;
		//}
		//if(g_player.pos.z < -630.0f)
		//{
		//	g_player.pos.z = -630.0f;
		//}

		//// �ړ��ʂɊ�����������
		//g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;
		//g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		//g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		// �e�̈ʒu�ݒ�
		{
			SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

			float fSizeX = 20.0f + (g_player.pos.y - 10.0f) * 0.05f;
			if (fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (g_player.pos.y - 10.0f) * 0.05f;
			if (fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			SetVertexShadow(g_player.nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (g_player.pos.y - 10.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}

		if ((g_player.move.x * g_player.move.x
			+ g_player.move.y * g_player.move.y
			+ g_player.move.z * g_player.move.z) > 1.0f)
		{
			D3DXVECTOR3 pos;

			pos.x = g_player.pos.x + sinf(g_player.rot.y) * 10.0f;
			pos.y = g_player.pos.y + 2.0f;
			pos.z = g_player.pos.z + cosf(g_player.rot.y) * 10.0f;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);
		}




		// �G�l�~�[�Ƃ̓����蔻��
		ENEMY *pEnemy;		 //	�G�l�~�[��ݒ�
		pEnemy = GetEnemy(); // �G�l�~�[���擾
		//int enemycnt = GetEnemyCounter();

		for (int i = 0; i < ENEMY_MAX; i++, pEnemy++)
		{
			if (pEnemy->use == true)
			{
				float fLength;

				fLength = (g_player.pos.x - pEnemy->pos.x) * (g_player.pos.x - pEnemy->pos.x)
					+ (g_player.pos.y - pEnemy->pos.y) * (g_player.pos.y - pEnemy->pos.y)
					+ (g_player.pos.z - pEnemy->pos.z) * (g_player.pos.z - pEnemy->pos.z);
				if (fLength < (g_player.fRadius + pEnemy->fRadius) * (g_player.fRadius + pEnemy->fRadius)) // �����蔻��
				{
					//// �A�C�e������
					//DeleteItem(nCntItem);

					SetExplosion(g_player.pos, 300.0f, 300.0f);

					pEnemy->use = false;
					//enemycnt--;

					g_player.use = false;

					counter = 0;

					SetFade(FADE_OUT);

					//SetMode(MODE_TITLE);

				//	// SE�Đ�
				//	//PlaySound(SOUND_LABEL_SE_COIN);
				}

				//if (CheckHitBC(g_player.pos, pEnemy->pos, 10.0f, 10.0f, 10.0f))
				//{
				//	//// �A�C�e������
				//	//DeleteItem(nCntItem);

				//	// �X�R�A���Z
				//	ChangeScore(1000);
				//			
				//	pEnemy->use = false;

				//	SetMode(MODE_TITLE);
				//}
			}
		}

		if (counter < 500)
		{
			counter += 1;
		}
		if (counter >= 500)
		{
			//ENEMY *enemy = GetEnemy();
			//if (enemy[0].use == false)
			//{
			//	if (enemy[1].use == false)
			//	{
			//		if (enemy[2].use == false)
			//		{
			counter = 0;
			g_player.pos.z = 0;

			// InitEnemy();���悤�Ǝv�������ǁA�A���̕����������ƂɋC�Â���w
			SetEnemyPos();
			ENEMY *enemy = GetEnemy(); // �|�C���^�[�̏�����
			for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			{
				enemy->use = true;
			}

			//		}
			//	}
			//}
		}




		//// �A�C�e���Ƃ̓����蔻��
		//{
		//	ITEM *pItem;

		//	// �A�C�e�����擾
		//	pItem = GetItem();
		//	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		//	{
		//		if(pItem->bUse == true)
		//		{
		//			float fLength;

		//			fLength = (g_player.pos.x - pItem->pos.x) * (g_player.pos.x - pItem->pos.x)
		//						+ (g_player.pos.y - pItem->pos.y) * (g_player.pos.y - pItem->pos.y)
		//						+ (g_player.pos.z - pItem->pos.z) * (g_player.pos.z - pItem->pos.z);
		//			if(fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius)) // �����蔻��?
		//			{
		//				// �A�C�e������
		//				DeleteItem(nCntItem);

		//				// �X�R�A���Z
		//				ChangeScore(100);

		//				// SE�Đ�
		//				//PlaySound(SOUND_LABEL_SE_COIN);
		//			}
		//		}
		//	}
		//}
	}

	else
	{
		if (counter < 20)
		{
			counter++;
			//effectcounter++;
		}
		else
		{
			counter = 0;
			SetExplosion(g_player.pos, 300.0f, 300.0f);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	//if (g_player.use == true)
	//{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldPlayer);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			// �`��
			g_pMeshPlayer->DrawSubset(nCntMat);
		}
	//}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2 ,float size3)
{
	if ((size1 + size2 + size3) * (size1 + size2 + size3) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z))
	{
		return true;
	}

	return false;
}
