#include "driverfunc.h"

#include <tchar.h>



USER_INFO user_info;
HANDLE hDevice;
/*
int _cdecl init() {
  PCHAR DevicePath = GetDevicePath((LPGUID)&GUID_DEVINTERFACE_CS490);
  hDevice = CreateFile((LPCTSTR)DevicePath,
      GENERIC_READ|GENERIC_WRITE,
      0,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  if (hDevice == NULL) {
    return 0;
  }
  return 1;
}
*/

<<<<<<< HEAD
  while (1) {
	  scanf("%d", &num);
	  printf("Username: ");
	  scanf("%s", user_info.username);
	  printf("Password: ");
	  scanf("%s", user_info.password);
	  if (ApplyToDriver(&user_info, num ? ADDUSER : LOGIN, hDevice)) {
        puts("SUCCESS");
	  } else {
        puts("FAILED");
	  }
  }
  CloseHandle(hDevice);
  return 0;
=======
BOOL ApplyDriver(int num, USER_INFO *usr) {
 if (ApplyToDriver(usr, num ? ADDUSER : LOGIN, hDevice)) {
		return TRUE;
	  } else {
		return FALSE;
	  }
>>>>>>> e1f13d38812e10d6530d383ee40f08149bc5d693
}

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Username and Passwork Management");

HINSTANCE hInst;
HWND hWnd;

HWND hCPTextUser, hCPTextPwd;
HWND hCPButtonCheck, hCPButtonCreate;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	WNDCLASSEX wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));


    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 ERROR"),
			MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }
	/*
	if (init() == 0) {
		MessageBox(NULL,
			_T("Create Device failed!"),
			_T("Driver ERROR"),
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}
	*/
    hInst = hInstance; // Store instance handle in our global variable

    // The parameters to CreateWindow explained:
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        440, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 ERROR"),
			MB_ICONEXCLAMATION | MB_OK);

        return 1;
    }

	hCPTextUser = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		_T("Edit"),
		_T(""),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
		100, 40, 220, 30,
		hWnd, NULL, hInst, NULL);
	
	hCPTextPwd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		_T("Edit"),
		_T(""),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
		100, 90, 220, 30,
		hWnd, NULL, hInst, NULL);

	hCPButtonCheck = CreateWindow( 
		_T("BUTTON"),  // Predefined class; Unicode assumed 
		_T("Check"),      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		100,         // x position 
		160,         // y position 
		100,        // Button width
		20,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		hInst, 
		NULL);      // Pointer not needed.
	
	hCPButtonCreate = CreateWindow( 
		_T("BUTTON"),  // Predefined class; Unicode assumed 
		_T("Create"),      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		220,         // x position 
		160,         // y position 
		100,        // Button width
		20,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		hInst, 
		NULL);      // Pointer not needed.

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


LRESULT CALLBACK WndProc(HWND curWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_COMMAND:	
		if ((HWND) lParam == hCPButtonCreate)
		{
			GetWindowText(hCPTextUser, user_info.username, sizeof(user_info.username));
			GetWindowText(hCPTextPwd, user_info.password, sizeof(user_info.password));
			/*
			if(!ApplyDriver(1, &user_info)) {
				MessageBox(NULL,
						_T("Create user failed!"),
						_T("Windows Notification"),
						MB_ICONEXCLAMATION | MB_OK);
			}
			else {
				MessageBox(NULL,
						_T("Create user successfully!"),
						_T("Windows Notification"),
						MB_ICONEXCLAMATION | MB_OK);
			}
			*/
			ShowWindow(hWnd, SW_NORMAL);
		}
		else if ((HWND) lParam == hCPButtonCheck)
		{
			GetWindowText(hCPTextUser, user_info.username, sizeof(user_info.username));
			GetWindowText(hCPTextPwd, user_info.password, sizeof(user_info.password));
			/*
			if(!ApplyDriver(0, &user_info)) {
				MessageBox(NULL,
						_T("Username or password invalid!"),
						_T("Windows Notification"),
						MB_ICONEXCLAMATION | MB_OK);
			}
			else {
				MessageBox(NULL,
						_T("Congratulations: Username and password are valid!"),
						_T("Windows Notification"),
						MB_ICONEXCLAMATION | MB_OK);
			}
			*/
			ShowWindow(hWnd, SW_NORMAL);
		}
        else
		{
			return DefWindowProc(curWnd, message, wParam, lParam);
		}
		break;
    case WM_DESTROY:
		if (curWnd == hWnd) {
			PostQuitMessage(0);
			CloseHandle(hDevice);
		}
        break;
    default:
        return DefWindowProc(curWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

/*
const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
*/
