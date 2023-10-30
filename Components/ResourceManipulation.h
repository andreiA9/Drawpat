#ifndef RESOURCEMANIPULATION_H
#define RESOURCEMANIPULATION_H

#include "CompaniesWrapper.h"
#include "ProgrammersWrapper.h"

class ResourceManipulationModule
{
public:
    ResourceManipulationModule(CompaniesWrapper *m_companies, ProgrammersWrapper *m_programmers);
    ~ResourceManipulationModule();

private:
    CompaniesWrapper *m_companies;
    ProgrammersWrapper *m_programmers;
};

#endif // RESOURCEMANIPULATION_H
