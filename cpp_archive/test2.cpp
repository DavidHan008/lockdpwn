#include <iostream>
#include <tr1/functional>

using namespace std;

class Shape
{
  public:
    virtual void draw() const = 0;
    virtual void error(const string& msg);

    int objectID() const;

};

class Rectangle : public Shape
{
  public:
    virtual void draw() const
    {
        cout << endl;
    }
    virtual void error(const string& msg)
    {
        cout << endl;
    }
};


class Ellipse : public Shape
{
  public:
    virtual void draw() const
    {
        cout << endl;
    }
    virtual void error(const string& msg)
    {
        cout << endl;
    }
};

class ZergUnit
{
    virtual void Attack();
    virtual void Move();
    virtual void Patrol();
    virtual void Borrow();
};

class TerranUnit
{
    virtual void Attack();
    virtual void Move();
    virtual void Patrol();
    virtual void Repair();
};

class Zergling : public ZergUnit
{
    virtual void Attack();
    virtual void Move();
    virtual void Patrol();
};

class Hydralisk : public ZergUnit
{
    virtual void Attack();
    virtual void Move();
    virtual void Patrol();
};

class SCV : public TerranUnit
{
    virtual void Attack();
    virtual void Move();
    virtual void Patrol();
    void MineralMining();
};

class Calculator
{
    explicit Calculator(int a,int b)
    {};

};


int main()
{

  return 0;
}
