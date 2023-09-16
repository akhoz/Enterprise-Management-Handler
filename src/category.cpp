#include <Category.hh>

Category::Category() {
    //This is an empty constructor of the Inventory struct, it creates an empty object, returns nothing
    this->category_name = "";
    this->products = nullptr;
    this->next = nullptr;
}
Category::Category(string category_name, Product* products, Category* next) {
    //This is a constructor of the Inventory struct, it creates an object with the given parameters, returns nothing
    this->category_name = category_name;
    this->products = products;
    this->next = next;
}

