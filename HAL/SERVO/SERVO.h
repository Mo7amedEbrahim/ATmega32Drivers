#ifndef _SERVO_H_
#define _SERVO_H_


/* servo motor configurations */
#define SERVO_MIN_DUTY_CYCLE	(u16) 97
#define SERVO_MAX_DUTY_CYCLE	(u16) 625
#define SERVO_0_DEGREE_DUTY_CYCLE	(u16) 97
#define SERVO_90_DEGREE_DUTY_CYCLE	(u16) 313
#define SERVO_180_DEGREE_DUTY_CYCLE	(u16) 625


ES_t SERVO_init(void);
ES_t SERVO_setAngle(u8 angle);



#endif