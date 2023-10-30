#ifndef RESOURCE_MANIPULATION_H
#define RESOURCE_MANIPULATION_H

// local project headers
// ----------------------
#include "CompaniesWrapper.h"
#include "ProgrammersWrapper.h"

// standard C/C++ headers
// ----------------------

class ResourceManipulationModule
{
public:
    ResourceManipulationModule(CompaniesWrapper *m_companies, ProgrammersWrapper *m_programmers);
    ~ResourceManipulationModule();

private:
    CompaniesWrapper *m_companies;
    ProgrammersWrapper *m_programmers;
};

#endif // RESOURCE_MANIPULATION_H
