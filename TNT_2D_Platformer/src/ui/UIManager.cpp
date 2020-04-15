#include "UIManager.h"

UIManager::UIManager()
{
	this->_grid = UIGrid::TOP_LEFT;
	this->_state = UIState::INACTIVE;
	this->_length = 0;
	this->_timer = 0;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, 0 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

UIManager::UIManager(UIGrid grid, UIState state, int length, int timer, std::vector<float> active_position, std::vector<float> inactive_offset)
{
	this->_grid = grid;
	this->_state = state;
	this->_length = length;
	this->_timer = timer;
	this->_active_position = active_position;
	this->_inactive_offset = inactive_offset;
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

UIManager::~UIManager()
{
}

/**
* Update the UI position based on its state
*/
void UIManager::update()
{
	switch (this->_state)
	{
		case UIState::ACTIVE:
		{
			setPosition({ this->_active_position[0], this->_active_position[1] });
			break;
		}
		case UIState::INACTIVE:
		{
			setPosition({ this->_active_position[0] + this->_inactive_offset[0],
						  this->_active_position[1] + this->_inactive_offset[1]
						});
			break;
		}
		case UIState::ACTIVATING:
		{
			this->_timer++;
			
			int _x = Util::tween(this->_active_type,
								 this->_active_position[0] + this->_inactive_offset[0],
								 this->_active_position[0],
								 this->_timer / this->_length);
			int _y = Util::tween(this->_active_type,
								 this->_active_position[1] + this->_inactive_offset[1],
								 this->_active_position[1],
								 this->_timer / this->_length);
			setPosition({ _x, _y });
			// TODO (@nghialam): Find a way to set image alpha - blend using tween)
			if (this->_timer >= this->_length) this->_state = UIState::ACTIVE;
			break;
		}
		case UIState::DEACTIVATING:
		{
			this->_timer++;
			
			int _x = Util::tween(this->_deactive_type,
								 this->_active_position[0],
								 this->_active_position[0] + this->_inactive_offset[0],
								 this->_timer / this->_length);
			int _y = Util::tween(this->_deactive_type,
								 this->_active_position[1],
								 this->_active_position[1] + this->_inactive_offset[1],
								 this->_timer / this->_length);
			setPosition({ _x, _y });
			// TODO (@nghialam): Find a way to set image alpha - blend using tween)
			if (this->_timer >= this->_length) this->_state = UIState::INACTIVE;
			break;

		}
	}
}

void UIManager::draw()
{

}

void UIManager::clean()
{
}

void UIManager::UpdateElementPos()
{
	// GUI Size
	int _gw = Globals::sWindowWidth;
	int _gh = Globals::sWindowHeight;
	// View Guide Size
	int _vw = Globals::sViewWidth;
	int _vh = Globals::sViewHeight;
	// Center Position for Guide
	int _vcx = _vw / 2;
	int _vcy = _vh / 2;
	// Starting position
	int _x = getPosition()[0];
	int _y = getPosition()[1];
	// Identify all offset for various grid
	int _posx[] = { _x,    _gw / 2 - (_vcx - _x),		_gw - (_vw - _x) };
	int _posy[] = { _y,    _gh / 2 - (_vcy - _y),		_gh - (_vh - _y) };

	// Apply Offset for current GRID
	switch (this->_grid)
	{
		// Top
		case UIGrid::TOP_LEFT:
			setPosition({ _posx[UIAlignment::ALEFT], _posy[UIAlignment::ATOP] });
			break;
		case UIGrid::TOP_CENTER:
			setPosition({ _posx[UIAlignment::ACENTER], _posy[UIAlignment::ATOP] });
			break;
		case UIGrid::TOP_RIGHT:
			setPosition({ _posx[UIAlignment::ARIGHT], _posy[UIAlignment::ATOP] });
			break;
		// Middle		 
		case UIGrid::MID_LEFT:
			setPosition({ _posx[UIAlignment::ALEFT], _posy[UIAlignment::AMID] });
			break;
		case UIGrid::MID_CENTER:
			setPosition({ _posx[UIAlignment::ACENTER], _posy[UIAlignment::AMID] });
			break;
		case UIGrid::MID_RIGHT:
			setPosition({ _posx[UIAlignment::ARIGHT], _posy[UIAlignment::AMID] });
			break;
		// Bot		 
		case UIGrid::BOT_LEFT:
			setPosition({ _posx[UIAlignment::ALEFT], _posy[UIAlignment::ABOT] });
			break;
		case UIGrid::BOT_CENTER:
			setPosition({ _posx[UIAlignment::ACENTER], _posy[UIAlignment::ABOT] });
			break;
		case UIGrid::BOT_RIGHT:
			setPosition({ _posx[UIAlignment::ARIGHT], _posy[UIAlignment::ABOT] });
			break;
	}

	this->_active_position = { getPosition()[0], getPosition()[1] };
} 

// Getter & Setter
UIGrid UIManager::GetUIGrid()
{
	return UIGrid();
}

UIState UIManager::GetUIState()
{
	return this->_state;
}

int UIManager::GetLength()
{
	return 0;
}

int UIManager::GetTimer()
{
	return 0;
}

std::vector<int> UIManager::GetActivePos()
{
	return std::vector<int>();
}

std::vector<int> UIManager::GetInActiveOff()
{
	return std::vector<int>();
}

void UIManager::SetUIGrid(UIGrid grid)
{
}

void UIManager::SetUIState(UIState state)
{
	this->_state = state;
}

void UIManager::SetLength(int length)
{
}

void UIManager::SetTimer(int timer)
{
}

void UIManager::SetActivePos(std::vector<float> active_position)
{
}

void UIManager::SetInactiveOff(std::vector<float> inactive_offset)
{
}

