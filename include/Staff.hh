#include <iostream>
#include <string>
#include <Workday.hh>
#pragma once

using std::string;

//Staff struct, used to store the information of the employees and create the Staff Roster linked list
class Staff {
public:
    int salary = 0;
	string id; //Unique identifier of the employee
	string job_title; //Kind of employee
	string salary_bonuses; //Such as experience or other bonuses
	string job_performed; //What the employee does
	string employment_sector; //Sector where the staff performs his job, for example, production line
	Workday* workdays; //Workdays of the employee
	Staff* boss; //Boss of the employee, null if the employee is the boss
	Staff* next; //Next employee in the list
	Staff* prev; //Previous employee in the list
    
    Staff(string staff_id, string job_title, string salary_bonuses, string job_performed, string employment_sector);
    Staff();

	//Overload of the << operator, used to print the information of the employee
	friend std::ostream& operator<<(std::ostream& os, const Staff& staff) {
		os << "Staff ID: " << staff.id << std::endl;
		os << "Job Title: " << staff.job_title << std::endl;
		os << "Salary Bonuses: " << staff.salary_bonuses << std::endl;
		os << "Job Performed: " << staff.job_performed << std::endl;
		os << "Employment Sector: " << staff.employment_sector << std::endl;
		os << "Boss: ";
		if (staff.boss) {
			os << staff.boss->id << "\n";
		}
		else {
			os << "None" << "\n";
		}
		return os;
	}
};

