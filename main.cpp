#include <iostream>

class A{
    std::string name = "none";
    int number = 1;
public:
    void setName(std::string inName)
    {
        name = inName;
    };

    std::string getName()
    {
        return name;
    };

    void setumber (int inNumber)
    {
        number = inNumber;
    };

    int getNumber()
    {
        return number;
    };

    ~A()
    {
        std::cout << name << " " << "destroyed" << std::endl;
    }
};

int main()
{
    A* a = new A;
    A* b = new A;

    //b = a;

    b->setName("Carl");
    a->setName("Mark");

    std::cout << b->getName() << " " << b->getNumber() << std::endl;

    delete a;
    delete b;

    return 0;
}
