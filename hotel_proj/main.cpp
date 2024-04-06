#include <iostream>
#include "hotel.h"
#include <cstdlib>
#include <fstream>
using namespace std;

int main()
{
    cout << "Hotel Management System\n" << endl;

    Hotel *htl = new Hotel(10, "Mini Lodge", "Fremont");
    htl->setRoomProps(101, "single", 99.99);
    htl->setRoomProps(102, "triple", 109.99);
    htl->setRoomProps(103, "single", 89.99);
    htl->setRoomProps(104, "single", 79.99);
   // htl->setRoomProps(105, "triple", 119.99);
    htl->setRoomProps(106, "double", 104.99);
   // htl->setRoomProps(107, "triple", 119.99);
    htl->setRoomProps(108, "double", 99.99);
    htl->setRoomProps(109, "double", 104.99);
    htl->setRoomProps(110, "single", 99.99);

    string style;
    int startDate;
    int endDate;
    int num_of_nights;
    int num_keys;
    int cancel_num;



    Room *r;
    htl->readGuestRecord();

    int total = htl->getRoomCount();
    cout << total << " rooms in the hotel\n";


    while(true)
    {
       // htl->readGuestRecord();

        cout << "Pick a room style (single, double, triple): ";
        cin >> style;

        cout << "Enter the date to check in: ";
        cin >> startDate;

        cout << "Enter the date to check out: ";
        cin >> endDate;


        r = htl->findAvailableRoom(style, startDate, endDate);

        if(r != nullptr)
        {
            htl->addGuestRecord(r->getRoomNum(), startDate, endDate);
            cout << "You got Room " << r->getRoomNum() << endl;
            num_of_nights = endDate - startDate;
            cout << "Total Cost of stay: $" << num_of_nights * r->getPrice() << endl;
            cout << "\n";
        }

        else
        {
            cout << "No room of " << style << " found for dates " << startDate << " to " << endDate << endl;
        }


        // Options to Cancel or View bookings, or just keep going
        cout << "Do you want to cancel booking? (1. Yes, 2. No, 3. View Bookings, 4. Exit Program)\n";
        cin >> cancel_num;

        if(cancel_num == 1)
        {
            cout << "All the bookings:\n";
            htl->printAllRecords();
            cout << "Provide start date for cancellation: ";
            cin >> startDate;

            cout << "Provide end date for cancellation: ";
            cin >> endDate;



            htl->removeGuestRecord(r->getRoomNum(), startDate, endDate);

            cout << "Booking of dates " << startDate << " to " << endDate << " for Room " << r->getRoomNum() << " cancelled.\n";
        }

        else if(cancel_num == 2)
        {
            continue;
        }

        else if(cancel_num == 3)
        {
            cout << "All the bookings:\n";
            htl->printAllRecords();
        }

        else if(cancel_num == 4)
        {
            break;
        }

        else
        {
            cout << "Invalid option\n";
        }

      //  currDate++;
    }

    return 0;
}
