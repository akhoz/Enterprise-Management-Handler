#include <iostream>
#include <string>
#pragma once

using std::string;

//Staff struct, used to store the information of the employees and create the Staff Roster linked list
class Staff {
public:
	string staff_id; //Unique identifier of the employee
	string job_title; //Kind of employee
	string salary_bonuses; //Such as experience or other bonuses
	string job_performed; //What the employee does
	string employment_sector; //Sector where the staff performs his job, for example, production line
	//Workday* workdays; //Workdays of the employee
	Staff* boss; //Boss of the employee, null if the employee is the boss
	Staff* next; //Next employee in the list
	Staff* prev; //Previous employee in the list

	Staff() {
		//This is an empty constructor of the Staff struct, it creates an empty object, returns nothing
		this->staff_id = "";
		this->job_title = "";
		this->salary_bonuses = "";
		this->job_performed = "";
		this->employment_sector = "";
		this->boss = nullptr;
		//this->workdays = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}

	Staff(string staff_id, string job_title, string salary_bonuses, string job_performed, string employment_sector) {
		//This is the constructor of the Staff struct, it receives all the information of the employee and creates the object, returns nothing
		this->staff_id = staff_id;
		this->job_title = job_title;
		this->salary_bonuses = salary_bonuses;
		this->job_performed = job_performed;
		this->employment_sector = employment_sector;
		this->boss = nullptr;
		//this->workdays = workdays;
		this->next = nullptr;
		this->prev = nullptr;
	}	

	//Overload of the << operator, used to print the information of the employee
	friend std::ostream& operator<<(std::ostream& os, const Staff& staff) {
		os << "Staff ID: " << staff.staff_id << std::endl;
		os << "Job Title: " << staff.job_title << std::endl;
		os << "Salary Bonuses: " << staff.salary_bonuses << std::endl;
		os << "Job Performed: " << staff.job_performed << std::endl;
		os << "Employment Sector: " << staff.employment_sector << std::endl;
		os << "Boss: ";
		if (staff.boss) {
			os << staff.boss->staff_id;
		}
		else {
			os << "None";
		}
		os << "\n";
		return os;
	}
};

//Workday struct, used to store the information of the workdays of the employees
class Workday {
public:
	string day; //Day of the week
	string start_time; //Start time of the workday
	string end_time; //End time of the workday
	bool is_holiday; //If the day is a holiday, if the employee worked that day, he will get a bonus
	bool is_weekend; //If the day is a weekend, if the employee worked that day, he will get a bonus
	Workday* next; //Next workday in the list

	//Constructor
	Workday(string day, string start_time, string end_time, bool is_holiday, bool is_weekend) {
		//This is the constructor of the Workday struct, it receives all the information of the workday and creates the object, returns nothing
		this->day = day;
		this->start_time = start_time;
		this->end_time = end_time;
		this->is_holiday = is_holiday;
		this->is_weekend = is_weekend;
		this->next = nullptr;
	}
};