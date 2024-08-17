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


    char* generateKeyID()
    {
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        default_random_engine rng(random_device{}());
        uniform_int_distribution<> dist(0, sizeof(charset) - 2); // -2 to exclude null terminator
        char* randomID = new char[KEY_ID_LENGTH];

        for(int i = 0; i < KEY_ID_LENGTH - 1; i++)
        {
            randomID[i] = charset[dist(rng)];
        }

        randomID[KEY_ID_LENGTH - 1] = '\0'; // Null-terminate
        return randomID;
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

    void delete_RKey_Info_From_File(char *id, int sDate, int eDate)
    {
        FILE *file = fopen("rkey_info.txt", "r");
        if(file == NULL)
        {
            perror("Error opening file for WRITING key info");
            return;
        }

        FILE *tmpFile = fopen("tmp.txt", "w");
        if(tmpFile == NULL)
        {
            perror("Error opening file for READING key info");
            return;
        }

       // char buffer[BUFFER_SIZE];
        RoomKey key;

        while(fread(&key, sizeof(RoomKey), 1, file) == 1)
        {
            if(strcmp(key.keyID, id) == 0 && key.issuedDate == sDate && key.expireDate == eDate)
            {
                continue;
            }

            fwrite(&key, sizeof(RoomKey), 1, tmpFile);

        }

        fclose(file);
        fclose(tmpFile);

        if(remove("rkey_info.txt") != 0)
        {
            perror("Error deleting original file");
            return;
        }

        if(rename("tmp.txt", "rkey_info.txt") != 0)
        {
            perror("Error renaming temporary file");
            return;
        }

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
