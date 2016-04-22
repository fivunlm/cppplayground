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
    ExternalEvent(TRANSITIONS[m_currentState], NULL);
}

void Motor::ST_Idle(EventData *pData) {
    cout << "Motor::ST_Idle" << endl;
}

// stop the motor
void Motor::ST_Stop(EventData *pData) {
    cout << "Motor::ST_Stop" << endl;

    // perform the stop motor processing here
    // transition to ST_Idle via an internal event
    InternalEvent(ST_IDLE, NULL);
}

// start the motor going
void Motor::ST_Start(MotorData *pData) {
    cout << "Motor::ST_Start" << endl;
    // set initial motor speed processing here
}

// changes the motor speed once the motor is moving
void Motor::ST_ChangeSpeed(MotorData *pData) {
    cout << "Motor::ST_ChangeSpeed" << endl;
    // perform the change motor speed to pData->speed here
}