#pragma once
#include <string>
#include <vector>
#include <iostream>
#include<iomanip>
#include"error_Handling.h"
using namespace std;
class material
{
    // ------------------------ Material Class ------------------------ //
    
    /*
    ***	 material Class is responsible for all properties of material and find sepcific material or add or showing the materials exist recently	*** 
	*/
private :
    string material_type;
    float yield_strength;
    float density;
    public:
    ///     Set Functions     ///
    void setMaterialType(string type)
    { material_type = type; }
    void setYieldStrength(float strength)
    { yield_strength = strength; }
    void setDensity(float d) 
    { density = d; }

    ///     Get Functions     ///
    string getMaterialType()
    { return material_type; }
    float getYieldStrength() 
    { return yield_strength; }
    float getDensity() 
    { return density; }

	static vector < vector<string>> materials;
    
    static vector<material> from_string_to_materials() {
        ///     function converts the data base vector<vector<string>> => vector<mtaerial> to ease using the data   ///
        vector<material> all_material;
        for (vector<string>& row : materials)
            {
            if (row.size() == 3) 
            {
                material m;
                //m.material_type = row[0];
                m.setMaterialType(row[0]);
                m.setYieldStrength(stof(row[1]));
                m.setDensity(stof(row[2]));
                //m.yield_strength = row[1];
               // m.density = row[2];
                all_material.push_back(m);
            }
        }
        return all_material;  // it will return a vector of the class "material"
    }

    static vector<vector<string>> from_materials_to_string(vector<material> clsmaterial)
    {
        ///     function converts vector<mtaerial> => the data base vector<vector<string>> to save the changes in the data   ///

        materials  = {};
        for (material& m : clsmaterial)
            materials.push_back({ m.getMaterialType(), to_string(m.getYieldStrength()), to_string(m.getDensity()) });

        return materials;// it will return string vector again // I still dont know why you want vector of string to be repeated    ///
    }

    static void material_list() 
    {
        ///     function shows all the materials exist in data in the table /// 
            vector<material> materialList = from_string_to_materials();

    // Table Header
    cout << "\n";
    cout << "+----------------------+----------------------+----------------------+\n";
    cout << "| " << left << setw(21) << "Material"
        << "| " << setw(21) << "Yield Strength (MPa)"
        << "| " << setw(21) << "Density (g/cm³)" << " |\n";
    cout << "+----------------------+----------------------+----------------------+\n";

    // Table Rows
    for (int i = 0; i < materialList.size(); i++) {
        string name_with_index = to_string(i + 1) + ". " + materialList[i].getMaterialType();
        cout << "| " << left << setw(21) << name_with_index
            << "| " << setw(21) << materialList[i].getYieldStrength()
            << "| " << setw(21) << materialList[i].getDensity() << "|\n";
        }
        cout << "+----------------------+----------------------+----------------------+\n";

        }

    static material Find_Material(int  choice) 
    {
        /// function get a specific magerial in the data according to the user choice   /// 
        vector<material> materialList =  from_string_to_materials();
        return materialList[choice - 1];
    }

    static void add_Material()
        {
        ///     function makes the user can add material he want to the data    ///
            vector <material> material_List = from_string_to_materials();
            material mat1 ;
            int number = Input_Handling::get_validated_input<int>("\n Do you want to add Material ?  Yes[1] or No[0] \n",0,1);
            while (number == 1)
            {
                
                mat1.material_type = Input_Handling::Reads_tring("Enter Material Name: ");
                mat1.setDensity( Input_Handling::get_validated_input<float>("Enter Density: ",0.00016f, 22.59f) );
                mat1.setYieldStrength(Input_Handling::get_validated_input<float>("Enter Strength: ",1,6000));
                material_List.push_back(mat1);
                from_materials_to_string(material_List);
                material_list();
                number = Input_Handling::get_validated_input<int>("\n Do you want to add Material ?  Yes[1] or No[0] \n",0,1);
                if (number == 0)
                    continue;
            }
        }
    static void modify_added_materials()
    {
        /// Function to modify only added (non-standard) materials ///
        vector<material> material_List = from_string_to_materials();
        if (material_List.size() <= 9)
        {
            cout << "\nNo added materials available to modify.\n";
            return;
        }
        int number = Input_Handling::get_validated_input<int>("\n Do you want to  Modify Material ?  Yes[1] or No[0] \n",0,1);
        while (number == 1)
            {
        cout << "\nAdded Materials:\n";
        for (size_t i = 9; i < material_List.size(); ++i)
        {
            cout << i+1 << " - " << material_List[i].material_type << "\n";
        }
    
        int index = Input_Handling::get_validated_input<int>("\nEnter the index of the material you want to modify: ", 9, material_List.size());
    
        // Update fields
        cout << "Modifying: " << material_List[index-1].material_type << "\n";
        material_List[index-1].material_type = Input_Handling::Reads_tring("Enter New Material Name: ");
        material_List[index-1].setDensity(Input_Handling::get_validated_input<float>("Enter new density: ", 0.00016f, 22.59f)
        );
    
        material_List[index-1].setYieldStrength(Input_Handling::get_validated_input<float>("Enter new yield strength: ",1,6000)
        );
    
        // Save updated list
        from_materials_to_string(material_List);
        cout << "Material updated successfully.\n";
    
        // Optional: display updated list
        material_list();
        number = Input_Handling::get_validated_input<int>("\n Do you want to Modify Material ?  Yes[1] or No[0] \n",0,1);
        if (number == 0)
        continue;
    }
    }
};
