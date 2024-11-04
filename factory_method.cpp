#include<iostream>
#include<string>

using namespace std;

// The Product interface declares the operations that all concrete  products must implement
class Product {
    public:
        virtual ~Product() { };
        virtual string Operation() const = 0;
};


// Concrete Products provide various implementations of the Product interface

class ConcreteProduct0 : public Product {
    public:
        string Operation() const override {
            return "{result of the ConcreteProduct0}";
        }
};

class ConcreteProduct1 : public Product {
    public:
        string Operation() const override {
            return "{result of the ConcreteProduct1}";
        }
};


/*
The Creator class declares the factory method that is supposed to return  an object
of a Product class. The Creator's subclasses usually provide the implementation of this method.
*/

// The Creator might also provide some default implementation of the factory method
class Creator {
    public:
        virtual ~Creator() { };
        virtual Product* FactoryMethod() const = 0;
        // Despite it's name, the Creator's primary responsibility is not creating products. Usually, it contains some core bussiness logic
        // that relies on Product objects, returned by the factory method. Subclasses can inderectly change that bussiness logic by overriding the factory method
        // and returning a different type of product from it

        string SomeOperation() const {
            // Call the factory method to creat a Product object
            Product* product = this->FactoryMethod();

            // Now, use the product
            string result = "Creator: The same creator's code has just worked with " + product->Operation();
            delete product;
            return result;
        }
};


// Concrete Creators override the factory method in order to change the resulting product's type

class ConcreteCreator0 : public Creator {
    // The signature of the method still uses the abstract product type, even though the concrete product is actually returned from the method.
    // This way the Creator can stay independent of concrete product classes. 
    
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProduct0();
        }
};

class ConcreteCreator1 : public Creator {
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProduct1();
        }
};


// The client code works with an instance of a concrete creator, albeit through it's base interface.
// As long as the client keeps working with the creator via the base interface, you can pass it any creator's subclass

void ClientCode(const Creator& creator) {
    cout << "Client: I'm not aware of the creator's class, but it still works.\n" << creator.SomeOperation() << endl;
};


// The Application picks a creator's type depending on the configuration of enviroment

int main() {
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator0 = new ConcreteCreator0();
    ClientCode(*creator0);
    
    cout << "\nApp: Launched with the ConcreteCreator2.";
    Creator* creator1 = new ConcreteCreator1();
    ClientCode(*creator1);

    delete creator0;
    delete creator1;

    return 0;
}
