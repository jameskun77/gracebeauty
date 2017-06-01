#include <windows.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "D3DRender.h"
#include "libyuv.h"


#pragma comment(lib,"yuv.lib")


#define WIDTH 500
#define HEIGHT 752

D3DVideoRender* gVideoRender = new D3DVideoRender();

bool LoadImageFromDisk(char* pChar,char* &pData,int& imgWidth,int& imgHeight)
{
	if (!pChar)
	{
		MessageBox(0, 0, "LoadImage path is NULL", 0);
		return false;
	}

	IplImage* imgBGR = cvLoadImage(pChar);

	

	IplImage* imgRGB = cvCreateImage(cvGetSize(imgBGR), 8, 3);
	//cvCvtColor(imgBGR, imgRGB, CV_RGB2BGR); //OpencvÄ¬ÈÏÊÇBGR

	int width = imgRGB->width;
	int height = imgRGB->height;

	imgWidth = width;
	imgHeight = height;

	if (!pData)
	{
		pData = new char[width *  height * 4];
	}
	
	libyuv::RGB24ToARGB((unsigned char*)imgBGR->imageData, width * 3, (unsigned char*)pData, width * 4, width, height);

	cvReleaseImage(&imgBGR);
	cvReleaseImage(&imgRGB);

	return true;
}


//int main()
//{
//	char* pSzName = NULL;
//	int width = 0;
//	int height = 0;
//	if (!LoadImageFromDisk("5.jpg", pSzName, width, height))
//	{
//		return -1;
//	}
//
//	
//	char* dst = new char[width * height * 4];
//
//	gVideoRender->Init(NULL, width, height);
//	gVideoRender->DrawToWindow((LPBYTE)pSzName, width, height, width * 4);
//	gVideoRender->RenderToTexture((LPBYTE)pSzName, (LPBYTE)dst, width, height, width * 4);
//	BMP_SaveFile("save32.bmp", dst, width, height, 32);
//
//	delete[]pSzName;
//	delete[]dst;
//
//	return 0;
//}



LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	char* pSzName = NULL;
	int width = 0;
	int height = 0;
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MsgProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInst;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "ForTheDreamOfGameDevelop";

	if (!RegisterClassEx(&wndClass))
		return -1;

	HWND hWnd = CreateWindow("ForTheDreamOfGameDevelop", "Test",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH,
		HEIGHT, NULL, NULL, wndClass.hInstance, NULL);

	int err = GetLastError();


	if (gVideoRender->Init(hWnd, WIDTH, HEIGHT))
	{
		if (LoadImageFromDisk("5.jpg", pSzName, width, height))
		{
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					gVideoRender->DrawToWindow((LPBYTE)pSzName, width, height, width * 4);
				}
			}
		}
	}

	delete[] pSzName;

	UnregisterClass("ClassName", wndClass.hInstance);
	return 0;
}
