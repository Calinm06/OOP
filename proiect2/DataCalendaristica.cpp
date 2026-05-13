#include <iostream>
#include "DataCalendaristica.h"

DataCalendaristica::DataCalendaristica(const DataCalendaristica &d) {
    zi = d.zi;
    luna = d.luna;
    an = d.an;
}

DataCalendaristica &DataCalendaristica::operator=(const DataCalendaristica &d) {
    if (this == &d)
        return *this;
    zi = d.zi;
    luna = d.luna;
    an = d.an;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const DataCalendaristica& d) {
    os<<d.zi<<"/"<<d.luna<<"/"<<d.an<<"\n";
    return os;
}
