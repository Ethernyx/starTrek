#ifndef CLE_H_
#define CLE_H_

#include    <string>

using namespace std;

class Cle
{
private:
    string      _name;
    int         _id;
public:
    Cle(const string, int);
    ~Cle();

    string  getName() const;
    int     getId() const;
    bool    operator==(Cle &);
};

#endif