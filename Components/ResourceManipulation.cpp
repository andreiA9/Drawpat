// local project headers
// ----------------------
#include "ResourceManipulation.h"

// standard C/C++ headers
// ----------------------

ResourceManipulationModule::ResourceManipulationModule(CompaniesWrapper *m_companies, ProgrammersWrapper *m_programmers)
{

}

ResourceManipulationModule::~ResourceManipulationModule()
{
    delete m_companies;
    delete m_programmers;
}
