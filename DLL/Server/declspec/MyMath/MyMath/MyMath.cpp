#include<windows.h>
#include"MyMath.h"

// Entry point function
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	//Code
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

//Exported function defination
// __declspec(dllexport) says that MakeSquare function is exportable. it will get embeed in EFT table in top of DLL.
__declspec(dllexport) INT MakeSquare(INT num)
{
	// Code
	return num * num;	
}