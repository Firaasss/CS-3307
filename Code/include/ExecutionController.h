#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H

#include <string>
#include <deque>
#include "State.h"
#include "Instruction.h"
#include "Path.h"
#include "WheelController.h"
#include "BladeController.h"

class ExecutionController {
	public:
		ExecutionController(State& currentState, Path& path, WheelController& wheelControl, BladeController& bladeControl);
		~ExecutionController();
		int startExecutionListener();
		int assignInstructions();
		int clearInstructions();
		State getCurrentState();
        
	protected:
		
	private:
		State* m_currentState;
		Path* m_path;
		WheelController* m_wheelControl;
		BladeController* m_bladeControl;
		std::deque<Instruction> m_remainingInstructions;

		int executeInstruction(Instruction instruction);
};

#endif // EXECUTIONCONTROLLER_H
