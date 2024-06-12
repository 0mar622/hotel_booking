#include <iostream>
#include <string.h>
#include "hotel.h"
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <time.h>
//#include <openssl/rand.h>
using namespace std;

struct Login
{
    char guestName[GUEST_NAME_SIZE];
    char userID[GUEST_NAME_SIZE];
    char password[GUEST_NAME_SIZE];
};

bool doesUserExist(char *uid)
{
    FILE *file;
    struct Login lg;

    file = fopen("logins.db", "r");
    if (file == NULL) {
<<<<<<< HEAD
    	printf("%s, %d: Error opening file to access everybodys login\n", __func__, __LINE__);
=======
>>>>>>> cb9bf1ed659163fd928f327e1a58dbb57d004e25
        return false;
    }

    while(fread(&lg, sizeof(lg), 1, file))
    {
        if(strcmp(uid, lg.userID) == 0)
        {

            fclose(file);
            return true;

        }
    }
    fclose(file);

    return false;
}


bool isAccountValid(char *uid, char *passwd)
{
    FILE *file;
    struct Login lg;

    file = fopen("logins.db", "r");
    if (file == NULL) {
        printf("%s, %d: Error opening file to access everybodys login\n", __func__, __LINE__);
        return false;
    }

    while(fread(&lg, sizeof(lg), 1, file))
    {
        if(strcmp(uid, lg.userID) == 0)
        {
            if(strcmp(passwd, lg.password) == 0)
            {
                fclose(file);
                return true;
            }
            else
            {
                fclose(file);
                cout << "Password incorrect\n";
                return false;
            }
        }
    }
    fclose(file);
    return false;
}




/*void generate_salt(unsigned char *salt, int length)
{
    if (RAND_bytes(salt, length) != 1)
    {
        fprintf(stderr, "Error generating random bytes.\n");
        exit(1);
    }
}   */


bool createNewAccount(char *gName, char *uid, char *passwd)
{
    FILE *file;
    struct Login lg;

    if(doesUserExist(uid) == true)
    {
        cout << "User already exists\n";
        return false;
    }

    file = fopen("logins.db", "a");
    if (file == NULL) {
        printf("Error opening file to create account\n");
        return false;
    }

    memset(&lg, 0, sizeof(lg));
    strncpy(lg.guestName, gName, GUEST_NAME_SIZE);
    strncpy(lg.userID, uid, GUEST_NAME_SIZE);
    strncpy(lg.password, passwd, GUEST_NAME_SIZE);

    fwrite(&lg, sizeof(lg), 1, file);
    fclose(file);

    return true;
}

