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

