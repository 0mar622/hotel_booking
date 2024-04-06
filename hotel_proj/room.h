#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "house_keeping.h"
#include "key.h"
#include <fstream>

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
