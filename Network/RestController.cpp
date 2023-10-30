// local project headers
// ----------------------
#include "RestController.h"

// standard C/C++ headers
// ----------------------
#include <QThread>

static QString g_CompaniesUrl = "http://127.0.0.1:8000/companies/";
static QString g_loginUrl = "http://127.0.0.1:8000/customlogin/";

RestController::RestController(HttpClient *httpClient)
{
    m_httpClient = httpClient;

    qDebug() << "Thread started";
    // THIS is necessary because QObject THREADS must be created from
    // the same thread where they are RUNNING
    m_httpClient->moveToThread(&m_thread);

    // VEZI ca AICI iti trebuie
    // o FUNCTIE = run()
    // run() este apelata de m_thread.start()
    m_thread.start();
}

RestController::~RestController()
{
    delete m_httpClient;
}

void RestController::login()
{
    m_httpClient->setRequestType(HttpClient::Login);
    QMetaObject::invokeMethod(m_httpClient, "startGetRequest", Qt::QueuedConnection, Q_ARG(QString, g_loginUrl));

    // if no thread was used < this LOOP=while will
    // block the EVENT LOOP of the QNetworkManager from HttpClient>
    // so the SLOT=HttpClient::finished is not executed after receiving
    // the RESPONSE.from the WEBSITE)-
    // (in this case the next REQUEST=POST will also not be executed)
    while (!m_httpClient->isRequestFinished())
    {
        QThread::msleep(1);
    }

    m_httpClient->setRequestType(HttpClient::LoginSession);
    QByteArray payload = m_httpClient->getLoginData().toString(QUrl::FullyEncoded).toUtf8();
    qDebug() << "Payload" << payload;
    QMetaObject::invokeMethod(m_httpClient, "startPostRequest", Qt::QueuedConnection, Q_ARG(QString, g_loginUrl), Q_ARG(QByteArray, payload));
}

void RestController::logout()
{

}

void RestController::requestCompanies()
{
    m_httpClient->setRequestType(HttpClient::ListAllCompanies);
    /* ASTA NU e BINE<pentru ca iti da EROAREA:
     * QObject: Cannot create children for a parent that is in a different thread. (Parent is
     * QNetworkAccessManager(0x55e92f8b92d0), parent's thread is QThread(0x55e92f8c0ce8),
     * current thread is QThread(0x55e92f8b4f20)
    m_httpClient->startGetRequest(g_CompaniesUrl);
    */
    QMetaObject::invokeMethod(m_httpClient, "startGetRequest", Qt::QueuedConnection, Q_ARG(QString, g_CompaniesUrl));

    while (!m_httpClient->isRequestFinished())
    {
        QThread::msleep(1);
    }
}
