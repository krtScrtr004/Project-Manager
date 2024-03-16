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
#include <type_traits>

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
            for (const auto &dir : project.m_get_dir_vector())
            {
                std::cout << dir << '\n';
            }

            std::cout << "PROJECT MANAGER\n";
            std::cout << "[1] OPEN PROJECT\n";
            std::cout << "[2] ADD PROJECT\n";
            std::cout << "[3] SEARCH PROJECT\n";
            std::cout << "[4] EDIT PROJECT\n";
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
                    open_dir(project);
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }
            else if (option == Options_e::ADD)
            {
                add_content(project, Content_Type_e::DIRECTORY);
            }
            else if (option == Options_e::SEARCH)
            {
                search_content(project, Content_Type_e::DIRECTORY);
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

// temp_dir_name CONTAINS DEFAULT PARAM (" ")
void open_dir(const Project &project, std::string temp_dir_name)
{
    Project temp_project(project);
    std::cout << "OPEN DIRECTORY: \n";
    bool is_valid = false;
    if (temp_dir_name == " ")
    {
        temp_dir_name = enter_dir_name();
    }
    const std::size_t INDEX = project.m_search(temp_dir_name, temp_project.m_get_dir_vector());
    if (INDEX < 0 || INDEX > project.m_get_dir_vector().size() - 1)
    {
        std::cout << "DIRECTORY NAME NOT FOUND!\n";
        return;
    }

    temp_project.m_init_proj(temp_project.m_get_dir_name(INDEX));

    Options_e option;
    while (option != Options_e::EXIT)
    {
        print_contents(temp_project.m_get_dir_vector(), temp_project.m_get_file_vector());
        option = select_option(temp_project);
    }

    try
    {
        temp_project.m_change_dir("..");
    }
    catch (const std::exception &e)
    {
        throw;
    }

    return;
}

// temp_file_name CONTAINS DEFAULT PARAM (" ")
void open_file(const Project &project, std::string temp_file_name)
{
    std::cout << "OPEN FILE: \n";
    bool is_valid = false;
    if (temp_file_name == " ")
    {
        temp_file_name = enter_file_name();
    }
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

// Adding Dir / File
void add_dir(Project &project)
{
    std::cout << "ADD SUB-DIRECTORY: \n";
    project.m_add_dir(enter_dir_name());
    std::cout << "SUB-DIRECTORY SUCCESSFULLY ADDDED\n";

    return;
}

void add_file(Project &project)
{
    std::cout << "ADD FILE: \n";
    project.m_add_file(enter_file_name());
    std::cout << "FILE SUCCESSFULLY ADDDED\n";

    return;
}

void search_content(const Project &project, const Content_Type_e CONTENT_TYPE)
{
    const std::string TARGET_NAME = (CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                        ? enter_dir_name()
                                        : enter_file_name();
    const size_t INDEX = project.m_search(TARGET_NAME, (CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                                           ? project.m_get_dir_vector()
                                                           : project.m_get_file_vector());
    if (INDEX < 0 || INDEX > ((CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                  ? project.m_get_dir_vector()
                                  : project.m_get_file_vector())
                                     .size() -
                                 1)
    {
        std::cout << "DIRECTORY NOT FOUND\n";
        return;
    }

    search_options(project, CONTENT_TYPE, INDEX);

    return;
}
