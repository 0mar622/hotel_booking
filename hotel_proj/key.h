#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <string>
#include <random>
#define KEY_ID_LENGTH 20
#define BUFFER_SIZE 100
using namespace std;

class RoomKey
{
private:
    int issuedDate;
    int expireDate;
    bool active;
    char keyID[KEY_ID_LENGTH];
public:
    RoomKey()
    {
        issuedDate = 0;
        expireDate = 0;
        active = false;
        keyID[0] = '\0'; // Initialize keyID as an empty string
    }

    void setKeyID(const char *id)
    {
        strncpy(keyID, id, KEY_ID_LENGTH - 1);
        keyID[KEY_ID_LENGTH - 1] = '\0';
    }

    char* getKeyID()
    {
        return keyID;
    }

    void write_RKey_Info_To_File()
    {
        FILE *file;
        file = fopen("rkey_info.txt", "a");

        if(file == NULL)
        {
            perror("Error opening file for WRITING key info");
        }


        fwrite(keyID, sizeof(char), KEY_ID_LENGTH, file);
        fwrite(&issuedDate, sizeof(int), 1, file);
        fwrite(&expireDate, sizeof(int), 1, file);
        fwrite(&active, sizeof(bool), 1, file);
        fclose(file);
    }

    void setIssuedDate(int iDate)
    {
        issuedDate = iDate;
    }

    int getIssuedDate()
    {
        return issuedDate;
    }


    void setExpireDate(int xDate)
    {
        expireDate = xDate;
    }

    int getExpireDate()
    {
        return expireDate;
    }


    void setActivity(bool act)
    {
        active = act;
    }

    bool isActive(int date, int isd, int exd)
    {
        if((date >= isd) && (date <= exd))
        {
            return true;
        }

        return false;
    }
};

#endif // KEY_H_INCLUDED
