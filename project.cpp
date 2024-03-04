#include "project.h"

std::istream &operator>>(std::istream &is, Options_e &option)
{
    int value;
    is >> value;                            // Assuming the enum is represented as an integer in the input stream
    option = static_cast<Options_e>(value); // Convert the integer to Home_Options_e
    return is;
}

// PRIVATE METHODS
void Project::m_sort(std::vector<std::string> orig_directory)
{
    if (orig_directory.size() <= 1)
    {
        return;
    }

    const unsigned short left_size = m_directory.size() / 2;
    std::vector<std::string> left_directory(orig_directory.begin(), orig_directory.begin() + left_size);
    std::vector<std::string> right_directory(orig_directory.begin() + left_size, orig_directory.end());

    m_sort(left_directory);
    m_sort(right_directory);

    m_sort_compare(orig_directory, left_directory, right_directory);
}

void Project::m_sort_compare(std::vector<std::string> orig_directory, std::vector<std::string> left_directory, std::vector<std::string> right_directory) const
{
    unsigned short i = 0, j = 0, k = 0,
                   left_size = left_directory.size(),
                   right_size = right_directory.size();

    while (i < left_size && j < right_size)
    {
        if (left_directory[i] < right_directory[j])
        {
            orig_directory[k] = left_directory[i];
            i++;
            k++;
        }
        else
        {
            orig_directory[k] = right_directory[j];
            j++;
            k++;
        }
    }

    while (i < left_size)
    {
        orig_directory[k] = left_directory[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        orig_directory[k] = right_directory[j];
        j++;
        k++;
    }

    return;
}

void Project::m_fetch_directory(std::vector<std::string> &vector)
{
#ifdef _WIN32
    WIN32_FIND_DATAA find_data;
    HANDLE handle_find = FindFirstFileA("*", &find_data);

    if (handle_find != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                (strcmp(find_data.cFileName, ".") != 0) &&
                (strcmp(find_data.cFileName, "..") != 0))
            {
                vector.push_back(find_data.cFileName);
            }
        } while (FindNextFileA(handle_find, &find_data) != 0);
        FindClose(handle_find);
    }
    else
    {
        throw std::runtime_error("ERROR ENUMERATING DIRECTORY CONTENTS");
    }
#else
    0
#endif
}

void Project::m_fetch_file(void)
{
#ifdef _WIN32
    WIN32_FIND_DATAA find_data;
    HANDLE handle_find = FindFirstFileA("*", &find_data);

    if (handle_find != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
            {
                m_current_project.m_file.push_back(find_data.cFileName);
            }
        } while (FindNextFileA(handle_find, &find_data) != 0);

        FindClose(handle_find);
    }
    else
    {
        throw std::runtime_error("ERROR ENUMERATING DIRECTORY CONTENTS");
    }
#else
    DIR *directory = opendir(".");
    if (directory != nullptr)
    {
        struct dirent *entry;
        while ((entry = readdir(directory)) != nullptr)
        {
            struct stat st;
            if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode))
            {
                m_current_project.m_file.push_back(entry->d_name);
            }
        }
        closedir(directory);
    }
    else
    {
        throw std::runtime_error("FAILED TO OPEN DIRECTORY!");
    }
#endif

    return;
}

// PUBLIC METHIDS
Project::Project()
{
    try
    {
        m_change_directory("..");
        m_fetch_directory(m_directory);
    }
    catch (const std::exception &e)
    {
        throw;
    }

    m_sort(this->m_directory);
}

std::string &Project::operator[](const size_t INDEX)
{
    if (INDEX >= m_directory.size())
    {
        throw std::out_of_range("INDEX OUT OF BOUNDS");
    }

    return m_directory[INDEX];
}

const short Project::m_search(const std::string INPUT, const std::vector<std::string> &VECTOR) const
{
    if (VECTOR.size() < 0)
    {
        return -1;
    }

    short index = -1, start = 0, end = VECTOR.size() - 1;
    while (start <= end)
    {
        const short mid = (start + end) / 2,
                    comparison = strcmp(INPUT.c_str(), VECTOR[mid].c_str());
        if (comparison == 0)
        {
            index = mid;
            break;
        }
        else if (comparison < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return index;
}

void Project::m_change_directory(const std::string DIRECTORY_NAME) const
{
#ifdef _WIN32
    if (_chdir(DIRECTORY_NAME.c_str()) != 0)
    {
        throw std::runtime_error("FAILED TO CHANGE DIRECTORY!");
    }
#else
    if (chdir(DIRECTORY_NAME.c_str()) != 0)
    {
        throw std::runtime_error("FAILED TO CHANGE DIRECTORY!");
    }
#endif

    return;
}

void Project::m_init_project(const std::string PROJECT_NAME)
{
    try
    {
        m_change_directory(PROJECT_NAME);
        m_fetch_directory(m_current_project.m_sub_directory);
        m_fetch_file();
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
