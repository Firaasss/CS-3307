#ifndef BLADECONTROLLER_H
#define BLADECONTROLLER_H

#include "Motor.h"
#include "MotorController.h"

class BladeController : public MotorController {
	public:
		BladeController(Motor& bladeMotor);
		~BladeController();
		int stopMotor();
		int startMotor();
		Motor* getBladeMotor();

	protected:

	private:
		Motor* m_bladeMotor;

};

#endif // BLADECONTROLLER_H
