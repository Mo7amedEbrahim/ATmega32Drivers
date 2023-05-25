#include "../../lib/STD_TYPES.h"
#include "../../lib/BIT_MATH.h"
#include "../../lib/Error_States.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER0/TMR0_interface.h"
#include "SERVO.h"

static TMR0_t SERVO_PWM = {
    .TIMER0_Mode = FAST_PWM,
    .TIMER0_Prescaler = TMR0_DIV_BY_8,
    .TMR0_OCR0 = 97,
    .ActionFunction = NULLPTR
};
/* Initialize servo motor */
ES_t SERVO_init(void) {
	/* Initialize timer0 for fast PWM mode with non-inverting output and 8 prescaler */
    TMR0_Init(&SERVO_PWM);

	/* Set initial angle to 0 degree */
	TMR0_SetDutyCycle(SERVO_0_DEGREE_DUTY_CYCLE);

	return ES_OK;
}

/* Set servo motor angle */
ES_t SERVO_setAngle(u8 angle) {
	/* Check if angle is within valid range */
	if (angle > 180) {
		return ES_OUT_OF_RANGE;
	}

	/* Calculate duty cycle corresponding to the requested angle */
	u16 dutyCycle = (angle / 180) * (SERVO_180_DEGREE_DUTY_CYCLE - SERVO_0_DEGREE_DUTY_CYCLE) + SERVO_0_DEGREE_DUTY_CYCLE;

	/* Set OCR0 register to the calculated duty cycle */
	TMR0_SetDutyCycle(dutyCycle);

	return ES_OK;
}


