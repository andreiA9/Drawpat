#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include "RestController.h"


class NetworkModule
{
public:
    NetworkModule(CompaniesWrapper *companies, ProgrammersWrapper *programmers);
    ~NetworkModule();

    void mediate(int menuCategory, int action);

private:
    RestController* m_controller;
};

#endif // NETWORK_MODULE_H
