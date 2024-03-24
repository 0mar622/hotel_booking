#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "house_keeping.h"
#include "key.h"
#include <fstream>

struct BookingRecord
{
    // string guestName;
    int startDate;
    int endDate;
    int rNum;
};

struct GuestRecord
{
    struct BookingRecord bkr;
    struct GuestRecord *next;
};

class Room
{
private:
    int roomNumber;
    string status;
    string style;
    double price;
public:

    struct GuestRecord *head;

public:
    Room()
    {

    }

    Room(int num)
    {
        roomNumber = num;
    }

    void addGuestRecord(int sd, int ed)
    {
        // FILE IO IN PROGRESS

        FILE *file;


        // Open the file in append mode
        file = fopen("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings.db", "a");

        if (file == NULL) {
            printf("Error opening file to store booking records\n");
            return ;
        }



        #if 0
        ofstream bookingsFile;
        bookingsFile.open("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings.db", ios::app);
        if(!bookingsFile.is_open())
        {
            cout << "ERROR ACCESSING bookingsFile\n";
            return ;
        }

        bookingsFile.seekp(0, ios::end);
#endif

        GuestRecord *newBooking;
        GuestRecord *nodePtr;

        newBooking = new GuestRecord;
        newBooking->bkr.startDate = sd;
        newBooking->bkr.endDate = ed;
        newBooking->bkr.rNum = roomNumber;
        newBooking->next = nullptr;

        if(head == nullptr)
        {
            head = newBooking;
        }
        else
        {
            nodePtr = head;

            while(nodePtr->next != nullptr)
            {
                nodePtr = nodePtr->next;
            }

            nodePtr->next = newBooking;
        }

        // Write the structure to the file
        fwrite(&(newBooking->bkr), sizeof(newBooking->bkr), 1, file);

        // Close the file
        fclose(file);

        printf("Booking record stored successfully!\n");
        //bookingsFile << newBooking->bkr << endl;

    }

    void removeGuestRecord(int sd, int ed)
    {
        GuestRecord *nodePtr;
        GuestRecord *prevBooking;
        GuestRecord *nextBooking;

        nodePtr = head;
        prevBooking = head;
        nextBooking = head;

        if(head == nullptr)
        {
            cout << "There needs to be at least one booking in order to delete or cancel.\n";
        }
        else
        {
            nextBooking = nodePtr->next;
            while(nodePtr != nullptr)
            {
                if((nodePtr->bkr.startDate == sd) && (nodePtr->bkr.endDate == ed))
                {
                    prevBooking->next = nextBooking;

                    if(head == nodePtr)    // delete first booking
                    {
                        head = nextBooking;
                    }
                    delete nodePtr;
                    break;
                }

                prevBooking = nodePtr;
                nodePtr = nodePtr->next;
                nextBooking = nodePtr->next;
            }
        }
    }

    void printAllRecords()
    {
        GuestRecord *nodePtr;
        nodePtr = head;

        while(nodePtr != nullptr)
        {
            cout << "Start Date: " << nodePtr->bkr.startDate << endl;
            cout << "End Date: " << nodePtr->bkr.endDate << endl;
            cout << "\n";
            nodePtr = nodePtr->next;
        }
    }

    void setStyle(string type)
    {
        style = type;
    }

    string getStyle()
    {
        return style;
    }


    void setPrice(double cost)
    {
        price = cost;
    }

    double getPrice()
    {
        return price;
    }


    void setRoomNum(int num)
    {
        roomNumber = num;
    }

    int getRoomNum()
    {
        return roomNumber;
    }


    bool isBooked(int oldStart, int oldEnd, int newStart, int newEnd)
    {
        // True means unavailable (Occupied)
        // False means available, dates not booked yet

        if(newStart < oldStart)     // MAYBE available (false)
        {
            if(newEnd > oldStart)   // Checking collision of dates
            {
                return true;
            }

            return false;
        }

        if((newStart >= oldStart) && (newStart < oldEnd))
        {
            return true;
        }

        return false;

    }

};

#endif // ROOM_H_INCLUDED
