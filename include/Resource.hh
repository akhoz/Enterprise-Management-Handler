#pragma once
#include <string>

using std::string;

class Resource {
public:
	string name; //Name of the resource
    int quantity; //Quantity of the resource
	Resource* next; //Next resource in the list
    
    Resource(string resource_name, int quantity, Resource* next); //Constructor
    Resource(); //Constructor
};
