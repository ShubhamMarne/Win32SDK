// Headers
#include<windows.h>

//Global function delclaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM ,LPARAM);

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	HMODULE hDll = NULL;
	// Create new Type for function pointer.
	typedef int (*MakeSquareFunctionPointer)(int);
	MakeSquareFunctionPointer makeSquareFunctionPointer = NULL;
	int i = 5, j;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		// Load DLL explicitly. Returns starting virutal address of loaded DLL.
		hDll = LoadLibrary(TEXT("MyMath.dll"));
		if (hDll == NULL)
		{
			MessageBox(hwnd, TEXT("Failed to load Library.."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// Get address of function(e.g. MakeSquare) from loaded DLL. Returns FARPROC
		makeSquareFunctionPointer = (MakeSquareFunctionPointer)GetProcAddress(hDll, "MakeSquare");
		if (makeSquareFunctionPointer == NULL)
		{
			// Free loaded library if function address not found.
			FreeLibrary(hDll);
			MessageBox(hwnd, TEXT("Failed to find function address"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// Call the function using pointer
		j = makeSquareFunctionPointer(i);
		wsprintf(str, TEXT("Square of %d is %d"), i, j);
		MessageBox(hwnd, str, TEXT("Result of Square."), MB_OK | MB_ICONINFORMATION | WMSZ_TOP);
		// Free loaded library if function address not found.
		FreeLibrary(hDll);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left click..."), TEXT("Test message "),MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}