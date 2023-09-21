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

void assign_boss(string new_staff_id) {
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
	std::cout << "Id: ";
	std::cin >> new_staff->id;
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
		assign_boss(new_staff->id); //Assign the boss of the employee

	std::cout << "Employee added successfully" << std::endl;
}

void remove_staff() {
	//This is a function that removes an employee from the staff roster
	//Recieves nothing
	//Returns nothing

	string staff_id;
	std::cout << "Type the id of the employee you want to remove: ";
	std::cin >> staff_id;

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
		std::cin >> staff_to_modify->id;
	}
	else if (property_to_change == "job_title") { //If the property to change is the job title, change the job title of the employee
		std::cout << "New job title: ";
		std::cin >> staff_to_modify->job_title;
	}
	else if (property_to_change == "salary_bonuses") { //If the property to change is the salary bonuses, change the salary bonuses of the employee
		std::cout << "New salary bonuses: ";
		std::cin >> staff_to_modify->salary_bonuses;
	}
	else if (property_to_change == "job_performed") { //If the property to change is the job performed, change the job performed of the employee
		std::cout << "New job performed: ";
		std::cin >> staff_to_modify->job_performed;
	}
	else if (property_to_change == "employment_sector") { //If the property to change is the employment sector, change the employment sector of the employee
		std::cout << "New employment sector: ";
		std::cin >> staff_to_modify->employment_sector;
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
    Staff* current = staff_roster;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void print_workday(Staff*& staff) {
    Workday* current = staff->workdays;
    while (current) {
        std::cout << current << std::endl;
        current = current->next;
    }
}


int worked_hours(const string& start, const string& end) {
	tm parsed_start = parse_hour(start);
	tm parsed_end = parse_hour(end);

	time_t t_inicio = mktime(&parsed_start);
	time_t t_fin = mktime(&parsed_end);

	int seconds = difftime(t_fin, t_inicio);
	int hours = seconds / 3600;
	return hours;

}

void registerHours(Staff*& staff) {
	Workday* workday = new Workday();
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

void set_salary(Staff*& person) {
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


void register_hours_menu(Staff*& staff) {
    std::cout << "Register hours menu" << std::endl;
    std::cout << "Type your id: ";
    string id;
    std::cin >> id;
    Staff* staff_member = find_staff_by_id(id);
    if (!staff_member) {
        std::cout << "Staff member not found" << std::endl;
        return;
    }
    registerHours(staff_member);
}

void consult_salary(Staff*& List) {
    std::cout << "Consult salary menu" << std::endl;
    std::cout << "Type your id: ";
    string id;
    std::cin >> id;
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
    while (current->next) { //While the current node is not null, move to the next node
        current = current->next;
    }
    current->next = resource_to_add; //The next node of the current node is the resource to add
}

//------> Evaluate if this functions will stay or we will replace the template conversor <------

void complete_category(const string name){
    // This function can be factored into several smaller functions 
    Category *new_category = new Category();
    Product *new_product = new Product();
    Stage *new_stage = new Stage();
    Resource *component_list = nullptr;
    bool completed = false;

    std::cout << "Type the product you want to register: " << std::endl;
    std::cin >> new_product->name;
    std::cout << "Type the serial number of the product: " << std::endl;
    std::cin >> new_product->serial_number;
    std::cout << "Type the name of the stage: " << std::endl;
    std::cin >> new_stage->stage_name;
    std::cout << "Type if the stage is completed (true/false): " << std::endl;
    std::cin >> std::boolalpha >> completed;
    std::cin.ignore();
    std::cout << "How many resources does the stage have? " << std::endl;
    int amount;
    std::cin >> amount;
    for (int i = 0; i < amount; i++) {
        Resource *new_resource = new Resource();
        std::cout << "Type the name of the resource needed to build the product" << std::endl;
        std::cin >> new_resource->name;
        std::cout << "Type the quantity of the resource needed to build the product" << std::endl;
        std::cin >> new_resource->quantity;
        // Add the Resource to the components list
        add_resources(component_list, new_resource);

    }
    append_resources(new_stage, component_list);
    // Add the stage to the product
    new_product->current_stage = new_stage;
    // Add the product to the category
    append_product_to_category(new_category, new_product);
    // Add the category to the inventory
    append_category(new_category);
    return;
}

Category* find_category(const string& category_name) {
    Category* current = inventory;
    while (current) {
        if (current->category_name == category_name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Product* find_product_by_serial_number(const string& serial_number, string category_name) {
    Category *current = find_category(category_name);
    if (!current) {
        return nullptr;
    }
    Product* current_product = current->products;
    while (current_product) {
        if (current_product->serial_number == serial_number) {
            return current_product;
        }
        current_product = current_product->next;
    }
    return nullptr;
}

bool check_progress(string category_name, string serial_number){
    Stage* current_stage = find_product_by_serial_number(serial_number, category_name)->current_stage;
    while(current_stage){
        Resource* current_resource = current_stage->resources;
        Warehouse* current_warehouse = warehouse_inventory;
        while(current_resource){
            while(current_warehouse){
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
    std::cout << "The product is ready for the next stage" << std::endl;
    return true;
}

void reduce_warehouse(string category_name, string serial_number) {
    Product* product = find_product_by_serial_number(serial_number, category_name);
    Stage* current_stage = product->current_stage;

    while (current_stage->completed) {
        current_stage = current_stage->next;
    }

    Resource* current_resource = current_stage->resources;
    Warehouse* current_warehouse = warehouse_inventory;

    while (current_resource) {
        while (current_warehouse) {
            if (current_resource->name == current_warehouse->name) {
                current_warehouse->quantity -= current_resource->quantity;
            }
            current_warehouse = current_warehouse->next;
        }
        current_resource = current_resource->next;
    }

}

void reduceResources(){
    std::cout << "Reducing resources" << std::endl;
}

void advance_stage() {
    std::cout << "Type the name of the category: " << std::endl;
    string category_name;
    std::cout << "Type the serial number of the product: " << std::endl;
    string serial_number;
    std::cin >> category_name;
    if(!check_progress(category_name, serial_number)){
        std::cout << "The product is not ready for the next stage" << std::endl;
        return;
    }
    else{
        std::cout << "The product is ready for the next stage" << std::endl;
        std::cout << "Do you want to advance the stage? (true/false)" << std::endl;
        bool answer;
        std::cin >> std::boolalpha >> answer;
        if(!answer){
            return;
        }
        else{
            std::cout << "Reducing resources" << std::endl;
        reduce_warehouse(category_name, serial_number);
        }
    }
    
}



void menu(Staff*& list){
    int option;
    string answer;
    std::cout << "Welcome to the Staff menu" << std::endl;
    std::cout << "1. Register user" << std::endl;
    std::cout << "2. Register Category and Product" << std::endl;
    std::cout << "3. Consult category status" << std::endl;
    std::cout << "4. Register user worked hours" << std::endl;
    std::cout << "5. Consult salary" << std::endl;
    std::cout << "6. Prints" << std::endl;
    std::cout << "10. Exit" << std::endl;
    std::cin >> option;

    switch (option) {
        case 1:
            add_staff();
            break;
        case 2:
            std::cout << "Type the name of the category: " << std::endl;
            std::cin >> answer;
            complete_category(answer);
            break;
        case 3:
            advance_stage();

            break;
        case 4:
            register_hours_menu(list);
            /* system("clear"); */
            break;
        case 5:
            consult_salary(list);
            break;
        case 6:
            std::cout << "Staff Members" << std::endl;
            print_linked_list(list);
            std::cout << "Warehouse" << std::endl;
            print_circular_linked_list(warehouse_inventory);
            std::cout << "Inventory" << std::endl;
            print_linked_list(inventory);
            /* system("clear"); */
            break;
        case 10:
            exit_menu = true;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }

}

void add_stock(string name) {
    int amount{};
    Warehouse* current = warehouse_inventory;
    while (current) {
        if (current->name == name) {
            break;
        }
        current = current->next;
    }
    std::cout << "Type the amount of stock you want to add: " << std::endl;
    std::cin >> amount;
    current->quantity += amount;
    std::cout << "Stock added successfully" << std::endl;
}

void append_stock() {
    string name;
    int amount{};
    std::cout << "Type the name of the product you want to add stock: " << std::endl;
    std::cin >> name;
    std::cout << "Type the amount of stock you want to add: " << std::endl;
    std::cin >> amount;
    Warehouse* new_stock = new Warehouse(name, amount);

    double_circular_append_end(warehouse_inventory, new_stock);
}

int main(){
	Staff* first_staff = new Staff("1", "boss", "experience", "managment", "administration"); //Create the first employee, the boss
	Staff* second_staff = new Staff("2", "employee", "experience", "production", "production"); //Create the second employee, the employee
	Staff* third_staff = new Staff("3", "boss", "experience", "managment", "administration"); //Create the first employee, the boss
	Staff* fourth_staff = new Staff("4", "intern", "experience", "managment", "maintenance"); //Create the first employee, the boss
	Staff* fifth_staff = new Staff("5", "boss", "experience", "managment", "production"); //Create the first employee, the boss
    double_append_end(staff_roster,first_staff);
    double_append_end(staff_roster,second_staff);
    double_append_end(staff_roster,third_staff);
    double_append_end(staff_roster,fourth_staff);
    double_append_end(staff_roster,fifth_staff);

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

    Category *first_category = new Category("Smurf Cat");
    first_category->products = new Product("Default", "1");
    first_category->products->current_stage = new Stage("Initial", false);
    Resource *first_resource = new Resource("blue_paint", 1);
    Resource *second_resource = new Resource("Blue paint", 1);


    while (!exit_menu) {
        menu(staff_roster);
    }
    return 0;
}

