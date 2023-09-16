#pragma once
#include <string>
#include <Stage.hh>

using std::string;

class Product {
public:
    string name;
	string serial_number; //Unique identifier of the product
	Stage* current_stage; //Current stage of the product
	Product* next; //Next product in the list	

    Product(string name, string serial_number, Stage* current_stage, Product* next);
    Product();
};

