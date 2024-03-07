//=============================================================================
//
// プレイヤー処理 [player.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER			"data/MODEL/carmodel.x"	// 読み込むモデル名
#define	PLAYER_RADIUS			(12.0f)						// 半径
#define	VALUE_MOVE_PLAYER		(0.3f)						// 加速度
#define	VALUE_MOVE_MAX_PLAYER	(45.0f)						// 最高速度
#define	RATE_MOVE_PLAYER		(0.025f)					// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.025f)			// 回転速度
#define	RATE_ROTATE_PLAYER		(0.10f)						// 回転慣性係数
#define	VALUE_MOVE_BULLET		(7.5f)						// 弾の移動速度

#define SIDE_MOVE_PLAYER					(14.0f)	 // プレイヤーの移動量
//#define SIDE_MOVE_PLAYER_MAX				(140.0f) // 一回のマックス移動量
//#define SIDE_MOVE_PLAYER_MAX_LEFT			(100.f)  // プレイヤーが動ける最大値
//#define SIDEMOVE_PLAYER_MAX_RIGHT		(380.f)  // プレイヤーが動ける最大値

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshPlayer;				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffPlayer;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer;			// 属性情報の総数

D3DXMATRIX			g_mtxWorldPlayer;			// ワールドマトリックス
PLAYER				g_player;					// プレイヤーワーク

bool				moveflag;					// 移動フラグ
bool				moveflag_left;				// 上移動フラグ
bool				moveflag_right;				// 下移動フラグ

float				moveamount;					// 移動量

bool				leftlineflag;				// 左レーンにいるか
bool				rightlineflag;				// 右レーンにいるか
bool				centerlineflag;				// 中央レーンにいるか

int					counter;
int					effectcounter;

