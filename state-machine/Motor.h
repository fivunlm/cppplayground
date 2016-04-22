//
// Created by FernandoDamian on 4/21/2016.
//

#ifndef CSSPLAYGROUND_MOTOR_H
#define CSSPLAYGROUND_MOTOR_H

#include <cstdio>
#include "EventData.h"
#include "StateMachine.h"

struct MotorData : public EventData {
    int speed;
};

class Motor : public StateMachine {

    enum E_States {
        ST_IDLE = 0,
        ST_STOP,
        ST_START,
        ST_CHANGE_SPEED,
        ST_MAX_STATES
    };

    void ST_Idle(EventData *);

    void ST_Stop(EventData *);

    void ST_Start(MotorData *);

    void ST_ChangeSpeed(MotorData *);

    const StateStruct *GetStateMap() {
        static const StateStruct StateMap[] = {
                {reinterpret_cast<StateFunc>(&Motor::ST_Idle)},
                {reinterpret_cast<StateFunc>(&Motor::ST_Stop)},
                {reinterpret_cast<StateFunc>(&Motor::ST_Start)},
                {reinterpret_cast<StateFunc>(&Motor::ST_ChangeSpeed)},
                { NULL }
        };
        return &StateMap[0];
    }

public:
    Motor() : StateMachine(ST_MAX_STATES, ST_IDLE) { }

    void Halt();

    void SetSpeed(MotorData *);
};


#endif //CSSPLAYGROUND_MOTOR_H
