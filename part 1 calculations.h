
#pragma once
#include "material.h"
#include "inputs_calc.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include"error_Handling.h"
using namespace std;

class part_1_calculations
{
    /*
			***	 Part one Calculations Class is responsible for all the calcualtions that we need to to get the optimal dimensions for the data user enter    *** 
    */
    private:
    double M;
    double I;
    double Calculated_Stress;
    public:
            ///     Set Functions     ///
    void setM(double m) 
    { M = m; }
    void setI(double i) 
    { I = i; }
    void setCalculatedStress(double stress) 
    { Calculated_Stress = stress; }

            ///     Get Functions     ///
    double getM()  
    { return M; }
    double getI()  
    { return I; }
    double getCalculatedStress()  
    { return Calculated_Stress; }
    

    static void mass_link(inputs_calc& inputs)
    {
                ///     function responsible to get the mass link according to the cross section   ///
        double mass;
        float density = inputs.get_denisty()*1000;// *1000 to make density in kg/m3
        float radi = inputs.get_radius()/1000 ;
        float b = inputs.get_width()/1000;
        float h = inputs.get_hight()/1000;
        float l = inputs.get_link_length()/1000;
        if(inputs.get_cross_section()=="Rectangle"){
            mass= density*b*h*l;
            inputs.set_link_mass(mass);
        }
        if(inputs.get_cross_section()=="Circle"){
            mass= density*(22.0/7)*pow(radi,2)*l;
            inputs.set_link_mass(mass);
        }
    }
    static double bending_moment(inputs_calc& inputs, part_1_calculations& part1)
    {
        ///     function responsible to get Bending Moment   ///
        float ml=inputs.get_link_mass();//kg
        float l=inputs.get_link_length()/1000;//m
        float mp=inputs.get_payload_mass();//kg
        float a_max=inputs.get_max_angular_acc();//rad/s*2
        part1.M = (ml*9.81*(l/2))+(mp*9.81*l)+(ml*pow(l/2,2)*a_max)+(mp*pow(l,2)*a_max);    //bending moment in (N.m)
        part1.M = part1.M*1000;    //in(N.mm)
        return part1.M;
    }
    static double moment_of_inertia(inputs_calc& inputs, part_1_calculations& part1)
    {
        ///     function responsible to get  moment of inertia   ///
        float b=inputs.get_width();
        float h=inputs.get_hight();
        float r=inputs.get_radius();
        
        if (inputs.get_cross_section()=="Rectangle"){
            part1.I=(b*pow(h,3))/12;
        }
        if(inputs.get_cross_section()=="Circle"){
            part1.I=((22.0/7)*pow(r,4))/4;
        }
        //moment of inertia in (mm*4)
        return part1.I;
    }
    static double max_stress(inputs_calc& inputs, part_1_calculations& part1)
    {
        ///     function responsible to get  Stress on the Link   ///
        float h=inputs.get_hight();
        float r=inputs.get_radius();
        if(inputs.get_cross_section()=="Rectangle"){
            part1.Calculated_Stress = (bending_moment(inputs, part1)*h)/(2*moment_of_inertia(inputs, part1));
        }
        if(inputs.get_cross_section()=="Circle"){ part1.Calculated_Stress = (bending_moment(inputs, part1)*r)/moment_of_inertia(inputs, part1);}
        //segma in (mpa)
        return  part1.Calculated_Stress;
    }

    static void  ChangingDimension( inputs_calc& inputs , char sign = '+',float Increas_Dimension = 0.01)
    {
        ///     function responsible for Changing Dimensions if the link stress is higher or much lower than the yield stength of the material   ///

        if (inputs.get_cross_section() == "Rectangle")
        {
            float b =0;
            float h =0;
            if (sign == '-')
            {
                b = inputs.get_width() - inputs.get_width() * 0.01; //Increas_Dimension
                h = inputs.get_hight() - inputs.get_hight() * 0.01; //Increas_Dimension
                inputs.set_width(b);
                inputs.set_hight(h);
            }
            else
            {
                b = inputs.get_width() + inputs.get_width() * Increas_Dimension;
                h = inputs.get_hight() + inputs.get_hight() * Increas_Dimension;
                inputs.set_width(b);
                inputs.set_hight(h);
            }
        }
        else if (inputs.get_cross_section() == "Circle")
        {
            if (sign == '-')
            {
                inputs.set_radius(inputs.get_radius() - inputs.get_radius() * 0.01);
            }
            else
            {
                inputs.set_radius(inputs.get_radius() + inputs.get_radius() * 0.01);
            }
        }
    }

    static void GetAccurateDimension(inputs_calc& inputs ,part_1_calculations& calc)
    {
        ///     function responsible to check that if the link stress is not higher or not much lower than the yield stength of the material and get the optimal Dimension ///
        float MuchLower = 0.01;
        float Increas_Dimension = 0.01;

        int desire        =    Input_Handling::get_validated_input<int>("Do you want to determine the lowest percentage for Strength ? Yes[1] or No[0]\n",0,1);
        if (desire)        MuchLower     =    Input_Handling::get_validated_input<float>("Enter the percentage \n",0,0.5);

        desire            =    Input_Handling::get_validated_input<int>("Do you want to determine the  percentage for Increas_Dimension  ? Yes[1] or No[0]\n",0,1);
        if (desire)     Increas_Dimension =    Input_Handling::get_validated_input<float>("Enter the percentage \n",0,0.5);  
        
        calc.setCalculatedStress(max_stress(inputs,calc)) ;
        while ( ((calc.getCalculatedStress() > inputs.get_strength()) ||
                 (calc.getCalculatedStress() < inputs.get_strength() - inputs.get_strength() * MuchLower)))
        {
            if (calc.Calculated_Stress < inputs.get_strength()-inputs.get_strength() * MuchLower)
            {
                ChangingDimension(inputs,'-',0.01);
                calc.setCalculatedStress(max_stress(inputs,calc));
                mass_link(inputs);
            }
            else if (calc.Calculated_Stress > inputs.get_strength())
            {
                ChangingDimension(inputs,Increas_Dimension);
                calc.setCalculatedStress(max_stress(inputs,calc)) ;
                mass_link(inputs);
            }
        }
            // inputs.Set_CalculatedStrength(calc.Calculated_Stress);
    }
};
