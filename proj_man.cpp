#include "proj_man.h"

std::istream &operator>>(std::istream &is, Home_Options_e &option)
{
    int value;
    is >> value;                                 // Assuming the enum is represented as an integer in the input stream
    option = static_cast<Home_Options_e>(value); // Convert the integer to Home_Options_e
    return is;
}

// PRIVATE METHODS
void Project_Manager::m_fetch_data(void)
{
    m_infile.open(M_FILE_NAME, std::ios::in);
    if (!m_infile.is_open())
    {
        throw std::ios_base::failure("Failed to open file: " + M_FILE_NAME);
    }

    bool is_alternate = true;
    std::string current_name = " ", current_path = " ", current_link = " ", current_status = " ", white_space;
    unsigned short current_id = 0U;
    while (m_infile.peek() != std::ifstream::traits_type::eof())
    {
        if (is_alternate)
        {
            getline(m_infile, current_name);
            getline(m_infile, current_path);
            getline(m_infile, current_link);
            getline(m_infile, current_status);
            m_infile >> current_id;

            m_info.m_name.push_back(current_name);
            m_info.m_path.push_back(current_path);
            m_info.m_link.push_back(current_link);
            m_info.m_status.push_back(current_status);
            m_info.m_id.push_back(current_id);

            m_infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            getline(m_infile, white_space);
        }
        is_alternate = !is_alternate;
    }

    return;
}

void Project_Manager::m_save_data(void)
{
    m_outfile.open(M_FILE_NAME, std::ios::out);
    if (!m_outfile.is_open())
    {
        throw std::ios_base::failure("Failed to open file: " + M_FILE_NAME + " Data won't be saved!");
    }

    bool is_alternate = true;
    unsigned short counter = 0U;

    while (counter < m_info.m_name.size())
    {
        if (is_alternate)
        {
            m_outfile << m_info.m_name[counter] << '\n';
            m_outfile << m_info.m_path[counter] << '\n';
            m_outfile << m_info.m_link[counter] << '\n';
            m_outfile << m_info.m_status[counter] << '\n';
            m_outfile << m_info.m_id[counter] << '\n';

            ++counter;
        }
        is_alternate = !is_alternate;
    }

    m_info.m_name.clear();
    m_info.m_path.clear();
    m_info.m_link.clear();
    m_info.m_status.clear();
    m_info.m_id.clear();

    return;
}

// PUBLIC METHODS
void Project_Manager::m_add_project(const std::string PROJECT_NAME, const std::string PROJECT_PATH,
                                    const std::string PROJECT_LINK, const std::string PROJECT_STATUS)
{
    m_info.m_name.push_back(PROJECT_NAME);
    m_info.m_path.push_back(PROJECT_PATH);
    m_info.m_link.push_back(PROJECT_LINK);
    m_info.m_status.push_back(PROJECT_STATUS);
    srand(time(nullptr));
    m_info.m_id.push_back(rand() % 9999);
}

void Project_Manager::m_open_project(Project_Manager &project)
{
    unsigned short counter = 0U;
    while (counter < m_info.m_name.size())
    {
        std::cout << m_info.m_name[counter] + ' ' + m_info.m_path[counter] + ' ' + m_info.m_link[counter] + ' ' +  m_info.m_status[counter] + ' ' << m_info.m_id[counter] << '\n';
        ++counter;
    }
}
