//Windows GDI

#include <windows.h>
#include <math.h>


LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char szWindowClass[] = "SineWave";
	
	//注册窗口类
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
	
	//创建主窗口
	HWND hWnd = ::CreateWindowEx(
		WS_EX_CLIENTEDGE,	//扩展样式
		szWindowClass,		//类名
		"Window",		    //标题
		WS_OVERLAPPEDWINDOW,//窗口样式
		CW_USEDEFAULT,	    //初始 X 坐标
		CW_USEDEFAULT,	    //初始 X 坐标
		CW_USEDEFAULT,	    //宽度
		CW_USEDEFAULT,	    //高度
		NULL,		        //父窗口句柄
		NULL,	            //菜单句柄
		hInstance,	        //程序实例句柄
		NULL);
	
	::ShowWindow(hWnd, nShowCmd);
	::UpdateWindow(hWnd);
	
	//进入消息循环
	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	
	return 1;
}


//消息处理函数
LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#define SEGMENTS 500    //取的点数（在一个周期内取500个点）
#define SQUARESIZE 20   //圆的直径
#define PI 3.1415926    //圆周率
	
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
		
		//获得设备环境句柄
		hdc = ::BeginPaint(hWnd, &ps);
		
		//获得绘图的客户区
		::GetClientRect(hWnd, &rt);
		cxClient = rt.right - rt.left;
		cyClient = rt.bottom - rt.top;
		
		//创建字体并装入设备环境
		HFONT hFont = ::CreateFont(12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
		HFONT hOldFont = (HFONT)::SelectObject(hdc, hFont);
		
		//设置字体颜色
		::SetTextColor(hdc, RGB(0,255,0));
		//绘制文本
		char szStr[] = " Sine Wave";
		::DrawText(hdc, szStr, sizeof(szStr), &rt, 0);
		::Sleep(1000);
		
		//释放字体
		::SelectObject(hdc, hOldFont);
		::DeleteObject(hFont);
		
		//创建画笔并装入设备环境
		HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
		
		//画坐标轴
		::MoveToEx(hdc, 0, cyClient/2, NULL);
		::LineTo(hdc, cxClient, cyClient/2);
		::MoveToEx(hdc, cxClient/2, 0, NULL);
		::LineTo(hdc, cxClient/2, cyClient);
		::Sleep(1000);
		
		//释放画笔
		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);
		
		//创建画刷并装入设备环境
		HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
		
		//找出SEGMENTS个点的坐标
		POINT pt[SEGMENTS];
		for(int i=0; i<SEGMENTS; i++)
		{
			pt[i].x = cxClient*i/SEGMENTS;
			pt[i].y = (int)((cyClient/2)*(1 - sin(2*PI*i/SEGMENTS)));
			//画一个圆
			::Ellipse(hdc, pt[i].x-SQUARESIZE, pt[i].y+SQUARESIZE,
				pt[i].x+SQUARESIZE, pt[i].y-SQUARESIZE);
			::Sleep(2);
		}
		
		//释放画刷
		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);
		
		//结束绘制
		::EndPaint(hWnd, &ps);
		break;
	}
	
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}