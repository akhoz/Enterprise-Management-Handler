#pragma once
#include <string>
#include <iostream>
#include <Stage.hh>

using std::string;

class Product {
public:
    string name;
	string serial_number; //Unique identifier of the product
	Stage* current_stage; //Current stage of the product
	Product* next; //Next product in the list	

    Product(string name, string serial_number);
    Product();

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << "Product: " << product.name << std::endl;
        os << "Serial number: " << product.serial_number << std::endl;
        os << "Current stage: " << product.current_stage->stage_name << std::endl;
        if (product.current_stage->completed) {
            os << "Current stage state: completed" << std::endl;
        } else {
            os << "Current stage state: in process" << std::endl;
        }
        return os;
    }; //Overload of the << operator
};

