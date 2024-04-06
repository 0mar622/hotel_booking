#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

#include "room.h"
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

class Hotel
{
private:
    string hotelName;
    string location;
    Room *room_list;
    int total_rooms;
public:
    Hotel(int num_rooms, string name, string loc)
    {
        Room *obj;
        total_rooms = num_rooms;
        hotelName = name;
        location = loc;
        room_list = new Room[num_rooms];
        for(int i = 0; i < num_rooms; i++)
        {
            obj = &room_list[i];
            obj->setRoomNum(i+101);
            obj->head = nullptr;
            #if 0
            room_list[i].setRoomNum(i+101);

            (room_list+i)->setRoomNum(i+101);
            #endif
        }
    }

    void setRoomProps(int rmNum, string style, double price)
    {
        Room *r = getRoom(rmNum);

        if(r == nullptr)
        {
            cout << "Invalid room\n";
            return;
        }

        r->setStyle(style);
        r->setPrice(price);
    }

    void addGuestRecord(int rmNum, int sd, int ed)
    {
        Room *r = getRoom(rmNum);

        FILE *file;

        // Open the file in append mode
        file = fopen("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings.db", "a");

        if (file == NULL) {
            printf("Error opening file to store booking records\n");
            return ;
        }


        GuestRecord *newBooking;
        GuestRecord *nodePtr;

        newBooking = new GuestRecord;
        newBooking->bkr.startDate = sd;
        newBooking->bkr.endDate = ed;
        newBooking->bkr.rNum = rmNum;
        newBooking->next = nullptr;

        if(r->head == nullptr)
        {
            r->head = newBooking;
        }
        else
        {
            nodePtr = r->head;

            while(nodePtr->next != nullptr)
            {
                nodePtr = nodePtr->next;
            }

            nodePtr->next = newBooking;
        }

        fwrite(&(newBooking->bkr), sizeof(newBooking->bkr), 1, file);

        fclose(file);

        printf("Booking record stored successfully!\n");

    }

    void readGuestRecord()
    {
        // FILE IO IN PROGRESS

        FILE *file;

        // Open the file in append mode
        file = fopen("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings.db", "r");

        if (file == NULL) {
            printf("Error opening file to read booking records\n");
            return ;
        }


        GuestRecord *newBooking;
        GuestRecord *nodePtr;
        struct BookingRecord bkr;
        Room *r;

        while(fread(&bkr, sizeof(bkr), 1, file) == 1)
        {
            newBooking = new GuestRecord;
            newBooking->bkr.startDate = bkr.startDate;
            newBooking->bkr.endDate = bkr.endDate;
            newBooking->bkr.rNum = bkr.rNum;
            newBooking->next = nullptr;
            r = getRoom(bkr.rNum);

            if(r->head == nullptr)
            {
                r->head = newBooking;
            }
            else
            {
                nodePtr = r->head;

                while(nodePtr->next != nullptr)
                {
                    nodePtr = nodePtr->next;
                }

                nodePtr->next = newBooking;
            }
        }
    }

    void removeGuestRecord(int rmNum, int sd, int ed)
    {
        Room *r = getRoom(rmNum);

        FILE *file;

        // Open the file in read/write mode
        file = fopen("/Users/omar/git_projects/hotel_booking/hotel_proj/bookings.db", "rw");

        if (file == NULL) {
            printf("Error opening file to store booking records\n");
            return ;
        }


        GuestRecord *newBooking;
        GuestRecord *nodePtr;
        GuestRecord *prevBooking;
        GuestRecord *nextBooking;
        struct BookingRecord bkr;

        // Reading from file to create Linked List before node deletion
        while(fread(&bkr, sizeof(bkr), 1, file) == 1)
        {
            newBooking = new GuestRecord;
            newBooking->bkr.startDate = bkr.startDate;
            newBooking->bkr.endDate = bkr.endDate;
            newBooking->bkr.rNum = bkr.rNum;
            newBooking->next = nullptr;
            r = getRoom(bkr.rNum);

            if(r->head == nullptr)
            {
                r->head = newBooking;
            }
            else
            {
                nodePtr = r->head;

                while(nodePtr->next != nullptr)
                {
                    nodePtr = nodePtr->next;
                }

                nodePtr->next = newBooking;
            }
        }

        fseek(file, 0, SEEK_SET);

        // Deletes node from Linked List
        nodePtr = r->head;
        prevBooking = r->head;
        nextBooking = r->head;

        if(r->head == nullptr)
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

                    if(r->head == nodePtr)    // delete first booking
                    {
                        r->head = nextBooking;
                    }
                    delete nodePtr;
                    break;
                }

                prevBooking = nodePtr;
                nodePtr = nodePtr->next;
                nextBooking = nodePtr->next;
            }
        }

        nodePtr = r->head;
        while(nodePtr != nullptr)
        {
            nodePtr->bkr.startDate = sd;
            nodePtr->bkr.endDate = ed;
            nodePtr->bkr.rNum = rmNum;
            fwrite(&(nodePtr->bkr), sizeof(nodePtr->bkr), 1, file);
            nodePtr = nodePtr->next;
        }

    }

    void printAllRecords()
    {
        Room *r;
        GuestRecord *tmp;

        for(int i = 0; i < total_rooms; i++)
        {
            r = &room_list[i];
            tmp = r->head;
            while(tmp != nullptr)
            {
                cout << "Room " << tmp->bkr.rNum << " booked for dates " << tmp->bkr.startDate << " and " << tmp->bkr.endDate << endl;
                tmp = tmp->next;
            }
        }

    }

    int getRoomCount()
    {
        return total_rooms;
    }


    Room *findAvailableRoom(string style, int newStartDate, int newEndDate)
    {
        Room *r;
        struct GuestRecord *tmp;

        for(int i = 0; i < total_rooms; i++)
        {
            r = &room_list[i];
            if(style.compare(r->getStyle()) == 0)
            {
                tmp = r->head;
                while(tmp != nullptr)
                {
                    if(r->isBooked(tmp->bkr.startDate, tmp->bkr.endDate, newStartDate, newEndDate) == true)    // Dates Occupied???
                    {
                        break;
                    }

                    tmp = tmp->next;
                }

                if(tmp == nullptr)      // Room is found
                {
                    return r;
                }
            }
        }

        // Shows that the room with requested style not found
        // returning null
        return nullptr;

    }

    Room *getRoom(int rmNum)
    {
        Room *temp;

        for(int i = 0; i < total_rooms; i++)
        {
            temp = &room_list[i];
            if(rmNum == temp->getRoomNum())
            {
                return temp;
            }
        }

        return nullptr;

    }


};

#endif // HOTEL_H_INCLUDED
