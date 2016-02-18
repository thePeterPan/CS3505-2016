#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
protected:
    double age;
    std::string name;

public:
    Animal(string n) : name(n), age(0) { };

    // The following turns Animal into a pure virtual base class
    // i.e. an abstract class.
    // virtual void speak() = 0;

    virtual void speak() {
        std::cout << "I am an Animal named " << name << std::endl;
    }

    virtual void incrementAge() {
        age += 1.0;
    }
};

class Cat : public Animal {
    bool isHouseCat;

public:
    Cat(std::string n, bool houseCat) : Animal(n), isHouseCat(houseCat) { };

    virtual void speak() {
        std::cout << "Meow" << " and I am " << name << " and my housecatness is " << isHouseCat << std::endl;
    }
};

class Whale : public Animal {
    bool isWild;

public:
    Whale(std::string n, bool wild) : Animal(n), isWild(wild) { };

    virtual void speak() {
        std::cout << "I am a whale named " << name << " and my wilderness is " << isWild << std::endl;
    }
};

void make_speak(Animal& a) {
    Animal b = a;
    b.speak();
}

int main() {
    Animal a("David");
    Cat c("Mittens", true);
    Whale w("Moby", false);

    a.speak();
    c.speak();
    w.speak();

    std::vector<Animal*> zoo;
    zoo.push_back(&a);
    zoo.push_back(&c);
    zoo.push_back(&w);

    for (auto animal : zoo) {
        animal->speak();
    }

    // The following is an example of slicing, where part of the object is
    // sliced off unexpectedly.
    make_speak(a);
    make_speak(c);
    make_speak(w);

    return 0;
}
