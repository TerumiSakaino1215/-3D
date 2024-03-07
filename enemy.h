//=============================================================================
//
// �v���C���[���� [enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define ENEMY_MAX				(15)							// �G�l�~�[�̐�
#define ENEMY_POS_HEIGHT		(20.0f)						// �G�l�~�[�̈ʒu�̍���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ���݂̌���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID

	bool		use;		// �g�p�t���O
	bool		draw;		// �`��t���O
} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);

D3DXVECTOR3 GetPositionEnemy(void);
D3DXVECTOR3 GetRotationEnemy(void);
D3DXVECTOR3 GetRotationDestEnemy(void);
D3DXVECTOR3 GetMoveEnemy(void);

//int GetEnemyCounter(void);
void SetEnemyPos(void);

#endif
