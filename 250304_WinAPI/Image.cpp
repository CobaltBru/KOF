#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, 
    bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    BITMAP bitmap;
    GetObject(imageInfo->hBitmap, sizeof(BITMAP), &bitmap);

    imageInfo->width = bitmap.bmWidth;
    imageInfo->height = bitmap.bmHeight;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

void Image::Render(HDC hdc, int destX, int destY)
{
    if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->width, imageInfo->height,
            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,                // 복사 목적지 DC
            destX, destY,       // 복사 목적지 위치
            imageInfo->width,   // 원본에서 복사될 가로크기
            imageInfo->height,  // 원본에서 복사될 세로크기
            imageInfo->hMemDC,  // 원본 DC
            0, 0,               // 원본 복사 시작 위치
            SRCCOPY             // 복사 옵션
        );
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex)
{
    imageInfo->currFrameX = frameIndex;

    //StretchBlt()

    if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX, 
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,
            destX, destY,
            imageInfo->width / imageInfo->maxFrameX,
            imageInfo->height,
            imageInfo->hMemDC,
            imageInfo->width / imageInfo->maxFrameX * frameIndex, 0,
            SRCCOPY
        );
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex, bool isFlip)
{
    if (isFlip && isTransparent)
    {
        imageInfo->currFrameX = frameIndex;

        StretchBlt(imageInfo->hTempDC, 0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            (imageInfo->frameWidth * imageInfo->currFrameX) + (imageInfo->frameWidth -1),
            imageInfo->frameHeight * imageInfo->currFrameY,
            -imageInfo->frameWidth, imageInfo->frameHeight, SRCCOPY);

        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hTempDC,
            0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        Render(hdc, destX, destY, frameIndex);
    }
}

void Image::HpRender(HDC hdc, int destX, int destY, float hpCalculate, int health, bool isPlayer1)
{
	if (isTransparent)
	{
		int width = imageInfo->width;
		int height = imageInfo->height;

		// HP에 따라 이미지 너비 계산
		int renderWidth = width - (100 - health) * hpCalculate;

		if (isPlayer1)
		{
			// 소스 사각형의 시작 x 좌표
			int srcX = (100 - health) * hpCalculate;
			GdiTransparentBlt(
				hdc,
				destX - width / 2 + (100 - health) * hpCalculate,
				destY - height / 2,
				renderWidth,
				height,

				imageInfo->hMemDC,
				srcX, 0,
				renderWidth, height,
				transColor
			);
		}
		else
		{
			GdiTransparentBlt(
				hdc,
				destX - width / 2,
				destY - height / 2,
				renderWidth,
				height,

				imageInfo->hMemDC,
				0, 0,
				renderWidth, height,
				transColor
			);
		}
	}
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        delete imageInfo;
        imageInfo = nullptr;
    }
}
