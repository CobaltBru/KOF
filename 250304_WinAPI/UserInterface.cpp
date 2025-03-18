#include "UserInterface.h"
#include "Image.h"
void UserInterface::Init()
{
    p1Pos = { 0,0 };
    p1Image = new Image();
    if (FAILED(p1Image->Init(TEXT("Image/p1.bmp"), 612, 104, 9, 1,
        true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p1.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }

    p2Pos = { 612,0 };
    p2Image = new Image();
    if (FAILED(p2Image->Init(TEXT("Image/p2.bmp"), 612, 104, 9, 1,
        true, RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, TEXT("Image/p2.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
    }
}

void UserInterface::Release()
{
    if (p1Image)
    {
        p1Image->Release();
        delete p1Image;
        p1Image = nullptr;
    }

    if (p2Image)
    {
        p2Image->Release();
        delete p2Image;
        p2Image = nullptr;
    }
}

void UserInterface::Update()
{
}

void UserInterface::Render(HDC hdc)
{
    if (p1Image)
        p1Image->Render(hdc, p1Pos.x, p1Pos.y);
    if (p2Image)
        p2Image->Render(hdc, p2Pos.x, p2Pos.y);
}

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}
