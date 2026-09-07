#include "ScalarConverter.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <cctype>
#include <cmath>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    (void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &literal)
{
    if (isPseudoLiteral(literal))
        printPseudoLiteral(literal);
    else if (isCharLiteral(literal))
        convertChar(literal);
    else if (isIntLiteral(literal))
        convertInt(literal);
    else if (isFloatLiteral(literal))
        convertFloat(literal);
    else if (isDoubleLiteral(literal))
        convertDouble(literal);
    else
        printAllImpossible();
}

bool ScalarConverter::isCharLiteral(const std::string &literal)
{
    return (literal.length() == 1
        && !std::isdigit(static_cast<unsigned char>(literal[0])));
}

bool ScalarConverter::isIntLiteral(const std::string &literal)
{
    std::size_t i;

    if (literal.empty())
        return false;

    i = 0;

    if (literal[i] == '+' || literal[i] == '-')
        i++;

    if (i == literal.length())
        return false;

    while (i < literal.length())
    {
        if (!std::isdigit(static_cast<unsigned char>(literal[i])))
            return false;
        i++;
    }

    return true;
}

bool ScalarConverter::isFloatLiteral(const std::string &literal)
{
    std::size_t i;
    std::size_t end;
    int dotCount;
    int digitCount;

    if (literal.length() < 3)
        return false;

    if (literal[literal.length() - 1] != 'f')
        return false;

    i = 0;
    end = literal.length() - 1;
    dotCount = 0;
    digitCount = 0;

    if (literal[i] == '+' || literal[i] == '-')
        i++;

    if (i == end)
        return false;

    while (i < end)
    {
        if (literal[i] == '.')
            dotCount++;
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
            digitCount++;
        else
            return false;

        i++;
    }

    return (dotCount == 1 && digitCount > 0);
}

bool ScalarConverter::isDoubleLiteral(const std::string &literal)
{
    std::size_t i;
    int dotCount;
    int digitCount;

    if (literal.length() < 2)
        return false;

    i = 0;
    dotCount = 0;
    digitCount = 0;

    if (literal[i] == '+' || literal[i] == '-')
        i++;

    if (i == literal.length())
        return false;

    while (i < literal.length())
    {
        if (literal[i] == '.')
            dotCount++;
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
            digitCount++;
        else
            return false;

        i++;
    }

    return (dotCount == 1 && digitCount > 0);
}

bool ScalarConverter::isPseudoLiteral(const std::string &literal)
{
    return literal == "nan"
        || literal == "nanf"
        || literal == "+inf"
        || literal == "-inf"
        || literal == "+inff"
        || literal == "-inff";
}

void ScalarConverter::convertChar(const std::string &literal)
{
    char c;
    int i;
    float f;
    double d;

    c = literal[0];

    i = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);

    printCharValue(c);
    printIntValue(i);
    printFloatValue(f);
    printDoubleValue(d);
}

void ScalarConverter::convertInt(const std::string &literal)
{
    std::stringstream ss(literal);
    int i;
    char c;
    float f;
    double d;

    ss >> i;

    if (ss.fail() || !ss.eof())
    {
        printAllImpossible();
        return;
    }

    c = static_cast<char>(i);
    f = static_cast<float>(i);
    d = static_cast<double>(i);

    printCharFromInt(i, c);
    printIntValue(i);
    printFloatValue(f);
    printDoubleValue(d);
}

void ScalarConverter::convertFloat(const std::string &literal)
{
    std::string numericLiteral;
    std::stringstream ss;
    float f;
    char c;
    int i;
    double d;

    numericLiteral = literal.substr(0, literal.length() - 1);

    ss.str(numericLiteral);
    ss >> f;

    if (ss.fail() || !ss.eof())
    {
        printAllImpossible();
        return;
    }

    if (f < static_cast<float>(std::numeric_limits<int>::min())
        || f > static_cast<float>(std::numeric_limits<int>::max()))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    }
    else
    {
        i = static_cast<int>(f);
        c = static_cast<char>(i);

        printCharFromInt(i, c);
        printIntValue(i);
    }

    d = static_cast<double>(f);

    printFloatValue(f);
    printDoubleValue(d);
}

void ScalarConverter::convertDouble(const std::string &literal)
{
    std::stringstream ss(literal);
    double d;
    char c;
    int i;
    float f;

    ss >> d;

    if (ss.fail() || !ss.eof())
    {
        printAllImpossible();
        return;
    }

    if (d < static_cast<double>(std::numeric_limits<int>::min())
        || d > static_cast<double>(std::numeric_limits<int>::max()))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    }
    else
    {
        i = static_cast<int>(d);
        c = static_cast<char>(i);

        printCharFromInt(i, c);
        printIntValue(i);
    }

    if (d < -static_cast<double>(std::numeric_limits<float>::max())
        || d > static_cast<double>(std::numeric_limits<float>::max()))
    {
        std::cout << "float: impossible" << std::endl;
    }
    else
    {
        f = static_cast<float>(d);
        printFloatValue(f);
    }

    printDoubleValue(d);
}

void ScalarConverter::printCharValue(char c)
{
    if (!std::isprint(static_cast<unsigned char>(c)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << c << "'" << std::endl;
}

void ScalarConverter::printCharFromInt(int value, char c)
{
    if (value < 0 || value > 127)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }

    if (!std::isprint(static_cast<unsigned char>(c)))
    {
        std::cout << "char: Non displayable" << std::endl;
        return;
    }

    std::cout << "char: '" << c << "'" << std::endl;
}

void ScalarConverter::printIntValue(int value)
{
    std::cout << "int: " << value << std::endl;
}

void ScalarConverter::printFloatValue(float value)
{
    std::cout << "float: ";

    if (value == std::floor(value))
        std::cout << std::fixed << std::setprecision(1) << value;
    else
        std::cout << std::setprecision(
            std::numeric_limits<float>::digits10) << value;

    std::cout << "f" << std::endl;
}

void ScalarConverter::printDoubleValue(double value)
{
    std::cout << "double: ";

    if (value == std::floor(value))
        std::cout << std::fixed << std::setprecision(1) << value;
    else
        std::cout << std::setprecision(
            std::numeric_limits<double>::digits10) << value;

    std::cout << std::endl;
}

void ScalarConverter::printPseudoLiteral(const std::string &literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

void ScalarConverter::printAllImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}