#pragma once
#include <string>
#include <Product.hh>


class Category {
public:
	string category_name; //Category of the product
	Product* products; //Products of the category
	Category* next; //Next product in the list
    
    Category(string category_name, Product* products, Category* next); //Constructor
    Category(); //Constructor
    
};

