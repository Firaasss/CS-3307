#include <iostream>
#include <wiringPi.h>

int main (void) {
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

    bool buttonPressed = false;
    bool buttonPressed2 = false;
    bool buttonPressed3 = false;
    bool buttonPressed4 = false;

    while (true) {
        if (digitalRead(START_PIN) == LOW) {
            if (buttonPressed) {
                std::cout << "start button pressed" << std::endl;
                buttonPressed = false;
                delay(500);
            }
        } else {
            buttonPressed = true;
        }
        
        if (digitalRead(INPUT_PIN) == LOW) {
            if (buttonPressed2) {
                std::cout << "input button pressed" << std::endl;
                buttonPressed2 = false;
                delay(500);
            }
        } else {
            buttonPressed2 = true;
        }

        if (digitalRead(UP_PIN) == LOW) {
            if (buttonPressed3) {
                std::cout << "up button pressed" << std::endl;
                buttonPressed3 = false;
                delay(500);
            }
        } else {
            buttonPressed3 = true;
        }

        if (digitalRead(DOWN_PIN) == LOW) {
            if (buttonPressed4) {
                std::cout << "down button pressed" << std::endl;
                buttonPressed4 = false;
                delay(500);
            }
        } else {
            buttonPressed4 = true;
        }

        
    }

	return 0;
}
