#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include "RestController.h"



class HttpClient
{
public:
    HttpClient(RestController *restController);
    ~HttpClient();

    void login();

    void logout();

    void requestCompanies();

private:
    RestController* m_restController;
};

#endif // HTTPCONNECTION_H
