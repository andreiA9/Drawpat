#include "NetworkModule.h"



NetworkModule::NetworkModule(CompaniesWrapper *companies, ProgrammersWrapper *programmers)
{
    if (!companies || !programmers)
    {
        return;
    }
    HttpClient *httpClient = new HttpClient(companies, programmers);
    m_controller = new RestController(httpClient);
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::mediate(int menuCategory, int action)
{
    qDebug() << "Action: " << action;
    HttpClient::RequestType requestType = static_cast<HttpClient::RequestType>(menuCategory);
    HttpClient::RequestType requestAction = static_cast<HttpClient::RequestType>(action);

    switch (requestType)
    {
        case HttpClient::RequestType::Login:
        {
            m_controller->login();
            break;
        }
        case HttpClient::RequestType::ListAllCompanies:
        {
            m_controller->requestCompanies();
            break;
        }
        default:
            break;
    }
}
