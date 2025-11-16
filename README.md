# OOP Concepts Demonstration in C++

This project contains a single, comprehensive C++ program that
demonstrates all major Object-Oriented Programming (OOP) concepts in one
place. Each concept is accompanied by comments in the source code to
help you understand how and where it is applied.

------------------------------------------------------------------------

## Covered OOP Concepts

### 1. Encapsulation

Encapsulation is demonstrated by keeping class variables private and
exposing controlled access through getters and setters. The `Person`
class encapsulates `age` and uses a setter method that also demonstrates
the use of the `this` pointer.

### 2. Inheritance and Its Types

Multiple forms of inheritance are demonstrated: - **Single
Inheritance:** `Employee` inherits from `Person` - **Multilevel
Inheritance:** `Manager` inherits from `Employee` - **Multiple
Inheritance:** `Lead` inherits from both `Manager` and `Consultant` -
**Hierarchical Inheritance:** `Intern` inherits from `Employee`

### 3. Polymorphism (Compile-Time and Runtime)

-   **Compile-Time Polymorphism:** Achieved through function overloading
    and operator overloading in the `Salary` class.
-   **Runtime Polymorphism:** Demonstrated through virtual functions
    (`show()`) and overriding in derived classes.

### 4. Abstraction

The class `Payable` is an abstract class containing a pure virtual
function `getPay()`, enforcing derived classes to provide their own
implementation.

### 5. Virtual and Pure Virtual Functions

-   Virtual functions allow runtime polymorphism.
-   Pure virtual functions create abstract classes that cannot be
    instantiated.

### 6. Friend Function

The `promote()` function is declared a friend of `Employee`, which
allows it to access the private salary data and modify it.

### 7. Constructors and Destructors

The program demonstrates: - Default constructors - Parameterized
constructors - Copy constructors - Move constructors - Destructors Each
class prints messages during construction and destruction for better
understanding of object lifecycle.

### 8. Static Members

The `Person` class maintains a static variable `population` to track the
number of alive objects.

### 9. Operator Overloading

The `Salary` class overloads the `+` operator to allow the addition of
salary objects.

### 10. The `this` Pointer

Used inside setters to refer to the calling object.

------------------------------------------------------------------------

## File Included

-   `oop.cpp`: Full C++ source code with comments explaining every
    concept.

------------------------------------------------------------------------

## How to Compile

``` bash
g++ -std=c++17 oop.cpp -o oop
./oop
```

------------------------------------------------------------------------

## Purpose

This consolidated example helps beginners and intermediate C++ learners
understand all OOP concepts clearly within one complete and real-world
style program.
