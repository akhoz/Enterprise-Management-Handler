#include <iostream>
#include <string>
#include <cstdlib>
#include "staff_roster.h"
using std::string;

//Linked lists
Staff* staff_roster = nullptr; //Create a pointer to the staff roster linked list, set it to null


template <typename T> //This is a template function, it can take any type of data, this is used avoid code duplication, such as having to write the same function for different structs or linked lists
void double_append_end(T*& linked_list, T*& element_to_append) {
	//This is a function that appends an element to the end of a double linked list
	//It receives a pointer to the linked list and a pointer to the element to append
	//Returns nothing

	if (!element_to_append) { //If the element to append is null
		return; //Return nothing, this is in order to avoid appending null elements
	}

	if (!linked_list) { //If the linked list is empty
		linked_list = element_to_append; //Set the new element as the first node of the linked list
		return; //Return nothing
	}

	T* current = linked_list; //Create a pointer to the current node
	while (current->next) { //While the current node is not null
		current = current->next; //Move to the next node
	}
	current->next = element_to_append; //Set the next node to the new element
	element_to_append->prev = current; //Set the previous node of the new element to the current node
}

template <typename T>
void print_linked_list(T*& linked_list) {
	//This is a function that prints the elements of a linked list
	//It receives a pointer to the linked list
	//Returns nothing

	T* current = linked_list; //Create a pointer to the current node
	while (current) { //While the current node is not null, print the data of the current node and move to the next node

		//if (current->boss != nullptr)
		std::cout << *current << std::endl;
		current = current->next;
	}

}

void assignBoss(string new_staff_id) {
	//This is a function that assigns a boss to an employee
	//It receives the id of the employee
	//Returns nothing

	string boss_id;
	std::cout << "Boss id: ";
	std::cin >> boss_id;

	if (boss_id.empty()) //If the boss id is not empty, exit the function
		return;

	Staff* boss = nullptr; //Create a pointer that later will point to the boss of the employee
	Staff* current = staff_roster; //Create a pointer to the current node
	while (current) { //While the current node is not null, search for the boss of the employee
		if (current->staff_id == boss_id) {
			boss = current; //Set the boss pointer to the current node
			break;
		}
		current = current->next;
	}

	current = staff_roster;
	while (current) { //While the current node is not null, search for the employee
		if (current->staff_id == new_staff_id) {
			current->boss = boss; //Set the boss of the employee to the boss pointer
			return;
		}
		current = current->next;
	}
}

void add_staff() {
	//This is a function that adds a new employee to the staff roster, it requests the information of the employee
	//Recieves nothing
	//Returns nothing

	//Here is where the information is requested
	Staff* new_staff = new Staff(); //Create a pointer to the new employee
	std::cout << "Please fill the following information: " << std::endl;
	std::cout << "Id: ";
	std::cin >> new_staff->staff_id;
	std::cout << "Job title: ";
	std::cin >> new_staff->job_title;
	std::cout << "Salary bonuses: ";
	std::cin >> new_staff->salary_bonuses;
	std::cout << "Job performed: ";
	std::cin >> new_staff->job_performed;
	std::cout << "Employment sector: ";
	std::cin >> new_staff->employment_sector;

	double_append_end(staff_roster, new_staff); //Append the new employee to the staff roster

	if (new_staff->job_title != "boss") //If the employee is not the boss, assign a boss to the employee
		assignBoss(new_staff->staff_id); //Assign the boss of the employee

	std::cout << "Employee added successfully" << std::endl;
}

void sort_by_sector() {
	//This is a function that sorts the staff roster by sector
	//Recieves nothing
	//Returns nothing

	Staff* administration_sector = nullptr; //Create a pointer to the administration sector linked list, set it to null
	Staff* production_sector = nullptr; //Create a pointer to the production sector linked list, set it to null
	Staff* maintenance_sector = nullptr; //Create a pointer to the maintenance sector linked list, set it to null

	Staff* current = staff_roster; //Create a pointer to the current node
	Staff* next = nullptr; //Create a pointer to the next node
	while (current) {
		next = current->next; //Set the next node to the next node of the current node
		current->next = nullptr; //Set the next node of the current node to null

		if (current->employment_sector == "administration") { //If the current node is in the administration sector, append it to the administration sector linked list
			double_append_end(administration_sector, current);
		}
		else if (current->employment_sector == "production") { //If the current node is in the production sector, append it to the production sector linked list
			double_append_end(production_sector, current);
		}
		else if (current->employment_sector == "maintenance") { //If the current node is in the maintenance sector, append it to the maintenance sector linked list
			double_append_end(maintenance_sector, current);
		}
		current = next;
	}

	Staff* new_staff_roster = nullptr; //Create a pointer to the new staff roster linked list, set it to null 
	double_append_end(new_staff_roster, administration_sector);
	double_append_end(new_staff_roster, production_sector);
	double_append_end(new_staff_roster, maintenance_sector);
	staff_roster = new_staff_roster; //Set the staff roster to the new staff roster
}

void sort_by_job_title() {
	//This is a function that sorts the staff roster by job title
	//Recieves nothing
	//Returns nothing

	Staff* boss = nullptr; //Create a pointer to the boss linked list, set it to null
	Staff* employee = nullptr; //Create a pointer to the employee linked list, set it to null
	Staff* intern = nullptr; //Create a pointer to the intern linked list, set it to null

	Staff* current = staff_roster; //Create a pointer to the current node
	Staff* next = nullptr; //Create a pointer to the next node
	while (current) {
		next = current->next; //Set the next node to the next node of the current node
		current->next = nullptr; //Set the next node of the current node to null

		if (current->job_title == "boss") { //If the current node is a boss, append it to the boss linked list
			double_append_end(boss, current);
		}
		else if (current->job_title == "employee") { //If the current node is an employee, append it to the employee linked list
			double_append_end(employee, current);
		}
		else if (current->job_title == "intern") { //If the current node is an intern, append it to the intern linked list
			double_append_end(intern, current);
		}
		current = next;
	}

	Staff* new_staff_roster = nullptr; //Create a pointer to the new staff roster linked list, set it to null
	double_append_end(new_staff_roster, boss);
	double_append_end(new_staff_roster, employee);
	double_append_end(new_staff_roster, intern);
	staff_roster = new_staff_roster; //Set the staff roster to the new staff roster
}

int main() {

	//Those instance are just for testing

	Staff* first_staff = new Staff("1", "boss", "experience", "managment", "administration"); //Create the first employee, the boss
	Staff* second_staff = new Staff("2", "employee", "experience", "production", "production"); //Create the second employee, the employee
	Staff* third_staff = new Staff("3", "boss", "experience", "managment", "administration"); //Create the first employee, the boss
	Staff* fourth_staff = new Staff("4", "intern", "experience", "managment", "maintenance"); //Create the first employee, the boss
	Staff* fifth_staff = new Staff("5", "boss", "experience", "managment", "production"); //Create the first employee, the boss

	double_append_end(staff_roster, first_staff); //Append the first employee to the staff roster
	double_append_end(staff_roster, second_staff); //Append the second employee to the staff roster
	double_append_end(staff_roster, third_staff); //Append the first employee to the staff roster
	double_append_end(staff_roster, fourth_staff); //Append the first employee to the staff roster
	double_append_end(staff_roster, fifth_staff); //Append the first employee to the staff roster


	//add_staff();
	sort_by_sector();
	print_linked_list(staff_roster);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	sort_by_job_title();
	print_linked_list(staff_roster);

	return 0;
}