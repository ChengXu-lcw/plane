#include <windows.h>
#include "GameApp.h"
#include <time.h>
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
HINSTANCE hIns = 0;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	srand((unsigned int)time(0));
	//-----------------------------------------------------
	HWND hwnd = 0;
	MSG msg;       //  װ��Ϣ�Ľṹ��
	WNDCLASSEX wndclass;
	//-----------------------------------------------------
	
	hIns = hInstance;

	//----------------------�������ڹ���-----------------------------------
	//  1. ���
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = LoadCursor(0,MAKEINTRESOURCE(IDC_ARROW));
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.lpszClassName = "lcw";
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
	// 2.  ע��
	if(RegisterClassEx(&wndclass) == FALSE)
	{
		MessageBox(0,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}
	//  3.  ����
	hwnd = CreateWindow("lcw","�ɻ���ս��Ϸ",WS_OVERLAPPEDWINDOW,0,0,380+16,550+38,0,0,hInstance,0);
	if(hwnd == 0)
	{
		MessageBox(0,"����ʧ��","��ʾ",MB_OK);
		return 0;	
	}
	//  4.  ��ʾ����
	ShowWindow(hwnd,SW_SHOW);
	//---------------------------�������ڹ���------------------------------------------------



	//----------------------------��Ϣѭ��-------------------------------------------
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//----------------------------��Ϣѭ��-------------------------------------------

	return 0;
}


//=================================������Ϣ========================================================
CGameApp* pApp = 0;
CGameApp* CreateObject();  //  ����һ��������Ϸ�Ķ���

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			// ����һ�� ��Ϸ������Ķ���
			pApp = CreateObject();
			if(pApp != 0)
			{
				//  ���þ��
				pApp->SetHandle(hIns,hwnd);
				//  ��Ϸ�Ĵ���
				pApp->OnCreateGame();
			}
		}
		break;
	case WM_PAINT:
		{
			if(pApp != 0)
			{
				//  ��Ϸ��ʾ
				pApp->OnGameDraw();
			}
		}
		break;
	case WM_TIMER:
		{
			if(pApp != 0)
			{
				//  ��Ϸ����
				pApp->OnGameRun(wParam);
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(pApp != 0)
			{
				//  ���̲���
				pApp->OnKeyDown(wParam);
			}
		}
		break;
	case WM_KEYUP:
		{
			if(pApp != 0)
			{
				//  ���̲���
				pApp->OnKeyUp(wParam);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if(pApp != 0)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				//  ���̲���
				pApp->OnLButtonDown(pt);
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(pApp != 0)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				//  ���̲���
				pApp->OnLButtonUp(pt);
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(pApp != 0)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				//  ���̲���
				pApp->OnMouseMove(pt);
			}
		}
		break;
	case WM_CLOSE:
		{
			//  ɾ����Ϸ����
			delete pApp;
			pApp = 0;
			PostQuitMessage(0);
		}
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam);
}