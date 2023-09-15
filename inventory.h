#pragma once
#include <iostream>
#include <string>
using std::string;

class Category; //Forward declaration of the Inventory struct
class Product; //Forward declaration of the Product struct
class Stage; //Forward declaration of the Stage struct
class Resource; //Forward declaration of the Resource struct


class Category {
public:
	string category_name; //Category of the product
	Product* products; //Products of the category
	Category* next; //Next product in the list

	Category() {
		//This is an empty constructor of the Inventory struct, it creates an empty object, returns nothing
		this->category_name = "";
		this->products = nullptr;
		this->next = nullptr;
	}
};

class Product {
public:
	string serial_number; //Unique identifier of the product
	Stage* current_stage; //Current stage of the product
	Product* next; //Next product in the list	

	Product() {
		//This is an empty constructor of the Product struct, it creates an empty object, returns nothing
		this->serial_number = "";
		this->current_stage = nullptr;
		this->next = nullptr;
	}
};

class Stage {
public:
	string stage_name; //Name of the stage
	bool completed; //If the stage is completed or not
	Resource* resources; //Resources used in the stage
	Stage* next; //Next stage in the list

	Stage() {
		//This is an empty constructor of the Stage struct, it creates an empty object, returns nothing
		this->stage_name = "";
		this->completed = false;
		this->resources = nullptr;
		this->next = nullptr;
	}
};

class Resource {
public:
	string resource_name; //Name of the resource
	Resource* next; //Next resource in the list

	Resource() {
		//This is an empty constructor of the Resource struct, it creates an empty object, returns nothing
		this->resource_name = "";
		this->next = nullptr;
	}
};
