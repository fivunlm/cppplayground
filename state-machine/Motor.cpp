//
// Created by FernandoDamian on 4/21/2016.
//

#include "Motor.h"
#include <iostream>

using namespace std;

void Motor::Halt() {

    const int TRANSITIONS[] = {
            EVENT_IGNORED,
            CANNOT_HAPPEN,
            ST_STOP,
            ST_STOP,
            ST_IDLE
    };
    ExternalEvent(TRANSITIONS[m_currentState], NULL);

}

void Motor::SetSpeed(MotorData *pData) {
    const int TRANSITIONS[] = {
            ST_START,
            CANNOT_HAPPEN,
            ST_CHANGE_SPEED,
            ST_CHANGE_SPEED,
            ST_IDLE,
    };
    ExternalEvent(TRANSITIONS[m_currentState], pData);
}

void Motor::ST_Idle(EventData *pData) {
    m_speed = 0;
    cout << "Motor::ST_Idle - Speed " << m_speed << endl;
}

// stop the motor
void Motor::ST_Stop(EventData *pData) {
    m_speed = 0;
    cout << "Motor::ST_Stop - Speed " << m_speed << endl;

    // perform the stop motor processing here
    // transition to ST_Idle via an internal event
    InternalEvent(ST_IDLE, NULL);
}

// start the motor going
void Motor::ST_Start(MotorData *pData) {
    m_speed = pData->speed;
    cout << "Motor::ST_Start - Speed " << m_speed << endl;
}

// changes the motor speed once the motor is moving
void Motor::ST_ChangeSpeed(MotorData *pData) {
    m_speed = pData->speed;
    cout << "Motor::ST_ChangeSpeed - Speed " << m_speed << endl;
}