#pragma once
#include <string>
#include <vector>
#include <iostream>
#include<iomanip>
#include"error_Handling.h"
using namespace std;

// ------------------------ Motor Class ------------------------ //


class Motor {
    /*
    ***	 Motor Class is responsible for all properties of Motor and find sepcific Motor or add or showing the Motors exist recently	*** 
    */
    private : 
    string name; float  torque, Rot_Speed, efficiency, diameter, weight;
    public:
            ///     Set Functions     ///
        void setName(string n) 
        { name = n; }
        void setTorque(float t) 
        { torque = t; }
        void setRot_Speed(float r) 
        { Rot_Speed = r; }
        void setEfficiency(float e) 
        { efficiency = e; }
        void setDiameter(float d) 
        { diameter = d; }
        void setWeight(float w) 
        { weight = w; }

        ///     Get Functions     ///
        string getName()  


        { return name; }
        float getTorque()  
        { return torque; }
        float getRot_Speed()  
        { return Rot_Speed; }
        float getEfficiency()  
        { return efficiency; }
        float getDiameter()  
        { return diameter; }
        float getWeight()  
        { return weight; }

    static vector<vector<string>> motors;


    static vector<Motor> from_string_to_motors() 
    {
        ///     function converts the data base vector<vector<string>> => vector<Motor> to ease using the data   ///


        vector<Motor> all_motors;
        for (vector<string>& row : motors) {
            if (row.size() == 6) {
                Motor m;
                m.setName       (row[0]);
                m.setTorque     (stof(row[1]));
                m.setRot_Speed  (stof(row[2]));
                m.setEfficiency (stof(row[3]));
                m.setDiameter   (stof(row[4]));
                m.setWeight     (stof(row[5]));
                all_motors.push_back(m);
            }
        }
        return all_motors;
    }

    static vector<vector<string>> from_motors_to_string(vector<Motor> clsmotors)
    {
        ///     function converts vector<Motor> => the data base vector<vector<string>> to save the changes in the data   ///
        motors={};
        for (Motor& m : clsmotors) {
            motors.push_back({ m.getName(),to_string(m.getTorque()) ,to_string(m.getRot_Speed()),
                to_string(m.getEfficiency()),to_string(m.getDiameter()) , to_string(m.getWeight()) });
        }
        return motors;
    }

    static void motor_list() 
    {
            ///     function shows all the Motors exist in data in the table /// 
        vector<Motor> motorList = from_string_to_motors();

        cout << "\n";
        cout << "+---------------------+-----------------+----------+---------------+---------------+-------------+\n";
        cout << "| " << left << setw(20) << "Motor Name" // wider to fit number + name
            << "| " << setw(16) << "Torque (N.mm)"
            << "| " << setw(9) << "W (rpm)"
            << "| " << setw(14) << "Efficiency"
            << "| " << setw(14) << "Diameter (mm)"
            << "| " << setw(11) << "Weight (gm)" << " |\n";
        cout << "+---------------------+-----------------+----------+---------------+---------------+-------------+\n";

        for (int i = 0; i < motorList.size(); i++) {
            string name_with_index = to_string(i + 1) + ".  " + motorList[i].getName();
            cout << "| " << left << setw(20) << name_with_index
            << "| " << setw(16) <<  motorList[i].getTorque()
            << "| " << setw(9) <<  motorList[i].getRot_Speed()
            << "| " << setw(14) << motorList[i].getEfficiency()
            << "| " << setw(14) <<  motorList[i].getDiameter()
            << "| " << setw(11) <<  motorList[i].getWeight() << " |\n";
        }
        cout << "+---------------------+-----------------+----------+---------------+---------------+-------------+\n";
    }
    
    static Motor Find_Motor(string Motor_Name)
    {
                    /// function get a specific Motor in the data according to the user choice   ///
        vector<Motor> motorList =  from_string_to_motors();
        Motor motor ;
        for (int i = 0; i < motorList.size(); i++)
        {
            if (motorList[i].name == Motor_Name)
            {
                motor =  motorList[i];
            }
        }
        return motor;
    }
    static void add_motor()
    {
        ///     function makes the user can add Motor he want to the data    ///
        vector <Motor> Motor_list = from_string_to_motors();
            Motor mot1 ;
            int number            =    Input_Handling::get_validated_input<int>("\n Do you want to add Motor ?  Yes[1] or No[0] \n",0,1);
            while (number == 1)
            {
                mot1.setName        (Input_Handling::Reads_tring("Enter motor name: "));
                mot1.setTorque      (Input_Handling::get_validated_input<float>("Enter torque (N.mm): ",0.0001f,5000));    
                mot1.setDiameter    (Input_Handling::get_validated_input<float>("Enter Diameter (mm): ",0.0001f,200));
                mot1.setRot_Speed   (Input_Handling::get_validated_input<float>("Enter speed (rpm): ",0.0001f,50000)) ;
                mot1.setEfficiency  (Input_Handling::get_validated_input<float>("Enter Efficiency: ",0.0001f,300));
                mot1.setWeight      (Input_Handling::get_validated_input<float>("Enter Weight (gm): ",0.0001f,5000));
                Motor_list.push_back(mot1);
                from_motors_to_string(Motor_list);
                motor_list();
                number            =    Input_Handling::get_validated_input<int>("\n Do you want to add Motor ?  Yes[1] or No[0] \n",0,1);
                if (number == 0)
                    continue;
        }
    }
    static void modify_added_Motor()
    {
        /// Function to modify only added (non-standard) materials ///
        vector<Motor> Motor_List = from_string_to_motors();
    
        if (Motor_List.size() <= 10)
        {
            cout << "\nNo added materials available to modify.\n";
            return;
        }
            int number = Input_Handling::get_validated_input<int>("\n Do you want to  Modify Motor ?  Yes[1] or No[0] \n",0,1);
            while (number == 1)
            {
        cout << "\nAdded Materials:\n";
        for (size_t i = 10; i < Motor_List.size(); ++i)
        {
            cout << i+1 << " - " << Motor_List[i].getName() << "\n";
        }
        int index = Input_Handling::get_validated_input<int>("\nEnter the index of the material you want to modify: ", 10, Motor_List.size() );
    
        // Update fields
        cout << "Modifying: " << Motor_List[index-1].getName() << "\n";
        Motor_List[index-1].setName        (Input_Handling::Reads_tring("Enter motor name: "));
        Motor_List[index-1].setTorque      (Input_Handling::get_validated_input<float>("Enter torque (N.mm): ",0.0001f,5000));    
        Motor_List[index-1].setDiameter    (Input_Handling::get_validated_input<float>("Enter Diameter (mm): ",0.0001f,200));
        Motor_List[index-1].setRot_Speed   (Input_Handling::get_validated_input<float>("Enter speed (rpm): ",0.0001f,50000)) ;
        Motor_List[index-1].setEfficiency  (Input_Handling::get_validated_input<float>("Enter Efficiency: ",0.0001f,300));
        Motor_List[index-1].setWeight      (Input_Handling::get_validated_input<float>("Enter Weight (gm): ",0.0001f,5000));
    
        // Save updated list
        from_motors_to_string(Motor_List);
        cout << "Material updated successfully.\n";
    
        // Optional: display updated list
        motor_list();
        number = Input_Handling::get_validated_input<int>("\n Do you want to Modify Motor ?  Yes[1] or No[0] \n",0,1);
        if (number == 0)
        continue;
    }
    }
};
