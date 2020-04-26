#include <iostream>
#include <wiringPi.h>

int main(void) {
	const int START_PIN = 6;
	const int INPUT_PIN = 1;
	const int UP_PIN = 4;
	const int DOWN_PIN = 5;

	wiringPiSetup();

	pinMode(START_PIN, INPUT); // red
	pullUpDnControl(START_PIN, PUD_UP);

	pinMode(INPUT_PIN, INPUT); // blue
	pullUpDnControl(INPUT_PIN, PUD_UP);

	pinMode(UP_PIN, INPUT); // up yellow
	pullUpDnControl(UP_PIN, PUD_UP);

	pinMode(DOWN_PIN, INPUT); // down yellow
	pullUpDnControl(DOWN_PIN, PUD_UP);

	//bool buttonPressed = false;
	//bool buttonPressed2 = false;
	//bool buttonPressed3 = false;
	//bool buttonPressed4 = false;

	while (true) {
		if (digitalRead(START_PIN) == LOW) {

			std::cout << "start button pressed" << std::endl;

			while (digitalRead(START_PIN) == LOW)
				delay(100);
		}
		

		if (digitalRead(INPUT_PIN) == LOW) {

			std::cout << "input button pressed" << std::endl;
			while (digitalRead(INPUT_PIN) == LOW)
				delay(100);
			}
		}

		if (digitalRead(UP_PIN) == LOW) {
			std::cout << "up button pressed" << std::endl;

			while (digitalRead(UP_PIN) == LOW)
				delay(100);
			}
		}


		if (digitalRead(DOWN_PIN) == LOW) {
				std::cout << "down button pressed" << std::endl;
				while (digitalRead(DOWN_PIN) == LOW)
					delay(100);
			
		}

	}
	return 0;
}