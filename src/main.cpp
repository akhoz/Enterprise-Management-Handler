#include <Category.hh>
#include <Product.hh>
#include <Resource.hh>
#include <Staff.hh>
#include <Stage.hh>
#include <Workday.hh>
#include <Warehouse.hh>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>

using std::string;
using std::tm;

// Create a pointer to the staff roster linked list, set it to null
Staff *staff_roster = nullptr;

// Create a pointer to the inventory linked list, set it to null
Category *inventory = nullptr;


Warehouse *warehouse_inventory = nullptr;

bool exit_menu = false;

tm parse_hour(const string& hour) {
    tm time = {};
    strptime(hour.c_str(), "%H:%M", &time);
    return time;
}

//This is a template function, it can take any type of data, this is used avoid code duplication, such as having to write the same function for different structs or linked lists 
template <typename T>
void lineal_append_end(T*& linked_list, T*& element_to_append) {
	//This function appends an element to the end of a lineal linked list
	//It receives the linked list and the element to append 
	//Returns nothing

	if (!linked_list) {
		linked_list = element_to_append; //If the linked list is empty, the linked list is the element to append
		return; //Returns nothing
	}

	T* current = linked_list;
	while (current->next) {
		current = current->next;
	}
	current->next = element_to_append; //The next element of the linked list is the element to append
}

