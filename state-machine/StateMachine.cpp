//
// Created by FernandoDamian on 4/19/2016.
//
#include <assert.h>
#include <cstdio>
#include "StateMachine.h"
#include "EventData.h"

StateMachine::StateMachine(int maxStates, int initialState) :
        m_maxStates( maxStates ),
        m_currentState(initialState),
        m_eventGenerated(0),
        m_pEventData(NULL)
{
}

void StateMachine::ExternalEvent(int newState, EventData * pData)
{
    if( newState == EVENT_IGNORED)
    {
        if( pData ) {
            delete pData;
            pData = NULL;
        }

    }
    else
    {
        InternalEvent(newState, pData);
        StateEngine();
    }
}

void StateMachine::InternalEvent(int newState, EventData * pData)
{
    if( pData == NULL)
        pData = new EventData();

    m_pEventData = pData;
    m_eventGenerated = true;
    m_currentState = newState;
}

void StateMachine::StateEngine()
{
    EventData* pDataTemp = NULL;

    while( m_eventGenerated )
    {
        pDataTemp = m_pEventData;
        m_pEventData = NULL;
        m_eventGenerated = false;

        assert(m_currentState < m_maxStates);

        const StateStruct * pStateMap = GetStateMap();

        (this->*pStateMap[m_currentState].pStateFunc)(pDataTemp);

        if(pDataTemp)
        {
            delete pDataTemp;
            pDataTemp = NULL;
        }
    }
}