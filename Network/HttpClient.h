#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

// local project headers
// ----------------------
#include "JsonDeserializer.h"
#include "CompaniesWrapper.h"
#include "ProgrammersWrapper.h"

// standard C/C++ headers
// ----------------------
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QObject>

typedef QPair<QString, QString> Token;

//enum HttpRespStatus
//{
//    NoResponse = 0,
//    Ok = 200,
//    NoContent = 204,
//    Found = 302,
//    BadRequest = 400,
//    Unauthorized = 401,
//    Forbidden = 403,
//    NotFound = 404,
//    MethodNotAllowed = 405,
//    NotAcceptable = 406, // Shouldn't be used.
//    Conflict = 409,
//    Gone = 410,
//    UnsupportedMediaType = 415,
//    InternalError = 500,
//    NotImplemented = 501,
//    ServiceUnavailable = 503
//};

class HttpClient : public QObject
{
    Q_OBJECT

public:
    enum StatusCode {
        HttpOk = 200,
        HttpFound = 302,
        HttpForbidden = 403
    };

    enum RequestOption
    {
        Authentication = 1,
        Directories = 2,
        Files = 3,
        Users = 4
    };

    // ASTEA sunt exact aceleasi valori din enum class Action din Constants.h
    enum RequestType
    {
        LoginSession = 0,
        Login = 1,
        Logout = 3,
        ListAllCompanies = 4,
        ListAllProgrammers = 5
    };
//    Login,
//    Logout,
//    // PANA AICI
//    Add,
//    Delete,
//    Change,     // Change if for changing the atrributes of a file{text/image}
//    ShowSingle,
//    ListAll,
//    Move,
//    Edit,       // Edit if for editing the contents of a file{text/image}
//    Export,

    HttpClient(CompaniesWrapper *companies, ProgrammersWrapper *programmers);
    ~HttpClient();

    inline QUrlQuery getLoginData() const { return m_postData; }

    inline bool isRequestFinished() const { return m_isRequestFinished; }

    bool isRequestSuccessful(QNetworkReply *reply);
    void setRequestType(RequestType type);

    /** \brief extract csrfmiddlewaretoken from the form
      * <input type=\"hidden\" name=\"csrfmiddlewaretoken\" value=\"nOR2wrHL2uelHOGxwyWqQzGDHxtxOAVu7MQ9vJNgNMhSdKSTFKCJKOCeYURllCYd\">
      * \return the middlewareToken
      */
    QPair<QString, QString> extractMiddlewareToken(const QByteArray &response);

    QJsonArray processCompanyJson(QByteArray &response);
    QJsonArray processProgrammerJson(QByteArray &response);

    Q_INVOKABLE void startGetRequest(const QString url);
    // fii foarte ATENT aici<pentru ca PARAMETRII nu trebuie sa fie transmisi
    // prin REFERINTA)<=(din CAUZA ca se iese din FUNCTIA.care a apelat acest
    // THREAD>incat nu vei mai avea REFERINTELE.pentru VARIABILELE.respective
    Q_INVOKABLE void startPostRequest(const QString url, QByteArray payload);

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

    QUrlQuery m_postData;
    QPair<QString, QString> m_middlewareToken;
    bool m_isRequestFinished;
};

#endif // HTTP_CLIENT_H
