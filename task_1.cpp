#include <iostream>
#include <string>
#include <vector>

class Toy
{
private:
    std::string toyName;
public:
    Toy(std::string inName): toyName(inName){};
    void getToyName()
    {
        std::cout << toyName << std::endl;
    }
};

class shared_ptr_toy {
private:
    Toy* sharingToy = nullptr;
    int* counter = nullptr;
public:
    //конструктор по умолчанию
    shared_ptr_toy(std::string name, int* inNumber): counter(inNumber)
    {
        sharingToy = new Toy(name);
    }

    //конструктор копирования
    shared_ptr_toy(const shared_ptr_toy& other)
    {
        sharingToy = new Toy(*other.sharingToy);
    }

    //оператор присваивания
    shared_ptr_toy& operator = (const shared_ptr_toy& other)
    {
        if(this == &other) return *this;
        if(sharingToy != nullptr) delete sharingToy;
        sharingToy = new Toy(*other.sharingToy);
        return *this;
    }

    //деструктор
    ~shared_ptr_toy()
    {
        (*counter)--;
        if(*counter == 0)
        {
            sharingToy = nullptr;
        }
    }

    void addLink()
    {
        (*counter)++;
    }

    void reduceLink()
    {
        (*counter)--;
    }

    void getName()
    {
        sharingToy->getToyName();
    }
};

class Dog
{
    std::string dogName;
    shared_ptr_toy* myToy;
public:
    Dog(std::string inName, shared_ptr_toy* inToy) : dogName(inName), myToy(inToy)
    {
        myToy->addLink();
    };

    ~Dog()
    {
        myToy->reduceLink();
    }

    void getFavToy()
    {
        myToy->getName();
    }
};


int main()
{
    int counter = 0;
    char user_input = 'x';

    shared_ptr_toy* ball = new shared_ptr_toy("ball", &(++counter));

    Dog* sobaka_a = new Dog("Pushok",ball);

    while(counter > 0)
    {
        std::cout << "destroy toy? y/n: ";
        std::cin >> user_input;
        if(user_input == 'y') delete ball;

        std::cout << "destroy dog a? y/n: ";
        std::cin >> user_input;
        if(user_input == 'y')  delete sobaka_a;

        std::cout << "links: " << counter << std::endl;

        std::cout << "get favorite toy name? y/n: ";
        std::cin >> user_input;
        if(user_input == 'y') sobaka_a->getFavToy();

    };
    
    delete sobaka_a;
    sobaka_a->getFavToy();

    return 0;
}