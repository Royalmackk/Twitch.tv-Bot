#pragma once
#include <windows.h>

class KeyPress
{
	private:
		INPUT input;

	public:
		KeyPress();
		~KeyPress();

		void pressKey(int k);
};

