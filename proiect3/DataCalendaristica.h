#pragma once
#include <iostream>

class DataCalendaristica {
private:
    int zi;
    int luna;
    int an;
public:
    DataCalendaristica(int zi = -1,int luna = -1,int an = -1)
        :zi(zi),luna(luna),an(an){}
    ~DataCalendaristica(){std::cout<<"Destructor DataCalendaristica\n";}

    DataCalendaristica(const DataCalendaristica& d);
    DataCalendaristica& operator=(const DataCalendaristica& d);
    friend std::ostream& operator<<(std::ostream& os,const DataCalendaristica& d);
};
