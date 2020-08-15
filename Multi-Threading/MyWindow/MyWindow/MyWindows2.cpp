// Headers
#include<windows.h>
#include<process.h>

//Global function delclaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID _cdecl ThreadProc1(VOID*); 
VOID _cdecl ThreadProc2(VOID*);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// Code initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register above class
	RegisterClassEx(&wndclass);

	// create window 
	hwnd = CreateWindow(szAppName,
		TEXT("MY APPLICATION"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variables
	uintptr_t ulThread1 = 0;
	uintptr_t ulThread2 = 0;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		ulThread1 = _beginthread(ThreadProc1, 0, (VOID*)hwnd);
		ulThread2 = _beginthread(ThreadProc2, 0, (VOID*)hwnd);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is multithread application"), TEXT("MESSAGE"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

VOID __cdecl ThreadProc1(VOID* param)
{
	//local variables
	HDC hdc;
	INT i;
	TCHAR str[255];

	//code
	hdc = GetDC((HWND)param);

	for (i = 0; i < 32787148168; i++)
	{
		wsprintf(str, TEXT("Thread1 : Increasing order : %d", i));
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);
	_endthread();
}

VOID __cdecl ThreadProc2(VOID* param)
{
	//local variables
	HDC hdc;
	INT i;
	TCHAR str[255];

	//code
	hdc = GetDC((HWND)param);

	for (i = 32787148168; i > 0; i--)
	{
		wsprintf(str, TEXT("Thread2 : Decreasing order : %d", i));
		TextOut(hdc, 5, 25, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);
	_endthread();
}