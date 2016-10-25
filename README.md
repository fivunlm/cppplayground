# State Machine

[![Build Status](https://travis-ci.org/fivunlm/cppplayground.svg?branch=master)](https://travis-ci.org/fivunlm/cppplayground)

## State Machine Design

A common design technique in the repertoire of most programmers is the venerable finite state machine (FSM). Designers use this programming construct to break complex problems into manageable states and state transitions. There are innumerable ways to implement a state machine.

A switch statement provides one of the easiest to implement and most common version of a state machine. Here, each case within the switch statement becomes a state, implemented something like:

```
switch (currentState) {
   case ST_IDLE:
       // do something in the idle state
       break;
    case ST_STOP:
       // do something in the stop state
       break;
    // etc...
}
```

This method is certainly appropriate for solving many different design problems. When employed on an event driven, multithreaded project, however, state machines of this form can be quite limiting.

The first problem revolves around controlling what state transitions are valid and which ones are invalid. There is no way to enforce the state transition rules. Any transition is allowed at any time, which is not particularly desirable. For most designs, only a few transition patterns are valid. Ideally, the software design should enforce these predefined state sequences and prevent the unwanted transitions. Another problem arises when trying to send data to a specific state. Since the entire state machine is located within a single function, sending additional data to any given state proves difficult. And lastly these designs are rarely suitable for use in a multithreaded system. The designer must ensure the state machine is called from a single thread of control.
