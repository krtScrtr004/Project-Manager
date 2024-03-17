#include <cstdlib>
#include <cctype>
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
            std::cout << "PROJECT MANAGER\n\n";

            std::cout << "PROJECTS: \n";
            for (const auto &dir : project.m_get_dir_vector())
            {
                std::cout << "* " << dir << '\n';
            }

            std::cout << '\n';

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
                std::cout << "<SELECT FROM OPTIONS:> ";
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
                const short INDEX = search_content(project, Content_Type_e::DIRECTORY);
                if (INDEX >= 0)
                {
                    search_options(project, Content_Type_e::DIRECTORY, INDEX);
                }
            }
            else if (option == Options_e::EDIT)
            {
                edit_content(project, Content_Type_e::DIRECTORY);
            }
            else if (option == Options_e::REMOVE)
            {
                remove_content(project, Content_Type_e::DIRECTORY);
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
    const short INDEX = project.m_search(temp_dir_name, temp_project.m_get_dir_vector());
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
    const short INDEX = project.m_search(temp_file_name, project.m_get_file_vector());
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
    std::cout << "\nADD DIRECTORY: \n";
    project.m_add_dir(enter_dir_name());
    std::cout << "DIRECTORY SUCCESSFULLY ADDDED\n";

    return;
}

void add_file(Project &project)
{
    std::cout << "\nADD FILE: \n";
    project.m_add_file(enter_file_name());
    std::cout << "FILE SUCCESSFULLY ADDDED\n";

    return;
}

// Searching Dir / File
const short search_content(Project &project, const Content_Type_e CONTENT_TYPE)
{
    std::cout << "\nSEARCH DIRECTORY / FILE\n";
    const std::string TARGET_NAME = (CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                        ? enter_dir_name()
                                        : enter_file_name();
    const short INDEX = project.m_search(TARGET_NAME, (CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                                           ? project.m_get_dir_vector()
                                                           : project.m_get_file_vector());
    if (INDEX < 0 || INDEX > ((CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                  ? project.m_get_dir_vector()
                                  : project.m_get_file_vector())
                                     .size() -
                                 1)
    {
        std::cout << "DIRECTORY NOT FOUND\n";
        return -1;
    }

    return INDEX;
}

void edit_content(Project &project, CONST Content_Type_e CONTENT_TYPE)
{
    std::cout << "\nEDIT DIRECTORY / FILE NAME\n";
    const short INDEX = search_content(project, CONTENT_TYPE);
    if (INDEX < 0)
    {
        std::cout << ((CONTENT_TYPE == Content_Type_e::DIRECTORY) ? "DIRECTORY" : "FILE") << "NOT FOUND!\n";
    }

    std::cout << "ENTER NEW NAME:\n";
    const std::string NEW_NAME = (CONTENT_TYPE == Content_Type_e::DIRECTORY)
                                     ? enter_dir_name()
                                     : enter_file_name();

    if (CONTENT_TYPE == Content_Type_e::DIRECTORY)
    {
        project.m_set_dir_name(NEW_NAME, INDEX);
    }
    else
    {
        project.m_set_file_name(NEW_NAME, INDEX);
    }
    std::cout << "NEW NAME SET SUCCESSFULLY!\n";

    return;
}

void remove_content(Project &project, const Content_Type_e CONTENT_TYPE)
{
    std::cout << "\nDELETE DIRECTORY / FILE NAME\n";
    const short INDEX = search_content(project, CONTENT_TYPE);
    if (INDEX < 0)
    {
        std::cout << ((CONTENT_TYPE == Content_Type_e::DIRECTORY) ? "DIRECTORY" : "FILE") << "NOT FOUND!\n";
    }

    bool is_valid = false;
    char answer = ' ';
    do
    {
        std::cout << "\nARE YOU SURE TO REMOVE " + ((CONTENT_TYPE == Content_Type_e::DIRECTORY) ? project.m_get_dir_name(INDEX) : project.m_get_file_name(INDEX)) + "? (y / n) ";
        std::cin >> answer;
        tolower(answer);
        is_valid = (answer == 'y' || answer == 'n') ? true : false;
        if (!is_valid)
        {
            std::cout << "ENTER A VALID ANSWER ONLY!\n";
        }
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (answer == 'y')
    {
        if (CONTENT_TYPE == Content_Type_e::DIRECTORY)
        {
            project.m_remove_dir(INDEX);
        }
        else
        {
            project.m_remove_file(INDEX);
        }

        std::cout << ((CONTENT_TYPE == Content_Type_e::DIRECTORY) ? project.m_get_dir_name(INDEX) : project.m_get_file_name(INDEX)) + " IS REMOVED SUCCESSFULLY!\n";
    }

    return;
}