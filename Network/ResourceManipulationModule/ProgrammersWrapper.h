#ifndef PROGRAMMERSWRAPPER_H
#define PROGRAMMERSWRAPPER_H

#include <QList>
#include "Programmer.h"


class ProgrammersWrapper
{
public:
    ProgrammersWrapper();

    void setProgrammers(QList<Programmer> &programmers);
};

#endif // PROGRAMMERSWRAPPER_H