void showAllLogins()
{
    FILE *file;
    struct Login lg;

    file = fopen("logins.db", "r");
    if(file == NULL)
    {
        perror("Error opening file to read and display content\n");
    }

    while(fread(&lg, sizeof(lg), 1, file))
    {
        cout << "Name: " << lg.guestName << endl;
        cout << "User ID: " << lg.userID << endl;
        cout << "Password: " << lg.password << endl;
        cout << endl;
    }
}

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

    cout << " 1\n";
    string style;
    char guestName[GUEST_NAME_SIZE];
    char userID[GUEST_NAME_SIZE];
   // char password[GUEST_NAME_SIZE];
    char newUID[GUEST_NAME_SIZE];
    char password[GUEST_NAME_SIZE];
    char newPswd[GUEST_NAME_SIZE];
    char salt[GUEST_NAME_SIZE];
    char *hashed_password;

    int startDate;
    int endDate;
    int num_of_nights;
    int num_keys;
    int booking_ops;
    int acct_ops;
    int rNum = 0;
    cout << " 2\n";
    Room *r = nullptr;
    htl->readGuestRecord();
    cout << " 3\n";

    int total = htl->getRoomCount();
    cout << total << " rooms in the hotel\n";


    while(true)
    {
        //cout << "__FUNC__: __LINE__: OPTIONS: \n 1. Login \n 2. Create Account \n 3. EXIT PROGRAM \n";
        cout << "OPTIONS: \n 1. Login \n 2. Create Account \n 3. EXIT PROGRAM \n";
        cout << "Enter 1, 2, or 3 for the user options above: ";
        cin >> acct_ops;

        if(acct_ops == 1)
        {
            cout << "User ID: ";
            cin >> userID;

            cout << "Password: ";
            cin >> password;

           // generate_salt(salt, GUEST_NAME_SIZE);
            hashed_password = crypt(password, salt);

            if((strncmp(userID, "admin", sizeof(userID)) == 0) && (strncmp(password, "admin", sizeof(password)) == 0))
            {
                cout << "All the bookings made by different users:\n";
                htl->printAllRecords();
                cout << endl;

                cout << "All the users and login:\n";
                showAllLogins();

                cout << "OPTIONS \n 1. Cancel Booking \n 2. EXIT PROGRAM \n";
                cout << "Enter 1 or 2 for the user options above: ";
                cin >> booking_ops;

                if(booking_ops == 1)
                {
                    cout << "Enter guest name: ";
                    cin >> guestName;

                    cout << "Provide start date for cancellation: ";
                    cin >> startDate;

                    cout << "Provide end date for cancellation: ";
                    cin >> endDate;
                    cout << endl;

                    cout << "Provide room number to cancel: ";
                    cin >> rNum;

                   // cout << "Room Number = " << rNum;
                    htl->removeGuestRecord(rNum, startDate, endDate);
                }
                else if(booking_ops == 2)
                {
                    break;
                }
                else
                {
                    cout << "Invalid option\n";
                }
            }

            else if(isAccountValid(userID, hashed_password) == true)
            {
                cout << "Hello " << userID << ", these are all the bookings you made.\n";
                htl->printUserRecords(userID);
                cout << "OPTIONS: \n 1. Make Booking \n 2. Cancel Booking \n 3. EXIT PROGRAM \n";
                cin >> booking_ops;

                if(booking_ops == 1)
                {
                    cout << "Provide room style (single, double, triple): ";
                    cin >> style;

                    cout << "Provide check-in date: ";
                    cin >> startDate;

                    cout << "Provide check-out date: ";
                    cin >> endDate;
                    cout << endl;

                    r = htl->findAvailableRoom(style, startDate, endDate);

                    if(r != nullptr)
                    {
                        htl->addGuestRecord(r->getRoomNum(), startDate, endDate, guestName, userID, GUEST_NAME_SIZE);
                        cout << "You got Room " << r->getRoomNum() << endl;
                        num_of_nights = endDate - startDate;
                        cout << "Total Cost of stay: $" << num_of_nights * r->getPrice() << endl;
                        cout << "\n";
                    }

                    else
                    {
                        cout << "No room of " << style << " found for dates " << startDate << " to " << endDate << endl;
                    }
                }
                else if(booking_ops == 2)
                {
                    cout << "Provide start date for cancellation: ";
                    cin >> startDate;

                    cout << "Provide end date for cancellation: ";
                    cin >> endDate;
                    cout << endl;

                    cout << "Provide room number to cancel: ";
                    cin >> rNum;

                   // cout << "Room Number = " << rNum;
                    htl->removeGuestRecord(rNum, startDate, endDate);
                    cout << "Booking removed successfully!\n";
                }
                else if(booking_ops == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid option\n";
                }


            }
            else
            {
                cout << "User not found\n";
                continue;
            }

        }

        else if(acct_ops == 2)
        {
            cout << "Enter your name: ";
            cin >> guestName;

            cout << "New User ID: ";
            cin >> newUID;

            cout << "New Password: ";
            cin >> newPswd;

           // generate_salt(salt, GUEST_NAME_SIZE);
            hashed_password = crypt(newPswd, salt);

            if(createNewAccount(guestName, newUID, hashed_password) == true)
            {
                cout << "Account created\n";

            }
            else
            {
                cout << "Account creation failed\n";
                continue;
            }


        }

        else if(acct_ops == 3)
        {
            break;
        }

        else
        {
            cout << "Invalid option\n";
        }

    }

}
