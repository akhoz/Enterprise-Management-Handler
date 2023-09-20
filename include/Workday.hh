#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

using std::string;
//workday struct, used to store the information of the workdays of the employees
class Workday {
public:
	string start_time; //Start time of the workday
	string end_time; //End time of the workday
    int worked_hours;
	bool is_holiday; //If the day is a holiday, if the employee worked that day, he will get a bonus #3x
	bool is_weekend; //If the day is a weekend, if the employee worked that day, he will get a bonus #2x
	Workday* next; //Next workday in the list
    
    Workday(string start_time, string end_time, int worked_hours, bool is_holiday, bool is_weekend, Workday* next); //Constructor
    Workday(); //Constructor

    friend std::ostream& operator<<(std::ostream& os, const Workday& workday) {
        os << "Start time: " << workday.start_time << std::endl;
        os << "End time: " << workday.end_time << std::endl;
        os << "Worked hours: " << workday.worked_hours << std::endl;
        os << "Is holiday: " << workday.is_holiday;
        if (workday.is_holiday) {
            os << "yes" << std::endl;
        } else {
            os << "no" << std::endl;
        }
        os << "Is weekend: " << workday.is_weekend;
        if (workday.is_weekend) {
            os << "yes" << std::endl;
        } else {
            os << "no" << std::endl;
        }
        return os;
    }; //Overload of the << operator
};
