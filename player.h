//=============================================================================
//
// �v���C���[���� [player.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

#define SIDE_MOVE_PLAYER_MAX				(130.0f) // ���̃}�b�N�X�ړ���

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
	//bool		draw;		// �`��t���O
} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);

bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2, float size3);

#endif
