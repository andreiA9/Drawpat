#ifndef EVENTS_H
#define EVENTS_H

// local project headers
// ----------------------
#include "CommonTypes.h"

// standard C/C++ headers
// ----------------------

class Events
{
public:
    Events();

    PaintEvent getCurrentEvent() const { return m_event; }

    /** \brief specifies if an image rotate event was sent
      * \param imageRotated - if the rotate event was triggered
      */
    void setEventEnabled(PaintEvent event)
    {
        m_previousEvent = m_previousEvent;
        m_event = event;
    }

    void resetToPreviousEvent() { m_event = m_previousEvent; }

private:
    PaintEvent m_event;
    PaintEvent m_previousEvent;
};

#endif // EVENTS_H
