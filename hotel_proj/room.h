#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "house_keeping.h"
#include "key.h"

struct GuestRecord
{
   // string guestName;
    int startDate;
    int endDate;
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
        GuestRecord *newBooking;
        GuestRecord *nodePtr;

        newBooking = new GuestRecord;
        newBooking->startDate = sd;
        newBooking->endDate= ed;
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
            cout << "There needs to be at least one booking in order to delete or cancel.";
        }
        else
        {
            nextBooking = nodePtr->next;
            while(nodePtr != nullptr)
            {
                if((nodePtr->startDate == sd) && (nodePtr->endDate == ed))
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

};

#endif // ROOM_H_INCLUDED
