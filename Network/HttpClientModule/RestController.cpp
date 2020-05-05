#include "RestController.h"

#include <iostream>



RestController::RestController(CompaniesWrapper *companies, ProgrammersWrapper *programmers)
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &RestController::handleReplyFinished);

    m_companies = companies;
    m_programmers = programmers;
}

RestController::~RestController()
{
    delete m_networkManager;
}

void RestController::setRequestType(RequestType type)
{
    m_requestType = type;
}

bool RestController::isRequestSuccessful(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    bool retVal;

    // TODO: trateaza EXCEPTIILE de TIMEOUT / altele

    // asta este pentru NETWORK ERROR
    if (reply->error()) {
        qDebug() << "Error occured: " << reply->errorString();
        retVal = false;
    }
    else {
        if (statusCode == HttpOk)
        {
            qDebug() << "ContentType: "<< reply->header(QNetworkRequest::ContentTypeHeader).toString();
            qDebug() << "ContentLength: "<< reply->header(QNetworkRequest::ContentLengthHeader).toString();
            retVal = true;
        }
        else {
            // STATUS CODE = 403
            qDebug() << "Status code: " << statusCode;
            // REASON = Forbidden
            QString reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
            qDebug() << "Reason: "<< reason;
            retVal = false;
        }
    }

    return retVal;
}

void RestController::startGetRequest(const QString &url)
{
    QUrl getUrl = QUrl(url);
    m_networkManager->get(QNetworkRequest(getUrl));
//    m_networkManager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/article/")));
//    m_networkManager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/customlogin/")));
}

void RestController::startPostRequest(const QString &url, std::string &payload)
{
    QUrl postUrl = QUrl(url);
    m_networkManager->get(QNetworkRequest(postUrl));
//    m_networkManager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/article/")));
}


void RestController::handleReplyFinished(QNetworkReply *reply)
{
    if (isRequestSuccessful(reply))
    {
        const QByteArray response = reply->readAll();

        switch (m_requestType)
        {
            case RequestLogin: {
                handleLoginResponse(response);
                break;
            }
            case RequestLogout: {
                handleLogoutResponse(response);
                break;
            }
            case RequestCompany: {
                handleGetCompaniesResponse(response);
                break;
            }
            case RequestProgrammer: {
                handleGetProgrammersResponse(response);
                break;
            }
        }


    }
}

Token RestController::extractMiddlewareToken(const QByteArray &response)
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

void RestController::handleLoginResponse(const QByteArray &response)
{
    qDebug() << "Login started...";

    m_middlewareToken = extractMiddlewareToken(response);
}

void RestController::handleLogoutResponse(const QByteArray &response)
{
    qDebug() << "Logout completed";
}

void RestController::handleGetCompaniesResponse(const QByteArray &response)
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

void RestController::handleGetProgrammersResponse(const QByteArray &response)
{
    qDebug() << "Programmers fetched...";
    QList<Programmer> programmers = m_deserializer.extractProgrammers();
    m_programmers->setProgrammers(programmers);
}
