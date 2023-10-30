#ifndef JSON_DESERIALIZER_H
#define JSON_DESERIALIZER_H

// local project headers
// ----------------------
#include "Company.h"
#include "Programmer.h"

// standard C/C++ headers
// ----------------------
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class JsonDeserializer
{
public:
    JsonDeserializer();

    void setCompany(Company &company);
    void setProgrammer(Programmer &programmer);

    QJsonObject processJsonObject(QByteArray& response);
    QJsonArray processJsonArray(const QByteArray &response);

    QList<Company> extractCompanies();
    QList<Programmer> extractProgrammers();

private:
    Company m_company;
    Programmer m_programmer;
};

#endif // JSON_DESERIALIZER_H
