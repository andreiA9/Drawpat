#include "NetworkModule.h"



NetworkModule::NetworkModule(CompaniesWrapper *companies, ProgrammersWrapper *programmers)
{
    RestController *controller = new RestController(companies, programmers);
    m_httpClient = new HttpClient(controller);
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::run()
{
    qDebug() << "Thread started";
    // THIS is necessary because QObject THREADS must be created from
    // the same thread where they are RUNNING

//    m_httpClient->requestCompanies();

    m_httpClient->login();
}
