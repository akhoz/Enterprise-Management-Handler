#pragma once

#include <string>
#include <iostream>

using std::string;

class Warehouse{
    public:
        string name;
        int quantity;
        Warehouse* next;
        Warehouse* prev;
        
        Warehouse(string resource_name, int quantity);
        Warehouse();

        friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse) {
            os << "Warehouse: " << warehouse.name << std::endl;
            os << "Quantity: " << warehouse.quantity << std::endl;
            return os;
        }; //Overload of the << operator
};
