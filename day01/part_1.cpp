#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

int calculateCalibValue(string calibLine) {
    string twoDigitNumber = "";
    bool firstDigitFound = false;
    bool lastDigitFound = false;
    char firstDigit;
    char lastDigit;

    // iterate over string forwards and backwards simultaneously
    for (int i = 0; i < calibLine.length(); i++) {
        if (!firstDigitFound) {
            if (isdigit(calibLine[i])) {
                firstDigitFound = true;
                firstDigit = calibLine[i];
            }
        }
        if (!lastDigitFound) {
            if (isdigit(calibLine[calibLine.length() - (i + 1)])) {
                lastDigitFound = true;
                lastDigit = calibLine[calibLine.length() - (i + 1)];
            }
        }
        if (firstDigitFound && lastDigitFound) {
            twoDigitNumber = string(1, firstDigit) + lastDigit;
            break;
        }
    }
    return stoi(twoDigitNumber);
}


int main() {
    ifstream calibrationFile("calibration_file.txt");

    string calibLine;

    int sum = 0;

    while (getline(calibrationFile, calibLine)) {
        sum += calculateCalibValue(calibLine);
    }

    cout << sum << endl;
    

    return 0;
}
