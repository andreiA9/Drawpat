#include "JsonDeserializer.h"

// QT
#include <QDebug>



JsonDeserializer::JsonDeserializer()
{

}

void JsonDeserializer::setCompany(Company &company)
{
    m_company = company;
}

void JsonDeserializer::setProgrammer(Programmer &programmer)
{
    m_programmer = programmer;
}

QJsonObject JsonDeserializer::processJsonObject(QByteArray& response)
{
    QJsonDocument document;

    QJsonParseError error{-1, QJsonParseError::NoError};
    document = QJsonDocument::fromJson(response, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "JSON reply parse error: " << error.errorString()
                 << ", reply content was: " << response;

        return QJsonObject();
    }

    return document.object();
}

QJsonArray JsonDeserializer::processJsonArray(const QByteArray& response)
{
    QJsonDocument document;

    QJsonParseError error{-1, QJsonParseError::NoError};
    document = QJsonDocument::fromJson(response, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "JSON reply parse error: " << error.errorString()
                 << ", reply content was: " << response;

        return QJsonArray();
    }

    return document.array();
}

QList<Company> JsonDeserializer::extractCompanies()
{

}

QList<Programmer> JsonDeserializer::extractProgrammers()
{

}
