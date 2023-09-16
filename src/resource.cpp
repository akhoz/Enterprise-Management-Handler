#include <Resource.hh>

Resource::Resource(string resource_name, Resource* next) {
    //This is a constructor of the Resource struct, it creates an object with the given parameters, returns nothing
    this->name = resource_name;
    this->next = next;
}

Resource::Resource() {
    //This is an empty constructor of the Resource struct, it creates an empty object, returns nothing
    this->name = "";
    this->next = nullptr;
}
