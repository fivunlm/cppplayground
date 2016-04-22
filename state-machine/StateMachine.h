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

    int m_currentState;
private:
    int m_maxStates;
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

#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct StateMap[] = {

#define STATE_MAP_ENTRY(stateFunc)\
    { reinterpret_cast<StateFunc>(stateFunc) },

#define END_STATE_MAP \
    { NULL }\
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    ExternalEvent(TRANSITIONS[m_currentState], data);

#endif //CPPPLAYGROUND_STATEMACHINE_H
