#include <iostream>
#include <string>
#include <memory>

class Toy{
    std::string name;
public:
    Toy(std::string inName): name(inName) {};
    Toy() : name("Toy") {};
};

class smart_ptr_toy{
private:
    Toy* obj;
public:
    //конструктор по умолчанию
    smart_ptr_toy()
    {
        obj = new Toy("SomeName");
    }
    //конструктор по умолчанию
    smart_ptr_toy(std::string name)
    {
        obj = new Toy(name);
    }

    //конструктор копирования
    smart_ptr_toy(const smart_ptr_toy& other)
    {
        obj = new Toy(*other.obj);
    }

    //оператор присваивания
    smart_ptr_toy& operator = (const smart_ptr_toy& other)
    {
        if(this == &other) return *this;
        if(obj != nullptr) delete obj;
        obj = new Toy(*other.obj);
        return *this;
    }

    //деструктор
    ~smart_ptr_toy()
    {
        delete obj;
    }

};

class Dog
{
    std::string name;
    std::string toyName;
    int age;
    std::shared_ptr<Toy> myToy;
    std::shared_ptr<Dog> bestFriend;
public:
    Dog(std::string inName, std::shared_ptr<Toy> toy, int inAge) : name(inName), myToy(toy)
    {
        if(inAge >= 0 && inAge < 30) age = inAge;
    }
    Dog() : Dog("Snow", std::make_shared<Toy>("Toy"), 0) {};
    Dog(std::string inName) : Dog(inName, std::make_shared<Toy>(inName),  0) {};
    Dog(int inAge) : Dog("Snow", std::make_shared<Toy>("Toy"), inAge) {};

    void copyToy(const Dog& other)
    {
        myToy = other.myToy;
    }

    void setBestFriend(std::shared_ptr<Dog> _friend)
    {
        bestFriend = _friend;
    }

};

int main()
{
    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> bone = std::make_shared<Toy>("Bone");

    std::shared_ptr<Dog> a = std::make_shared<Dog>("Sharik", ball, 10);
    std::shared_ptr<Dog> b = std::make_shared<Dog>("Druzok", ball, 11);
    std::shared_ptr<Dog> c = std::make_shared<Dog>("Pushok", ball, 12);

    std::cout << ball.use_count();

    return 0;
}
