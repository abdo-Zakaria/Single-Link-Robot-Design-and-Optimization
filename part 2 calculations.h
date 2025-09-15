#pragma once
#include "inputs_calc.h"
#include "Motors.h"
#include "Gears.h"
#include "part 1 calculations.h"
#include"error_Handling.h"
#include <vector>
#include <string>
#include <iostream>
            using namespace std;

class part_optimizer
{
/*
			***	 part_optimizer Class is responsible for getting the best combinations for the Robot link and sorting it from lower cost to higher cost 	***
*/
    public:

    static vector<string> calculate(inputs_calc input , part_1_calculations part1)
    {
        ///     calculate function result is a vector of best combinations for the user 's data ///
            vector<string> valid_combinations;
            valid_combinations.clear();
            double T_required = part_1_calculations::bending_moment(input, part1);
            float W_required = input.get_w();
            vector<Motor> motors = Motor::from_string_to_motors();
            vector<Gear> gears = Gear::from_string_to_gears();

            for (Motor& m : motors) {
                float Tmotor = (m.getTorque());
                float Wmotor = (m.getRot_Speed());
                for (Gear& g : gears) {

                    float ratio = (g.getRatio());
                    float eff = (g.getEfficiency());
                    float T_output = Tmotor * ratio * eff;
                    float W_output = Wmotor / ratio;

                    if (T_output >= T_required && W_output >= W_required)
                    {
                        string combo = m.getName() + "," + g.getName();
                        valid_combinations.push_back(combo);
                    }
                }
            }
            return valid_combinations;
        }
    static float get_total_mass(const string& m_name, const string& g_name, vector<Motor>& motors, vector<Gear>& gears) {
            /// this function calculate the total wieght of the combination     ///
                Motor motor = Motor::Find_Motor(m_name);
                Gear gear   = Gear::Find_Gear(g_name);
                float total_motor = (motor.getWeight());
                float total_gear = (gear.getWeight());
                return total_motor + total_gear;
            }
    static float get_total_diameter(const string& m_name, const string& g_name, vector<Motor>& motors, vector<Gear>& gears) {
                /// this function calculate the total Diameters of the combination     ///
                Motor motor = Motor::Find_Motor(m_name);
                Gear gear   = Gear::Find_Gear(g_name);
                float total_motor = (motor.getDiameter());
                float total_gear = (gear.getDiameter());
                return total_motor + total_gear;
            }
    static float get_total_cost(const string& m_name, const string& g_name, vector<Motor>& motors, vector<Gear>& gears, const string& priority) {
            /// this function calculate the total cost of the combination     ///
            Motor motor = Motor::Find_Motor(m_name);
            Gear gear   = Gear::Find_Gear(g_name);
            float motor_mass (motor.getWeight());
            float gear_mass =(gear.getWeight());
            float motor_dia =(motor.getDiameter());
            float gear_dia = (gear.getDiameter());
            if (priority == "mass") {
                return motor_mass + gear_mass;
            }
            else if (priority == "diameter") {
                return motor_dia + gear_dia;
            }
            else if (priority == "both") {
                return (motor_mass + gear_mass) + ((motor_dia + gear_dia) / 100);
            }
            return 0;
        }
    static void sort_combinations(const string& priority, vector<Motor>& motors, vector<Gear>& gears , vector<string>& valid_combinations) {
                /// this function sort the best combinations for Robot link from lower cost to higher     ///
                for (int i = 0; i < valid_combinations.size() - 1; i++) {
                    for (int j = 0; j < valid_combinations.size() - i - 1; j++) {
                        string m1 = valid_combinations[j].substr(0, valid_combinations[j].find(","));
                        string g1 = valid_combinations[j].substr(valid_combinations[j].find(",") + 1);
                        string m2 = valid_combinations[j + 1].substr(0, valid_combinations[j + 1].find(","));
                        string g2 = valid_combinations[j + 1].substr(valid_combinations[j + 1].find(",") + 1);

                        float v1 = get_total_cost(m1, g1, motors, gears, priority);
                        float v2 = get_total_cost(m2, g2, motors, gears, priority);

                        if (v1 > v2)
                            swap(valid_combinations[j], valid_combinations[j + 1]);
                    }
                }
            }
    static void print_results(vector<string> valid_combinations) {
                /// this function prints the arragnment of the combinations     ///
                if (valid_combinations.empty()) {
                    cout << "No valid motor-gear combinations found.\n";
                    return;
                }

                vector<Motor> motors = Motor::from_string_to_motors();
                vector<Gear> gears = Gear::from_string_to_gears();

                    cout << "\n the all valid combinations :\n";
                    cout << "+----------------------+----------------------+\n";
                    cout << "| " << left << setw(21) << "Motor"
                        << "| " << setw(21) << "Gear";
                    cout << "|\n+----------------------+----------------------+\n";
                    int j=0;
                for (const string& combo : valid_combinations) {
                    string motor = combo.substr(0, combo.find(","));
                    string gear = combo.substr(combo.find(",") + 1);

                    string name_with_index = to_string(j + 1) + ". " + motor;
                        cout << "| " << left << setw(21) << name_with_index
                            << "| " << setw(21) << gear << "|\n";
                    j++;
                    cout << "+-----------------------+---------------------+\n";
                }


                string priority = Input_Handling::Read_specific("Write which priority has to be minimized of the following  'mass', 'diameter', 'both' \n","mass","diameter","both");
                sort_combinations(priority, motors, gears , valid_combinations);

                cout << "\n the Sorted  Combinations by " << priority <<" option :\n";
                // cout << "\n";
                    cout << "+----------------------+----------------------+----------------------+\n";
                    cout << "| " << left << setw(21) << "Motor"
                        << "| " << setw(21) << "Gear"
                        << "| " << setw(21) << "Cost" << "|\n";
                    cout << "+----------------------+----------------------+----------------------+\n";
                    j = 0;
                for (const string& combo : valid_combinations) {
                    string motor = combo.substr(0, combo.find(","));
                    string gear = combo.substr(combo.find(",") + 1);

                    float cost = get_total_cost(motor, gear, motors, gears, priority);
                    string name_with_index = to_string(j + 1) + ". " + motor;
                        cout << "| " << left << setw(21) << name_with_index
                            << "| " << setw(21) << gear
                            << "| " << setw(21) << cost << "|\n";

                    cout << "+-----------------------+-----------------------+--------------------+\n";
                    j++;
                    // cout << "Motor: " << motor << " | Gear: " << gear << " | Cost: " << cost << endl;
                }
                cout << "\n\n+-----------------------+-----------------------+--------------------+\n";
                cout <<"the best Pair Combinations according to your priority : \n";
                string motor = valid_combinations[0].substr(0, valid_combinations[0].find(","));
                string gear = valid_combinations[0].substr(valid_combinations[0].find(",") + 1);
                float cost = get_total_cost(motor, gear, motors, gears, priority);
                string name_with_index = to_string(j + 1) + ". " + motor;
                            cout << "| " << left << setw(21) << name_with_index
                            << "| " << setw(21) << gear
                            << "| " << setw(21) << cost << "|\n";;
                        cout << "\n\n+-----------------------+-----------------------+--------------------+\n";
            }

};
