#include "project.h"

std::istream &operator>>(std::istream &is, Options_e &option)
{
    int value;
    is >> value;                            // Assuming the enum is represented as an integer in the input stream
    option = static_cast<Options_e>(value); // Convert the integer to Home_Options_e
    return is;
}

// PRIVATE METHODS
void Project::m_sort(std::vector<std::string> orig_vect)
{
    if (orig_vect.size() <= 1)
    {
        return;
    }

    const unsigned short left_size = orig_vect.size() / 2;
    std::vector<std::string> left_vect(orig_vect.begin(), orig_vect.begin() + left_size);
    std::vector<std::string> right_vect(orig_vect.begin() + left_size, orig_vect.end());

    m_sort(left_vect);
    m_sort(right_vect);

    m_sort_compare(orig_vect, left_vect, right_vect);
}

void Project::m_sort_compare(std::vector<std::string> orig_vect, std::vector<std::string> left_vect, std::vector<std::string> right_vect) const
{
    unsigned short i = 0, j = 0, k = 0,
                   left_size = left_vect.size(),
                   right_size = right_vect.size();

    while (i < left_size && j < right_size)
    {
        if (left_vect[i] < right_vect[j])
        {
            orig_vect[k] = left_vect[i];
            i++;
            k++;
        }
        else
        {
            orig_vect[k] = right_vect[j];
            j++;
            k++;
        }
    }

    while (i < left_size)
    {
        orig_vect[k] = left_vect[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        orig_vect[k] = right_vect[j];
        j++;
        k++;
    }

    return;
}

void Project::m_fetch_dir(std::vector<std::string> &vector)
{
// m_clear_current_proj_vector();
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
    DIR* dir = opendir(".");

    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_DIR) {
                vector.push_back(entry->d_name);
            }
        }
        closedir(dir);
    } else {
        throw std::runtime_error("ERROR ENUMERATING DIRECTORY CONTENTS");
    }
#endif
}

void Project::m_fetch_file(void)
{
// m_clear_current_proj_vector();
#ifdef _WIN32
    WIN32_FIND_DATAA find_data;
    HANDLE handle_find = FindFirstFileA("*", &find_data);

    if (handle_find != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
            {
                m_current_proj.m_file.push_back(find_data.cFileName);
            }
        } while (FindNextFileA(handle_find, &find_data) != 0);

        FindClose(handle_find);
    }
    else
    {
        throw std::runtime_error("ERROR ENUMERATING DIRECTORY CONTENTS");
    }
#else
    DIR *dir = opendir(".");
    if (dir != nullptr)
    {
        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr)
        {
            struct stat st;
            if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode))
            {
                m_current_proj.m_file.push_back(entry->d_name);
            }
        }
        closedir(dir);
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
        m_change_dir("..");
        m_fetch_dir(this->m_current_proj.m_dir);
    }
    catch (const std::exception &e)
    {
        throw;
    }

    m_sort(this->m_current_proj.m_dir);
}

Project::~Project()
{
    m_clear_current_proj_vector();
}

// std::string &Project::operator[](const size_t INDEX)
// {
//     if (INDEX >= m_current_proj.m_dir.size())
//     {
//         throw std::out_of_range("INDEX OUT OF BOUNDS");
//     }

//     return m_current_proj.m_dir[INDEX];
// }

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

void Project::m_change_dir(const std::string DIRECTORY_NAME) const
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

void Project::m_init_proj(const std::string DIR_NAME)
{
    try
    {
        m_change_dir(DIR_NAME);
        m_clear_current_proj_vector();
        m_fetch_dir(this->m_current_proj.m_dir);
        m_fetch_file();
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
