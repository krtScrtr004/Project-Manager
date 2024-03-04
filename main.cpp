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

inline const Content_Type_e select_content(void)
{
    std::cout << "SELECT CONTENT TYPE: \n";
    std::cout << "[1] DIRECTORY\n";
    std::cout << "[2] FILE\n";

    Content_Type_e select_content;
    bool is_valid = false;
    do
    {
        std::cout << "ENTER HERE: ";
        std::cin >> select_content;
        is_valid = is_valid_num(static_cast<short>(select_content),
                                static_cast<short>(Content_Type_e::DIRECTORY),
                                static_cast<short>(Content_Type_e::FILE));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return select_content;
}

inline void fetch_contents(Project &project, const std::size_t INDEX)
{
    try
    {
        project.m_init_project(project[INDEX]);
    }
    catch (const std::exception &e)
    {
        throw;
    }

    const auto& sub_directories = project.m_get_sub_directory_vector();
    const auto& files = project.m_get_file_vector();

    if (!sub_directories.empty())
    {
        std::cout << "SUB-DIRECTORIES: \n";
        for (const auto &sub_dir : sub_directories)
        {
            std::cout << sub_dir << '\n';
        }
    }
    else
    {
        std::cout << "NO SUB-DIRECTORIES AVAILABLE\n";
    }

    if (!files.empty())
    {
        std::cout << "\nFILES: \n";
        for (const auto &file : files)
        {
            std::cout << file << '\n';
        }
    }
    else
    {
        std::cout << "NO FILES AVAILABLE\n";
    }

    return;
}


void open_content(Project &projject, const Content_Type_e CONTENT_TYPE)
{
    switch (CONTENT_TYPE)
    {
    case Content_Type_e::DIRECTORY:
    {
    }

    case Content_Type_e::FILE:
    {
    }
    }
}

void open_project(Project &project)
{
    bool is_valid = false;

    std::string temp_project_name = " ";
    do
    {
        std::cout << "ENTER PROJECT DIRECTORY NAME: ";
        getline(std::cin, temp_project_name);
        is_valid = is_valid_str(temp_project_name, 1, 50);
    } while (!is_valid);
    const std::size_t INDEX = project.m_search(temp_project_name, project.m_get_project_vector());
    if (INDEX < 0 || INDEX > project.m_size() - 1)
    {
        std::cout << "PROJECT NAME NOT FOUND!\n";
        return;
    }

    try
    {
        fetch_contents(project, INDEX);
    }
    catch (const std::exception &e)
    {
        throw;
    }

    std::cout << "OPTIONS: \n";
    std::cout << "[1] OPEN\n";
    std::cout << "[2] ADD\n";
    std::cout << "[3] SEARCH\n";
    std::cout << "[4] EDIT\n";
    std::cout << "[5] REMOVE\n";
    std::cout << "[6] BACK\n";

    Options_e select_option;
    do
    {
        std::cout << "SELECT FROM OPTIONS: ";
        std::cin >> select_option;
        is_valid = is_valid_num(static_cast<short>(select_option),
                                static_cast<short>(Options_e::OPEN),
                                static_cast<short>(Options_e::EXIT));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (select_option)
    {
    case Options_e::OPEN:
        break;

    case Options_e::ADD:
        break;

    case Options_e::SEARCH:
        break;

    case Options_e::EDIT:
        break;

    case Options_e::REMOVE:
        break;

    case Options_e::EXIT:
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Options_e::OPEN),
                                         static_cast<short>(Options_e::EXIT));
    }

    try
    {
        project.m_change_directory("..");
    }
    catch (const std::exception &e)
    {
        throw;
    }

    return;
}

int main(void)
{
    try
    {
        Project project;
        while (true)
        {
            std::cout << "PROJECTS: \n";
            for (const auto &dir : project.m_get_project_vector())
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

            Options_e select_option = static_cast<Options_e>(0);
            bool is_valid = false;
            do
            {
                std::cout << "SELECT FROM OPTIONS: ";
                std::cin >> select_option;
                is_valid = is_valid_num(static_cast<short>(select_option),
                                        static_cast<short>(Options_e::OPEN),
                                        static_cast<short>(Options_e::EXIT));
            } while (!is_valid);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (select_option == Options_e::OPEN)
            {
                try
                {
                    open_project(project);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "EXCEPTION CAUGHT: " << e.what() << '\n';
                    return 1;
                }
            }
            else if (select_option == Options_e::ADD)
            {
                /* code */
            }
            else if (select_option == Options_e::SEARCH)
            {
                /* code */
            }
            else if (select_option == Options_e::EDIT)
            {
                /* code */
            }
            else if (select_option == Options_e::REMOVE)
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
