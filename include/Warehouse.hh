#pragma once

#include <string>


using std::string;

class Warehouse{
    public:
        string name;
        int quantity;
        Warehouse* next;
        Warehouse* prev;
        
        Warehouse(string resource_name, int quantity);
        Warehouse();

};
