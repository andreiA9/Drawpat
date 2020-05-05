#ifndef COMPANYWRAPPER_H
#define COMPANYWRAPPER_H

// QT
#include <QList>

// USER-DEFINED
#include "Company.h"


class CompaniesWrapper
{
public:
    CompaniesWrapper();

    void setCompanies(QList<Company> &companies);
};

#endif // COMPANYWRAPPER_H
