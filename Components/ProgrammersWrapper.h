#ifndef PROGRAMMERS_WRAPPER_H
#define PROGRAMMERS_WRAPPER_H

// local project headers
// ----------------------
#include "Programmer.h"

// standard C/C++ headers
// ----------------------
#include <QList>

class ProgrammersWrapper
{
public:
    ProgrammersWrapper();

    void setProgrammers(QList<Programmer> &programmers);
};

#endif // PROGRAMMERS_WRAPPER_H
