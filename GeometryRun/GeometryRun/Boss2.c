#include "Boss2.h"

Status Boss2Load()
{
	// ========================
	// boss2
	// ========================
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_BOSS2, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/boss.png"), theBaseList);
	return OK;
}

Status Boss2Start()
{
	pBoss2 = NULL;
	Boss2ImpactSpeed = 1.0f;
	Boss2Status = B2STATUS_ENTER;
	Boss2SkillCycle = 100.0f;
	Boss2HP = 50;
	Boss2AngerHP = 40;
	// ����Ѳ�߷�Χ
	Boss2PatrolMaxY = 100.0f;
	Boss2PatrolMinY = -100.0f;
	// ����ľ���
	Boss2EnterX = 30.0f;
	// ��ײ����x
	Boss2ImpactX = -400.0f;
	Vector2DSet(&Boss2EnterVel, -2.3f, 0.0f);
	Vector2DSet(&Boss2MoveUpward, 0.0f, 1.0f);
	Vector2DSet(&Boss2MoveDownward, 0.0f, -1.0f);
	Vector2DSet(&Boss2IniPos, 500.0f, 0.0f);
	Vector2DSet(&Boss2ImpactVelLeft, -10.0f, 0.0f);
	Vector2DSet(&Boss2ImpactVelRight, 10.0f, 0.0f);
	Boss2SkillLoad();
	return OK;
}

Status Boss2SkillLoad()
{
	Boss2SkillCount = 2;
	boss2skills[0] = Boss2Skill_CreateMonster;
	boss2skills[1] = Boss2Skill_CreateBlock;
	
	return OK;
}

Status Boss2Update(GameObj* pInst)
{
	pBoss2->posCurr.x += pBoss2->velCurr.x;
	pBoss2->posCurr.y += pBoss2->velCurr.y;
	switch (Boss2Status)
	{
		case B2STATUS_ENTER:
		{
			if (pBoss2->posCurr.x <= winMaxX - Boss2EnterX)
			{
 				Boss2Status = B2STATUS_NORMAL;
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				break;
			}
			break;
		}
		case B2STATUS_NORMAL:
		{
			if (Boss2HP <= Boss2AngerHP)
			{
				Boss2Status = B2STATUS_ANGRY;
				Boss2Skill_GetAngey();
				break;
			}
			if (pBoss2->posCurr.y >= Boss2PatrolMaxY)
			{
				SetObjSpeed(pBoss2, Boss2MoveDownward);
				Boss2UseSkillRandomly(passTime);
			}
			else if (pBoss2->posCurr.y <= Boss2PatrolMinY)
			{
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				Boss2UseSkillRandomly(passTime);
			}
			break;
		}
		case B2STATUS_ANGRY:
		{
			if (pBoss2->posCurr.y >= Boss2PatrolMaxY)
			{
				SetObjSpeed(pBoss2, Boss2MoveDownward);
				Boss2UseSkillRandomly(passTime);
			}
			else if (pBoss2->posCurr.y <= Boss2PatrolMinY)
			{
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				Boss2UseSkillRandomly(passTime);
			}
			break;
		}
		case B2STATUS_IMPACTL:
		{
			if (pBoss2->posCurr.x <= Boss2ImpactX)
			{
				SetObjSpeed(pBoss2, Boss2ImpactVelRight);
				Boss2Status = B2STATUS_IMPACTR;
			}
			break;
		}
		case B2STATUS_IMPACTR:
		{
			if (pBoss2->posCurr.x >= winMaxX - Boss2EnterX)
			{
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				Boss2Status = B2STATUS_ANGRY;
			}
			break;
		}
		default:
			break;
	}
	if (Boss2HP <= 0)
		Boss2Dead();
	return OK;
}

Status Boss2Collision(insNode* pinsNode)
{
	return OK;
}

Status Boss2Skill_CreateMonster(float curTime)
{
	float iniFloat = 1.0f;
	float iniMinX = winMaxX - 40.0f, iniMaxX = winMaxX, iniMinY = winMinY, iniMaxY = winMaxY, iniMinVx = -4.0f, iniMaxVx = -2.0f;
	float iniMinVy = 0.0f, iniMaxVy = 0.0f, iniMinDir = -3.0f, iniMaxDir = 3.0f;

	return CreateSomeObjAtSameTimeWithRange(curTime, 3, OTYPE_BLOCK, SIZE_BLOCK, theBaseList, 0, NULL, iniMinX, iniMaxX, iniMinY, iniMaxY, iniMinVx, iniMaxVx, iniMinVy, iniMaxVy, iniMinDir, iniMaxDir);
}

Status Boss2Skill_CreateBlock(float curTime)
{
	float iniFloat = 1.0f;
	float iniMinX = winMaxX - 40.0f, iniMaxX = winMaxX, iniMinY = winMinY, iniMaxY = winMaxY, iniMinVx = -4.0f, iniMaxVx = -2.0f;
	float iniMinVy = 0.0f, iniMaxVy = 0.0f, iniMinDir = 0.0f, iniMaxDir = 0.0f;

	return CreateSomeObjAtSameTimeWithRange(curTime, 5, OTYPE_MONSTER, SIZE_MONSTER, theBaseList, 0, NULL, iniMinX, iniMaxX, iniMinY, iniMaxY, iniMinVx, iniMaxVx, iniMinVy, iniMaxVy, iniMinDir, iniMaxDir);

}

Status Boss2Skill_Impact(float curTime)
{
	Boss2Status = B2STATUS_IMPACTL;
	SetObjSpeed(pBoss2, Boss2ImpactVelLeft);
	return OK;
}

Status Boss2Skill_GetAngey()
{
	Vector2DSet(&Boss2MoveUpward, 0.0f, 1.7f);
	Vector2DSet(&Boss2MoveDownward, 0.0f, -1.7f);
	Boss2SkillCount = 3;
	boss2skills[2] = Boss2Skill_Impact;
	return OK;
}

Status Boss2UseSkillRandomly(float curTime)
{
	int CurSkill = rand() % Boss2SkillCount;
	boss2skills[CurSkill](curTime + OFFSETTIME);
	return OK;
}

Status Boss2GetHurt(int hurt)
{
	Boss2HP -= hurt;
	if (PlayerHP <= 0)
		PlayerDead();
}

Status Boss2Dead(){
	GameObjDelete(pBoss2);
}