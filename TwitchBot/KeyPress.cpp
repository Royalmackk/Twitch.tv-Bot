#include "KeyPress.h"



KeyPress::KeyPress()
{
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
}


KeyPress::~KeyPress()
{
}

void KeyPress::pressKey(int key)
{
	switch (key)
	{
		//Up arrow
		case 1:
			keybd_event(VK_UP, 0x48, KEYEVENTF_EXTENDEDKEY | 0, 0);
			Sleep(200);
			keybd_event(VK_UP, 0x48, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;

		//Down arrow
		case 2:
			keybd_event(VK_DOWN, 0x50, KEYEVENTF_EXTENDEDKEY | 0, 0);
			Sleep(200);
			keybd_event(VK_UP, 0x50, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;

		//Left arrow
		case 3:
			keybd_event(VK_LEFT, 0x4B, KEYEVENTF_EXTENDEDKEY | 0, 0);
			Sleep(200);
			keybd_event(VK_LEFT, 0x4B, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;

		//Right arrow
		case 4:
			keybd_event(VK_RIGHT, 0x4D, KEYEVENTF_EXTENDEDKEY | 0, 0);
			Sleep(200);
			keybd_event(VK_RIGHT, 0x4D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;

		//Z Key
		case 5:
			keybd_event(VkKeyScan('z'), 0x2C, 0, 0);
			Sleep(200);
			keybd_event(VkKeyScan('z') , 0x2C, KEYEVENTF_KEYUP, 0);
		break;

		//x Key
		case 6:
			keybd_event(VkKeyScan('z'), 0x2D, 0, 0);
			Sleep(200);
			keybd_event(VkKeyScan('z'), 0x2D, KEYEVENTF_KEYUP, 0);
		break;

		//Enter key
		case 7:
			keybd_event(VK_RETURN, 0x1C, 0, 0);
			Sleep(200);
			keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
		break;
	}
}