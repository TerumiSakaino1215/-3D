//=============================================================================
//
// エネミー処理 [enemy.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MODEL_ENEMY			"data/MODEL/carmodel2.x"	// 読み込むモデル名
#define	ENEMY_RADIUS			(12.0f)						// 半径
#define	VALUE_MOVE_ENEMY		(0.05f)						// 加速度
#define	VALUE_MOVE_MAX_ENEMY	(4.0f)						// 最高速度
#define	RATE_MOVE_ENEMY			(0.025f)					// 移動慣性係数
#define	VALUE_ROTATE_ENEMY		(D3DX_PI * 0.025f)			// 回転速度
#define	RATE_ROTATE_ENEMY		(0.10f)						// 回転慣性係数
#define	VALUE_MOVE_BULLET		(7.5f)						// 弾の移動速度



//#define COUNT_MAX				(2)						// カウンターのマックス値

//#define SIDE_MOVE_ENEMY					(10.0f)	 // プレイヤーの移動量
//#define SIDE_MOVE_ENEMY_MAX				(140.0f) // 一回のマックス移動量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshEnemy;				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffEnemy;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatEnemy;			// 属性情報の総数

D3DXMATRIX			g_mtxWorldEnemy;			// ワールドマトリックス
//ENEMY				g_enemy;					// エネミーワーク
ENEMY				g_enemy[ENEMY_MAX];				// エネミーワーク

struct D3DXVECTOR3	playerpos;					//	プレイヤーの位置

//D3DXVECTOR3			enemypos[10]
//{
//	(0.0f, ENEMY_POS_HEIGHT, 2500.0f),
//SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 4000.0f;
//-SIDE_MOVE_PLAYER_MAX, ENEMY_POS_HEIGHT, 6000.0f;
//};

	

//int					enemycnt;				// エネミーのカウンター(ダブらないように敵の数を管理)
//int					random;					// ランダム処理のやつ

//int					llusefrag;				// レフトレーン使用フラグ
//int					clusefrag;				// センターレーン使用フラグ
//int					rlusefrag;				// ライトレーン使用フラグ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &g_enemy[0];

	// ランダムにしたいところ
	//for (int i = 0; i < ENEMY_MAX; i++)							// ようわからん
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
		// ゴリ押しw

	enemy = &g_enemy[0];
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 2500.0f); // z値 2500
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

		// Xファイルの読み込み
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
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FILENAME,		// ファイルの名前
			&g_pD3DTextureEnemy);	// 読み込むメモリー
#endif

		// 影の設定
		enemy->nIdxShadow = SetShadow(enemy->pos, enemy->fRadius * 2.0f, enemy->fRadius * 2.0f);		// 影の設定
	}

	//enemycnt = 0;
	//random    = 0;

	//llusefrag = false;
	//clusefrag = false;
	//rlusefrag = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_pD3DTextureEnemy != NULL)
		{// テクスチャの開放
			g_pD3DTextureEnemy->Release();
			g_pD3DTextureEnemy = NULL;
		}

		if (g_pMeshEnemy != NULL)
		{// メッシュの開放
			g_pMeshEnemy->Release();
			g_pMeshEnemy = NULL;
		}

		if (g_pD3DXMatBuffEnemy != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffEnemy->Release();
			g_pD3DXMatBuffEnemy = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &g_enemy[0]; // ポインターの初期化


	/*
	if () // ランダム制御 enemy[0]の場合
	{
		// enemy[1]=使用 且つ enemy[2]=使用 以外のときランダムで出現 みたいな

		// trueにするコードを入れる
	}

	// enemy[1]の場合...
	// enemy[2]の場合...
	*/

	// 上記ではなく、、、
	// シンプルにカウンターで制御した方がいいのではないかということが判明


	//enemy = &g_enemy[0]; // ポインターの初期化
	
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		//if (enemy->use == false && enemycnt < COUNT_MAX) // 他のエネミーが両方とも使われてないとき
		//{// ランダム制御
		//	random = rand() % 90;
		//	if (random == 0)
		//	{
		//		enemy->use = true;
		//		playerpos = GetPositionPlayer();
		//		enemy->pos.z = playerpos.z + 2000.0f;
		//		enemycnt++;
		//	}
		//}

		if (enemy->use == true) // エネミーが使われてるとき
		{
			// 移動処理
			enemy->pos.z += enemy->move.z;		// 移動速度を反映

			// プレイヤーの位置取得
			playerpos = GetPositionPlayer();
			if (enemy->pos.z <= playerpos.z - 100.0f) // プレイヤーより後ろ(画面外)に行ったら
			{// 未使用状態にして位置を初期化
				enemy->use = false;
				enemy->pos.z = 30000.0f;
				//enemycnt--;
			}
		}

		// 影の位置設定
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

			// エフェクトの設定
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
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	ENEMY *enemy = &g_enemy[0]; // ポインターの初期化
	
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemy->pos.x, enemy->pos.y, enemy->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemy);

				// 描画
				g_pMeshEnemy->DrawSubset(nCntMat);
			}
		}

		{// マテリアルをデフォルトに戻す
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			pDevice->SetMaterial(&mat.MatD3D);
		}
	}
}

//=============================================================================
// エネミーを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_enemy[0];
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(void)
{
	return g_enemy->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(void)
{
	return g_enemy->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(void)
{
	return g_enemy->rotDest;
}

//=============================================================================
// 移動量取得
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
	enemy->pos = D3DXVECTOR3(0.0f, ENEMY_POS_HEIGHT, 2500.0f); // z値 2500
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