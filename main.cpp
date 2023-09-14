#include <ctime>
#include <iostream>
#include <string>
#include "staff_roster.h"

using std::string;
using std::tm;

Staff* people_list = nullptr;


template <typename T> //This is a template function, it can take any type of data, this is used avoid code duplication, such as having to write the same function for different structs or linked lists

void double_append_end(T*& linked_list, T*& element_to_append) {
	if (!element_to_append) { //If the element to append is null
		return; 
	}
	if (!linked_list) { 
			linked_list = element_to_append; 
			return;
	}
	T* current = linked_list;
	while (current->next) { 
			current = current->next; 
	}
	current->next = element_to_append; 
	element_to_append->prev = current;
}

Staff* findStaffById(const string& id) {
    Staff* current = people_list;
    while (current) {
        if (current->staff_id == id) {
            std::cout << "The person has been found" << std::endl;
            return current;
        }
        current = current->next;
    }
    return nullptr; // Si no se encuentra la persona con el ID dado
}


template <typename T>
void print_linked_list(T*& linked_list) {
	T* current = linked_list; 
	while (current) {
		std::cout << *current << std::endl;
		current = current->next;
	}
}

void print_person_workday(Staff*& person) {
    Workday* current = person->workdays;
    while (current) {
        current->print();
        current = current->next;
    }
}


tm parseHour(const string& hora) {
    tm tiempo = {};
    strptime(hora.c_str(), "%H:%M", &tiempo);
    return tiempo;
}

int worked_hours(const string& start, const string& end){
    tm parsed_start = parseHour(start);
    tm parsed_end = parseHour(end);

    time_t t_inicio = mktime(&parsed_start);
    time_t t_fin = mktime(&parsed_end);

    int seconds = difftime(t_fin, t_inicio);
    int hours = seconds / 3600;
    return hours;

}

void registerHours(Staff*& staff) {
    Workday *workday = new Workday();
    string weeknd;
    string holiday;
    std::cout << "Enter the start hour: \n";
    std::cin >> workday->start_time;
    std::cout << "Enter the end hour: \n";
    std::cin >> workday->end_time;
    std::cout << "Is it a weekend? (y/n): \n";
    std::cin >> weeknd;
    std::cout << "Is it a holiday? (y/n): \n";
    std::cin >> holiday;
    if (weeknd == "y") {
         workday->is_weekend = true;
    }
    else {
        workday->is_weekend = false;
    }
    if (holiday == "y") {
        workday->is_holiday = true;
    }
    else {
        workday->is_holiday = false;
    }
    workday->worked_hours = worked_hours(workday->start_time, workday->end_time);
    // Add the workday to the staff workdays list
    if (staff->workdays == nullptr) {
        staff->workdays = workday;
    }
    else {
        Workday* current = staff->workdays;
        while (current->next) {
            current = current->next;
        }
        current->next = workday;
    }

}

void set_salary(Staff*& person){
    int user_worked_hours = 0;
    Workday* current = person->workdays;
    if (current == nullptr) {
        std::cout << "The user has not worked yet" << std::endl;
        return;
    }
    while (current) {
        if (current->is_weekend == true) {
            user_worked_hours += current->worked_hours * 2;
        }
        else if (current->is_holiday == true) {
            user_worked_hours += current->worked_hours * 3;
        }
        else {
            user_worked_hours += current->worked_hours;
        }
        current = current->next;
    }
    person->salary = user_worked_hours * 100;
    std::cout << "The salary of the user is: " << person->salary << std::endl;
}



int main() {

	Staff* first_staff = new Staff("hola", "Boss", "experience", "Managment", "Administration sector", "");
	Staff* second_staff = new Staff("2023121213", "Employee", "", "Production", "Production sector", "hola");

	double_append_end(people_list, first_staff);
	double_append_end(people_list, second_staff);
	print_linked_list(people_list);
    std::cout << "Enter the id of the person you want to register hours: ";
    string id;
    std::cin >> id;
    Staff* person = findStaffById(id);
    registerHours(person);
    print_person_workday(person);
    set_salary(person);

	return 0;
}
