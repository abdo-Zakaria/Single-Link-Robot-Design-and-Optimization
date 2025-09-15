#pragma once
#include <string>
#include <vector>
#include<iomanip>
#include <iostream>
#include"error_Handling.h"
using namespace std;
// ------------------------ Gear Class ------------------------ //

class Gear {
    /*
            ***	 Gear Class is responsible for all properties of Gear and find sepcific Gear or add or showing the Gears exist recently	*** 
    */
    private : 
    string name; float diameter, ratio, efficiency, weight;
    public:
        ///     Set Functions     ///
    void setName(string n) 
    { name = n; }
    void setDiameter(float d) 
    { diameter = d; }
    void setRatio(float r) 
    { ratio = r; }
    void setEfficiency(float e)
    { efficiency = e; }
    void setWeight(float w) 
    { weight = w; }

    ///     Get Functions     ///

    string getName()  
    { return name; }
    float getDiameter()  
    { return diameter; }
    float getRatio()  
    { return ratio; }
    float getEfficiency()  
    { return efficiency; }
    float getWeight()  
    { return weight; }

    static vector<vector<string>> gears;

        static vector<Gear> from_string_to_gears()
        {
            ///     function converts the data base vector<vector<string>> => vector<Gear> to ease using the data   ///
            vector<Gear> gears_list;
            for (vector<string>& row : gears) {
                if (row.size() == 5) {
                    Gear g;
                    g.setName((row[0])) ;
                    g.setDiameter(stof(row[1]));
                    g.setRatio(stof(row[2]));
                    g.setEfficiency(stof(row[3]));
                    g.setWeight(stof(row[4]));
                    gears_list.push_back(g);
                }
            }
            return gears_list;
        }
    
        static vector<vector<string>> from_gears_to_string(vector<Gear> clsgears)
        {
            ///     function converts vector<Gear> => the data base vector<vector<string>> to save the changes in the data   ///
            gears={};
            for (Gear& g : clsgears) {
                gears.push_back({ g.getName(), to_string (g.getDiameter()), to_string(g.getRatio()), to_string (g.getEfficiency()), to_string (g.getWeight()) });
            }
            return gears;
        }
    
        static void gear_list()
        {
            ///     function shows all the Gears exist in data in the table /// 
        vector<Gear> gearList = from_string_to_gears();
        cout << "\n";
        cout << "+-------------------+---------------+----------+--------------+-------------+\n";
        cout << "| " << left << setw(18) << "Gear Name"
            << "| " << setw(14) << "Diameter (mm)"
            << "| " << setw(9) << "Ratio"
            << "| " << setw(12) << "Efficiency"
            << "| " << setw(12) << "Weight (gm)" << " |\n";
        cout << "+-------------------+---------------+----------+-------------+--------------+\n";
                
        for (int i = 0; i < gearList.size(); i++) {
            string name_with_index = to_string(i + 1) + ".  " + gearList[i].getName();
            cout << "| " << left << setw(18) << name_with_index
                << "| " << setw(14) << gearList[i].getDiameter()
                << "| " << setw(9) << gearList[i].getRatio()
                << "| " << setw(12) << gearList[i].getEfficiency()
                << "| " << setw(12) << gearList[i].getWeight() << " |\n";
        }
        cout << "+-------------------+---------------+----------+--------------+-------------+\n";
        }
    
        static Gear Find_Gear(string Gear_Name)
        {
            /// function get a specific Gear in the data according to the user choice   /// 
            vector<Gear> GearList =  from_string_to_gears();
            Gear gear ;
            for (int i = 0; i < GearList.size(); i++)
            {
                if (GearList[i].name == Gear_Name)
                {
                    gear =  GearList[i];
                }
            }
            return gear;
        }
    
        static void add_gear()
        {
        ///     function makes the user can add Gear he want to the data    ///
            vector<Gear> Gear_List = from_string_to_gears();
            int number     =        Input_Handling::get_validated_input<int>("\n Do you want to add Gear ?  Yes[1] or No[0] \n",0,1);
            while (number == 1)
            {
                Gear G1;
                G1.setName          (Input_Handling::Reads_tring("Enter Gear Name: "));
                G1.setDiameter      (Input_Handling::get_validated_input<float>("Enter Diameter: ",0.0001f,500)) ;
                G1.setRatio         (Input_Handling::get_validated_input<float>("Enter Ratio: ",0.0001f,1000));
                G1.setEfficiency    (Input_Handling::get_validated_input<float>("Enter Efficiency: ",0.0001f,100));
                G1.setWeight        (Input_Handling::get_validated_input<float>("Enter Weight: ",0.0001f,5000));

                Gear_List.push_back(G1);
                from_gears_to_string(Gear_List);
                Gear::gear_list();
                number   =          Input_Handling::get_validated_input<int>("\n Do you want to add Material ?  Yes[1] or No[0] \n",0,1);
                
                if (number == 0)
                    continue;
            }
        }
    static void modify_added_Gears()
    {
        /// Function to modify only added (non-standard) materials ///
        vector<Gear> Gear_List = from_string_to_gears();
    
        if (Gear_List.size() <= 10)
        {
            cout << "\nNo added materials available to modify.\n";
            return;
        }
        int number = Input_Handling::get_validated_input<int>("\n Do you want to Modify Gear ?  Yes[1] or No[0] \n",0,1);
        while (number == 1)
            {
        cout << "\nAdded Materials:\n";
        for (size_t i = 10; i < Gear_List.size(); ++i)
        {
            cout << i+1 << " - " << Gear_List[i].getName() << "\n";
        }
    
        int index = Input_Handling::get_validated_input<int>("\nEnter the index of the material you want to modify: ", 10, Gear_List.size());
    
        // Update fields
        cout << "Modifying: " << Gear_List[index-1].getName() << "\n";
        Gear_List[index-1].setName          (Input_Handling::Reads_tring("Enter Gear Name: "));
        Gear_List[index-1].setDiameter      (Input_Handling::get_validated_input<float>("Enter Diameter (mm): ",0.0001f,500)) ;
        Gear_List[index-1].setRatio         (Input_Handling::get_validated_input<float>("Enter Ratio: ",0.0001f,1000));
        Gear_List[index-1].setEfficiency    (Input_Handling::get_validated_input<float>("Enter Efficiency: ",0.0001f,100));
        Gear_List[index-1].setWeight        (Input_Handling::get_validated_input<float>("Enter Weight (gm): ",0.0001f,5000));
    
        // Save updated list
        from_gears_to_string(Gear_List);
        cout << "Material updated successfully.\n";
    
        // Optional: display updated list
        gear_list();
        number = Input_Handling::get_validated_input<int>("\n Do you want to Modify Gear ?  Yes[1] or No[0] \n",0,1);
        if (number == 0)
        continue;
    }
    }
    };