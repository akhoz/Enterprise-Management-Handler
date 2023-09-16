#include <Staff.hh>
#include <string>

Staff::Staff(string staff_id, string job_title, string salary_bonuses, string job_performed, string employment_sector) {
    //This is the constructor of the Staff struct, it receives all the information of the employee and creates the object, returns nothing
    this->id = staff_id;
    this->job_title = job_title;
    this->salary_bonuses = salary_bonuses;
    this->job_performed = job_performed;
    this->employment_sector = employment_sector;
    this->boss = nullptr;
    this->workdays = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
}

Staff::Staff() {
    //This is an empty constructor of the Staff struct, it creates an empty object, returns nothing
    this->id = "";
    this->job_title = "";
    this->salary_bonuses = "";
    this->job_performed = "";
    this->employment_sector = "";
    this->boss = nullptr;
    this->workdays = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
}

