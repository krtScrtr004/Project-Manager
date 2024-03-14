#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unistd.h>

#include "project.h"

// FUNCTIONS FROM main.cpp
void open_dir(Project &project);
void open_proj(Project &project);
void open_file(Project &project);

// --------------------------------------------------------------

enum class Content_Type_e : unsigned short
{
    DIRECTORY = 1,
    FILE
};
std::istream &operator>>(std::istream &is, Content_Type_e &content_tyoe);

// --------------------------------------------------------------

inline const std::string cin_error(void) { return "INVALID INPUT. PLEASE TRY AGAIN.\n"; }
inline const std::string out_of_bounds_error(const short MIN, const short MAX) { return "INPUT OUT OF BOUNDS! MINIMUM: " + std::to_string(MIN) + " MAXSIMUM: " + std::to_string(MAX) + ".\n"; }

inline bool is_valid_num(const short INPUT, const short MIN, const short MAX)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    if (INPUT < MIN || INPUT > MAX)
    {
        std::cerr << out_of_bounds_error(MIN, MAX);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

inline bool is_valid_str(const std::string INPUT, const short MIN, const short MAX)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    const short LEN = INPUT.length();
    if (LEN < MIN || LEN > MAX)
    {
        std::cerr << out_of_bounds_error(MIN, MAX);
        return false;
    }

    return true;
}

// --------------------------------------------------------------

inline void fetch_current_path(void)
{
    char path[4096];
    if (getcwd(path, sizeof(path)) != nullptr)
    {
        std::cout << "CURRENT PATH: " << path << std::endl;
    }
    else
    {
        std::cerr << "ERROR FETCHING CURRENT PATH" << std::endl;
    }

    return;
}

void print_contents(const std::vector<std::string> &DIR_VECTOR, const std::vector<std::string> &FILE_VECTOR);

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

void select_option(Project &project);

inline void open_content(Project &project, const Content_Type_e CONTENT_TYPE)
{
    switch (CONTENT_TYPE)
    {
    case Content_Type_e::DIRECTORY:
        open_dir(project);
        break;

    case Content_Type_e::FILE:
        open_file(project);
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Content_Type_e::DIRECTORY),
                                         static_cast<short>(Content_Type_e::FILE));
    }

    return;
}

#endif