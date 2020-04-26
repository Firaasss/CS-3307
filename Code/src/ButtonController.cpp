#include "ButtonController.h"
#include <wiringPi.h>
#include <iostream>

ButtonController::ButtonController(int pinStart, int pinSetDimensions, int pinUpArrow, int pinDownArrow, State& currentState, Path& path, ExecutionController& exeControl) {
	m_pinStart = pinStart;
	m_pinSetDimensions = pinSetDimensions;
	m_pinUpArrow = pinUpArrow;
	m_pinDownArrow = pinDownArrow;
	m_currentState = &currentState;
	m_path = &path;
	m_exeControl = &exeControl;
	m_inputLength = 0;
	m_inputWidth = 0;
	m_errorNum = 0;
}

ButtonController::~ButtonController() {

}

int ButtonController::sendButtonPress(int pinButtonPressed) {
	if (pinButtonPressed == m_pinStart) {
		onStart();
	} else if (pinButtonPressed == m_pinSetDimensions) {
		onSetDimensions();
	} else if (pinButtonPressed == m_pinUpArrow) {
		onUpArrow();
	} else if (pinButtonPressed == m_pinDownArrow) {
		onDownArrow();
	} else {
		m_errorNum = -1;
		return -1;
	}

	return 0;
}

int ButtonController::startInputListener() {
    wiringPiSetup();

	pinMode(m_pinStart, INPUT); // red
    pullUpDnControl(m_pinStart, PUD_UP);

    pinMode(m_pinSetDimensions, INPUT); // blue
    pullUpDnControl(m_pinSetDimensions, PUD_UP);

    pinMode(m_pinUpArrow, INPUT); // up yellow
    pullUpDnControl(m_pinUpArrow, PUD_UP);

    pinMode(m_pinDownArrow, INPUT); // down yellow
    pullUpDnControl(m_pinDownArrow, PUD_UP);

    bool buttonPressed = false;
    bool buttonPressed2 = false;
    bool buttonPressed3 = false;
    bool buttonPressed4 = false;

	bool test_flag = false;

    while (!test_flag) {
        if (digitalRead(m_pinStart) == LOW) {
            if (buttonPressed) {
                std::cout << "start button pressed" << std::endl;
                buttonPressed = false;
				*m_currentState = MOWING;
				// onStart();
                delay(500);
            }
        } else {
            buttonPressed = true;
        }
        
        if (digitalRead(m_pinSetDimensions) == LOW) {
            if (buttonPressed2) {
                std::cout << "input button pressed" << std::endl;
                buttonPressed2 = false;
				*m_currentState = INPUT_LENGTH;
				// onSetDimensions();
                delay(500);
            }
        } else {
            buttonPressed2 = true;
        }

        if (digitalRead(m_pinUpArrow) == LOW) {
            if (buttonPressed3) {
                std::cout << "up button pressed" << std::endl;
                buttonPressed3 = false;
				*m_currentState = MOWING;
				// onUpArrow();
				delay(1000);
				m_exeControl->assignInstructions();
                delay(500);
            }
        } else {
            buttonPressed3 = true;
        }

        if (digitalRead(m_pinDownArrow) == LOW) {
            if (buttonPressed4) {
                std::cout << "down button pressed" << std::endl;
                buttonPressed4 = false;
				*m_currentState = PAUSED;
				// onDownArrow();
                delay(500);
				test_flag = true;
            }
        } else {
            buttonPressed4 = true;
        }  
    }

	return 0;
}

State ButtonController::getCurrentState() {
	return *m_currentState;
}

int ButtonController::getErrorNum() {
	return m_errorNum;
}

int ButtonController::onStart() {
	switch (*m_currentState) {
		case IDLE:
			*m_currentState = MOWING;
			// start sending instructions to motor controllers
			break;
		case MOWING:
			*m_currentState = IDLE;
			// stop sending instructions, end current mowing job
			break;
		case INPUT_LENGTH:
			*m_currentState = IDLE;
			// don't set new inputs
			break;
		case INPUT_WIDTH:
			*m_currentState = IDLE;
			// don't set new inputs
			break;
		case PAUSED:
			*m_currentState = IDLE;
			// end current mowing job
			break;
		default:
			m_errorNum = -2;
			return -2;
	}

	return 0;
}

int ButtonController::onSetDimensions() {
	switch (*m_currentState) {
		case IDLE:
			*m_currentState = INPUT_LENGTH;
			break;
		case MOWING:
			*m_currentState = PAUSED;
			// stop sending instructions to motor controllers
			break;
		case INPUT_LENGTH:
			*m_currentState = INPUT_WIDTH;
			// save length value in local variable
			break;
		case INPUT_WIDTH:
			*m_currentState = IDLE;
			// send new dimensions to path object
			break;
		case PAUSED:
			*m_currentState = MOWING;
			// resume sending instructiosn to motor controllers
			break;
		default:
			m_errorNum = -2;
			return -2;
	}

	return 0;
}

int ButtonController::onUpArrow() {
	switch (*m_currentState) {
		case IDLE:
			break;
		case MOWING:
			break;
		case INPUT_LENGTH:
			m_inputLength += 1;
			break;
		case INPUT_WIDTH:
			m_inputWidth += 1;
			break;
		case PAUSED:
			break;
		default:
			m_errorNum = -2;
			return -2;
	}

	return 0;
}

int ButtonController::onDownArrow() {
	switch (*m_currentState) {
		case IDLE:
			break;
		case MOWING:
			break;
		case INPUT_LENGTH:
			m_inputLength -= 1;
			break;
		case INPUT_WIDTH:
			m_inputWidth -= 1;
			break;
		case PAUSED:
			break;
		default:
			m_errorNum = -2;
			return -2;
	}

	return 0;
}
