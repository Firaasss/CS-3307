#include "Motor.h"
#include "MotorController.h"
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
		Motor motor2(5, 4);
		
		motor1.start(Direction::CW);
		delay(1000); 
		motor2.start(Direction::CW);
		delay(1000);
		motor1.stop();
		motor2.stop();
	} catch (...) {
		std::cout << "we broke" << std::endl;
		return -1;
	}
	return 0;
}
