#ifndef CONSTANTS_H
#define CONSTANTS_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <string>
#include <array>
#include <map>

using MenuItem = uint32_t;

enum class MenuLevel
{
    OptionLevel,
    ActionLevel,
    ExecuteLevel
};

enum Option : MenuItem // MenuItem = underlying type
{
    Main = 0,
    Authentication = 1,
    Directories = 2,
    Files = 3,
    Users = 4,
    Exit = 5
};

enum Action : MenuItem
{
    NoAction,
    Login,
    Logout,
    Add,
    Delete,
    Change,     // Change if for changing the atrributes of a file{text/image}
    ShowSingle,
    ListAll,
    Move,
    Edit,       // Edit if for editing the contents of a file{text/image}
    Export,
    Back
};

static const std::array<Option, 6> menuOption =
{
    Option::Main,
    Option::Authentication,
    Option::Directories,
    Option::Files,
    Option::Users,
    Option::Exit
};

static const std::array<Action, 3> authenticationAction =
{
    Action::Login,
    Action::Logout,
    Action::Back
};

static const std::array<Action, 7> fileAction =
{
    Action::Add,
    Action::Delete,
    Action::Change,
    Action::ShowSingle,
    Action::ListAll,
    Action::Move,
    Action::Back
};

static const std::array<Action, 7> directoryAction =
{
    Action::Add,
    Action::Delete,
    Action::Change,
    Action::ShowSingle,
    Action::ListAll,
    Action::Move,
    Action::Back
};

static const std::array<Action, 6> usersAction =
{
    Action::Add,
    Action::Delete,
    Action::Change,
    Action::ShowSingle,
    Action::ListAll,
    Action::Back
};

#endif // CONSTANTS_H
