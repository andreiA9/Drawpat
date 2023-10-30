#ifndef REST_CONTROLLER_H
#define REST_CONTROLLER_H

// local project headers
// ----------------------
#include "HttpClient.h"

// standard C/C++ headers
// ----------------------
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
