#include <Product.hh>

Product::Product(string name,string serial_number, Stage* current_stage, Product* next) {
    //This is a constructor of the Product struct, it creates an object with the given parameters, returns nothing
    this->name = name;
    this->serial_number = serial_number;
    this->current_stage = current_stage;
    this->next = next;
}

Product::Product() {
    //This is an empty constructor of the Product struct, it creates an empty object, returns nothing
    this->serial_number = "";
    this->current_stage = nullptr;
    this->next = nullptr;
}
