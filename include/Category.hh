#pragma once
#include <string>
#include <iostream>
#include <Product.hh>


class Category {
public:
	string category_name; //Category of the product
	Product* products; //Products of the category
	Category* next; //Next product in the list
    
    Category(string category_name); //Constructor
    Category(); //Constructor

	friend std::ostream& operator<<(std::ostream& os, const Category& category) {
		os << "Category: " << category.category_name << std::endl;
		os << "Products: " << std::endl;
        return os;
	}; //Overload of the << operator
    

    
};

