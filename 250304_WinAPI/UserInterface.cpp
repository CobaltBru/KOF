#include "UserInterface.h"
#include "Image.h"
void UserInterface::Init()
{
    hpCalculate = 214*1.4 /100.0f;
    p1Health = 100;
    p2Health = 100;
    for (int i = 0; i < eBattle::eBattleEnd; i++)
    {
        battleImage[i] = new Image();
    }
    // ü�¹�
    if (FAILED(battleImage[eBattle::HP_bar]->Init(TEXT("Image/HP_bar.bmp"), 676*1.4, 79*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }
    // p1ü��
    if (FAILED(battleImage[eBattle::HP_gage_p1]->Init(TEXT("Image/HP_gage.bmp"), 214*1.4, 9*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }
    // p2ü��
    if (FAILED(battleImage[eBattle::HP_gage_p2]->Init(TEXT("Image/HP_gage_2.bmp"), 214*1.4, 9*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }
    // p1������
    if (FAILED(battleImage[eBattle::P1Character]->Init(TEXT("Image/king.bmp"), 85*1.4, 82*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }
    // p2������
    if (FAILED(battleImage[eBattle::P2Character]->Init(TEXT("Image/yuri_reverse.bmp"), 85*1.4, 82*1.4, true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p2.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }
    // Ÿ�̸�

    //���� ������
  

}

void UserInterface::Release()
{
	for (int i = 0; i < eBattle::eBattleEnd; i++)
	{
		if (battleImage[i])
		{
			battleImage[i]->Release();
			delete battleImage[i];
            battleImage[i] = nullptr;
		}
	}
}

void UserInterface::Update()
{
    // TODO. ĳ���� ü�� ������Ʈ
    
    // TODO. ĳ���Ϳ� �°� ���� ������Ʈ
}

void UserInterface::Render(HDC hdc)
{
    battleImage[HP_bar]->Render(hdc, (WINSIZE_X - 676 *1.4) / 2, 0); // w = 676
    battleImage[HP_gage_p1]->HpRender(hdc, WINSIZE_X / 2 - 133*1.4, 38,
        hpCalculate, p1Health, true);
    battleImage[HP_gage_p2]->HpRender(hdc, WINSIZE_X / 2 + 133*1.4, 38,
        hpCalculate, p2Health, false);
    battleImage[P1Character]->Render(hdc, WINSIZE_X / 2 - (85 + 238) * 1.4, -28); // w = 85
    battleImage[P2Character]->Render(hdc, WINSIZE_X / 2 + 238*1.4, -28);
}
UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

// TODO image�� ü�¹� ���� ���� �����
// p1�� ���� ��� p2�� ���� ��ܱ���
// �̹����� ü�� �ۼ�Ʈ��ŭ �ڸ� �� �־�� ��