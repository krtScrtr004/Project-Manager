#include "utility.h"

inline const std::string cin_error(void)
{
    return "INVALID INPUT. PLEASE TRY AGAIN.\n";
}

inline const std::string out_of_bounds_error(const short MIN, const short MAX)
{
    return "INPUT OUT OF BOUNDS! MINIMUM: " + std::to_string(MIN) + " MAXSIMUM: " + std::to_string(MAX) + ".\n";
}


bool is_valid_num(const short INPUT, const short MIN, const short MAX)
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

bool is_valid_str(const std::string INPUT, const short MIN, const short MAX)
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