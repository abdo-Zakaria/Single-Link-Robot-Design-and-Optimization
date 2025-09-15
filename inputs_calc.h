#pragma once
#include <string>
#include <vector>
#include "material.h"
#include"error_Handling.h"
#include <iostream>
using namespace std;
class inputs_calc
{
	/*
			***	 inputs Class is responsible for all the data user will enter	*** 
	*/
private:
	string material_type;
	float yield_strength;
	float density;
	string cross_section;
	float link_length;
	float payload_mass;
	float max_angular_acc;
	float link_mass;
	float w;                    //rotating speed of motor
	float width;
	float radius;
	float height;
public:	


	///		Set Functions is responsible to set all attributes in this class	///
	void set_payload_mass(float py) {
		payload_mass = py;
	}
	void set_max_angular_acc(float acc) {
		max_angular_acc = acc;
	}
	void set_cross_section(string cross) {
		cross_section = cross;
	}
	void set_w(float omega) {
		w = omega;
	}
	void set_link_length(float linklength) {
		link_length = linklength;
	}
	void set_material_type(string mat) {
		material_type = mat;
	}
	void set_width(float wd) {
		width = wd;
	}
	void set_hight(float ht) {
		height = ht;
	}
	void set_radius(float r) {
		radius = r;
	}
	void set_link_mass(double mass){
		link_mass= mass;
	}
		

	///		Get Functions is responsible to get all attributes in this class	///
	float get_strength() {
	return yield_strength;
}
	float get_denisty() {
	return density;
}
	float get_radius() {
		return radius;
	}
	float get_hight() {
		return height;
	}
	float get_width() {
		return width;
	}
	float get_link_mass() {
		return link_mass;
	}
	float get_payload_mass() {
		return payload_mass;
	}
	float get_max_angular_acc() {
		return max_angular_acc;
	}
	float get_w() {
		return w;
	}
	float get_link_length() {
		return link_length;
	}
	string get_cross_section() {
		return cross_section;
	}
	string get_material_type() {
		return material_type;
	}

	///		get_inputs Function is responsible to ask user to enter all the inputs needed to the single robot link	///
	static void get_inputs(inputs_calc & input) {
		material::material_list();
		material::add_Material();
		material::modify_added_materials();
		int Material_Choice 		=  Input_Handling::get_validated_input<int>("Select a material by number:\n",1,material::from_string_to_materials().size());
		
		material selected 			=  material::Find_Material(Material_Choice);
		input.set_material_type(selected.getMaterialType());
		input.yield_strength = (selected.getYieldStrength());
		input.density = (selected.getDensity());

		int cross 					=  Input_Handling::get_validated_input<int>("Enter cross section type: 1.Rectangle 2.Circle \n (enter number 1 or 2 )\n",1,2);		
		
		if (cross == 1) {
			input.cross_section = "Rectangle";
			input.set_hight			(Input_Handling::get_validated_input<float>("Enter the Link`s height (in mm)\n",0.001f,1000));
			input.set_width			(Input_Handling::get_validated_input<float>("Enter the Link`s width (in mm)\n",0.001f,1000));
		}

		else if (cross == 2) {
			input.cross_section 	= 	"Circle";
			input.set_radius		(Input_Handling::get_validated_input<float>("Enter the Link`s radius (in mm)\n",0.001f,1000)) ;
		}

		input.set_payload_mass		(Input_Handling::get_validated_input<float>("Enter payload mass (in kg)\n",0.0001f,500));
		input.set_max_angular_acc	(Input_Handling::get_validated_input<float>("Enter max angular acceleration (in m/sec*2)\n",0.0001,50000));
		input.set_link_length		(Input_Handling::get_validated_input<float>("Enter the link `s length (in mm)\n",0.0001f,50000));
		input.set_w					(Input_Handling::get_validated_input<float>("Enter the rotational speed (in rpm)\n",1,50000));
	}

};
