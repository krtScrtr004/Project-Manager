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
    void m_sort(std::vector<std::string> orig_vect);
    void m_sort_compare(std::vector<std::string> orig_vect, std::vector<std::string> left_vect, std::vector<std::string> right_vect) const;

    void m_fetch_dir(std::vector<std::string> &vector);
    void m_fetch_file(void);

public:
    Project();
    ~Project();

    // std::string &operator[](const size_t INDEX);

    // inline const unsigned short m_size(void) const { return m_proj.size(); }
    // inline const std::vector<std::string> &m_get_proj_vector(void) const { return m_proj; }
    inline const std::vector<std::string> &m_get_dir_vector(void) const { return m_current_proj.m_dir; }
    inline const std::vector<std::string> &m_get_file_vector(void) const { return m_current_proj.m_file; }

    // inline const
    inline const std::string m_get_dir_name(const size_t INDEX) const { return m_current_proj.m_dir[INDEX]; }
    inline const std::string m_get_file_name(const size_t INDEX) const { return m_current_proj.m_file[INDEX]; }

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
};

#endif