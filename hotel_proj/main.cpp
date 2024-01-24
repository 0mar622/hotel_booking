#include <iostream>
#include "hotel.h"

using namespace std;

int main()
{
    cout << "Hotel Management System\n" << endl;

    Hotel *htl = new Hotel(10, "Mini Lodge", "Fremont");
    htl->setRoomProps(101, "single", 99.99);
    htl->setRoomProps(102, "triple", 109.99);
    htl->setRoomProps(103, "single", 89.99);
    htl->setRoomProps(104, "single", 79.99);
    htl->setRoomProps(105, "triple", 119.99);
    htl->setRoomProps(106, "double", 104.99);
    htl->setRoomProps(107, "triple", 119.99);
    htl->setRoomProps(108, "double", 99.99);
    htl->setRoomProps(109, "double", 104.99);
    htl->setRoomProps(110, "single", 99.99);

    string style;
    int startDate;
    int endDate;
    Room *r;

    int total = htl->getRoomCount();
    cout << total << " rooms in the hotel\n";

    while(true)
    {
        cout << "Pick a room style (single, double, triple): ";
        cin >> style;

        cout << "Enter the date to check in: ";
        cin >> startDate;

        cout << "Enter the date to check out: ";
        cin >> endDate;

        r = htl->findAvailableRoom(style, startDate, endDate);

        if(r != nullptr)
        {
            htl->setOccupy(r->getRoomNum(), startDate, endDate);
            cout << r->getRoomNum() << endl;
        }
        else
        {
            cout << "No room of " << style << " found\n";
        }
    }

    return 0;
}
