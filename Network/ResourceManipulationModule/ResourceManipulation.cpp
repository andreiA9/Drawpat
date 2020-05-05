#include "ResourceManipulation.h"

ResourceManipulationModule::ResourceManipulationModule(CompaniesWrapper *m_companies, ProgrammersWrapper *m_programmers)
{

}

ResourceManipulationModule::~ResourceManipulationModule()
{
    delete m_companies;
    delete m_programmers;
}
