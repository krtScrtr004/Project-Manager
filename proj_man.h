#pragma once
#ifndef PROJ_MAN_H
#define PROJ_MAN_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>

#include "utility.h"

enum class Home_Options_e : unsigned short
{
    ADD = 1,
    OPEN,
    DELETE,
    SEARCH,
    EXIT
};

std::istream &operator>>(std::istream &is, Home_Options_e &option);

class Project_Manager
{
private:
    enum class Folder_Options_e : unsigned short
    {
        ADD = 1,
        OPEN,
        EDIT,
        SEARCH,
        DELETE
    };

    enum class File_Options_e : unsigned short
    {
        ADD = 1,
        OPEN,
        EDIT,
        SEARCH,
        DELETE
    };

    struct m_Info_t
    {
        std::vector<std::string> m_name, m_path, m_link, m_status;
        std::vector<unsigned short> m_id;
    } m_info;

    std::ifstream m_infile;
    std::ofstream m_outfile;

    const std::string M_FILE_NAME = "data/data.txt";

private:
    void m_fetch_data(void);
    void m_save_data(void);

public:
    inline Project_Manager()
    {
        try
        {
            m_fetch_data();
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    inline ~Project_Manager()
    {
        try
        {
            m_save_data();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception: " << e.what() << '\n';
        }
    }

    void m_add_project(const std::string PROJECT_NAME, const std::string PROJECT_PATH,
                       const std::string PROJECT_LINK, const std::string PROJECT_STATUS);

    inline const std::string m_enter_project_name(void)
    {
        std::string name = "";
        bool is_valid = false;
        constexpr unsigned short MIN = 5U, MAX = 20U;
        do
        {
            std::cout << "ENTER PROJECT NAME: ";
            getline(std::cin, name);
            is_valid = is_valid_str(name, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return name;
    }

    inline const std::string m_enter_project_path(void)
    {
        std::string path = "";
        bool is_valid = false;
        constexpr unsigned short MIN = 1U, MAX = 50U;
        do
        {
            std::cout << "ENTER PROJECT PATH: ";
            getline(std::cin, path);
            is_valid = is_valid_str(path, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return path;
    }

    inline const std::string m_enter_project_link(void)
    {
        std::string link = "";
        bool is_valid = false;
        constexpr unsigned short MIN = 5U, MAX = 50U;
        do
        {
            std::cout << "ENTER PROJECT GITHUB LINK: (N/A if none)";
            getline(std::cin, link);
            is_valid = is_valid_str(link, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return link;
    }

    inline const std::string m_enter_project_status(void)
    {
        std::string status = "";
        bool is_valid = false;
        constexpr unsigned short MIN = 5U, MAX = 50U;
        do
        {
            std::cout << "ENTER PROJECT STATUS: ";
            getline(std::cin, status);
            is_valid = is_valid_str(status, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return status;
    }

    void m_open_project(Project_Manager &project);
};

#endif