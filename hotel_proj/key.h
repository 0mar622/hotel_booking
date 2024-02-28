#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <string>
using namespace std;

class RoomKey
{
private:
    // string keyID;
    int issuedDate;
    int expireDate;
    bool active;
public:
    /* void setKeyID(string id)
    {
        keyID = id;
    }

    string getKeyID()
    {
        return keyID;
    }
    */


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
