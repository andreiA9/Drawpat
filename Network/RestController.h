#ifndef REST_CONTROLLER_H
#define REST_CONTROLLER_H

#include "HttpClient.h"

#include <QThread>

class RestController
{
public:
    RestController(HttpClient *httpClient);
    ~RestController();

    void login();

    void logout();

    void requestCompanies();

private:
    HttpClient* m_httpClient;

    QThread m_thread;
};

#endif // REST_CONTROLLER_H
