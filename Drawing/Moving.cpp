//Windows GDI

#include <windows.h>
#include <math.h>


LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char szWindowClass[] = "SineWave";
	
	//ע�ᴰ����
	WNDCLASSEX wcex;
	
	wcex.cbSize		     = sizeof(WNDCLASSEX);
	wcex.style		     = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	 = (WNDPROC)WndProc;
	wcex.cbClsExtra		 = 0;
	wcex.cbWndExtra	 	 = 0;
	wcex.hInstance		 = hInstance;
	wcex.hIcon		     = NULL;
	wcex.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	 = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	 = NULL;
	wcex.lpszClassName	 = szWindowClass;
	wcex.hIconSm		 = NULL;
	
	::RegisterClassEx(&wcex);
	
	//����������
	HWND hWnd = ::CreateWindowEx(
		WS_EX_CLIENTEDGE,	//��չ��ʽ
		szWindowClass,		//����
		"Window",		    //����
		WS_OVERLAPPEDWINDOW,//������ʽ
		CW_USEDEFAULT,	    //��ʼ X ����
		CW_USEDEFAULT,	    //��ʼ X ����
		CW_USEDEFAULT,	    //���
		CW_USEDEFAULT,	    //�߶�
		NULL,		        //�����ھ��
		NULL,	            //�˵����
		hInstance,	        //����ʵ�����
		NULL);
	
	::ShowWindow(hWnd, nShowCmd);
	::UpdateWindow(hWnd);
	
	//������Ϣѭ��
	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	
	return 1;
}


//��Ϣ������
LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#define SEGMENTS 500    //ȡ�ĵ�������һ��������ȡ500���㣩
#define SQUARESIZE 20   //Բ��ֱ��
#define PI 3.1415926    //Բ����
	
	switch(message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rt;
		int cxClient, cyClient;
		
		//����豸�������
		hdc = ::BeginPaint(hWnd, &ps);
		
		//��û�ͼ�Ŀͻ���
		::GetClientRect(hWnd, &rt);
		cxClient = rt.right - rt.left;
		cyClient = rt.bottom - rt.top;
		
		//�������岢װ���豸����
		HFONT hFont = ::CreateFont(12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
		HFONT hOldFont = (HFONT)::SelectObject(hdc, hFont);
		
		//����������ɫ
		::SetTextColor(hdc, RGB(0,255,0));
		//�����ı�
		char szStr[] = " Sine Wave";
		::DrawText(hdc, szStr, sizeof(szStr), &rt, 0);
		::Sleep(1000);
		
		//�ͷ�����
		::SelectObject(hdc, hOldFont);
		::DeleteObject(hFont);
		
		//�������ʲ�װ���豸����
		HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
		
		//��������
		::MoveToEx(hdc, 0, cyClient/2, NULL);
		::LineTo(hdc, cxClient, cyClient/2);
		::MoveToEx(hdc, cxClient/2, 0, NULL);
		::LineTo(hdc, cxClient/2, cyClient);
		::Sleep(1000);
		
		//�ͷŻ���
		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);
		
		//������ˢ��װ���豸����
		HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
		
		//�ҳ�SEGMENTS���������
		POINT pt[SEGMENTS];
		for(int i=0; i<SEGMENTS; i++)
		{
			pt[i].x = cxClient*i/SEGMENTS;
			pt[i].y = (int)((cyClient/2)*(1 - sin(2*PI*i/SEGMENTS)));
			//��һ��Բ
			::Ellipse(hdc, pt[i].x-SQUARESIZE, pt[i].y+SQUARESIZE,
				pt[i].x+SQUARESIZE, pt[i].y-SQUARESIZE);
			::Sleep(2);
		}
		
		//�ͷŻ�ˢ
		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);
		
		//��������
		::EndPaint(hWnd, &ps);
		break;
	}
	
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}