template <typename T>
void double_append_end(T*& linked_list, T*& element_to_append) {
    // This function appends an element to the end of a double linked list
    // It receives the linked list and the element to append
    // Returns nothing
	if (!element_to_append) { //If the element to append is null
		return;
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
	if (!linked_list) {
		linked_list = element_to_append;
		return;
	}
}

template <typename T>
void double_circular_append_end(T*& linked_list, T*& element_to_append) {
	//This function appends an element to the end of a double circular linked list
	//Receives the linked list and the element to append
	//Returns nothing

	if (!linked_list) { //If the linked list is empty
		linked_list = element_to_append; //The linked list is the element to append
		linked_list->next = linked_list; //The next element of the linked list is itself
		linked_list->prev = linked_list; //The previous element of the linked list is itself
		return; //Returns nothing
	}

	T* current = linked_list;

    //While the next element of the current element is not the first element of the linked list
	do { 
       		current = current->next;
	}  while (current->next != linked_list);
	current->next = element_to_append; //The next element of the current element is the element to append
	element_to_append->prev = current; //The previous element of the element to append is the current element
	element_to_append->next = linked_list; //The next element of the element to append is the first element of the linked list
	linked_list->prev = element_to_append; //The previous element of the first element of the linked list is the element to append
}


template <typename T>
void print_linked_list(T*& linked_list) {
	//This is a function that prints the elements of a non-circular linked list
	//It receives a pointer to the linked list
	//Returns nothing

	T* current = linked_list; //Create a pointer to the current node
	while (current) { //While the current node is not null, print the data of the current node and move to the next node
        /* std::cout << *current << std::endl; */ // Error with this one
        std::cout << *current << std::endl;
        current = current->next;
    }
}

template <typename T>
void print_circular_linked_list(T*& linked_list) {
	//This is a function that prints the elements of a circular linked list
	//It receives a pointer to the linked list
	//Returns nothing

	T* current = linked_list; //Create a pointer to the current node
	while (current->next != linked_list) { //While the next node of the current node is not the first node, print the data of the current node and move to the next node
		std::cout << *current << std::endl;
		current = current->next;
	}
	std::cout << *current << std::endl; //Print the data of the last node
}

void print_whole_categories() {
    //This is a function that prints the categories of the inventory
    //It receives nothing
    //Returns nothing
    Category* current = inventory;

    if (!current) {
        std::cout << "There are no categories" << std::endl;
        return;
    }
    while (current) {
    std::cout << "Category: " << current->category_name << std::endl;
    std::cout << std::endl;
    Product* current_product = current->products;
    std::cout << "Products of the category: " << std::endl;
    while (current_product) {
        std::cout << "Product name: " << current_product->name << std::endl;
        std::cout << "Serial number: " << current_product->serial_number << std::endl;
        Stage* current_stage = current_product->current_stage;
        std::cout << std::endl;
        std::cout << "Stages of the product: " << std::endl;
        while (current_stage) {
            std::cout << "Stage: " << current_stage->stage_name << std::endl;
            if (current_stage->completed) {
                std::cout << "Status: completed" << std::endl;
            }
            else {
                std::cout << "Status: in process" << std::endl;
            }
            Resource* current_resource = current_stage->resources; // Mover esto aquí
            std::cout << "Resources needed of this stage: " << std::endl;
            while (current_resource) {
                std::cout << current_resource->name << std::endl;
                current_resource = current_resource->next;
            }
            current_stage = current_stage->next;
        }
        std::cout << std::endl;
        current_product = current_product->next;
    }
    current = current->next;
    }
    std::cout << "\n";
}

void assign_boss(string new_staff_id) {
	//This is a function that assigns a boss to an employee
	//It receives the id of the employee
	//Returns nothing

	string boss_id;
	std::cout << "Boss id: ";
    std::getline(std::cin, boss_id);

	if (boss_id.empty()) //If the boss id is not empty, exit the function
		return;

	Staff* boss = nullptr; //Create a pointer that later will point to the boss of the employee
	Staff* current = staff_roster; //Create a pointer to the current node
	while (current) { //While the current node is not null, search for the boss of the employee
		if (current->id == boss_id) {
			boss = current; //Set the boss pointer to the current node
			break;
		}
		current = current->next;
	}

	current = staff_roster;
	while (current) { //While the current node is not null, search for the employee
		if (current->id == new_staff_id) {
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
    std::cin.ignore();
	std::cout << "Id: ";
    std::getline(std::cin, new_staff->id);
	std::cout << "Job title: ";
    std::getline(std::cin, new_staff->job_title);
	std::cout << "Salary bonuses: ";
    std::getline(std::cin, new_staff->salary_bonuses);
	std::cout << "Job performed: ";
    std::getline(std::cin, new_staff->job_performed);
	std::cout << "Employment sector: ";
    std::getline(std::cin,new_staff->employment_sector);
	double_append_end(staff_roster, new_staff); //Append the new employee to the staff roster

	if (new_staff->job_title != "boss") //If the employee is not the boss, assign a boss to the employee
		assign_boss(new_staff->id); //Assign the boss of the employee

	std::cout << "Employee added successfully" << std::endl;
}

void remove_staff() {
	//This is a function that removes an employee from the staff roster
	//Recieves nothing
	//Returns nothing

	string staff_id;
    std::cin.ignore();
	std::cout << "Type the id of the employee you want to remove: ";
    std::getline(std::cin, staff_id);

	Staff* current = staff_roster; //Create a pointer to the current node
	while (current) { //While the current node is not null, search for the employee
		if (current->id == staff_id) { //If the employee is found, remove it from the staff roster
			if (current->prev) {
				current->prev->next = current->next; //The previous node of the current node points to the next node of the current node
			}
			if (current->next) {
				current->next->prev = current->prev; //The next node of the current node points to the previous node of the current node
			}
			if (current == staff_roster) {
				staff_roster = current->next; //If the current node is the first node, set the staff roster to the next node of the current node
			}
			delete current; //Delete the current node in order to free memory
			std::cout << "Employee removed successfully" << std::endl;
			return;
		}
		current = current->next;
	}
}

void modify_staff(string staff_id) {
	//This function modifies the information of an employee
	//Recieves the id of the employee
	//Returns nothing
	string property_to_change;
	std::cout << "Type the property you want to change: ";
    std::cin >> property_to_change;
    std::cin.ignore();

	Staff* current = staff_roster; //Create a pointer to the current node
	Staff* staff_to_modify = nullptr; //Create a pointer to the employee to modify, set it to null

	while (current) {
		if (current->id == staff_id) { //If the employee is found, set the staff to modify pointer to the current node
			staff_to_modify = current; //Set the staff to modify pointer to the current node
			break;
		}
		current = current->next;
	}

	if (!staff_to_modify) { //If the employee is not found, exit the function
		std::cout << "No employee found with that id" << std::endl;
		return;
	}
	//Case comparison, this is to determine which property of the employee to change
	if (property_to_change == "id") { //If the property to change is the id, change the id of the employee
		std::cout << "New id: ";
        std::getline(std::cin, staff_to_modify->id);
	}
	else if (property_to_change == "job_title") { //If the property to change is the job title, change the job title of the employee
		std::cout << "New job title: ";
        std::getline(std::cin, staff_to_modify->job_title);
	}
	else if (property_to_change == "salary_bonuses") { //If the property to change is the salary bonuses, change the salary bonuses of the employee
		std::cout << "New salary bonuses: ";
        std::getline(std::cin, staff_to_modify->salary_bonuses);
	}
	else if (property_to_change == "job_performed") { //If the property to change is the job performed, change the job performed of the employee
		std::cout << "New job performed: ";
        std::getline(std::cin, staff_to_modify->job_performed);
	}
	else if (property_to_change == "employment_sector") { //If the property to change is the employment sector, change the employment sector of the employee
		std::cout << "New employment sector: ";
        std::getline(std::cin, staff_to_modify->employment_sector);
	}
	else if (property_to_change == "boss") { //If the property to change is the boss, change the boss of the employee
		assign_boss(staff_to_modify->id);
	}
	else { //If the property to change is not found, exit the function
		std::cout << "Property not found" << std::endl;
		return;
	}
}

Staff* find_staff_by_id(const string& id) {
    // This function finds a staff member by id
    // It receives the id of the staff member
    // Returns a pointer to the staff member
    Staff* current = staff_roster;
    while (current) {
        if (current->id == id) {
            /* std::cout << current->id << std::endl; */
            return current;
        }
        current = current->next;
    }
    // If the staff member is not found, return null
    return nullptr;
}

void print_workday(Staff*& staff) {
    // This function prints the workdays of a staff member
    // It receives a pointer to the staff member
    // Returns nothing
    Workday* current = staff->workdays;
    while (current) {
        std::cout << current << std::endl;
        current = current->next;
    }
}

int worked_hours(const string& start, const string& end) {
    //This is a function that calculates the worked hours of a staff member
    //It receives the start hour and the end hour
    //Returns the worked hours
	tm parsed_start = parse_hour(start);
	tm parsed_end = parse_hour(end);

	time_t t_inicio = mktime(&parsed_start);
	time_t t_fin = mktime(&parsed_end);

	int seconds = difftime(t_fin, t_inicio);
	int hours = seconds / 3600;
	return hours;

}

void registerHours(Staff*& staff) {
    // This is a function that registers the hours of a staff member
    // It receives a pointer to the staff member
    // Returns nothing
	Workday* workday = new Workday();
	string weeknd;
	string holiday;

	std::cout << "Enter the start hour: \n";
    std::getline(std::cin, workday->start_time);
	std::cout << "Enter the end hour: \n";
    std::getline(std::cin, workday->end_time);
	std::cout << "Is it a weekend? (y/n): \n";
    std::getline(std::cin, weeknd);
	std::cout << "Is it a holiday? (y/n): \n";
    std::getline(std::cin, holiday);
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
	// Add the workday to the staff workdays list if it is empty, if not, append it to the end of the list
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

void set_salary(Staff*& person) {
    // This is a function that calculates the salary of a staff member
    // It receives a pointer to the staff member
    // Returns nothing
    int user_worked_hours = 0;
    int user_salary = 0;
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
    user_salary = user_worked_hours * 100;
    // If the user is experienced, add 1000 to the salary
    if (person->salary_bonuses == "experienced") {
        user_salary += 1000;
    }
    // If the user is performance, add 500 to the salary
    else if (person->salary_bonuses == "performance") {
        user_salary += 500;
    }
    person->salary = user_salary;
    std::cout << "The salary of the user is: " << person->salary << std::endl;
}

void register_hours_menu(Staff*& staff) {
    // This is a function that prints the register hours menu
    // It receives a pointer to the staff member
    // Returns nothing
    string id;
    std::cin.ignore();
    std::cout << "Register hours menu" << std::endl;
    std::cout << "Type your id: ";
    std::getline(std::cin, id);
    Staff* staff_member = find_staff_by_id(id);
    if (!staff_member) {
        std::cout << "Staff member not found" << std::endl;
        return;
    }
    registerHours(staff_member);
}

void consult_salary(Staff*& List) {
    // This is a function that prints the consult salary menu
    // It receives a pointer to the staff member
    // Returns nothing
    string id;
    std::cin.ignore();
    std::cout << "Consult salary menu" << std::endl;
    std::cout << "Type your id: ";
    std::getline(std::cin, id);
    Staff* staff_member = find_staff_by_id(id);
    if (!staff_member) {
        std::cout << "Staff member not found" << std::endl;
        return;
    }
    set_salary(staff_member);
}

void stock_inquiry(Category*& selected_category) {
	//This is a function that prints the products of a category
	//It receives a pointer to the category
	//Returns nothing

	Category* current = inventory; //Create a pointer to the current node
	while (current) {
		if (current->category_name == selected_category->category_name) { //If the current node is the selected category, print the products of the category
			print_linked_list(current->products);
			return; //Return nothing
		}
		current = current->next;
	}
}

void state_inquiry(string serial_number){
    //This is a function that prints the state of a product
    //It receives the serial number of the product
    //Returns nothing
    Category* current = inventory;
    while(current){
        if(current->products->serial_number == serial_number){
            break;
        }
        Stage* current_stage = current->products->current_stage;
        while (current_stage->completed) {
            current_stage = current_stage->next;
        }
        std::cout << "The product is in the " << current_stage->stage_name << " stage" << std::endl; //Print the current stage of the product
    }
}
//------> Evaluate if this functions will stay or we will replace the template conversor <------

void append_category(Category*& category_to_append) {
    //This is a function that appends a category to the inventory
    //It receives a pointer to the category to append
    //Returns nothing

    if (!inventory) { //If the inventory is empty, the inventory is the category to append
        inventory = category_to_append;
        return; //Return nothing
    }

    Category* current = inventory; //Create a pointer to the current node
    while (current->next) { //While the current node is not null, move to the next node
        current = current->next;
    }
    current->next = category_to_append; //The next node of the current node is the category to append
}

void append_product_to_category(Category*& category, Product*& product) {
    //This is a function that appends a product to a category
    //It receives a pointer to the category and a pointer to the product
    //Returns nothing

    if (!category->products) { //If the products of the category is empty, the products of the category is the product
        category->products = product;
        return; //Return nothing
    }

    Product* current = category->products; //Create a pointer to the current node
    while (current->next) { //While the current node is not null, move to the next node
        current = current->next;
    }
    current->next = product; //The next node of the current node is the product
}

void append_resources(Stage*& stage, Resource*& resource) {
    //This is a function that appends a resource to a stage
    //It receives a pointer to the stage and a pointer to the resource
    //Returns nothing

    if (!stage->resources) { //If the resources of the stage is empty, the resources of the stage is the resource
        stage->resources = resource;
        return; //Return nothing
    }

    Resource* current = stage->resources; //Create a pointer to the current node
    while (current->next) { //While the current node is not null, move to the next node
        current = current->next;
    }
    current->next = resource; //The next node of the current node is the resource
}

void add_resources(Resource *&resource_list, Resource *&resource_to_add) {
    //This is a function that adds a resource to a resource list
    //It receives a pointer to the resource list and a pointer to the resource to add
    //Returns nothing

    if (!resource_list) { //If the resource list is empty, the resource list is the resource to add
        resource_list = resource_to_add;
        return; //Return nothing
    }

    Resource* current = resource_list; //Create a pointer to the current node
    while (current) { //While the current node is not null, move to the next node
        current = current->next;
    }
    current->next = resource_to_add; //The next node of the current node is the resource to add
}

//------> Evaluate if this functions will stay or we will replace the template conversor <------

void complete_category(const string name){
    //This is a function that completes a category of the inventory
    //It receives the name of the category
    //Returns nothing

    //Create a new category, set the name of the category to the name of the category to complete
    //Create a new product, set the name of the product to the name of the category to complete
    //Create a new stage, set the name of the stage to the name of the category to complete
    //Create a new resource, set the name of the resource to the name of the category to complete
    //Create a pointer to the current node, set it to the inventory
    Category *new_category = new Category(name);
    Product *new_product = nullptr;
    Stage *stage_list = nullptr;
    Resource *component_list = nullptr;
    bool completed = false;
    std::cout << "How many products you want to register? " << std::endl;
    int products;
    std::cin >> products;
    std::cin.ignore();
    for (int i = 0; i < products; i++) {
        // Iterate through the products of the category and add them to the category
        new_product = new Product();
        std::cout << "Type the product you want to register: " << std::endl;
        std::getline(std::cin, new_product->name);
        std::cout << "Type the serial number of the product: " << std::endl;
        std::getline(std::cin, new_product->serial_number);
        std::cout << "How many stages does the product has? " << std::endl;
        int stages;
        std::cin >> stages;
        std::cin.ignore();
        for (int j =0; j < stages; j++){
            // Iterate through the stages of the product and add them to the product
            Stage *new_stage = new Stage();
            std::cout << "Type the name of the stage: " << std::endl;
            std::getline(std::cin, new_stage->stage_name);
            std::cout << "Type if the stage is completed (true/false): " << std::endl;
            std::cin >> std::boolalpha >> completed;
            std::cin.ignore();
            std::cout << "How many resources does the stage have? " << std::endl;
            int amount;
            std::cin >> amount;
            std::cin.ignore();
            for (int y = 0; y < amount; y++) {
                // Iterate through the resources of the stage and add them to the stage
                Resource *new_resource = new Resource();
                std::cout << "Type the name of the resource needed to build the product" << std::endl;
                std::getline(std::cin, new_resource->name);
                std::cout << "Type the quantity of the resource needed to build the product" << std::endl;
                std::cin >> new_resource->quantity;
                std::cin.ignore();
                // Add the Resource to the components list
                lineal_append_end(component_list, new_resource);
            }
            lineal_append_end(new_stage->resources, component_list);
            lineal_append_end(stage_list, new_stage);
            component_list = nullptr;
        }
        lineal_append_end(new_product->current_stage, stage_list);
        stage_list = nullptr;
        lineal_append_end(new_category->products, new_product);
    }
    lineal_append_end(inventory, new_category);
    return;
}

void append_product(string category) {
    //This is a function that appends a product to a category
    //It receives the name of the category
    //Returns nothing

    //Create a pointer to the current node, set it to the inventory
    Category* current = inventory; //Create a pointer to the current node
    while (current->category_name != category) { //While the current node is not null, move to the next node
        current = current->next;
    }
    while (current) {
        if (current->category_name == category) { //If the current node is the selected category, append the product to the category
            Product* new_product = new Product();
            std::cin.ignore();
            std::cout << "Type the name of the product: " << std::endl;
            std::getline(std::cin, new_product->name);
            std::cout << "Type the serial number of the product: " << std::endl;
            std::getline(std::cin, new_product->serial_number);
            std::cout << "How many stages does the product has? " << std::endl;
            int stages;
            std::cin >> stages;
            std::cin.ignore();
            for (int i = 0; i < stages; i++) {
                // Iterate through the stages of the product and add them to the product
                Stage* new_stage = new Stage();
                std::cout << "Type the name of the stage: " << std::endl;
                std::getline(std::cin, new_stage->stage_name);
                std::cout << "Type if the stage is completed (true/false): " << std::endl;
                std::cin >> std::boolalpha >> new_stage->completed;
                std::cin.ignore();
                std::cout << "How many resources does the stage have? " << std::endl;
                int amount;
                std::cin >> amount;
                std::cin.ignore();
                for (int i = 0; i < amount; i++) {
                    // Iterate through the resources of the stage and add them to the stage
                    Resource* new_resource = new Resource();
                    std::cout << "Type the name of the resource needed to build the product" << std::endl;
                    std::getline(std::cin, new_resource->name);
                    std::cout << "Type the quantity of the resource needed to build the product" << std::endl;
                    std::cin >> new_resource->quantity;
                    std::cin.ignore();
                    // Add the Resource to the components list
                    lineal_append_end(new_stage->resources, new_resource);
                }
                lineal_append_end(new_product->current_stage, new_stage);
            }
            lineal_append_end(current->products, new_product);
            return; //Return nothing
        }
    }
}

void append_resource(string category, string stage, string product) {
    //This is a function that appends a resource to a stage
    //It receives the name of the category, the name of the stage and the name of the product
    //Returns nothing

    //Search for the category
    Category* current = inventory;
    while (current->category_name != category) {
        current = current->next;
    }
    //if the category is not found, exit the function
    if (!current) {
        std::cout << "Category not found" << std::endl;
        return;
    }
    //Search for the product
    Product* current_product = current->products;
    while (current_product->name != product) {
        current_product = current_product->next;
    }
    //if the product is not found, exit the function
    if (!current_product) {
        std::cout << "Product not found" << std::endl;
        return;
    }
    //Search for the stage
    Stage* current_stage = current_product->current_stage;
    while (current_stage->stage_name != stage) {
        current_stage = current_stage->next;
    }
    //if the stage is not found, exit the function
    if (!current_stage) {
        std::cout << "Stage not found" << std::endl;
        return;
    }
    int amount;
    std::cout << "How many resources do you want to add? " << std::endl;
    std::cin >> amount;
    std::cin.ignore();
    for (int i = 0; i < amount; i++) {
        // Iterate through the resources of the stage and add them to the stage
        Resource* new_resource = new Resource();
        std::cout << "Type the name of the resource needed to build the product" << std::endl;
        std::getline(std::cin, new_resource->name);
        std::cout << "Type the quantity of the resource needed to build the product" << std::endl;
        std::cin >> new_resource->quantity;
        std::cin.ignore();
        // Add the Resource to the components list
        lineal_append_end(current_stage->resources, new_resource);
    }
}

Category* find_category(const string& category_name) {
    // This function finds a category by name
    // It receives the name of the category
    // Returns a pointer to the category
    Category* current = inventory;
    while (current) {
        if (current->category_name == category_name) {
            return current;
        }
        current = current->next;
    }
    // If the category is not found, return null
    return nullptr;
}

void add_stage(string category, string product){
    //This is a function that adds a stage to a product
    //It receives the name of the category and the name of the product
    //Returns nothing

    //Search for the category
    Category *current = inventory;
    while(current->category_name != category){
        current = current->next;
    }
    //if the category is not found, exit the function
    if (!current) {
        std::cout << "Category not found" << std::endl;
        return;
    }
    //Search for the product
    Product *current_product = current->products;
    while(current_product->name != product){
        current_product = current_product->next;
    }
    //if the product is not found, exit the function
    if (!current_product) {
        std::cout << "Product not found" << std::endl;
        return;
    }
    int amount;
    std::cout << "How many stages do you want to add? " << std::endl;
    std::cin >> amount;
    std::cin.ignore();
    for (int i = 0; i < amount; i++) {
        // Iterate through the stages of the product and add them to the product
        Stage *new_stage = new Stage();
        std::cout << "Type the name of the stage: " << std::endl;
        std::getline(std::cin, new_stage->stage_name);
        std::cout << "Type if the stage is completed (true/false): " << std::endl;
        std::cin >> std::boolalpha >> new_stage->completed;
        std::cin.ignore();
        std::cout << "How many resources does the stage have? " << std::endl;
        int amount;
        std::cin >> amount;
        std::cin.ignore();
        for (int i = 0; i < amount; i++) {
            // Iterate through the resources of the stage and add them to the stage
            Resource *new_resource = new Resource();
            std::cout << "Type the name of the resource needed to build the product" << std::endl;
            std::getline(std::cin, new_resource->name);
            std::cout << "Type the quantity of the resource needed to build the product" << std::endl;
            std::cin >> new_resource->quantity;
            std::cin.ignore();
            // Add the Resource to the components list
            lineal_append_end(new_stage->resources, new_resource);
        }
        lineal_append_end(current_product->current_stage, new_stage);
    }
}

Product* find_product_by_serial_number(const string& serial_number, string category_name) {
    // This function finds a product by serial number
    // It receives the serial number of the product
    // Returns a pointer to the product

    // Search for the category
    Category* current = inventory;
    while (current) {
        if (current->category_name == category_name)
            break;
        current = current->next;
    }
    // If the category is not found, exit the function
    if (!current) {
        return nullptr;
    }
    // Search for the product and return it if the name matches
    std::cout << current->category_name << std::endl;
    Product* current_product = current->products;
    while (current_product) {
        if (current_product->serial_number == serial_number) {
            return current_product;
        }
        current_product = current_product->next;
    }
    // If the product is not found, return null
    return nullptr;
}

bool check_progress(string category_name, string serial_number){
    //This is a function that checks the progress of a product
    //It receives the name of the category and the serial number of the product
    //Returns true if the product is ready for the next stage, false if not
    //Search for the stage calling the find_product_by_serial_number function
    Stage* current_stage = find_product_by_serial_number(serial_number, category_name)->current_stage;
    while(current_stage){
        //If the stage is not completed, return false, because the product is not ready for the next stage
        Resource* current_resource = current_stage->resources;
        Warehouse* temp = warehouse_inventory;
        Warehouse* current_warehouse = warehouse_inventory;
        while(current_resource){
            while(current_warehouse != temp){
                if(current_resource->name == current_warehouse->name){
                    if(!(current_resource->quantity <= current_warehouse->quantity)){
                        return false;
                    }
                }
                current_warehouse = current_warehouse->next;
            }
            current_resource = current_resource->next;
        }
        current_stage = current_stage->next;
    }
    // If the product is ready for the next stage, return true
    return true;
}

void reduce_warehouse(string category_name, string serial_number) {
    //This is a function that reduces the warehouse inventory
    //It receives the name of the category and the serial number of the product
    //Returns nothing
    Product* product = find_product_by_serial_number(serial_number, category_name);
    Stage* current_stage = product->current_stage;
    if (current_stage->completed) {
        // If the product is already completed, exit the function
        while (current_stage->completed) {
            if (current_stage->next == nullptr) {
                std::cout << "The product is already completed" << std::endl;
                return;
            }
            current_stage = current_stage->next;
        }
    }
    Resource* current_resource = current_stage->resources;
    while (current_resource) {
        Warehouse* current_warehouse = warehouse_inventory;
        // Iterate through the resources of the stage and reduce the warehouse inventory, warehouse inventory is a double circular linked list so we need to iterate until it different from the start circular list
        do{
            if(current_resource->name == current_warehouse->name){
                current_warehouse->quantity -= current_resource->quantity;
                std::cout << "Reducing " << current_resource->name << " by " << current_resource->quantity << std::endl;
            }
            current_warehouse = current_warehouse->next;
        }while(current_warehouse != warehouse_inventory);
        
        current_resource = current_resource->next;
    }

}

void advance_stage() {
    // This is a function that advances the stage of a product
    // It asks for the name of the category and the serial number of the product
    // Returns nothing
    string category_name;
    std::cout << "Type the name of the category: " << std::endl;
    std::getline(std::cin, category_name);
    std::cout << "Type the serial number of the product: " << std::endl;
    string serial_number;
    std::getline(std::cin, serial_number);
    // If the product is not ready for the next stage, exit the function
    if(!check_progress(category_name, serial_number)){
        std::cout << "The product is not ready for the next stage" << std::endl;
        return;
    }
    else{
        // If the product is ready for the next stage, reduce the warehouse inventory
        std::cout << "The product is ready for the next stage" << std::endl;
        std::cout << "Do you want to advance the stage? (true/false)" << std::endl;
        bool answer;
        std::cin >> std::boolalpha >> answer;
        if(!answer){
            return;
        }
        else{
        reduce_warehouse(category_name, serial_number);
        }
    }
}

void append_new_stock(){
    // This is a function that appends a new stock to the warehouse inventory
    // It receives nothing
    // Returns nothing
    Warehouse* new_warehouse = new Warehouse();
    std::cin.ignore();
    std::cout << "Type the name of the resource: " << std::endl;
    std::cin >> new_warehouse->name;
    std::cout << "Type the quantity of the resource: " << std::endl;
    std::cin >> new_warehouse->quantity;
    double_circular_append_end(warehouse_inventory, new_warehouse);
}

void add_stock(){
    // This is a function that adds stock to the warehouse inventory
    // It receives nothing
    // Returns nothing
    string name;
    int quantity;
    std::cin.ignore();
    std::cout << "Type the name of the resource: " << std::endl;
    std::cin >> name;
    Warehouse* current = warehouse_inventory;
    // It iterates through the warehouse inventory and adds the stock to the asked resource
    while(current->name != name){
        if(current->next == warehouse_inventory){
            std::cout << "Resource not found" << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Type the quantity of the resource: " << std::endl;
    std::cin >> quantity;
    current->quantity += quantity;
}

void remove_stock(){
    // This is a function that removes stock from the warehouse inventory
    // It receives nothing
    // Returns nothing
    string name;
    std::cin.ignore();
    std::cout << "Type the name of the resource: " << std::endl;
    std::cin >> name;
    Warehouse* temp = warehouse_inventory;
    Warehouse* current = warehouse_inventory;
    // It iterates through the warehouse inventory and removes the stock from the asked resource
    while(current->name != name){
        if(current->next == temp){
            std::cout << "Resource not found" << std::endl;
            return;
        }
        current = current->next;
    }
    // remove the node from the warehouse inventory
    current->prev->next = current->next;
    current->next->prev = current->prev;
    std::cout << "Resource removed successfully" << std::endl;
}

void staff_menu(){
    // This is a function that prints the staff menu, with consist of the staff options
    // It receives nothing
    // Returns nothing
    bool exit_menu = false;
    string staff_id;
    std::cout << "Welcome to the staff menu" << std::endl;
    while(exit_menu == false){
        std::cout << "1. Register user" << std::endl;
        std::cout << "2. Modify user" << std::endl;
        std::cout << "3. Remove user" << std::endl;
        std::cout << "4. Register hours" << std::endl;
        std::cout << "5. Consult salary" << std::endl;
        std::cout << "6. Print staff" << std::endl;
        std::cout << "7. Exit and return to the main menu" << std::endl;
        int option;
        std::cin >> option;
        system("clear");
        switch (option) {
            case 1:
                // Call the add_staff function, that adds a staff member to the staff roster list
                add_staff();
                break;
            case 2:
                // Call the modify_staff function, that modifies a staff member of the staff roster list
                std::cin.ignore();
                std::cout << "Type the id of the employee you want to modify: ";
                std::cin >> staff_id;
                modify_staff(staff_id);
                break;
            case 3:
                // Call the remove_staff function, that removes a staff member of the staff roster list
                remove_staff();
                break;
            case 4:
                // Call the register_hours_menu function, that prints the register hours menu
                register_hours_menu(staff_roster);
                break;
            case 5:
                // Call the consult_salary function, that prints the consult salary menu
                consult_salary(staff_roster);
                break;
            case 6:
                // Call the print_linked_list function, that prints the staff roster list
                print_linked_list(staff_roster);
                break;
            case 7:
                // Exit the menu
                exit_menu = true;
                return;
            default:
                // If the option is invalid, print an error message
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}

void inventory_menu(){
    // This is a function that prints the inventory menu, with consist of the inventory options
    // It receives nothing
    // Returns nothing
    int option;
    bool exit_menu = false;
    string answer;
    string answer2;
    string answer3;
    std::cout << "Welcome to the inventory menu" << std::endl;
    while(exit_menu == false){
        std::cout << "1. Register a whole category" << std::endl;
        std::cout << "2. Register a new product to a category" << std::endl;
        std::cout << "3. Register a new resource to a stage" << std::endl;
        std::cout << "4. Register a new stage to a product" << std::endl;
        std::cout << "5. Consult category status" << std::endl;
        std::cout << "6. Print inventory" << std::endl;
        std::cout << "7. Exit and return to the main menu" << std::endl;
        std::cin >> option;
        std::cin.ignore();
        system("clear");
        switch (option) {
            case 1:
                // Call the complete_category function, that completes a category of the inventory
                std::cout << "Type your category name:  " << std::endl;
                std::getline(std::cin, answer);
                complete_category(answer);
                break;
            case 2:
                // Call the append_product function, that appends a product to a category
                std::cout << "Type the name of the category: " << std::endl;
                std::getline(std::cin, answer);
                append_product(answer);
                break;
            case 3:
                // Call the append_resource function, that appends a resource to a stage
                std::cout << "Type the name of the category: " << std::endl;
                std::getline(std::cin, answer3);
                std::cout << "Type the name of the stage: " << std::endl;
                std::getline(std::cin, answer);
                std::cout << "Type the name of the product: " << std::endl;
                std::getline(std::cin, answer2);
                append_resource(answer3, answer, answer2);
                break;
            case 4:
                // Call the add_stage function, that adds a stage to a product
                std::cout << "Type the name of the category: " << std::endl;
                std::getline(std::cin, answer2);
                std::cout << "Type the name of the product: " << std::endl;
                std::cin >> answer;
                add_stage(answer2, answer);
                break;
            case 5:
                // Call the advance_stage function, that advances the stage of a product
                advance_stage();
                break;
            case 6:
                // Call the print_whole_categories function, that prints the inventory
                std::cout << "----* Warehouse *----" << std::endl;
                print_circular_linked_list(warehouse_inventory);
                std::cout << "----* Inventory *----" << std::endl;
                print_whole_categories();
                break;
            case 7:
                // Exit the menu
                exit_menu = true;
                return;
            default:
                // If the option is invalid, print an error message
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
    // Clear the terminal only works on linux
    system("clear");
}

void warehouse_menu(){
    bool exit_menu = false;
    int option{0};
    std::cout << "Welcome to the warehouse menu" << std::endl;
    while(!exit_menu){
        std::cout << "1. Add new stock" << std::endl;
        std::cout << "2. Add stock" << std::endl;
        std::cout << "3. Remove stock" << std::endl;
        std::cout << "4. Print stock" << std::endl;
        std::cout << "5. Exit and return to the main menu" << std::endl;
        std::cin >> option;
        switch (option) {
            case 1:
                // Call the append_new_stock function, that appends a new stock to the warehouse inventory
                append_new_stock();
                break;
            case 2:
                // Call the add_stock function, that adds stock to the warehouse inventory
                add_stock();
                break;
            case 3:
                // Call the remove_stock function, that removes stock from the warehouse inventory
                remove_stock();
                break;
            case 4:
                // Call the print_circular_linked_list function, that prints the warehouse inventory
                print_circular_linked_list(warehouse_inventory);
                break;
            case 5:
                // Exit the menu
                exit_menu = true;
                break;
            default:
                // If the option is invalid, print an error message
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
    // Clear the terminal only works on linux
    system("clear");
}

void menu(){
    int option;
    bool exit_menu = false;
    while(exit_menu == false){
        std::cout << "Welcome to Chakalitos.SA" << std::endl;
        std::cout << "1. Staff" << std::endl;
        std::cout << "2. Inventory" << std::endl;
        std::cout << "3. Warehouse" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> option;
        switch (option) {
            case 1:
                // Call the staff_menu function, that prints the staff menu and clears the terminal
                system("clear");
                staff_menu();
                break;
            case 2:
                // Call the inventory_menu function, that prints the inventory menu and clears the terminal
                system("clear");
                inventory_menu();
                break;
            case 3:
                // Call the warehouse_menu function, that prints the warehouse menu and clears the terminal
                system("clear");
                warehouse_menu();
                break;
            case 4:
                // Exit the menu
                exit_menu = true;
                break;
            default:
                // If the option is invalid, print an error message
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}

void add_stock(string name) {
    // This is a function that adds stock to a resource
    // It receives the name of the resource
    // Returns nothing
    int amount{};
    Warehouse* current = warehouse_inventory;
    // Iterate through the warehouse inventory and add the stock to the asked resource
    while (current) {
        if (current->name == name) {
            break;
        }
        current = current->next;
    }
    std::cout << "Type the amount of stock you want to add: " << std::endl;
    std::cin >> amount;
    // Add the stock to the resource
    current->quantity += amount;
    std::cout << "Stock added successfully" << std::endl;
}

void append_stock() {
    // This is a function that appends a new stock to the warehouse inventory
    // It receives nothing
    // Returns nothing
    string name;
    int amount{};
    std::cout << "Type the name of the product you want to add stock: " << std::endl;
    std::cin >> name;
    std::cout << "Type the amount of stock you want to add: " << std::endl;
    std::cin >> amount;
    // Create a new warehouse node and append it to the warehouse inventory
    Warehouse* new_stock = new Warehouse(name, amount);

    double_circular_append_end(warehouse_inventory, new_stock);
}

void set(){
    // Create a Smurfcat category with all the products and stages
    Category* smurfcat = new Category("Smurfcat");
    Product* smurfcat_product = new Product("Default", "01");
    Stage* smurfcat_stage = new Stage("Initial", false);
    Resource* smurfcat_resource = new Resource("White paint", 5);
    Resource* smurfcat_resource2 = new Resource("Blue paint", 5);
    Resource* smurfcat_resource3 = new Resource("Box", 5);
    Resource* smurfcat_resource4 = new Resource("Bubble wrap", 5);
    lineal_append_end(smurfcat_stage->resources, smurfcat_resource);
    lineal_append_end(smurfcat_stage->resources, smurfcat_resource2);
    lineal_append_end(smurfcat_stage->resources, smurfcat_resource3);
    lineal_append_end(smurfcat_stage->resources, smurfcat_resource4);
    lineal_append_end(smurfcat_product->current_stage, smurfcat_stage);
    lineal_append_end(smurfcat->products, smurfcat_product);
    append_category(smurfcat);
    
    // Create a StrawberryElephant category with all the products and stages
    Category* Straberry = new Category("StrawberryElephant");
    Product* Straberry_product = new Product("Default", "02");
    Stage* Straberry_stage = new Stage("Initial", false);
    Resource* Straberry_resource = new Resource("Red paint", 5);
    Resource* Straberry_resource2 = new Resource("Green paint", 5);
    Resource* Straberry_resource3 = new Resource("Box", 5);
    Resource* Straberry_resource4 = new Resource("Bubble wrap", 5);
    Resource* Straberry_resource5 = new Resource("Strawberry", 5);
    lineal_append_end(Straberry_stage->resources, Straberry_resource);
    lineal_append_end(Straberry_stage->resources, Straberry_resource2);
    lineal_append_end(Straberry_stage->resources, Straberry_resource3);
    lineal_append_end(Straberry_stage->resources, Straberry_resource4);
    lineal_append_end(Straberry_stage->resources, Straberry_resource5);
    lineal_append_end(Straberry_product->current_stage, Straberry_stage);
    lineal_append_end(Straberry->products, Straberry_product);
    append_category(Straberry);
}

int main(){
    // Create the staff roster list
	Staff* first_staff = new Staff("1", "boss", "experienced", "managment", "administration"); //Create the first employee, the boss
	Staff* second_staff = new Staff("2", "employee", "experienced", "production", "production"); //Create the second employee, the employee
	Staff* third_staff = new Staff("3", "boss", "experienced", "managment", "administration"); //Create the first employee, the boss
	Staff* fourth_staff = new Staff("4", "intern", "experienced", "managment", "maintenance"); //Create the first employee, the boss
	Staff* fifth_staff = new Staff("5", "boss", "experienced", "managment", "production"); //Create the first employee, the boss

    // Append the staff members to the staff roster list
    double_append_end(staff_roster,first_staff);
    double_append_end(staff_roster,second_staff);
    double_append_end(staff_roster,third_staff);
    double_append_end(staff_roster,fourth_staff);
    double_append_end(staff_roster,fifth_staff);
    
    // Create the warehouse inventory
    Warehouse *plastic = new Warehouse("Plastic", 50);
    Warehouse *metal = new Warehouse("Cloth", 30);
    Warehouse *wood = new Warehouse("Wood", 20);
    Warehouse *blue_paint = new Warehouse("Blue paint", 25);
    Warehouse *white_paint = new Warehouse("White paint", 25);
    Warehouse *gold_paint = new Warehouse("Gold paint", 25);
    Warehouse *purple_paint = new Warehouse("Purple paint", 25);
    Warehouse *red_paint = new Warehouse("Red paint", 25);
    Warehouse *green_paint = new Warehouse("Green paint", 25);
    Warehouse *black_paint = new Warehouse("Black", 25);
    Warehouse *brown_paint = new Warehouse("Brown paint", 25);
    Warehouse *brown_mushroom = new Warehouse("Brown mushroom", 10);
    Warehouse *box = new Warehouse("Box", 70);
    Warehouse *sticker = new Warehouse("Sticker", 35);
    Warehouse *bubble_wrap = new Warehouse("Bubble wrap", 40);
    Warehouse *platinum_mushroom = new Warehouse("Platinum mushroom", 10);
    Warehouse *silver_box = new Warehouse("Silver box", 5);
    Warehouse *strawberry = new Warehouse("Strawberry", 30);
    Warehouse *leather = new Warehouse("Leather", 20);
    Warehouse *horn = new Warehouse("Horn", 15);
    Warehouse *leaf = new Warehouse("Leaf", 10);
    Warehouse *steel = new Warehouse("Steel", 20);
    Warehouse *lightsaber = new Warehouse("Lightsaber", 10);
    Warehouse *sword = new Warehouse("Sword", 10);
    Warehouse *shield = new Warehouse("Shield", 10);
    Warehouse *wheat = new Warehouse("Wheat", 40);
    Warehouse *stick = new Warehouse("Stick", 60);

    // Append the resources to the warehouse inventory
    double_circular_append_end(warehouse_inventory, plastic);
    double_circular_append_end(warehouse_inventory, metal);
    double_circular_append_end(warehouse_inventory, wood);
    double_circular_append_end(warehouse_inventory, blue_paint);
    double_circular_append_end(warehouse_inventory, white_paint);
    double_circular_append_end(warehouse_inventory, gold_paint);
    double_circular_append_end(warehouse_inventory, purple_paint);
    double_circular_append_end(warehouse_inventory, red_paint);
    double_circular_append_end(warehouse_inventory, green_paint);
    double_circular_append_end(warehouse_inventory, black_paint);
    double_circular_append_end(warehouse_inventory, brown_paint);
    double_circular_append_end(warehouse_inventory, brown_mushroom);
    double_circular_append_end(warehouse_inventory, box);
    double_circular_append_end(warehouse_inventory, sticker);
    double_circular_append_end(warehouse_inventory, bubble_wrap);
    double_circular_append_end(warehouse_inventory, platinum_mushroom);
    double_circular_append_end(warehouse_inventory, silver_box);
    double_circular_append_end(warehouse_inventory, strawberry);
    double_circular_append_end(warehouse_inventory, leather);
    double_circular_append_end(warehouse_inventory, horn);
    double_circular_append_end(warehouse_inventory, leaf);
    double_circular_append_end(warehouse_inventory, steel);
    double_circular_append_end(warehouse_inventory, lightsaber);
    double_circular_append_end(warehouse_inventory, sword);
    double_circular_append_end(warehouse_inventory, shield);
    double_circular_append_end(warehouse_inventory, wheat);
    double_circular_append_end(warehouse_inventory, stick);

    // Call the set function, that creates the categories, products and stages
    set();
    // Call the menu function, that prints the main menu
    menu();
    // Exit the program
    return 0;
}

