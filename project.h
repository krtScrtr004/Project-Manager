#pragma once
#ifndef PROJECT_H
#define PROJECT_H

// For copying of dir name to vectors
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

enum class Content_Type_e : unsigned short
{
    DIRECTORY = 1,
    FILE
};
std::istream &operator>>(std::istream &is, Content_Type_e &content_type);

enum class Options_e : unsigned short
{
    OPEN = 1U,
    ADD,
    SEARCH,
    EDIT,
    REMOVE,
    EXIT
};
std::istream &operator>>(std::istream &is, Options_e &option);

enum class Search_Options_e : unsigned short
{
    OPEN = 1,
    EDIT,
    REMOVE,
    EXIT
};
std::istream &operator>>(std::istream &is, Search_Options_e &option);

class Project
{
private:
    // std::vector<std::string> m_proj;
    struct m_current_proj_t
    {
    public:
        std::vector<std::string> m_dir, m_file;
    } m_current_proj;

private:
    void m_sort(std::vector<std::string> &orig_vect);
    void m_sort_compare(std::vector<std::string> &orig_vect, std::vector<std::string> &left_vect, std::vector<std::string> &right_vect) const;

    void m_fetch_dir(std::vector<std::string> &vector);
    void m_fetch_file(void);

public:
    Project();
    ~Project();

    inline const std::vector<std::string> &m_get_dir_vector(void) const { return m_current_proj.m_dir; }
    inline const std::vector<std::string> &m_get_file_vector(void) const { return m_current_proj.m_file; }

    // inline const
    inline const std::string m_get_dir_name(const short INDEX) const { return m_current_proj.m_dir[INDEX]; }
    inline const std::string m_get_file_name(const short INDEX) const { return m_current_proj.m_file[INDEX]; }

    const short m_search(const std::string INPUT, const std::vector<std::string> &VECTOR) const;

    void m_change_dir(const std::string DIRECTORRY_NAME) const;
    void m_init_proj(const std::string PROJECT_NAME);

    inline void m_clear_current_proj_vector(void)
    {
        m_current_proj.m_dir.clear();
        m_current_proj.m_file.clear();
        return;
    }

    inline void m_add_dir(const std::string DIR_NAME)
    {
        m_current_proj.m_dir.push_back(DIR_NAME);
        const std::string PARAM = "mkdir " + DIR_NAME;
        system(PARAM.c_str());
        m_sort(this->m_current_proj.m_dir);

        for (const auto &i : m_current_proj.m_dir)
            std::cout << i << '\n';

        return;
    }

    inline void m_add_file(const std::string FILE_NAME)
    {
        m_current_proj.m_file.push_back(FILE_NAME);
        const std::string PARAM = "code " + FILE_NAME;
        system(PARAM.c_str());
        m_sort(this->m_current_proj.m_file);
        return;
    }

    inline void m_set_dir_name(const std::string NEW_NAME, const short INDEX)
    {
        std::string PARAM;
#ifdef _WIN32
        PARAM = "ren " + m_get_dir_name(INDEX) + ' ' + NEW_NAME;
#else
        PARAM = "mv " + m_get_dir_name(INDEX) + ' ' + NEW_NAME;
#endif
        system(PARAM.c_str());
        m_current_proj.m_dir[INDEX] = NEW_NAME;

        return;
    }

    inline void m_set_file_name(const std::string NEW_NAME, const short INDEX)
    {
        std::string PARAM;
#ifdef _WIN32
        PARAM = "ren " + m_get_file_name(INDEX) + ' ' + NEW_NAME;
#else
        PARAM = "mv " + m_get_file_name(INDEX) + ' ' + NEW_NAME;
#endif
        system(PARAM.c_str());
        m_current_proj.m_file[INDEX] = NEW_NAME;

        return;
    }

    inline void m_remove_dir(const short INDEX)
    {
#ifdef _WIN32
    const std::string PARAM = "rmdir /s /q " + m_get_dir_name(INDEX); 
#else
    CONST STD::STRING param = "rm -r " + m_get_dir_name(INDEX); 
#endif
        m_current_proj.m_dir.erase(m_current_proj.m_dir.begin() + INDEX);
        system(PARAM.c_str());
        return;
    } 

     inline void m_remove_file(const short INDEX)
    {
#ifdef _WIN32
    const std::string PARAM = "del " + m_get_dir_name(INDEX); 
#else
    CONST STD::STRING param = "rm " + m_get_dir_name(INDEX); 
#endif
        system(PARAM.c_str());
        m_current_proj.m_file.erase(m_current_proj.m_file.begin() + INDEX);
        return;
    } 
};

#endif