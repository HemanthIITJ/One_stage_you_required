/*******************************************************
 * Chapter 8: Introduction to Object-Oriented Programming (OOP) - Thinking in Objects 🧬🤔
 * -----------------------------------------------------
 * This code file explores advanced OOP concepts in C++,
 * starting from inheritance to move semantics.
 * Each example builds upon the previous one.
 *******************************************************/

#include <iostream>     // For input/output operations
#include <string>       // For std::string
#include <vector>       // For std::vector
#include <memory>       // For smart pointers
#include <exception>    // For exception handling

// Example 1: Inheritance - Extending Classes 🧩
class Animal {          // Base class
public:
    void eat() {
        std::cout << "Animal eats." << std::endl;
    }
};

class Dog : public Animal { // Derived class
public:
    void bark() {
        std::cout << "Dog barks." << std::endl;
    }
};

int main() {
    // Inheritance demonstration
    Dog dog;
    dog.eat();   // Inherited from Animal
    dog.bark();  // Defined in Dog

    // Example 2: Overriding and Virtual Functions 🔄
    class Shape {
    public:
        virtual double area() const { // Virtual function
            return 0.0;
        }
    };

    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        double area() const override { // Override base class method
            return 3.1416 * radius * radius;
        }
    };

    class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(double w, double h) : width(w), height(h) {}
        double area() const override {
            return width * height;
        }
    };

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0));
    shapes.push_back(std::make_shared<Rectangle>(4.0, 6.0));

    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->area() << std::endl;
    }

    // Example 3: Abstract Classes and Pure Virtual Functions 🌫️
    class AnimalAbstract {
    public:
        virtual void makeSound() const = 0; // Pure virtual function
    };

    class Cat : public AnimalAbstract {
    public:
        void makeSound() const override {
            std::cout << "Cat meows." << std::endl;
        }
    };

    Cat cat;
    cat.makeSound();

    // Cannot instantiate abstract class
    // AnimalAbstract animal; // Error ❌

    // Example 4: Access Control and Encapsulation 🔒
    class Account {
    private:
        double balance;      // Private data member
        void logTransaction(double amount) { // Private method
            std::cout << "Transaction of $" << amount << " recorded." << std::endl;
        }
    public:
        Account() : balance(0.0) {}
        void deposit(double amount) {
            if (amount > 0) {
                balance += amount;
                logTransaction(amount);
            } else {
                std::cerr << "Invalid deposit amount." << std::endl;
            }
        }
        double getBalance() const {
            return balance;
        }
    };

    Account myAccount;
    myAccount.deposit(500.0);
    std::cout << "Balance: $" << myAccount.getBalance() << std::endl;

    // Possible Mistake: Accessing private members ❌
    // myAccount.balance = 1000.0;     // Error
    // myAccount.logTransaction(1000); // Error

    // Example 5: Copy Constructors and Assignment Operators 📋
    class Counter {
    private:
        int* count;
    public:
        Counter(int c = 0) {
            count = new int(c);
        }
        // Copy constructor
        Counter(const Counter& other) {
            count = new int(*(other.count));
        }
        // Assignment operator
        Counter& operator=(const Counter& other) {
            if (this != &other) { // Self-assignment check
                delete count;
                count = new int(*(other.count));
            }
            return *this;
        }
        ~Counter() {
            delete count;
        }
        void increment() {
            ++(*count);
        }
        int getCount() const {
            return *count;
        }
    };

    Counter c1(10);
    Counter c2 = c1;      // Invokes copy constructor
    c2.increment();
    std::cout << "c1 count: " << c1.getCount() << std::endl; // 10
    std::cout << "c2 count: " << c2.getCount() << std::endl; // 11

    // Possible Mistake: Not handling deep copy, leading to double deletion ❌

    // Example 6: Friendship in Classes 🤝
    class Box {
    private:
        double width;
    public:
        Box(double w) : width(w) {}
        friend void printWidth(const Box& b); // Friend function declaration
    };

    void printWidth(const Box& b) { // Friend function definition
        std::cout << "Width of box: " << b.width << std::endl;
    }

    Box box(10.0);
    printWidth(box); // Accesses private member width

    // Example 7: Multiple Inheritance and Diamond Problem ⚠️
    class A {
    public:
        void sayHello() {
            std::cout << "Hello from A" << std::endl;
        }
    };

    class B : public A {};

    class C : public A {};

    class D : public B, public C {}; // Multiple inheritance

    D d;
    // d.sayHello(); // Error: Ambiguous ❌

    // Correct way using scope resolution
    d.B::sayHello();
    d.C::sayHello();

    // Possible Mistake: Ambiguity due to multiple inheritance

    // Example 8: Virtual Inheritance to Solve Diamond Problem 💎
    class AVirtual {
    public:
        void sayHello() {
            std::cout << "Hello from AVirtual" << std::endl;
        }
    };

    class BVirtual : virtual public AVirtual {};

    class CVirtual : virtual public AVirtual {};

    class DVirtual : public BVirtual, public CVirtual {};

    DVirtual dv;
    dv.sayHello(); // No ambiguity

    // Example 9: Operator Overloading ➕

    class Complex {
    private:
        double real, imag;
    public:
        Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
        // Overload + operator
        Complex operator+(const Complex& other) const {
            return Complex(real + other.real, imag + other.imag);
        }
        void display() const {
            std::cout << real << " + " << imag << "i" << std::endl;
        }
    };

    Complex c3(1.0, 2.0);
    Complex c4(3.0, 4.0);
    Complex c5 = c3 + c4; // Uses overloaded operator
    c5.display(); // Displays 4.0 + 6.0i

    // Example 10: Exception Handling within Classes 🚨
    class Division {
    public:
        static double divide(double numerator, double denominator) {
            if (denominator == 0) {
                throw std::runtime_error("Division by zero!");
            }
            return numerator / denominator;
        }
    };

    try {
        double result = Division::divide(10.0, 0.0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl; // Handles exception
    }

    // Example 11: Static Members and Methods 📌
    class MathUtils {
    public:
        static const double PI; // Declaration
        static double square(double x) {
            return x * x;
        }
    };

    const double MathUtils::PI = 3.1416; // Definition

    std::cout << "PI: " << MathUtils::PI << std::endl;
    std::cout << "Square of 5: " << MathUtils::square(5.0) << std::endl;

    // Example 12: Templates with Classes 🛠️
    template <typename T>
    class Pair {
    private:
        T first, second;
    public:
        Pair(const T& a, const T& b) : first(a), second(b) {}
        T getFirst() const { return first; }
        T getSecond() const { return second; }
    };

    Pair<int> intPair(1, 2);
    std::cout << "First: " << intPair.getFirst() << ", Second: " << intPair.getSecond() << std::endl;

    Pair<std::string> stringPair("Hello", "World");
    std::cout << "First: " << stringPair.getFirst() << ", Second: " << stringPair.getSecond() << std::endl;

    // Example 13: Move Semantics and rvalue References 🚀
    class Movable {
    private:
        int* data;
    public:
        Movable(int value) {
            data = new int(value);
        }
        // Move constructor
        Movable(Movable&& other) noexcept : data(nullptr) {
            data = other.data;
            other.data = nullptr;
        }
        // Move assignment operator
        Movable& operator=(Movable&& other) noexcept {
            if (this != &other) {
                delete data;
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }
        ~Movable() {
            delete data;
        }
        int getData() const {
            return (data != nullptr) ? *data : 0;
        }
    };

    Movable m1(10);
    Movable m2 = std::move(m1); // Moves resources
    std::cout << "m2 data: " << m2.getData() << std::endl;
    // m1.getData(); // Undefined behavior if accessed ❌

    // Possible Mistake: Accessing moved-from object

    // Example 14: Nested Classes 🧳
    class Outer {
    public:
        int outerVar;
        class Inner {
        public:
            int innerVar;
            void display() {
                std::cout << "Inner class." << std::endl;
            }
        };
        void outerDisplay() {
            std::cout << "Outer class." << std::endl;
        }
    };

    Outer::Inner innerObj;
    innerObj.display();

    // Example 15: Enumeration inside Classes 🎌
    class TrafficLight {
    public:
        enum LightColor { RED, YELLOW, GREEN };
        void displaySignal(LightColor color) {
            switch (color) {
                case RED:
                    std::cout << "Stop!" << std::endl;
                    break;
                case YELLOW:
                    std::cout << "Get Ready!" << std::endl;
                    break;
                case GREEN:
                    std::cout << "Go!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid color." << std::endl;
                    break;
            }
        }
    };

    TrafficLight light;
    light.displaySignal(TrafficLight::GREEN);

    return 0; // End of program
}