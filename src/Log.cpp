#include "Log.h"

void LogSimpleFSM::add(LogEntrySimpleFSM &logEntry)
{
    logs[counter++] = logEntry;
    counter %= log_size;
    size = size >= log_size ? log_size : size + 1;
}

void LogSimpleFSM::add(unsigned long micros, State *state)
{
    LogEntrySimpleFSM entry{.micros = micros, .state = state, .transition = NULL};
    add(entry);
}

void LogSimpleFSM::add(unsigned long micros, AbstractTransition *transition)
{
    LogEntrySimpleFSM entry{.micros = micros, .state = NULL, .transition = transition};
    add(entry);
}

LogEntrySimpleFSM &LogSimpleFSM::get(int position)
{
    return logs[(log_size + counter - size + position) % log_size];
}

String LogSimpleFSM::toString()
{
    String retVal;
    for (int i = 0; i < size; i++)
    {
        auto entry = get(i);
        if (entry.state != NULL)
        {
            retVal += String() + entry.micros + " - transitioned to: " + entry.state->getName() + "\n";
        }
        if (entry.transition != NULL)
        {
            retVal += String() + entry.micros + " - transitioning: " + entry.transition->from->getName() + " -> " + entry.transition->to->getName() + "\n";
        }
    }
    if (retVal.length() != 0)
        retVal.remove(retVal.length() - 1);
    return retVal;
}

String LogSimpleFSM::toJson()
{
    auto buffer = String("[");
    for (int i = 0; i < size; i++)
    {
        auto entry = get(i);
        if (i != 0)
            buffer += ",";
        if (entry.state != NULL)
        {
            buffer += "{";
            buffer += "\"type\":";
            buffer += "\"state\",";
            buffer += "\"micros\":";
            buffer += entry.micros;
            buffer += ",";
            buffer += "\"name\":\"";
            buffer += entry.state->getName().c_str();
            buffer += "\"";
            buffer += "}";
        }
        if (entry.transition != NULL)
        {
            buffer += "{";
            buffer += "\"type\":";
            buffer += "\"transition\",";
            buffer += "\"micros\":";
            buffer += entry.micros;
            buffer += ",";
            buffer += "\"from\":\"";
            buffer += entry.transition->from->getName();
            buffer += "\"";
            buffer += ",";
            buffer += "\"to\":\"";
            buffer += entry.transition->to->getName();
            buffer += "\"";
            buffer += "}";
        }
    }
    buffer += "]";
    return buffer;
}

void LogSimpleFSM::reset()
{
    size = 0;
}
