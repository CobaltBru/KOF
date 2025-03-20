#include "UserInterface.h"
#include "Image.h"
#include "Character.h"

void UserInterface::Init()
{
    hpCalculate = 214*1.4 /100.0f;
    p1Health = 100;
    p2Health = 100;
    for (int i = 0; i < eBattle::eBattleEnd; i++)
    {
        battleImage[i] = new Image();
    }
    // 스테이지
    if (FAILED(battleImage[eBattle::Stage]->Init(TEXT("Image/UI/Japan_Stage.bmp"), WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/Japan_Stage.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
    // 체력바
    if (FAILED(battleImage[eBattle::HP_bar]->Init(TEXT("Image/UI/HP_bar.bmp"), 676*1.4, 79*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
    // p1체력
    if (FAILED(battleImage[eBattle::HP_gage_p1]->Init(TEXT("Image/UI/HP_gage.bmp"), 214*1.4, 9*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
    // p2체력
    if (FAILED(battleImage[eBattle::HP_gage_p2]->Init(TEXT("Image/UI/HP_gage_2.bmp"), 214*1.4, 9*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
    // 시간 무한
    if (FAILED(battleImage[eBattle::Time_infinite]->Init(TEXT("Image/UI/time_infinite.bmp"), 640, 480, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/king.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
    //// p1프로필
    //if (FAILED(battleImage[eBattle::P1Character]->Init(TEXT("Image/UI/king.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255))))
    //{
    //    MessageBox(g_hWnd, TEXT("Image/king.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    //}

    //// p2프로필
    //if (FAILED(battleImage[eBattle::P2Character]->Init(TEXT("Image/UI/king_reverse.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255))))
    //{
    //    MessageBox(g_hWnd, TEXT("Image/king_reverse.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    //}
}

void UserInterface::Release()
{
	for (int i = 0; i < eBattle::eBattleEnd; i++)
	{
        if (i == eBattle::P1Character || i == eBattle::P2Character)
            continue;
		if (battleImage[i])
		{
            battleImage[i]->Release();
            delete battleImage[i];
            battleImage[i] = nullptr;
		}
	}

    if (characterP1)
    {
        characterP1 = nullptr;
    }

    if (characterP2)
    {
        characterP2 = nullptr;
    }
}

void UserInterface::Update()
{
    // 캐릭터 HP 동기화
    p1Health = *(characterP1->getCurrentHp());
    p2Health = *(characterP2->getCurrentHp());

    *battleImage[eBattle::P1Character] = characterP1->getProfile();
    *battleImage[eBattle::P2Character] = characterP1->getProfile();

}

void UserInterface::Render(HDC hdc)
{
    battleImage[eBattle::Stage]->Render(hdc, 0, 0);

    battleImage[eBattle::HP_bar]->Render(hdc, (WINSIZE_X - 676 *1.4) / 2, 0); // w = 676

    battleImage[eBattle::Time_infinite]->Render(hdc, (WINSIZE_X-640)/2 +8, -72);
    
    battleImage[eBattle::HP_gage_p1]->HpRender(hdc, WINSIZE_X / 2 - 133*1.4, 38,
        hpCalculate, p1Health, true);
    battleImage[eBattle::HP_gage_p2]->HpRender(hdc, WINSIZE_X / 2 + 133*1.4, 38,
        hpCalculate, p2Health, false);
    
    battleImage[eBattle::P1Character]->Render(hdc, WINSIZE_X / 2 - (85 + 238) * 1.4, -28); // w = 85
    battleImage[eBattle::P2Character]->Render(hdc, WINSIZE_X / 2 + 238*1.4, -28);
}
UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}
