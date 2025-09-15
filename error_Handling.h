#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

class Input_Handling
{
    /*
			***	 Input_Handling Class is responsible for handling all the user inputs if he enter wrong data    *** 
    */
public:
    static constexpr float MAX_DIMENSION = 10000.0f; // mm
    static constexpr float MAX_MASS = 10000.0f;      // kg
    static constexpr float MAX_ACCEL = 5000.0f;      // m/s^2
    static constexpr float MAX_RPM = 100000.0f;      // rpm

    

    //    Template input validator for different types     //
    template <typename T>
    static T get_validated_input( string prompt, T min_val = 0.0001f, T max_val = MAX_DIMENSION) {
        T value;
        while (true) {
            cout << prompt;
            cin >> value;

            if (cin.fail() || value < min_val || value > max_val) {
                cout << "Invalid input. Please enter a value between "
                     << min_val << " and " << max_val << ".\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        return value;
    }

    static string Read_specific(string message ,string str1="",string str2="",string str3="") {
    string input="";
    do 
    {
        cout <<message;
        getline(cin, input);
        //if (str1=="" || str2=="" || str3=="")  continue;
        if( (input == str1 && str1 != "") || (input == str2 && str2 != "") || (input == str3 && str3 != "") ) break;
    } while (true);
    return input;
    }
    static string Reads_tring(string question) {
    cout << question;
    string ans;
    // Get input line
    getline(cin, ans);

    return ans;
    }
};