#pragma once
#ifndef SIMPLE_FSM_LOG_H
#define SIMPLE_FSM_LOG_H

#include "State.h"
#include "Transitions.h"

typedef struct LogEntrySimpleFSM
{
    unsigned long micros;
    State *state;
    AbstractTransition *transition;
} LogEntrySimpleFSM;

class LogSimpleFSM
{
public:
    static const int log_size = 10;
    LogEntrySimpleFSM logs[log_size];
    int counter = 0;
    int size = 0;
    void add(LogEntrySimpleFSM &logEntry);
    void add(unsigned long micros, State *state);
    void add(unsigned long micros, AbstractTransition *transition);
    LogEntrySimpleFSM &get(int position);
    String toString();
    String toJson();
    void reset();
};

#endif