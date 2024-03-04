#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>
#include <string>

enum class Content_Type_e : unsigned short
{
    DIRECTORY = 1,
    FILE
};
std::istream &operator>>(std::istream &is, Content_Type_e &content_tyoe);

const std::string cin_error(void);

const std::string out_of_bounds_error(const short MIN, const short MAX);

bool is_valid_num(const short INPUT, const short MIN, const short MAX);
bool is_valid_str(const std::string INPUT, const short MIN, const short MAX);

#endif