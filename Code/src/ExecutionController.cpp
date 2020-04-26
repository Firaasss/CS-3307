#include "ExecutionController.h"
#include <iostream>
#include <wiringPi.h>

ExecutionController::ExecutionController(State& currentState, Path& path, WheelController& wheelControl, BladeController& bladeControl) {
    m_currentState = &currentState;
    m_path = &path;
    m_wheelControl = &wheelControl;
    m_bladeControl = &bladeControl;
}

ExecutionController::~ExecutionController() {
	
}

int ExecutionController::startExecutionListener() {
    while (*m_currentState != PAUSED) {
        if (m_remainingInstructions.size() > 0) {
            std::cout << "# of instructions left: " << m_remainingInstructions.size() << std::endl;
            std::cout << "instruction: " << m_remainingInstructions.front().action << std::endl;

            Instruction currentInstruction = m_remainingInstructions.front();
            m_remainingInstructions.pop_front();
            executeInstruction(currentInstruction);
        } else { // if we finish all instructions
            if (*m_currentState == MOWING) { // only if we were previously mowing and finished all instructions, return to idle state
                *m_currentState = IDLE;
            }
        }

        delay(1000);
    }

    return 0;
}

int ExecutionController::assignInstructions() {
    std::cout << "assigning instructions" << std::endl;

    if (m_path->getInstructions().size() > 0) {
        std::cout << "assigned" << std::endl;
        m_remainingInstructions = m_path->getInstructions();
    } else {
        std::cout << "not assigned" << std::endl;
    }

    return 0;
}

int ExecutionController::clearInstructions() {
    std::cout << "clearing instructions" << std::endl;

    if (m_remainingInstructions.size() > 0) {
        m_remainingInstructions.clear();
    }

    return 0;
}

State ExecutionController::getCurrentState() {
	return *m_currentState;
}

int ExecutionController::executeInstruction(Instruction instruction) {
    // parse instruction, call appropriate motor classes
    double duration;

    if (instruction.action == "MF") {
        duration = instruction.value * 925;

        m_wheelControl->moveForward();
        delay(duration);
        m_wheelControl->stopMotor();
    } else if (instruction.action == "MB") {
        duration = instruction.value * 925;

        m_wheelControl->moveBackward();
        delay(duration);
        m_wheelControl->stopMotor();
    } else if (instruction.action == "TL") {
        if (instruction.value == 90.0) {
            m_wheelControl->turnLeft(TurnDuration::positionFive);
        } else if (instruction.value == 100.0) {
            m_wheelControl->turnLeft(TurnDuration::positionThree);
        } else if (instruction.value == 110.0) {
            m_wheelControl->turnLeft(TurnDuration::positionTwo);
        } else { // 180.0
            m_wheelControl->turnLeft(TurnDuration::positionFive);
            m_wheelControl->turnLeft(TurnDuration::positionFive);
        }
    } else if (instruction.action == "TR") {
        if (instruction.value == 90.0) {
            m_wheelControl->turnRight(TurnDuration::positionFive);
        } else if (instruction.value == 100.0) {
            m_wheelControl->turnRight(TurnDuration::positionFour);
        } else { // 180.0
            m_wheelControl->turnRight(TurnDuration::positionFive);
            m_wheelControl->turnRight(TurnDuration::positionFive);
        }
    }

    return 0;
}

// TurnDuration ExecutionController::calcTurnDuration(double value) {
//     switch (value) {
//         case 90.0:
//             return TurnDuration::
//     }
// }
