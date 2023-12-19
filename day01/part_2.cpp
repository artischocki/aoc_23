#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

string digitStrings[10] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int checkPartialStringForDigitString(string partialString) {
    int currentDigit = 0;
    for (string digitString : digitStrings) {
        bool stringsAreIdentical = true;
        // only iterate over the necessary (last) number of chars
        for (int i = 0; i < digitString.length(); i++) {

            if (partialString[i + partialString.length() -
                            digitString.length()] != digitString[i]) {
            stringsAreIdentical = false;
            break;
            }
        }
        if (stringsAreIdentical) {
            return currentDigit;
        }
        currentDigit++;
    }
    return -1;
}

int forwardCheck(string calibLine) {
    int firstDigit;
    for (int i = 0; i < calibLine.length(); i++) {
        // first check if its a digit (0-9)
        if (isdigit(calibLine[i])) {
            firstDigit = calibLine[i] - '0';
            break;
        }
        // then check if there is a digit in the string we have collected
        string partialString = calibLine.substr(0, i+1);
        firstDigit = checkPartialStringForDigitString(partialString);
        if (firstDigit != -1) {
            break;
        }
    }
    return firstDigit;
}


int backwardCheck(string calibLine) {
    int lastDigit;
    for (int i = calibLine.length() - 1; i >= 0; i--) {
        // first check if its a digit (0-9)
        if (isdigit(calibLine[i])) {
            lastDigit = calibLine[i] - '0';
            break;
        }
        // then check if there is a digit in the string we have collected
        string partialString = calibLine.substr(0, i+1);
        lastDigit = checkPartialStringForDigitString(partialString);
        if (lastDigit != -1) {
            break;
        }
    }
    return lastDigit;
}

int calculateCalibValue(string calibLine) {
    int firstDigit = forwardCheck(calibLine);
    int lastDigit = backwardCheck(calibLine);

    if (firstDigit == -1 | lastDigit == -1) {
        throw runtime_error("Something went wrong");
    }

    char firstDigitChar = '0' + firstDigit;
    char lastDigitChar = '0' + lastDigit;

    string calibNumberString;
    calibNumberString += firstDigitChar;
    calibNumberString += lastDigitChar;

    return stoi(calibNumberString);
}

int main () {
    ifstream calibrationFile("calibration_file.txt");

    string calibLine;

    int sum = 0;

    while (getline(calibrationFile, calibLine)) {
        sum += calculateCalibValue(calibLine);
    }

    cout << sum << endl;

    return 0;
}
