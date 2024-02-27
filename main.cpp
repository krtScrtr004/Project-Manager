#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "proj_man.h"
#include "utility.h"

inline void add_project(Project_Manager &project)
{
    std::cout << "ENTER PROJECT DETAILS: \n";
    project.m_add_project(project.m_enter_project_name(), project.m_enter_project_path(),
                          project.m_enter_project_link(), project.m_enter_project_status());
    std::cout << "NEW PROJECT SUCCESSFULLY ADDED\n";

    return;
}

void home_page(Project_Manager &project)
{
    std::cout << "HOME\n";
    std::cout << "[1] ADD PROJECT\n";
    std::cout << "[2] OPEN PROJECT\n";
    std::cout << "[3] DELETE PROJECTR\n";
    std::cout << "[4] SEARCH PROJECT\n";
    std::cout << "[5] EXIT\n";

    constexpr Home_Options_e MIN = Home_Options_e::ADD, MAX = Home_Options_e::EXIT;
    Home_Options_e select_option;
    bool is_valid = false;
    do
    {
        std::cout << "ENTER HERE: ";
        std::cin >> select_option;
        is_valid = is_valid_num(static_cast<short>(select_option), static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (select_option)
    {
    case Home_Options_e::ADD:
    {
        add_project(project);
        break;
    }

    case Home_Options_e::OPEN:
    {
        break;
    }

    case Home_Options_e::DELETE:
    {
        break;
    }

    case Home_Options_e::SEARCH:
    {
        break;
    }

    case Home_Options_e::EXIT:
    {
        break;
    }

    default:
    {
        std::cerr << out_of_bounds_error(static_cast<short>(Home_Options_e::OPEN), static_cast<short>(Home_Options_e::SEARCH));
    }
    }

    return;
}

int main(void)
{
    std::cout << "PROJECT MANAGER\n";

    try
    {
        Project_Manager project;\
        home_page(project);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return 1;
    }

   

    // if (!project.m_save_data())
    // {
    //     return 1;
    // }

    return 0;
}