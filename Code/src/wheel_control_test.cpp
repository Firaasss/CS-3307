#include "Motor.h"
#include "WheelController.h"
#include <wiringPi.h>
#include <iostream>

// GPIO 17 = 0 -- (CCW) ? maybe CW
// GPIO 22 = 3 -- (CW) ? maybe CCW
// GPIO 23 = 4 -- (CCW)
// GPIO 24 = 5 -- (CW)

// NOTE: Must be compiled with argument "-lwiringPi" in order to link the wiringPi library

int main (void) {
	try {
		Motor motor1(0, 3);
		Motor motor2(4, 5);
	
		WheelController controller(motor1, motor2);

		controller.moveForward();
		delay(1000);
		controller.stopMotor();
		delay(1000);
		controller.moveBackward();
		delay(1000);
		controller.stopMotor();
		delay(1000);
		controller.turnLeft(TurnDuration::positionOne);
		delay(1000);
		controller.turnRight(TurnDuration::positionFive);
		delay(1000);
		Motor* ptr1 = controller.getLeftWheelMotor();

		ptr1->start(Direction::CW);
		delay(1000);
		ptr1->stop();
	} catch (...) {
		std::cout << "we broke" << std::endl;
		return -1;
	}

	return 0;
}
