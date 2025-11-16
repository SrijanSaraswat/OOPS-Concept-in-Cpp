#include <iostream>
#include <string>
using namespace std;

/*
  ------------------------------
  Helper: Salary class (operator overloading)
  ------------------------------
*/
// Demonstrates operator overloading (compile-time polymorphism)
class Salary {
private:
    double amount;
public:
    Salary(double a = 0.0) : amount(a) {}                // parameterized / default ctor
    double get() const { return amount; }

    // operator+ overloaded to add salaries
    Salary operator+(const Salary& other) const {
        return Salary(this->amount + other.amount);
    }

    friend ostream& operator<<(ostream& os, const Salary& s) {
        os << s.amount;
        return os;
    }
};

/*
  ------------------------------
  Abstraction: Payable is an abstract class (interface)
  - pure virtual function getPay()
  ------------------------------
*/
class Payable {
public:
    virtual double getPay() const = 0;      // pure virtual -> makes class abstract
    virtual ~Payable() = default;           // virtual destructor for safe polymorphic deletion
};

/*
  ------------------------------
  Base class: Person
  - shows encapsulation (private age)
  - shows 'this' pointer usage
  - demonstrates constructors (default, parameterized, copy)
  - demonstrates function overloading (compile-time polymorphism)
  ------------------------------
*/
class Person {
private:
    // Encapsulated member: not directly accessible outside class
    int age;

protected:
    // Protected member: derived classes can access
    string name;

public:
    static int population; // static member shared across all Person objects

    // Default constructor
    Person() : age(0), name("Unknown") {
        ++population;
        cout << "[Person] default ctor called for " << name << '\n';
    }

    // Parameterized constructor (initializer list)
    Person(const string& nm, int a) : age(a), name(nm) {
        ++population;
        cout << "[Person] parameterized ctor called for " << name << '\n';
    }

    // Copy constructor
    Person(const Person& other) : age(other.age), name(other.name) {
        ++population;
        cout << "[Person] copy ctor called for " << name << '\n';
    }

    // Move constructor
    Person(Person&& other) noexcept : age(other.age), name(std::move(other.name)) {
        ++population;
        other.age = 0;
        cout << "[Person] move ctor called\n";
    }

    // Destructor
    virtual ~Person() {
        --population;
        cout << "[Person] dtor called for " << name << '\n';
    }

    // Getter (encapsulation)
    int getAge() const { return age; }

    // Setter that uses 'this' pointer and returns reference
    Person& setAge(int a) {
        // using this pointer explicitly
        this->age = a;
        return *this;
    }

    // Function overloading - compile-time polymorphism
    void introduce() const {
        cout << "Hi, I'm " << name << ".\n";
    }
    void introduce(const string& mood) const {
        cout << "Hi, I'm " << name << ". I'm feeling " << mood << ".\n";
    }

    // const method - doesn't modify object
    string getName() const { return name; }

    // Virtual function: can be overridden by derived classes (runtime polymorphism)
    virtual void show() const {
        cout << "[Person::show] Name: " << name << ", Age: " << age << '\n';
    }
};

int Person::population = 0; // initialize static member

/*
  ------------------------------
  Derived class: Employee
  - Single inheritance (Person -> Employee)
  - Implements Payable (abstraction)
  - Override virtual function (runtime polymorphism)
  - Demonstrates friend function declaration
  ------------------------------
*/
class Employee : public Person, public Payable {
private:
    int employeeId;
    Salary salary;

    // mutable example: can be changed even in const methods
    mutable string cache;

public:
    // Default
    Employee() : Person(), employeeId(0), salary(0.0) {
        cout << "[Employee] default ctor\n";
    }

    // Parameterized
    Employee(const string& nm, int a, int id, double sal)
        : Person(nm, a), employeeId(id), salary(sal) {
        cout << "[Employee] parameterized ctor for " << nm << '\n';
    }

    // Copy
    Employee(const Employee& other)
        : Person(other), employeeId(other.employeeId), salary(other.salary) {
        cout << "[Employee] copy ctor\n";
    }

    // Virtual destructor to ensure derived dtors run
    virtual ~Employee() {
        cout << "[Employee] dtor for " << getName() << '\n';
    }

    // override pure virtual from Payable
    double getPay() const override {
        return salary.get();
    }

    // override virtual show()
    void show() const override {
        cout << "[Employee::show] " << getName() << " (ID: " << employeeId
             << "), Salary: " << salary << '\n';
    }

    Salary getSalary() const { return salary; }

    void setSalary(const Salary& s) { salary = s; }

    // friend function declaration: promote can access private members
    friend void promote(Employee& e, double raise);
};

// friend function definition - can access Employee's private members
void promote(Employee& e, double raise) {
    cout << "[friend promote] Promoting " << e.getName() << " by " << raise << '\n';
    // direct access to private salary
    e.salary = e.salary + Salary(raise);
}

