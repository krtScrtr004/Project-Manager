// #ifdef _WIN32
//  system("cd ../ && dir /A:D /B");
// #else
//  system("cd ../ && ls -l | grep '^d'");
// #endif

#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "project.h"
#include "utility.h"

int main(void)
{
    try
    {
        Project project;
        while (true)
        {
            std::cout << "PROJECTS: \n";
            for (const auto &dir : project.m_get_proj_vector())
            {
                std::cout << dir << '\n';
            }

            std::cout << "PROJECT MANAGER\n";
            std::cout << "[1] OPEN PROJECT\n";
            std::cout << "[2] ADD PROJECT\n";
            std::cout << "[3] OPEN PROJECT\n";
            std::cout << "[4] SEARCH PROJECT\n";
            std::cout << "[5] DELETE PROJECT\n";
            std::cout << "[6] EXIT\n";

            Options_e option = static_cast<Options_e>(0);
            bool is_valid = false;
            do
            {
                std::cout << "SELECT FROM OPTIONS: ";
                std::cin >> option;
                is_valid = is_valid_num(static_cast<short>(option),
                                        static_cast<short>(Options_e::OPEN),
                                        static_cast<short>(Options_e::EXIT));
            } while (!is_valid);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (option == Options_e::OPEN)
            {
                try
                {
                    open_proj(project);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "EXCEPTION CAUGHT: " << e.what() << '\n';
                    return 1;
                }
            }
            else if (option == Options_e::ADD)
            {
                /* code */
            }
            else if (option == Options_e::SEARCH)
            {
                /* code */
            }
            else if (option == Options_e::EDIT)
            {
                /* code */
            }
            else if (option == Options_e::REMOVE)
            {
                /* code */
            }
            else
            {
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION CAUGHT: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

void open_proj(Project &project)
{
    bool is_valid = false;
    std::string temp_proj_name = " ";
    do
    {
        std::cout << "ENTER PROJECT NAME: ";
        getline(std::cin, temp_proj_name);
        is_valid = is_valid_str(temp_proj_name, 1, 50);
    } while (!is_valid);
    const std::size_t INDEX = project.m_search(temp_proj_name, project.m_get_proj_vector());
    if (INDEX < 0 || INDEX > project.m_size() - 1)
    {
        std::cout << "PROJECT NAME NOT FOUND!\n";
        return;
    }

    try
    {
        project.m_clear_current_proj_vector();
        project.m_init_proj(project[INDEX]);
    }
    catch (const std::exception &e)
    {
        throw;
    }

    Options_e option;
    while (option != Options_e::EXIT)
    {
        print_contents(project.m_get_sub_dir_vector(), project.m_get_file_vector());
        option = select_option(project);
    }

    try
    {
        project.m_change_dir("..");
    }
    catch (const std::exception &e)
    {
        throw;
    }

    return;
}

void open_dir(Project &project)
{
    Project *temp_project = new Project(project);
    
    bool is_valid = false;
    std::string temp_dir_name = " ";
    do
    {
        std::cout << "ENTER DIRECTORY NAME: ";
        getline(std::cin, temp_dir_name);
        is_valid = is_valid_str(temp_dir_name, 1, 50);
    } while (!is_valid);
    const std::size_t INDEX = temp_project->m_search(temp_dir_name, temp_project->m_get_sub_dir_vector());
    if (INDEX < 0 || INDEX > temp_project->m_get_sub_dir_vector().size() - 1)
    {
        std::cout << "DIRECTORY NAME NOT FOUND!\n";
        return;
    }

    try
    {
        temp_project->m_clear_current_proj_vector();
        temp_project->m_init_proj(temp_project->m_get_sub_dir_name(INDEX));
    }
    catch (const std::exception &e)
    {
        throw;
    }

    Options_e option;
    while (option != Options_e::EXIT)
    {
        print_contents(temp_project->m_get_sub_dir_vector(), temp_project->m_get_file_vector());
        option = select_option(*temp_project);
    }

    try
    {
        temp_project->m_change_dir("..");
    }
    catch (const std::exception &e)
    {
        throw;
    }

    delete temp_project;
    return;
}

void open_file(Project &project)
{
    bool is_valid = false;
    std::string temp_file_name = " ";
    do
    {
        std::cout << "ENTER FILE NAME: ";
        getline(std::cin, temp_file_name);
        is_valid = is_valid_str(temp_file_name, 1, 50);
    } while (!is_valid);
    const std::size_t INDEX = project.m_search(temp_file_name, project.m_get_file_vector());
    if (INDEX < 0 || INDEX > project.m_get_file_vector().size() - 1)
    {
        std::cout << "FILE NAME NOT FOUND!\n";
        return;
    }

    std::string param = "code " + temp_file_name;
    system(param.c_str());

    return;
}
