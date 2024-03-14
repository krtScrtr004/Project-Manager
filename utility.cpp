#include "utility.h"

std::istream &operator>>(std::istream &is, Content_Type_e &content_type)
{
    int value;
    is >> value;
    content_type = static_cast<Content_Type_e>(value);
    return is;
}

void print_contents(const std::vector<std::string> &DIR_VECTOR, const std::vector<std::string> &FILE_VECTOR)
{
    fetch_current_path();
    std::cout << '\n';
    if (!DIR_VECTOR.empty())
    {
        std::cout << "SUB-DIRECTORIES: \n";
        for (const auto &sub_dir : DIR_VECTOR)
        {
            std::cout << sub_dir << '\n';
        }
    }
    else
    {
        std::cout << "NO SUB-DIRECTORIES AVAILABLE\n";
    }

    if (!FILE_VECTOR.empty())
    {
        std::cout << "\nFILES: \n";
        for (const auto &file : FILE_VECTOR)
        {
            std::cout << file << '\n';
        }
    }
    else
    {
        std::cout << "NO FILES AVAILABLE\n";
    }
    std::cout << '\n';

    return;
}

void select_option(Project &project)
{
    std::cout << "OPTIONS: \n";
    std::cout << "[1] OPEN\n";
    std::cout << "[2] ADD\n";
    std::cout << "[3] SEARCH\n";
    std::cout << "[4] EDIT\n";
    std::cout << "[5] REMOVE\n";
    std::cout << "[6] BACK\n";

    bool is_valid = false;
    Options_e option;
    do
    {
        std::cout << "SELECT FROM OPTIONS: ";
        std::cin >> option;
        is_valid = is_valid_num(static_cast<short>(option),
                                static_cast<short>(Options_e::OPEN),
                                static_cast<short>(Options_e::EXIT));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const Content_Type_e CONTENT_TYPE = select_content();
    switch (option)
    {
    case Options_e::OPEN:
        open_content(project, CONTENT_TYPE);
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
}


