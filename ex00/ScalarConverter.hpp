#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter& operator=(const ScalarConverter &other);
    ~ScalarConverter();

    static bool isCharLiteral(const std::string &literal);
    static bool isIntLiteral(const std::string &literal);
    static bool isFloatLiteral(const std::string &literal);
    static bool isDoubleLiteral(const std::string &literal);
    static bool isPseudoLiteral(const std::string &literal);

    static void convertChar(const std::string &literal);
    static void convertInt(const std::string &literal);
    static void convertFloat(const std::string &literal);
    static void convertDouble(const std::string &literal);

    static void printCharValue(char c);
    static void printCharFromInt(int value, char c);
    static void printIntValue(int value);
    static void printFloatValue(float value);
    static void printDoubleValue(double value);

    static void printPseudoLiteral(const std::string &literal);
    static void printAllImpossible();

public:
    static void convert(const std::string &literal);
};

#endif