/*
  ------------------------------
  Multilevel inheritance:
  Manager derives from Employee (Employee -> Manager)
  ------------------------------
*/
class Manager : public Employee {
private:
    int teamSize;

public:
    Manager() : Employee(), teamSize(0) {
        cout << "[Manager] default ctor\n";
    }

    Manager(const string& nm, int a, int id, double sal, int team)
        : Employee(nm, a, id, sal), teamSize(team) {
        cout << "[Manager] parameterized ctor for " << nm << '\n';
    }

    ~Manager() override {
        cout << "[Manager] dtor\n";
    }

    void show() const override {
        cout << "[Manager::show] " << getName() << " manages team of " << teamSize << '\n';
    }
};

/*
  ------------------------------
  Multiple inheritance example:
  Consultant (independent) and Lead inherits from both Manager and Consultant
  ------------------------------
*/
class Consultant {
protected:
    string consultancyFirm;
public:
    Consultant(const string& firm = "Independent") : consultancyFirm(firm) {
        cout << "[Consultant] ctor for " << consultancyFirm << '\n';
    }
    virtual ~Consultant() {
        cout << "[Consultant] dtor\n";
    }
    virtual void showConsultancy() const {
        cout << "Consultancy: " << consultancyFirm << '\n';
    }
};

// Lead demonstrates multiple inheritance (Manager + Consultant)
class Lead : public Manager, public Consultant {
public:
    Lead(const string& nm, int a, int id, double sal, int team, const string& firm)
      : Manager(nm, a, id, sal, team), Consultant(firm) {
        cout << "[Lead] ctor for " << getName() << '\n';
    }

    ~Lead() override {
        cout << "[Lead] dtor\n";
    }

    // Resolve ambiguity by overriding show()
    void show() const override {
        cout << "[Lead::show] " << getName() << " is a lead at " << consultancyFirm << '\n';
    }
};

/*
  ------------------------------
  Hierarchical inheritance:
  Intern derives from Employee (same base Person -> many derived)
  ------------------------------
*/
class Intern : public Employee {
public:
    Intern(const string& nm, int a, int id, double sal)
        : Employee(nm, a, id, sal) {
        cout << "[Intern] ctor\n";
    }
    ~Intern() {
        cout << "[Intern] dtor\n";
    }
    void show() const override {
        cout << "[Intern::show] " << getName() << " is an intern.\n";
    }
};

/*
  ------------------------------
  Demonstrate virtual functions and pure virtual via polymorphic pointers
  ------------------------------
*/

int main() {
    cout << "----- OOP Concepts Demo Start -----\n\n";

    // Encapsulation + Constructors + this pointer + static member
    Person p1("Alice", 30);
    p1.introduce();                // overloaded method (no args)
    p1.introduce("happy");         // overloaded method (with arg)

    // using setter that returns reference (this usage)
    p1.setAge(31).setAge(32);      // chaining uses 'this' return
    cout << p1.getName() << " is " << p1.getAge() << " years old.\n\n";

    // Polymorphism: compile-time (operator overloading)
    Salary s1(5000), s2(1500);
    Salary s3 = s1 + s2;   // operator+ overloaded
    cout << "Combined Salary: " << s3 << '\n';

    // Single inheritance + abstraction + virtual functions
    Employee e1("Bob", 28, 1001, 7000.0);
    cout << "Employee pay: " << e1.getPay() << '\n';
    e1.show();             // calls Employee::show()

    // friend function modifies private salary
    promote(e1, 500.0);
    cout << "After promotion, pay: " << e1.getPay() << '\n';

    // Polymorphism (runtime): base pointer to derived object
    Person* ptr = &e1;
    ptr->show();           // Person* calls Employee::show() due to virtual

    // Multilevel inheritance
    Manager m("Carol", 35, 2001, 15000.0, 5);
    m.show();

    // Multiple inheritance
    Lead lead("Dave", 40, 3001, 20000.0, 10, "TopConsult");
    lead.show();          // Lead::show resolves ambiguity
    lead.showConsultancy();

    // Hierarchical inheritance (another child of Employee)
    Intern it("Eve", 22, 4001, 1000.0);
    it.show();

    // Demonstrate abstract class pointer (Payable*)
    Payable* pays[3];
    pays[0] = &e1;
    pays[1] = &m;
    pays[2] = &it;
    cout << "\nPayable objects:\n";
    for (int i = 0; i < 3; ++i) {
        cout << " - Pay: " << pays[i]->getPay() << '\n'; // dynamic dispatch to concrete getPay()
    }

    cout << "\nCurrent Person population (static member): " << Person::population << '\n';

    cout << "\n----- OOP Concepts Demo End -----\n";

    return 0;
}
