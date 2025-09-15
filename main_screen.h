// #pragma once
#include <vector>
#include <string>
#include <iostream>
#include "material.h"
#include "inputs_calc.h"
#include"part 1 calculations.h"
#include"part 2 calculations.h"
#include"error_Handling.h"
using namespace std;
class main_screen
{
	/*
			***	 main screen class is responsible for showing main screen for user and perform the project	*** 
	*/
private:

	static void perform_main_screen() 
	{
		///		this function is responsible for applying the project parts		///
		cout << "\n\n---------------------------------------------------------------------------\n";
		cout << "               	 ++++ Part One :  Optimal Dimensions  ++++\n";
		cout << "---------------------------------------------------------------------------\n";
		inputs_calc input;
        part_1_calculations clac1 ;
		inputs_calc::get_inputs(input);
		part_1_calculations::mass_link(input);
		show_part1_results(input, clac1);
		part_1_calculations::GetAccurateDimension(input, clac1);
		show_part1_optimized_results(input,clac1);
		part_optimizer::calculate(input , clac1 );
		int continueWithSameDimension = Input_Handling::get_validated_input<int>("\nDo you want to enter new Dimensions ? yes[1] or no[0]\n",0,1);		
        if (continueWithSameDimension)
        {
            inputs_calc::get_inputs(input);
        }
		cout << "\n\n---------------------------------------------------------------------------\n";
		cout << "               	 ++++ Part Two : Motor And Gearbox Selection  ++++\n";
		cout << "---------------------------------------------------------------------------\n";
		Motor::motor_list();
		Motor::add_motor();
		Motor::modify_added_Motor();
		Gear::gear_list();
		Gear::add_gear();
		Gear::modify_added_Gears();
		part_optimizer::print_results(part_optimizer::calculate(input,clac1));
	}

	static void show_part1_results(inputs_calc input, part_1_calculations clac1)
		{
		///		function show the user all the data he entered to confirm he entered the data he want (before getting the optimal dimension)	///
        cout << "---------------------------------------------------------------------------\n";
		cout << "Material Type       : " << input.get_material_type() << "\n";
		cout << "Cross Section       : " << input.get_cross_section() << "\n";
		cout << "Link Length (mm)    : " << input.get_link_length() << "\n";
		cout << "Payload Mass (kg)   : " << input.get_payload_mass() << "\n";
		cout << "Max Angular Acc (rad/s^2): " << input.get_max_angular_acc() << "\n";//rad/s*2
		cout << "Rotational Speed (rpm): " << input.get_w() << "\n";
		cout << "Link Mass (kg)      : " << input.get_link_mass() << "\n";
		if(input.get_cross_section()=="Rectangle")
		{
            cout << "Link height (mm)      : " << input.get_hight() << "\n";
			cout << "Link width (mm)      : " << input.get_width() << "\n";
		}
        if(input.get_cross_section()=="Circle") cout << "Link radius (mm)      : " << input.get_radius() << "\n";
		cout << "density (gm/cm^3)  : " << input.get_denisty() << "\n";
		cout << "strength (MPa)   	: " << input.get_strength() << "\n";
		}

    static void show_part1_optimized_results(inputs_calc input, part_1_calculations clac1)
		{
		///		function show the user optimal dimensions for the data he entered	///
		cout << "---------------------------------------------------------------------------\n";
		cout<<"the optimized dimensions :"<<endl;
		cout<<"Calc , Strength (Mpa)"<<clac1.getCalculatedStress()<<endl;
		cout << "Link Mass (kg)      : " << input.get_link_mass() << "\n";
				if(input.get_cross_section()=="Rectangle")
		{
            cout << "Link height (mm)      : " << input.get_hight() << "\n";
			cout << "Link width (mm)      : " << input.get_width() << "\n";
		}
        if(input.get_cross_section()=="Circle") cout << "Link radius (mm)      : " << input.get_radius() << "\n";
		}
public: 
	static void show_main_screen() {
		///		this function is responsible for showing the main screen and working the programm and appears only in the main file		///
		cout << "---------------------------------------------------------------------------\n";
		cout << "                Single-Link Robot Design and Optimization \n";
		cout << "---------------------------------------------------------------------------\n";
		perform_main_screen();
	}
};

