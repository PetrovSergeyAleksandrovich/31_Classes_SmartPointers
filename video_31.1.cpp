#include <iostream>
#include <string>

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
    smart_ptr_toy myToy;
public:
    Dog(std::string inName, std::string inToyName, int inAge) : name(inName), myToy(toyName)
    {
        if(inAge >= 0 && inAge < 30) age = inAge;
    }
    Dog() : Dog("Snow", "Toy", 0) {};
    Dog(std::string inName) : Dog(inName, "Toy",  0) {};
    Dog(int inAge) : Dog("Snow", "Toy", inAge) {};
};

int main()
{
    Dog d("Druzok", "Ball", 3);
    Dog q(d);
    return 0;
}
