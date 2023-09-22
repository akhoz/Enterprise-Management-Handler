#pragma once
#include <string>
#include <Resource.hh>

using std::string;
class Stage {
public:
	string stage_name; //Name of the stage
	bool completed; //If the stage is completed or not
	Resource* resources; //Resources used in the stage
	Stage* next; //Next stage in the list
    
    Stage(string stage_name, bool completed); //Constructor
    Stage(); //Constructor
};

