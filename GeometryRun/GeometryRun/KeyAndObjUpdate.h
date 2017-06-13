#pragma once

#include "GameObjectManager.h"
#include "BackGround.h"
#include "Input.h"
#include "Player.h"
#include "Boss2.h"
#include "Pause.h"
#include "SoundSystem.h"
#include "fmod.h"

#define FLAG_IMPORTANTKEY 2

float winMaxX, winMaxY, winMinX, winMinY;

// 碰撞检测主对象，方便遍历时使用
GameObj *pInstForCollisionDetect;

// ======================
// 帧时间：Unity中的dt
// ======================
double frameTime;

Status GetWinMaxMinXY();

Status KeyUpdate();

Status ObjUpdate();

Status Visit_CollisionDetect(insNode* pinsNode);

Status Visit_Matrix2DCount(insNode* pinsNode);

// never used
Status BossUpdate(int level, clock_t LevelTime, float bossOccurTime);

Status Visit_DestroyObj(insNode* pinsNode);

Status Visit_DrawObj(insNode* pinsNode);

