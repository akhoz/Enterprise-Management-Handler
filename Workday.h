#include <string>
#include <iostream>
#include <cstdlib>

using std::string;
//Workday struct, used to store the information of the workdays of the employees
class Workday {
public:
	string start_time; //Start time of the workday
	string end_time; //End time of the workday
    int worked_hours;
	bool is_holiday; //If the day is a holiday, if the employee worked that day, he will get a bonus #3x
	bool is_weekend; //If the day is a weekend, if the employee worked that day, he will get a bonus #2x
	Workday* next; //Next workday in the list

	//Constructor
	Workday(string day, string start_time, string end_time, bool is_holiday, bool is_weekend) {
		//This is the constructor of the Workday struct, it receives all the information of the workday and creates the object, returns nothing
		this->start_time = start_time;
		this->end_time = end_time;
		this->is_holiday = is_holiday;
		this->is_weekend = is_weekend;
		this->next = nullptr;
	}
    // No args 
    Workday(){
        this->start_time = "";
        this->end_time = "";
        this->is_holiday = false;
        this->next = nullptr;
    }
    friend std::ostream& operator<<(std::ostream& os, const Workday& workday) {
        os << "Start Time: " << workday.start_time << std::endl;
        os << "End Time: " << workday.end_time << std::endl;
        os << "Is it a holiday? ";
        if (workday.is_holiday) {
            os << "Yes" << std::endl;
        }
        else {
            os << "No" << std::endl;
        }
        os << "Is it a weekend? ";
        if (workday.is_weekend) {
            os << "Yes" << std::endl;
        }
        else {
            os << "No" << std::endl;
        }
        os << "\n";
        return os;
    }


};
