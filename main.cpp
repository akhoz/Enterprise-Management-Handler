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

template <typename T>
void print_linked_list(T*& linked_list) {
	T* current = linked_list; 
	while (current) {
		std::cout << *current << std::endl;
		current = current->next;
	}

}
void addWorkday(Staff*& staff, Workday workday) {
    if (staff->workdays == nullptr) {
        staff->workdays = &workday;
    }
    else {
        Workday* current = staff->workdays;
        while (staff->workdays->next != nullptr) {
            staff->workdays = staff->workdays->next;
        }
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
    printf("Horas trabajadas: %d\n", hours);
    return hours;

}

void registerHours(Staff*& staff) {
    Workday workday;
    string start_time;
    string end_time;
    std::cout << "Enter the start time: ";
    std::cin >> start_time;
    std::cout << "Enter the end time: ";
    std::cin >> end_time;
    std::cout << "Is it a holiday? (y/n): ";
    char holiday;
    std::cin >> holiday;
    std::cout << "Is it a weekend? (y/n): ";
    char weekend;
    std::cin >> weekend;
    workday.worked_hours = worked_hours(start_time, end_time);
    if (holiday == 'y') {
        workday.is_holiday = true;
    }
    else {
        workday.is_holiday = false;
    }
    if (weekend == 'y') {
        workday.is_weekend = true;
    }
    else {
        workday.is_weekend = false;
    }

    if (staff->workdays == nullptr) {
        staff->workdays = &workday;
    }
    else {
        addWorkday(staff, workday);
    }
    /* system("clear"); */
}
int main() {

	Staff* first_staff = new Staff("hola", "Boss", "experience", "Managment", "Administration sector", "");
	Staff* second_staff = new Staff("2023121213", "Employee", "", "Production", "Production sector", "hola");

	double_append_end(people_list, first_staff);
	double_append_end(people_list, second_staff);
    registerHours(second_staff);
	/* print_linked_list(people_list); */

	return 0;
}
