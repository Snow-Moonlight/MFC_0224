#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WinSunProc(
	HWND hwnd,//handle to window
	UINT uMsg,//message identifier
	WPARAM wParam,//first message parameter
	LPARAM lParam //second message parameter
);

int WINAPI WinMain(
	HINSTANCE hInstance, //handle to current instance
	HINSTANCE hPrevInstance, //handle to previous instance
	LPSTR lpCmdLine, //command line
	int nCmdShow     //show state
)

{//设计一个窗口类
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = hInstance; //应用程序实例句柄由WinMain函数传进来
	wndcls.lpfnWndProc = WinSunProc;
	wndcls.lpszClassName = "sunxin2006";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);


	//创建窗口，定义一个变量用来保存成功创建窗口后返回的句柄
	HWND hwnd;
	hwnd = CreateWindow("sunxin2006", "http://www.sunxin.org", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);

	//显示及刷新窗口
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//定义消息结构体，开始消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//编写窗口过程函数
LRESULT CALLBACK WinSunProc(
	HWND hwnd,//handle to window
	UINT uMsg,//message identifier
	WPARAM wParam,//first message parameter
	LPARAM lParam //second message parameter
)
{
	switch (uMsg)
	{
	case WM_CHAR:
		char szChar[20];
		sprintf(szChar, "char code is %d", wParam);
		MessageBox(hwnd, szChar, ("char"), 0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "mouse clicked", "message", 0);
		HDC hdc;
		hdc = GetDC(hwnd);  //不能在响应WM_PAINT消息时调用
		TextOut(hdc, 0, 50, "程序员之家", strlen("程序员之家"));
		//ReleaseDC(hwnd,hdc);
		break;
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hwnd, &ps); //BeginPaint只能在响应WM_PAINT消息时调用
		TextOut(hDC, 0, 0, "http://www.sunxin.org", strlen("http://www.sunxin.org"));
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, "是否真的结束？", "message", MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}