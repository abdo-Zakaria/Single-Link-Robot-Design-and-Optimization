#include<iostream>
#include <vector>
#include <string>
#include "Gears.h"
#include"Motors.h"
#include "material.h"
#include "inputs_calc.h"
#include "main_screen.h"
using namespace std;
    /*
			                                            ***	 Single Robot Link Project	*** 
	*/

/*
			***	 the main file will project work in and contain also the database  needed to get the best dimension and best combination for single robot link	*** 
*/
vector<vector<string>> Gear::gears = {
    {"GS 12", "12", "10:1", "90%", "10"},
    {"GS 14", "14", "20:1", "88%", "12"},
    {"GS 22", "22", "30:1", "85%", "20"},
    {"GS 30", "30", "60:1", "66%", "45"},
    {"GS 36", "36", "80:1", "65%", "50"},
    {"GS 52", "52", "100:1", "62%", "80"},
    {"GP 32", "32", "200:1", "64%", "200"},
    {"GP 42", "42", "342:1", "64%", "560"},
    {"GP 52", "52", "343:1", "72%", "460"},
    {"GP 62", "62", "499:1", "73%", "800"}
};
vector<vector<string>> Motor::motors = {
    {"ECX 8 ", "0.4", "50000", "80%", "8", "22"},
    {"ECX 16", "3.2", "30000", "85%", "16", "35"},
    {"ECX 22", "15.5", "12100", "87%", "22", "71"},
    {"ECX 32", "94.4", "10600", "81%", "32", "26"},
    {"EC 45 ", "200", "8000 ", "90%", "45", "110"},
    {"EC 60 ", "400", "6000 ", "91%", "60", "150"},
    {"EC 90 ", "1000", "4000 ", "92%", "90", "200"},
    {"A-max 12", "0.16", "15000", "70%", "12", "16"},
    {"A-max 19", "4.5", "11000", "78%", "19", "34"},
    {"A-max 26", "8.1", "9000", "80%", "26", "42"}
};
vector<vector<string>> material::materials={
 {"Cast iron",       "130", "7.3"},
    {"Copper nickel",   "130", "8.94"},
    {"Brass",           "200", "8.73"},
    {"Aluminum",        "241", "2.7"},
    {"Steel",           "247", "7.58"},
    {"Acrylic",         "72",  "1.16"},
    {"Copper",          "70",  "8.92"},
    {"Stainless steel", "275", "7.86"},
    {"Tungsten",        "941", "19.25"}
};

int main()
{
    main_screen::show_main_screen();
    return 0;
}
