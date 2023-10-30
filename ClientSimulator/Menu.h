#ifndef MENU_H
#define MENU_H

// local project headers
// ----------------------
#include "Constants.h"

// standard C/C++ headers
// ----------------------
#include <string>
#include <map>
#include <iostream>
#include <QDebug>

class Menu
{
public:
    typedef std::map<Option, const char*> OptionMap_t;
    typedef std::map<Action, const char*> ActionMap_t;

    Menu()
    {
        m_menuCategory = Option::Main;
        m_action = Action::NoAction;
        isMainMenu = false;
    }

    OptionMap_t getMainMenu()
    {
        return std::map<Option, const char*>(
            {
                { Option::Authentication, "1 - Authentication" },
                { Option::Directories, "2 - Directories" },
                { Option::Files, "3 - Files" },
                { Option::Users, "4 - Users" },
                { Option::Exit, "x - Exit" }
            });
    }

    ActionMap_t getDirectoryMenu()
    {
        return std::map<Action, const char*>(
            {
                { Action::Add, "1 - Add directory" },
                { Action::Delete, "2 - Delete directory" },
                { Action::Change, "3 - Change directory" },
                { Action::ShowSingle, "4 - Show single directory" },
                { Action::ListAll, "5 - List all directories" },
                { Action::Move, "6 - Move directory" },
                { Action::Back, "x - Back" }
            });
    }

    ActionMap_t getAuthenticationMenu()
    {
        return std::map<Action, const char*>(
            {
                { Action::Login, "1 - Login" },
                { Action::Logout, "2 - Logout" },
                { Action::Back, "x - Back" }
            });
    }

    ActionMap_t getFileMenu()
    {
        return std::map<Action, const char*>(
            {
                { Action::Add, "1 - Add file" },
                { Action::Delete, "2 - Delete file" },
                { Action::Change, "3 - Change file" },
                { Action::ShowSingle, "4 - Show single file" },
                { Action::ListAll, "5  - List all files" },
                { Action::Move, "6 - Move file" },
                { Action::Back, "x - Back" }
            });
    }

    ActionMap_t getUserMenu()
    {
        return std::map<Action, const char*>(
            {
                { Action::Add, "1 - Add user" },
                { Action::Delete, "2 - Delete user" },
                { Action::Change, "3 - Change user" },
                { Action::ShowSingle, "4 - Show single user" },
                { Action::ListAll, "5 - List all users" },
                { Action::Back, "x - Back" }
            });
    }

    void showMainMenu()
    {
        OptionMap_t menuMap = getMainMenu();
        for (const auto& menu : menuMap)
        {
           std::cout << menu.second << '\n';
        }
    }

    void showMenuByOption(MenuItem option)
    {
        ActionMap_t menuMap;
        switch (option)
        {
        case Authentication:
            menuMap = getAuthenticationMenu();
            break;
        case Files:
            menuMap = getFileMenu();
            break;
        case Directories:
            menuMap = getDirectoryMenu();
            break;
        case Users:
            menuMap = getUserMenu();
            break;
        case Exit:
            break;
        }

        for (const auto& menu : menuMap)
        {
           std::cout << menu.second << '\n';
        }
    }

    template<class MenuChoice>
    MenuChoice readUserChoice()
    {
        std::cout << "\nEnter choice\n" << '\n';
        unsigned int choice;
        std::cin >> choice;
        return static_cast<MenuChoice>(choice);
    }

    void setActionAndMenuCategory(Option menuCategory, Action action)
    {
        m_menuCategory = menuCategory;
        m_action = action;
    }

    void getActionAndMenuCategory(Option& menuCategory, Action& action)
    {
        menuCategory = m_menuCategory;
        action = m_action;
    }

    void resetActionAndMenuCategory()
    {
        m_menuCategory = Option::Main;
        m_action = Action::NoAction;
    }

    bool hasContent()
    {
        return (m_menuCategory != Option::Main && m_action != Action::NoAction);
    }

    bool hasExitCondition()
    {
        return m_menuCategory == Option::Exit;
    }

    bool run()
    {
        MenuItem input = Option::Main;
        MenuItem currentOption = Option::Main;
        MenuItem currentAction = Action::NoAction;
        MenuLevel level = MenuLevel::OptionLevel;
        bool stopped = false;

        while (!stopped)
        {
            if (currentOption == Option::Exit
                && level == MenuLevel::OptionLevel)
            {
                stopped = true;
            }
            else if (currentOption == Action::Back
                && level == MenuLevel::ActionLevel)
            {
                level = MenuLevel::OptionLevel;
            }
            else if (currentOption == Action::Back
                && level == MenuLevel::ExecuteLevel)
            {
                level = MenuLevel::ActionLevel;
            }

            if (level == MenuLevel::ExecuteLevel)
            {
                setActionAndMenuCategory(static_cast<Option>(currentOption), static_cast<Action>(currentAction));
            }
            else if (level == MenuLevel::ActionLevel)
            {
                showMenuByOption(currentOption);
            }
            else if (level == MenuLevel::OptionLevel)
            {
                showMainMenu();
            }

            input = readUserChoice<MenuItem>();

            if (level == MenuLevel::ExecuteLevel)
            {
                level = MenuLevel::ActionLevel;
            }
            else if (level == MenuLevel::ActionLevel)
            {
                currentAction = input;
                level = MenuLevel::ExecuteLevel;
            }
            else if (level == MenuLevel::OptionLevel)
            {
                currentOption = input;
                level = MenuLevel::ActionLevel;
            }
        }

        return stopped;
    }

private:
    bool isMainMenu;
    MenuLevel m_level;
    Option m_menuCategory;
    Action m_action;
};

#endif // MENU_H
