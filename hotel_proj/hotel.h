#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

#include "room.h"
#include <fstream>
#include <mutex>
#define GUEST_NAME_SIZE 32

struct BookingRecord
{
    char gName[GUEST_NAME_SIZE];
    char uID[GUEST_NAME_SIZE];
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
    mutex h_mtx;
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


    void addGuestRecord(int rmNum, int sd, int ed, char *gName, char *uID, int name_size)
    {
        Room *r = getRoom(rmNum);
        FILE *file;

        // Open the file in append mode
        file = fopen("bookings.db", "a");

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
        memcpy(newBooking->bkr.uID, uID, name_size);
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
        file = fopen("bookings.db", "r");

        if (file == NULL) {
            printf("%s:%d: Error opening file: Probably file is not present\n", __func__, __LINE__);
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
            memcpy(newBooking->bkr.uID, bkr.uID, GUEST_NAME_SIZE);
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
        FILE *file, *tmp_file;

        // Open the file in read mode
        file = fopen("bookings.db", "r");

        if (file == NULL) {
            printf("Error opening file to store booking records\n");
            return ;
        }

        // Open a temp file in write mode
        tmp_file = fopen("temp.db", "w");

        if (tmp_file == NULL) {
            printf("Error opening temp file to store booking records\n");
            return ;
        }

        struct BookingRecord bkr;

        // Reading from file to create Linked List before node deletion
        while(fread(&bkr, sizeof(bkr), 1, file) == 1)
        {

           if((bkr.rNum != rmNum) || (bkr.startDate != sd) || (bkr.endDate != ed))
           {
                fwrite((&bkr), sizeof(bkr), 1, tmp_file);
           }

        }

        // Close both files
        fclose(file);
        fclose(tmp_file);

        // Remove original file
        if (remove("bookings.db") != 0) {
            perror("Error deleting original file");
            return;
        }

        // Rename temporary file to original filename
        if (rename("temp.db", "bookings.db") != 0) {
            perror("Error renaming temporary file");
            return;
        }

        cout << "Record removed successfully.\n";

        GuestRecord *nodePtr, *prevBooking, *nextBooking;
        nodePtr = r->head;
        prevBooking = r->head;
        nextBooking = r->head;

        if(r->head == nullptr)
        {
            cout << "There is no booking made in Room " << rmNum << " to cancel.\n";
        }

        else
        {
            nextBooking = nodePtr->next;
            while(nodePtr != nullptr)
            {
                if((nodePtr->bkr.startDate == sd) && (nodePtr->bkr.endDate == ed) && (nodePtr->bkr.rNum == rmNum))
                {
                    prevBooking->next = nextBooking;
                    if(r->head == nodePtr)      // Deletes the first booking
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
                cout << "Room " << tmp->bkr.rNum << " booked for dates " << tmp->bkr.startDate << " and " << tmp->bkr.endDate << " for " << tmp->bkr.uID << endl;
                tmp = tmp->next;
            }
        }

    }


    void printUserRecords(char *uid)
    {
        Room *r;
        GuestRecord *tmp;

        for(int i = 0; i < total_rooms; i++)
        {
            r = &room_list[i];
            tmp = r->head;
            while((tmp != nullptr) && (strncmp(uid, tmp->bkr.uID, GUEST_NAME_SIZE) == 0))
            {
                cout << "Room " << tmp->bkr.rNum << " booked for dates " << tmp->bkr.startDate << " and " << tmp->bkr.endDate << " for " << tmp->bkr.uID << endl;
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
        lock_guard<mutex> lock(h_mtx);

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


        return nullptr;		// Shows that the room with requested style is not found

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
