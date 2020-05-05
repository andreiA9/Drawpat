#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H

// JSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// USER-DEFINED
#include "../ResourceManipulationModule/Company.h"
#include "../ResourceManipulationModule/Programmer.h"



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

#endif // JSONDESERIALIZER_H
