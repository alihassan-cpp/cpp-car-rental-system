#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car {
private:
    int carID;
    string brand;
    string model;
    double pricePerDay;
    bool isRented;

public:
    Car(int id, string b, string m, double price) {
        carID = id;
        brand = b;
        model = m;
        pricePerDay = price;
        isRented = false;
    }

    int getCarID() {
        return carID;
    }

    bool rentedStatus() {
        return isRented;
    }

    void rentCar() {
        if (!isRented) {
            isRented = true;
            cout << "Car rented successfully.\n";
        }
        else {
            cout << "Car is already rented.\n";
        }
    }

    void returnCar() {
        if (isRented) {
            isRented = false;
            cout << "Car returned successfully.\n";
        }
        else {
            cout << "Car was not rented.\n";
        }
    }

    void display() {
        cout << "Car ID: " << carID << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Price per day: " << pricePerDay << endl;
        cout << "Status: " << (isRented ? "Rented" : "Available") << endl;
        cout << "---------------------------\n";
    }
};

class RentalSystem {
private:
    vector<Car> cars;

public:

    void addCar() {

        int id;
        string brand, model;
        double price;

        cout << "\nEnter Car ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Brand: ";
        getline(cin, brand);

        cout << "Enter Model: ";
        getline(cin, model);

        cout << "Enter Price per day: ";
        cin >> price;

        cars.push_back(Car(id, brand, model, price));

        cout << "Car added successfully.\n";
    }

    void displayCars() {

        if (cars.empty()) {
            cout << "No cars available.\n";
            return;
        }

        cout << "\n--- Car List ---\n";

        for (auto& c : cars) {
            c.display();
        }
    }

    void rentCar() {

        int id;

        cout << "\nEnter Car ID to rent: ";
        cin >> id;

        for (auto& c : cars) {

            if (c.getCarID() == id) {
                c.rentCar();
                return;
            }
        }

        cout << "Car not found.\n";
    }

    void returnCar() {

        int id;

        cout << "\nEnter Car ID to return: ";
        cin >> id;

        for (auto& c : cars) {

            if (c.getCarID() == id) {
                c.returnCar();
                return;
            }
        }

        cout << "Car not found.\n";
    }
    void searchCar() {

        int id;

        cout << "\nEnter Car ID to search: ";
        cin >> id;

        for (auto& c : cars) {

            if (c.getCarID() == id) {

                cout << "\nCar Found:\n";
                c.display();
                return;
            }
        }

        cout << "Car not found.\n";
    }
};

int main() {

    RentalSystem system;
    int choice;

    while (true) {

        cout << "\n--- Car Rental System ---\n";
        cout << "1. Add Car\n";
        cout << "2. Display Cars\n";
        cout << "3. Rent Car\n";
        cout << "4. Return Car\n";
        cout << "5. Search Car\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            system.addCar();
            break;

        case 2:
            system.displayCars();
            break;

        case 3:
            system.rentCar();
            break;

        case 4:
            system.returnCar();
            break;

        case 5:
            system.searchCar();
            break;

        case 6:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
