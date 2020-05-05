#ifndef REST_CLIENT_H
#define REST_CLIENT_H

#include <QObject>

// HTTP COMMUNICATION
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

// QT
#include <QDebug>
//#include <QList>

// USER
#include "JsonDeserializer.h"
#include "../ResourceManipulationModule/CompaniesWrapper.h"
#include "../ResourceManipulationModule/ProgrammersWrapper.h"


typedef QPair<QString, QString> Token;


class RestController : public QObject
{
    Q_OBJECT

public:
    enum StatusCode {
        HttpOk = 200,
        HttpForbidden = 403
    };

    enum RequestType {
        RequestLogin,
        RequestLogout,
        RequestCompany,
        RequestProgrammer
    };

    RestController(CompaniesWrapper *companies, ProgrammersWrapper *programmers);
    ~RestController();

    bool isRequestSuccessful(QNetworkReply *reply);
    void setRequestType(RequestType type);

    /** \brief extract csrfmiddlewaretoken from the form
      * <input type=\"hidden\" name=\"csrfmiddlewaretoken\" value=\"nOR2wrHL2uelHOGxwyWqQzGDHxtxOAVu7MQ9vJNgNMhSdKSTFKCJKOCeYURllCYd\">
      * \return the middlewareToken
      */
    Token extractMiddlewareToken(const QByteArray &response);

    QJsonArray processCompanyJson(QByteArray &response);
    QJsonArray processProgrammerJson(QByteArray &response);

    void startGetRequest(const QString &url);
    void startPostRequest(const QString &url, std::string &payload);

    void handleLoginResponse(const QByteArray &response);
    void handleLogoutResponse(const QByteArray &response);
    void handleGetCompaniesResponse(const QByteArray &response);
    void handleGetProgrammersResponse(const QByteArray &response);

public slots:
    void handleReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager* m_networkManager;
    JsonDeserializer m_deserializer;
    RequestType m_requestType;
    CompaniesWrapper *m_companies;
    ProgrammersWrapper *m_programmers;

    Token m_middlewareToken;
};

#endif // REST_CLIENT_H
