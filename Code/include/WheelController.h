/**
 * This file contains the declaration of the WheelController class and all associated member functions and attributes.
 * The WheelController class is used to send instructions to the motors for the left and right wheels.
 * The methods in this class will be called by the main loop of the program, when executing instructions.
 */

#ifndef WHEELCONTROLLER_H
#define WHEELCONTROLLER_H

#include "MotorController.h"
#include "Motor.h"

enum TurnDuration { 
	positionOne = 100,
	positionTwo = 1075, // TL before finish
	positionThree = 1450, // TL after MB
	positionFour = 1075, // TR after MB
	positionFive = 900
};

class WheelController : public MotorController {
	public:
		WheelController(Motor& leftWheelMotor, Motor& rightWheelMotor);
		~WheelController();
		int stopMotor();
		int moveForward();
		int moveBackward();
		int turnLeft(TurnDuration turnDuration);
		int turnRight(TurnDuration turnDuration);
		Motor* getLeftWheelMotor();
		Motor* getRightWheelMotor();
		
	protected:
		
	private:
		Motor* m_leftWheelMotor;
		Motor* m_rightWheelMotor;
};

#endif // WHEELCONTROLLER_H
