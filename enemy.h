//=============================================================================
//
// プレイヤー処理 [enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define ENEMY_MAX				(15)							// エネミーの数
#define ENEMY_POS_HEIGHT		(20.0f)						// エネミーの位置の高さ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 現在の向き
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID

	bool		use;		// 使用フラグ
	bool		draw;		// 描画フラグ
} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
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
