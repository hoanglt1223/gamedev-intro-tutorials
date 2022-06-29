#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON && !mario->IsOnPlatform())
		{
			mario->SetState(MARIO_STATE_AIRBORNE);
		}
		else
			mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R:
		mario->Respawn();
		break;
	case DIK_P:
		if (CGame::GetInstance()->IsPaused()) CGame::GetInstance()->Unpause();
		else CGame::GetInstance()->Pause();
		break;
	case DIK_A:
		/*if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->GetState() != MARIO_STATE_SITDOWN && !mario->GetIsReadyToRun() && !mario->GetIsHolding())
			mario->SetState(MARIO_STATE_TAIL_ATTACK);*/
		if (mario->GetLevel() == MARIO_LEVEL_RACOON && !mario->IsSitting() && !mario->isHolding)
			mario->SetState(MARIO_STATE_TAIL_ATTACK);
		/*if (mario->GetLevel() == MARIO_LEVEL_FIRE && !mario->GetIsHolding()) mario->ShootFireBall();
		mario->SetIsReadyToRun(true);
		mario->SetIsReadyToHold(true);*/
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		if (mario->isHolding) {
			mario->isReadyToHold = false;
			mario->isHolding = false;
		}
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_S))
	{
		if (game->IsKeyDown(DIK_LEFT))
		{
			if (mario->IsAirBorne()) {
				mario->SetState(MARIO_STATE_AIRBORNE_LEFT);
			}
			else if (mario->IsPowerMaxed()) {
				mario->SetState(MARIO_STATE_AIRBORNE_LEFT);
			}
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->IsAirBorne()) {
				mario->SetState(MARIO_STATE_AIRBORNE_RIGHT);
			}
			else if (mario->IsPowerMaxed()) {
				mario->SetState(MARIO_STATE_AIRBORNE_RIGHT);
			}
		}
		/*else
			mario->SetState(MARIO_STATE_AIRBORNE);*/
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)) {
			mario->isReadyToHold = true;
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else {
			mario->isReadyToHold = false;
			mario->isHolding = false;
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	/*else if (game->IsKeyDown(DIK_S)) {
		float mVx, mVy;
		mario->GetSpeed(mVx, mVy);
		if (mario->GetDirection() > 0) {
			if (abs(mVx) == MARIO_RUNNING_SPEED) {
				mario->SetState(MARIO_STATE_AIRBORNE_RIGHT);
			}
		}
		else {
			mario->SetState(MARIO_STATE_AIRBORNE_LEFT);
		}
	}*/
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) {
			mario->isReadyToHold = true;
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else {
			mario->isReadyToHold = false;
			mario->isHolding = false;
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}