#pragma once
#include "MobyDick.h"

namespace ImGui
{
	namespace GameSettings {

		inline static ImVec2 button1Size{ 145,36 };

	}


	void continueGameLoad();
	void newGameLoad();
	void displayMouseLeftClickImage(ImVec4 color);
	void displayMouseRightClickImage(ImVec4 color);
	void displayPuzzlePieceImage(bool locked, ImVec4 color);
	void displayKeyImage(std::string keyValue, ImVec4 color);
	void displayUpArrowEnterImage(ImVec4 color);


}
