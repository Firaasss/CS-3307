#ifndef BUTTONCONTROLLER_H
#define	BUTTONCONTROLLER_H

#include "State.h"
#include "Path.h"
#include "ExecutionController.h"

class ButtonController {
	public:
		ButtonController(int pinStart, int pinSetDimensions, int pinUpArrow, int pinDownArrow, State& currentState, Path& path, ExecutionController& exeControl);
		~ButtonController();
		int sendButtonPress(int pinButtonPressed);
		int startInputListener();
		State getCurrentState();
		int getErrorNum();

	protected:

	private:
		State* m_currentState;
		Path* m_path;
		ExecutionController* m_exeControl;
		int m_pinStart;
		int m_pinSetDimensions;
		int m_pinUpArrow;
		int m_pinDownArrow;
		int m_inputLength;
		int m_inputWidth;
		int m_errorNum;

		int	onStart();
		int onSetDimensions();
		int onUpArrow();
		int onDownArrow();
};

#endif // BUTTONCONTROLLER_H
