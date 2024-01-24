#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

#include "room.h"


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
        r->setStyle(style);
        r->setPrice(price);
    }

    void setOccupy(int rmNum, int startDate, int endDate)
    {
        Room *r = getRoom(rmNum);
        r->addGuestRecord(startDate, endDate);
    }

    void setFree(int rmNum, int startDate, int endDate)
    {
        Room *r = getRoom(rmNum);
        r->removeGuestRecord(startDate, endDate);
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
                    if((tmp->startDate == newStartDate) || (tmp->endDate == newEndDate))
                    {
                        break;
                    }

                    tmp = tmp->next;
                }

                if(tmp == nullptr)
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
