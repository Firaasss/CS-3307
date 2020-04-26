#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "State.h"
#include "Path.h"
#include "Motor.h"
#include "WheelController.h"
#include "BladeController.h"
#include "ButtonController.h"
#include "ExecutionController.h"

int main (void) {
    const int START_PIN = 29;
    const int INPUT_PIN = 1;
    const int UP_PIN = 4;
    const int DOWN_PIN = 28;
    // const double LENGTH = 4.5;
    // const double WIDTH = 4.5;
    // const double CAR_DIAMETER = 2.0;
    // const double BLADE_DIAMETER = 1.0;

    State currentState = IDLE;
    Path path(3.0, 3.0, 0.87, 0.435);

    Motor motor1(24, 23); // 0, 3 previously
	Motor motor2(21, 22); // 4, 5 previously

    Motor motor3(2, 3);
	
	WheelController wheelControl(motor1, motor2);
    BladeController bladeControl(motor3);

    // ButtonController* btn = new ButtonController(START_PIN, INPUT_PIN, UP_PIN, DOWN_PIN, currentState);
    ExecutionController* exec = new ExecutionController(currentState, path, wheelControl, bladeControl);

    // ExecutionController exec(currentState, path);
    ButtonController btn(START_PIN, INPUT_PIN, UP_PIN, DOWN_PIN, currentState, path, *exec);

    // std::cout << "exec currentState: " << exec->getCurrentState() << std::endl;
    // std::cout << "btn currentState: " << btn.getCurrentState() << std::endl;

    std::thread button_thread(&ButtonController::startInputListener, btn);

    std::cout << "button thread now running" << std::endl;

    // delay(5000);

    // std::cout << "delay now complete" << std::endl;

    std::thread exec_thread(&ExecutionController::startExecutionListener, exec);

    std::cout << "exec thread now running" << std::endl;

    // delay(500);

    // std::cout << "exec currentState: " << exec->getCurrentState() << std::endl;
    // std::cout << "btn currentState: " << btn.getCurrentState() << std::endl;

    exec_thread.join();
    button_thread.join();

    std::cout << "All threads completed" << std::endl;

	return 0;
}
