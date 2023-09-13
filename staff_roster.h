#include <iostream>
#include <string>
#pragma once

using std::string;

//Staff struct, used to store the information of the employees and create the Staff Roster linked list
struct Staff {
	string staff_id; //Unique identifier of the employee
	string job_title; //Kind of employee
	string salary_bonuses; //Such as experience or other bonuses
	string job_performed; //What the employee does
	string employment_sector; //Sector where the staff performs his job, for example, production line
	Workday* workdays; //Workdays of the employee
	Staff* boss; //Boss of the employee, null if the employee is the boss
	Staff* next; //Next employee in the list

	//Constructor
	Staff(string staff_id, string job_title, string salary_bonuses, string job_performed, string employment_sector, Workday* workdays, string boss_id) {
		//This is the constructor of the Staff struct, it receives all the information of the employee and creates the object, returns nothing
		this->staff_id = staff_id;
		this->job_title = job_title;
		this->salary_bonuses = salary_bonuses;
		this->job_performed = job_performed;
		this->employment_sector = employment_sector;
		this->workdays = workdays;
		this->next = nullptr;

		this->boss = nullptr; //Set the boss to null, if the employee actually has a boss, it will be changed later
		if (!boss_id.empty()) { //If the boss_id is not empty, it means that the employee has a boss, so we need to find it
			Staff* current = this; //Create a pointer to the current employee
			while (current) { //While the current employee is not null
				if (current->staff_id == boss_id) { //If the current employee is the boss, set the boss pointer to the current employee
					this->boss = current;
					break;
				}
				current = current->next; //If the current employee is not the boss, move to the next employee
			}
		}

	}	
};

//Workday struct, used to store the information of the workdays of the employees
struct Workday {
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