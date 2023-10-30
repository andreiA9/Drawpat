#ifndef CLIENT_SIMULATOR_H
#define CLIENT_SIMULATOR_H

// local project headers
// ----------------------
#include "Menu.h"
#include "CompaniesWrapper.h"
#include "ProgrammersWrapper.h"
#include "ResourceManipulation.h"
#include "NetworkModule.h"

// standard C/C++ headers
// ----------------------
#include <QCoreApplication>
#include <unistd.h>

class ClientSimulator : public QObject
{
public:
    ClientSimulator() = default;

    bool init()
    {
//        std::thread threadObj(&ClientSimulator::run, *this);
//        threadObj.join();
        CompaniesWrapper *companies;
        companies = new CompaniesWrapper;
        ProgrammersWrapper *programmers;
        programmers = new ProgrammersWrapper;
        m_networkModule = new NetworkModule(companies, programmers);

        ResourceManipulationModule *resourceManipulation;
        resourceManipulation = new ResourceManipulationModule(companies, programmers);

        return m_menu.run();
    }

public slots:
    void run()
    {
        int a;
        a = 1;
        while (!m_menu.hasExitCondition())
        {
            Option menuCategory;
            Action action;
            if (m_menu.hasContent())
            {
                m_menu.getActionAndMenuCategory(menuCategory, action);
                m_networkModule->mediate(menuCategory, action);
                m_menu.resetActionAndMenuCategory();
            }
            usleep(100);
        }
    }

private:
    Menu m_menu;
    NetworkModule* m_networkModule;
};

#endif // CLIENT_SIMULATOR_H