//=============================================================================
// 初期化処理
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
	leftlineflag			= false;				// 左レーンにいるか
	rightlineflag			= false;				// 右レーンにいるか
	moveflag				= false;
	moveflag_left			= false;
	moveflag_right			= false;

	moveamount				= 0.0f;
	counter					= 0;
	effectcounter			= 0;

	// Xファイルの読み込み
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
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー
#endif

	// 影の設定
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);		// 影の設定


	//D3DXVECTOR3 rotCamera;
	//// カメラの向き取得
	//rotCamera = GetRotCamera();
	//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// 向き(前)


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if(g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	if(g_pMeshPlayer != NULL)
	{// メッシュの開放
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	if(g_pD3DXMatBuffPlayer != NULL)
	{// マテリアルの開放
		g_pD3DXMatBuffPlayer->Release();
		g_pD3DXMatBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (g_player.use == true)
	{
		// 走行速度
		if (g_player.move.z <= VALUE_MOVE_MAX_PLAYER)
		{
			g_player.move.z += VALUE_MOVE_PLAYER;
		}
		//else
		//{
		//	g_player.move.z = VALUE_MOVE_MAX_PLAYER;
		//}

		// キーボード入力で移動
		if (moveflag == false && centerlineflag == true)	// 中央レーンにいるとき
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



		if (moveflag == false && leftlineflag == true)								// 左レーンにいるとき
		{
			if (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(0, BUTTON_RIGHT))
			{
				moveflag = true;
				moveflag_right = true;
				leftlineflag = false;
				centerlineflag = true;
			}
		}



		if (moveflag == false && rightlineflag == true)								// 右レーンにいるとき
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

		//// カメラの向き取得
		//rotCamera = GetRotCamera();

		// 移動
		if (moveflag == true)
		{
			if (moveflag_left == true)
			{
				g_player.pos.x -= SIDE_MOVE_PLAYER;
				moveamount += SIDE_MOVE_PLAYER;

				////g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f; // 向き(左前)

				if (moveamount >= SIDE_MOVE_PLAYER_MAX)
				{
					moveflag = false;
					moveflag_left = false;
					moveamount = 0.0f;

					//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// 向き(前)
				}
			}
			else if (moveflag_right == true)
			{
				g_player.pos.x += SIDE_MOVE_PLAYER;
				moveamount += SIDE_MOVE_PLAYER;

				//g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f; // 向き(右前)

				if (moveamount >= SIDE_MOVE_PLAYER_MAX)
				{
					moveflag = false;
					moveflag_right = false;
					moveamount = 0.0f;

					//g_player.rotDest.y = D3DX_PI + rotCamera.y;		// 向き(前)
				}
			}
		}

















		//D3DXVECTOR3 rotCamera;
		//float fDiffRotY;

		//// カメラの向き取得
		//rotCamera = GetRotCamera();


		//// 弾発射
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

		//	// SE再生
		//	//PlaySound(SOUND_LABEL_SE_SHOT);
		//}

		//// 目的の角度までの差分
		//fDiffRotY = g_player.rotDest.y - g_player.rot.y;
		//if(fDiffRotY > D3DX_PI)
		//{
		//	fDiffRotY -= D3DX_PI * 2.0f;
		//}
		//if(fDiffRotY < -D3DX_PI)
		//{
		//	fDiffRotY += D3DX_PI * 2.0f;
		//}

		//// 目的の角度まで慣性をかける
		//g_player.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;
		//if(g_player.rot.y > D3DX_PI)
		//{
		//	g_player.rot.y -= D3DX_PI * 2.0f;
		//}
		//if(g_player.rot.y < -D3DX_PI)
		//{
		//	g_player.rot.y += D3DX_PI * 2.0f;
		//}

		///// 位置移動
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

		//// 移動量に慣性をかける
		//g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;
		//g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		//g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		// 影の位置設定
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

			// エフェクトの設定
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);
		}




		// エネミーとの当たり判定
		ENEMY *pEnemy;		 //	エネミーを設定
		pEnemy = GetEnemy(); // エネミーを取得
		//int enemycnt = GetEnemyCounter();

		for (int i = 0; i < ENEMY_MAX; i++, pEnemy++)
		{
			if (pEnemy->use == true)
			{
				float fLength;

				fLength = (g_player.pos.x - pEnemy->pos.x) * (g_player.pos.x - pEnemy->pos.x)
					+ (g_player.pos.y - pEnemy->pos.y) * (g_player.pos.y - pEnemy->pos.y)
					+ (g_player.pos.z - pEnemy->pos.z) * (g_player.pos.z - pEnemy->pos.z);
				if (fLength < (g_player.fRadius + pEnemy->fRadius) * (g_player.fRadius + pEnemy->fRadius)) // 当たり判定
				{
					//// アイテム消去
					//DeleteItem(nCntItem);

					SetExplosion(g_player.pos, 300.0f, 300.0f);

					pEnemy->use = false;
					//enemycnt--;

					g_player.use = false;

					counter = 0;

					SetFade(FADE_OUT);

					//SetMode(MODE_TITLE);

				//	// SE再生
				//	//PlaySound(SOUND_LABEL_SE_COIN);
				}

				//if (CheckHitBC(g_player.pos, pEnemy->pos, 10.0f, 10.0f, 10.0f))
				//{
				//	//// アイテム消去
				//	//DeleteItem(nCntItem);

				//	// スコア加算
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

			// InitEnemy();しようと思ったけど、、↓の方がいいことに気づいたw
			SetEnemyPos();
			ENEMY *enemy = GetEnemy(); // ポインターの初期化
			for (int i = 0; i < ENEMY_MAX; i++, enemy++)
			{
				enemy->use = true;
			}

			//		}
			//	}
			//}
		}




		//// アイテムとの当たり判定
		//{
		//	ITEM *pItem;

		//	// アイテムを取得
		//	pItem = GetItem();
		//	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		//	{
		//		if(pItem->bUse == true)
		//		{
		//			float fLength;

		//			fLength = (g_player.pos.x - pItem->pos.x) * (g_player.pos.x - pItem->pos.x)
		//						+ (g_player.pos.y - pItem->pos.y) * (g_player.pos.y - pItem->pos.y)
		//						+ (g_player.pos.z - pItem->pos.z) * (g_player.pos.z - pItem->pos.z);
		//			if(fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius)) // 当たり判定?
		//			{
		//				// アイテム消去
		//				DeleteItem(nCntItem);

		//				// スコア加算
		//				ChangeScore(100);

		//				// SE再生
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
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	//if (g_player.use == true)
	//{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldPlayer);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			// 描画
			g_pMeshPlayer->DrawSubset(nCntMat);
		}
	//}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
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
