//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

void SetVertexResultBG(void);

#endif
