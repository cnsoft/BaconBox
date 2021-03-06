/**
 * @file
 * @ingroup Helper
 */

#ifndef BB_PARSER_H
#define BB_PARSER_H

#define BB_FULL_PRECISION -1

#include <string>
#include "BaconBox/Console.h"
#include <vector>
namespace BaconBox {
	/**
	 * This helper class is used to parse number to/from string
	 * @ingroup Helper
	 */
	class Parser {
	public:
		static bool isNumeric(const std::string& str);
		static bool isInteger(const std::string& str);
		/**
		 * Parse the given string to an integer Ex: "123" would give 123.
		 */
		static int stringToInt(const std::string& str);

		static double stringToDouble(const std::string& str);

		
		static bool stringToBool(const std::string& str);
		/**
		 * Create a string from the given integer. Ex: 123 would give "123".
		 */
		static std::string intToString(const int anInt);

		/**
		 * Create a string from the given float. Ex: 12.3 would give "12.3".
		 */
		static std::string doubleToString(const double aFloat, int precision = BB_FULL_PRECISION);

        template <typename T> static void parseStringArray(const std::string & parsedString,  std::vector<T> & outputVector, char delimiter = ','){
		    std::string tempString;
		    for(std::string::const_iterator i  = parsedString.begin(); i != parsedString.end(); i++){
                if(*i != delimiter){
                    tempString += *i;
                }
                else{
                    outputVector.push_back(stringToDouble(tempString));
                    tempString.clear();
                }
		    }
		    outputVector.push_back(stringToDouble(tempString));
            tempString.clear();
		}
	};
}

#endif
