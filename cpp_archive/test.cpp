#include <cstring>
#include <iostream>
#include <set>
#include <list>

using namespace std;

class CompanyA
{
  public:
    void sendCleartext(const string& msg);
    void sendEncrypted(const string& msg);
};

class CompanyB
{
  public:
    void sendClearttext(const string& msg);
    void sendEncrypted(const string& msg);
};

class MsgInfo
{
  public:


};

template<typename T>
class MsgSender
{
  public:
    void sendClear(const MsgInfo& info)
    {
        string msg;

        CompanyA c;
        c.sendCleartext(msg);
    }

    void sendSecret(const MsgInfo& info)
    {}
};
