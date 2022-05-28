#include "HttpClient.h"

static QString g_CompaniesUrl = "http://127.0.0.1:8000/api/v1/companies/";
static QString g_loginUrl = "http://127.0.0.1:8000/customlogin/";



HttpClient::HttpClient(RestController *restController)
{
    m_restController = restController;
}

HttpClient::~HttpClient()
{
    delete m_restController;
}



void HttpClient::login()
{
    m_restController->setRequestType(RestController::RequestLogin);
    m_restController->startGetRequest(g_loginUrl);
}

void HttpClient::logout()
{

}

void HttpClient::requestCompanies()
{
    m_restController->setRequestType(RestController::RequestCompany);
    m_restController->startGetRequest(g_CompaniesUrl);
}
