//
// Created by FernandoDamian on 4/19/2016.
//

#ifndef CPPPLAYGROUND_STATEMACHINE_H
#define CPPPLAYGROUND_STATEMACHINE_H

class EventData;
class StateMapRow;
class StateMapRowEx;

struct StateStruct;

class StateMachine
{
public:
    enum { EVENT_IGNORED, CANNOT_HAPPEN };

    StateMachine(int maxStates, int initialState = 0);
    virtual ~StateMachine() {}

    int GetCurrentState() {return m_currentState;}

protected:
    void ExternalEvent(int newState, EventData * pData);
    void InternalEvent(int newState, EventData * pData);

private:
    int m_maxStates;
    int m_currentState;
    bool m_eventGenerated;
    EventData* m_pEventData;


    void SetCurrentState(int newState) { m_currentState = newState; }
    void StateEngine(void);

    virtual const StateStruct* GetStateMap() = 0;
};

typedef void (StateMachine::*StateFunc)(EventData *);
struct StateStruct
{
    StateFunc pStateFunc;
};

#endif //CPPPLAYGROUND_STATEMACHINE_H
