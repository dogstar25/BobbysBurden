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
	void displayUpArrowImage(ImVec4 color);
	void displayDownArrowImage(ImVec4 color);
	void displayPuzzlePieceImage(bool locked, ImVec4 color);
	void displayDropItemImage(ImVec4 color);
	void displayDropItemIntoContainerImage(ImVec4 color);
	void _buildPuzzleRow(GameObject* puzzleObjectM);


}
