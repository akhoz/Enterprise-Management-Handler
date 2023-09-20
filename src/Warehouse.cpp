#include "Warehouse.hh"

Warehouse::Warehouse(string name, int quantity){
    this->name = name;
    this->quantity = quantity;
    this->next = nullptr;
    this->prev = nullptr;
}

Warehouse::Warehouse(){
    this->name = "";
    this->quantity = 0;
    this->next = nullptr;
    this->prev = nullptr;
}
