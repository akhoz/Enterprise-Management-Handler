#pragma once
#include <string>
#include <iostream>

using std::string;

class Resource {
public:
	string name; //Name of the resource
    int quantity; //Quantity of the resource
	Resource* next; //Next resource in the list
    
    Resource(string resource_name, int quantity, Resource* next); //Constructor
    Resource(); //Constructor

    friend std::ostream& operator<<(std::ostream& os, const Resource& resource) {
        os << "Resource: " << resource.name << std::endl;
        os << "Quantity: " << resource.quantity << std::endl;
        return os;
    }; //Overload of the << operator
};
