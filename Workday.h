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
	Workday(string start_time, string end_time, bool is_holiday, bool is_weekend) {
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
    void print(){
        std::cout << "Start Time: " << start_time << std::endl;
        std::cout << "End Time: " << end_time << std::endl;
        std::cout << "Worked Hours: " << worked_hours << std::endl;
        std::cout << "Is Holiday: " << is_holiday << std::endl;
        std::cout << "Is Weekend: " << is_weekend << std::endl;
        std::cout << "\n";
    }
    };
