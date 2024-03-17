#include "utility.h"

void print_contents(const std::vector<std::string> &DIR_VECTOR, const std::vector<std::string> &FILE_VECTOR)
{
    std::cout << '\n';
    fetch_current_path();
    std::cout << '\n';

    if (!DIR_VECTOR.empty())
    {
        std::cout << "DIRECTORIES: \n";
        for (const auto &sub_dir : DIR_VECTOR)
        {
            std::cout << "* " << sub_dir << '\n';
        }
    }
    else
    {
        std::cout << "NO DIRECTORIES AVAILABLE\n";
    }

    std::cout << '\n';

    if (!FILE_VECTOR.empty())
    {
        std::cout << "\nFILES: \n";
        for (const auto &file : FILE_VECTOR)
        {
            std::cout << "- " << file << '\n';
        }
    }
    else
    {
        std::cout << "NO FILES AVAILABLE\n";
    }
    std::cout << '\n';

    return;
}

const Options_e select_option(Project &project)
{
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
        std::cout << "<SELECT FROM OPTIONS:> ";
        std::cin >> option;
        is_valid = is_valid_num(static_cast<short>(option),
                                static_cast<short>(Options_e::OPEN),
                                static_cast<short>(Options_e::EXIT));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Content_Type_e content_type;
    if (option != Options_e::EXIT)
    {
        content_type = select_content();
    }
    switch (option)
    {
    case Options_e::OPEN:
        open_content(project, content_type);
        break;

    case Options_e::ADD:
        add_content(project, content_type);
        break;

    case Options_e::SEARCH:
    {
        const short INDEX = search_content(project, content_type);
        if (INDEX >= 0)
        {
            search_options(project, content_type, INDEX);
        }
        break;
    }

    case Options_e::EDIT:
        edit_content(project, content_type);
        break;

    case Options_e::REMOVE:
        remove_content(project, content_type);
        break;

    case Options_e::EXIT:
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Options_e::OPEN),
                                         static_cast<short>(Options_e::EXIT));
    }

    return option;
}

void search_options(Project &project, const Content_Type_e CONTENT_TYPE, const short INDEX)
{
    Search_Options_e option;
    bool is_valid = false;
    do
    {
        std::cout << "[1] OPEN\n";
        std::cout << "[2] EDIT\n";
        std::cout << "[3] DELETE\n";
        std::cout << "[4] BACK\n";

        std::cout << "<SELECT FROM OPTIONS:> ";
        std::cin >> option;
        is_valid = is_valid_num(static_cast<short>(option),
                                static_cast<short>(Search_Options_e::OPEN),
                                static_cast<short>(Search_Options_e::EXIT));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (option)
    {
    case Search_Options_e::OPEN:
    {
        (CONTENT_TYPE == Content_Type_e::DIRECTORY)
            ? open_dir(project, project.m_get_dir_name(INDEX))
            : open_file(project, project.m_get_file_name(INDEX));
        break;
    }

    case Search_Options_e::EDIT:
        edit_content(project, CONTENT_TYPE);
        break;

    case Search_Options_e::REMOVE:
        remove_content(project, CONTENT_TYPE);
        break;

    case Search_Options_e::EXIT:
        break;

    default:
        std::cerr << out_of_bounds_error(static_cast<short>(Search_Options_e::OPEN),
                                         static_cast<short>(Search_Options_e::EXIT));
    }

    return;
}
