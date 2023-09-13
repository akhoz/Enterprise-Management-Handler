#include <iostream>
#include <string>
#include "staff_roster.h"
using std::string;

template <typename T> //This is a template function, it can take any type of data, this is used avoid code duplication, such as having to write the same function for different structs or linked lists

void append_end(T*& linked_list, T*& element_to_append) {
	//This is a function that appends an element to the end of a linked list
	//It receives a pointer to the linked list and a pointer to the element to append
	//Returns nothing

	if (!element_to_append) { //If the element to append is null
		return; //Return nothing, this is in order to avoid appending null elements
	}

	if (!linked_list) { //If the linked list is empty
			linked_list = element_to_append; //Set the new element as the first node of the linked list
			return; //Return nothing
		}

	T* current = linked_list; //Create a pointer to the current node
	while (current->next) { //While the current node is not null
			current = current->next; //Move to the next node
		}
	current->next = element_to_append; //Set the next node to the new element
}

int main() {

}