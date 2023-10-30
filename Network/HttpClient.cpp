#include "HttpClient.h"

#include <iostream>



HttpClient::HttpClient(CompaniesWrapper *companies, ProgrammersWrapper *programmers)
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &HttpClient::handleReplyFinished);

    m_companies = companies;
    m_programmers = programmers;
}

HttpClient::~HttpClient()
{
    delete m_networkManager;
}

void HttpClient::setRequestType(RequestType type)
{
    m_requestType = type;
}

bool HttpClient::isRequestSuccessful(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    bool retVal;

    // TODO: trateaza EXCEPTIILE de TIMEOUT / altele

    // asta este pentru NETWORK ERROR
    if (reply->error())
    {
        qDebug() << "Error occured: " << reply->errorString();
        retVal = false;
    }
    else
    {
        // HttpOk este la REQUEST.primul=GET pentru LOGIN
        // HttpFound este la REQUEST.2lea=POST pentru LOGIN
        if ((statusCode == HttpOk) || (statusCode == HttpFound))
        {
            qDebug() << "ContentType: "
                     << reply->header(QNetworkRequest::ContentTypeHeader).toString();
            qDebug() << "ContentLength: "
                     << reply->header(QNetworkRequest::ContentLengthHeader).toString();
            retVal = true;
        }
        else {
            // STATUS CODE = 403
            qDebug() << "Status code: " << statusCode;
            // REASON = Forbidden
            QString reason = reply->attribute(
                        QNetworkRequest::HttpReasonPhraseAttribute).toString();
            qDebug() << "Reason: "<< reason;
            retVal = false;
        }
    }

    return retVal;
}

void HttpClient::startGetRequest(const QString url)
{
    QUrl getUrl = QUrl(url);
    m_networkManager->get(QNetworkRequest(getUrl));
//    m_networkManager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/article/")));
//    m_networkManager->get(QNetworkRequest(QUrl("htt   p://127.0.0.1:8000/customlogin/")));
}

void HttpClient::startPostRequest(const QString url, QByteArray payload)
{
    QUrl postUrl = QUrl(url);
    //    QNetworkRequest request(serviceUrl);
    //    networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    QNetworkRequest request(postUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    m_networkManager->post(request, payload);
}


void HttpClient::handleReplyFinished(QNetworkReply *reply)
{
    qDebug() << "handleReplyFinished()";
    if (isRequestSuccessful(reply))
    {
        const QByteArray response = reply->readAll();

        switch (m_requestType)
        {
            case Login:
            case LoginSession:
            {
                handleLoginResponse(response);
                break;
            }
            case Logout:
            {
                handleLogoutResponse(response);
                break;
            }
            case ListAllCompanies:
            {
                qDebug() << "BEFORE handleGetCompaniesResponse()";
                handleGetCompaniesResponse(response);
                break;
            }
            case ListAllProgrammers:
            {
                handleGetProgrammersResponse(response);
                break;
            }
        }
    }
}

QPair<QString, QString> HttpClient::extractMiddlewareToken(const QByteArray &response)
{
    qDebug() << response;

    Token token;
    // EXTRACTING csrfmiddlewaretoken FROM
    // <input type=\"hidden\" name=\"csrfmiddlewaretoken\" value=\"nOR2wrHL2uelHOGxwyWqQzGDHxtxOAVu7MQ9vJNgNMhSdKSTFKCJKOCeYURllCYd\">
    const char *form = "<input type=";
    int formStart = response.indexOf(form);

    if (formStart)
    {
        const char* tokenName = "name=\"";
        const int nameLen = 6;
        int tokenNameStart = response.indexOf(tokenName, formStart);
        tokenNameStart += nameLen;
        const int tokenNameEnd = response.indexOf("\"", tokenNameStart);
        token.first = response.mid(tokenNameStart, tokenNameEnd - tokenNameStart);
        qDebug() << token.first;

        const char* tokenValue = "value=\"";
        const int valueLen = 7;
        int tokenValueStart = response.indexOf(tokenValue, formStart);
        tokenValueStart += valueLen;
        const int tokenValueEnd = response.indexOf("\"", tokenValueStart);
        token.second = response.mid(tokenValueStart, tokenValueEnd - tokenValueStart);
        qDebug() << token.second;

        return token;
    }

    return Token();
}

void HttpClient::handleLoginResponse(const QByteArray &response)
{
    if (m_requestType == Login)
    {
        qDebug() << "Login started...";

        m_middlewareToken = extractMiddlewareToken(response);
        m_postData.addQueryItem("username", "andrei");
        m_postData.addQueryItem("password", "00aaa!!!");
        m_postData.addQueryItem(m_middlewareToken.first, m_middlewareToken.second);
    }
    else if (m_requestType == LoginSession)
    {
        qDebug() << "Login continuing...";
    }

    m_isRequestFinished = true;
}

void HttpClient::handleLogoutResponse(const QByteArray &response)
{
    qDebug() << "Logout completed";
}

void HttpClient::handleGetCompaniesResponse(const QByteArray &response)
{
    qDebug() << "Companies fetched...";

    qDebug() << response;

    QJsonArray obj;
    obj = m_deserializer.processJsonArray(response);

    if (!obj.isEmpty()) {

    }

    int a = 1;
    a++;



    QList<Company> companies = m_deserializer.extractCompanies();
    m_companies->setCompanies(companies);
}

void HttpClient::handleGetProgrammersResponse(const QByteArray &response)
{
    qDebug() << "Programmers fetched...";
    QList<Programmer> programmers = m_deserializer.extractProgrammers();
    m_programmers->setProgrammers(programmers);
}
