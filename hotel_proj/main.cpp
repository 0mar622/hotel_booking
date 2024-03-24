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
    htl->setRoomProps(105, "triple", 119.99);
    htl->setRoomProps(106, "double", 104.99);
    htl->setRoomProps(107, "triple", 119.99);
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

    int total = htl->getRoomCount();
    cout << total << " rooms in the hotel\n";

    char tokens[10000];
    char rNum[3];

    #if 0
    ifstream bookedDates;
    bookedDates.open("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings_record.txt");
    if(!bookedDates.is_open())
    {
        cout << "ERROR ACCESSING bookedDates\n";
        return 1;
    }

    int i = 0;
    while(getline(bookedDates, tokens[i]))
    {
        if(tokens[i] == ' ')
        {

            if((int(tokens[i+1]) >= 48) && (int(tokens[i+1]) <= 57))
            {
                if((int(tokens[i+2]) >= 48) && (int(tokens[i+2]) <= 57))
                {
                    if((int(tokens[i+3]) >= 48) && (int(tokens[i+3]) <= 57))
                    {
                        int k = 0;
                        for(int j = i+1; j < i+3; j++)
                        {
                            rNum[k] = tokens[j];
                        }
                    }
                }
            }


        }
    }
    #endif



   // int currDate = rand() % 31 + 1;

    while(true)
    {
      //  cout << "Today is " << currDate << endl;

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
            cout << "You got Room " << r->getRoomNum() << endl;
            num_of_nights = endDate - startDate;
            cout << "Total Cost of stay: $" << num_of_nights * r->getPrice() << endl;

            // Room Keys
           /* if(currDate <= startDate)
            {
                cout << "How many room keys do you want for your room? ";
                cin >> num_keys;
                RoomKey *key = new RoomKey[num_keys];

                if(currDate == startDate)   // Only to be executed once
                {
                    for(int i = 0; i < num_keys; i++)
                    {
                        key->setActivity(true);
                        key++;
                    }
                }
            }

            else
            {
                cout << "Date " << startDate << " already past\n";
            }
                */
            cout << "\n";
        }

        else
        {
            cout << "No room of " << style << " found for dates " << startDate << " to " << endDate << endl;
        }


        // Options to Cancel or View bookings, or just keep going
        cout << "Do you want to cancel booking? (1. Yes, 2. No, 3. View Bookings)\n";
        cin >> cancel_num;

        if(cancel_num == 1)
        {
            cout << "All the bookings for Room " << r->getRoomNum() << ":\n";
            r->printAllRecords();
            cout << "Provide start date for cancellation: ";
            cin >> startDate;

            cout << "Provide end date for cancellation: ";
            cin >> endDate;

            htl->setFree(r->getRoomNum(), startDate, endDate);

            cout << "Booking of dates " << startDate << " to " << endDate << " for Room " << r->getRoomNum() << " cancelled.\n";
        }

        else if(cancel_num == 2)
        {
            continue;
        }

        else if(cancel_num == 3)
        {
            cout << "All the bookings for Room " << r->getRoomNum() << ":\n";
            r->printAllRecords();
        }

        else
        {
            cout << "Invalid option\n";
        }

      //  currDate++;
    }

    return 0;
}
