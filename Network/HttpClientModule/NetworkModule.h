#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include "HttpClient.h"



class NetworkModule
{
public:
    NetworkModule(CompaniesWrapper *companies, ProgrammersWrapper *programmers);
    ~NetworkModule();

    void run();

private:
    HttpClient *m_httpClient;
};

#endif // RESTCLIENT_H
