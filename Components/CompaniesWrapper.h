#ifndef COMPANIES_WRAPPER_H
#define COMPANIES_WRAPPER_H

// local project headers
// ----------------------
#include <QList>

// standard C/C++ headers
// ----------------------
#include "Company.h"

class CompaniesWrapper
{
public:
    CompaniesWrapper();

    void setCompanies(QList<Company> &companies);
};

#endif // COMPANIES_WRAPPER_H
