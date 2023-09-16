#include <Workday.hh>

Workday::Workday(string start_time, string end_time, int worked_hours, bool is_holiday, bool is_weekend, Workday* next) {
    //This is a constructor of the Workday struct, it creates an object with the given parameters, returns nothing
    this->start_time = start_time;
    this->end_time = end_time;
    this->worked_hours = worked_hours;
    this->is_holiday = is_holiday;
    this->is_weekend = is_weekend;
    this->next = next;
}

Workday::Workday() {
    //This is an empty constructor of the Workday struct, it creates an empty object, returns nothing
    this->start_time = "";
    this->end_time = "";
    this->worked_hours = 0;
    this->is_holiday = false;
    this->is_weekend = false;
    this->next = nullptr;
}
