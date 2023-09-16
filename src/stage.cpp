#include <Stage.hh>

Stage::Stage(string stage_name, bool completed, Resource* resources, Stage* next) {
    //This is a constructor of the Stage struct, it creates an object with the given parameters, returns nothing
    this->stage_name = stage_name;
    this->completed = completed;
    this->resources = resources;
    this->next = next;
}

Stage::Stage() {
    //This is an empty constructor of the Stage struct, it creates an empty object, returns nothing
    this->stage_name = "";
    this->completed = false;
    this->resources = nullptr;
    this->next = nullptr;
}
