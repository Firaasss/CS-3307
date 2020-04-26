/**
 * This file contains the implementation of the WheelController class and all associated member functions that are included in the WheelController.h file.
 * The WheelController class is used to send instructions to the motors for the left and right wheels.
 * The methods in this class will be called by the main loop of the program, when executing instructions.
 * 
 * TODO: Add comments describing each method in terms of usage, parameters, and return value
 */

#include "WheelController.h"
#include <iostream>
#include <wiringPi.h>

WheelController::WheelController(Motor& leftWheelMotor, Motor& rightWheelMotor) {
	m_leftWheelMotor = &leftWheelMotor;
	m_rightWheelMotor = &rightWheelMotor;

	m_errorNum = 0;
}

WheelController::~WheelController() {
	
}

int WheelController::stopMotor() {
	m_leftWheelMotor->stop();
	m_rightWheelMotor->stop();
	
	return 0;
}

int WheelController::moveForward() {
	m_leftWheelMotor->start(Direction::CCW);
	m_rightWheelMotor->start(Direction::CW);
	
	return 0;
}

int WheelController::moveBackward() {
	m_leftWheelMotor->start(Direction::CW);
	m_rightWheelMotor->start(Direction::CCW);
	
	return 0;
}

int WheelController::turnLeft(TurnDuration turnDuration) {
	// m_rightWheelMotor->start(Direction::CW, turnDuration);
	// m_leftWheelMotor->start(Direction::CCW, turnDuration);

	// m_rightWheelMotor->start(Direction::CW);
	// m_leftWheelMotor->start(Direction::CW);
	// delay(turnDuration);

	// stopMotor();

	return m_rightWheelMotor->start(Direction::CW, turnDuration);
	// return 0;
}

int WheelController::turnRight(TurnDuration turnDuration) {
	// m_leftWheelMotor->start(Direction::CCW, turnDuration);
	// m_rightWheelMotor->start(Direction::CW, turnDuration);

	// m_leftWheelMotor->start(Direction::CCW);
	// m_rightWheelMotor->start(Direction::CCW);
	// delay(turnDuration);

	// stopMotor();

	return m_leftWheelMotor->start(Direction::CCW, turnDuration);
	// return 0;
}

Motor* WheelController::getLeftWheelMotor() {
	return m_leftWheelMotor;
}

Motor* WheelController::getRightWheelMotor() {
	return m_rightWheelMotor;
}
