#pragma once
#ifndef __UIMANAGER__
#define __UIMANAGER__

#include "..\Util.h"
#include "..\GameObject.h"

// UIGrid is used for manage UI location based on dividing the view into 9 grids
// -------------------------------
// |         |         |         |
// |         |         |         |
// -------------------------------
// |         |         |         |
// |         |         |         |
// -------------------------------
// |         |         |         |
// |         |         |         |
// -------------------------------
enum class UIGrid
{
	TOP_LEFT, TOP_CENTER, TOP_RIGHT,
	MID_LEFT, MID_CENTER, MID_RIGHT,
	BOT_LEFT, BOT_CENTER, BOT_RIGHT
};
enum UIAlignment
{
	TOP = 0, MID = 1, BOT = 2,
	LEFT = 0, CENTER = 1, RIGHT = 2
};
enum class UIState
{
	ACTIVE,
	ACTIVATING,
	INACTIVE,
	DEACTIVATING
};


// Manage all UI elements that appears on the screen.
// This class is helpful for consistent position of UI elements when changing windows size or windows aspect ratio
class UIManager : public GameObject {
private:
	UIGrid _grid;
	UIState _state;

	int _length;
	int _timer;

	std::vector<float> _active_position;
	std::vector<float> _inactive_offset;
	
	TweenType _active_type;
	TweenType _deactive_type;
public:
	UIManager();
	UIManager(UIGrid grid, UIState state, int length, int timer, std::vector<float> active_position, std::vector<float> inactive_offset);
	~UIManager();

	void update() override;
	void draw() override;
	void clean() override;

	void UpdateElementPos(); // Update all elements positions

	// Getter
	UIGrid GetUIGrid();
	UIState GetUIState();
	int GetLength();
	int GetTimer();
	std::vector<int> GetActivePos();
	std::vector<int> GetInActiveOff();

	// Setter
	void SetUIGrid(UIGrid grid);
	void SetUIState(UIState state);
	void SetLength(int length);
	void SetTimer(int timer);
	void SetActivePos(std::vector<float> active_position);
	void SetInactiveOff(std::vector<float> inactive_offset);
};

#endif // TNT2D_UIMANAGER_H
