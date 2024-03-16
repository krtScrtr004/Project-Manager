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
// OPENING PROJECT / FOLDER / FILE
void open_dir(const Project &project, std::string temp_dir_name = " ");
void open_file(const Project &project, std::string temp_file_name = " ");

// ADDING
void add_dir(Project &project);
void add_file(Project &project);

void search_content(const Project &project, const Content_Type_e CONTENT_TYPE);

// --------------------------------------------------------------

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

inline const std::string enter_dir_name(void)
{
    bool is_valid = false;
    std::string temp_dir_name = " ";
    do
    {
        std::cout << "ENTER DIRECTORY NAME: ";
        getline(std::cin, temp_dir_name);
        is_valid = is_valid_str(temp_dir_name, 1, 50);
    } while (!is_valid);

    return temp_dir_name;
}

inline const std::string enter_file_name(void)
{
    bool is_valid = false;
    std::string temp_file_name = " ";
    do
    {
        std::cout << "ENTER FILE NAME: ";
        getline(std::cin, temp_file_name);
        is_valid = is_valid_str(temp_file_name, 1, 50);
    } while (!is_valid);

    return temp_file_name;
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

const Options_e select_option(Project &project);

inline void open_content(Project &project, const Content_Type_e CONTENT_TYPE)
{
    switch (CONTENT_TYPE)
    {
    case Content_Type_e::DIRECTORY:
    {
        try
        {
            open_dir(project);
        }
        catch(const std::exception& e)
        {
            throw;
        }        
        break;
    }

    case Content_Type_e::FILE:
        open_file(project);
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Content_Type_e::DIRECTORY),
                                         static_cast<short>(Content_Type_e::FILE));
    }

    return;
}

inline void add_content(Project &project, const Content_Type_e CONTENT_TYPE)
{
    switch (CONTENT_TYPE)
    {
    case Content_Type_e::DIRECTORY:
        add_dir(project);
        break;

    case Content_Type_e::FILE:
        add_file(project);
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Content_Type_e::DIRECTORY),
                                         static_cast<short>(Content_Type_e::FILE));
    }

    return;
}

void search_options(const Project &project, const Content_Type_e CONTENT_TYPE, const size_t INDEX);

#endif