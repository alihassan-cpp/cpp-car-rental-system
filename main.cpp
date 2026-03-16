#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Car {
private:
    int carID;
    string brand;
    string model;
    double pricePerDay;
    bool isRented;

public:
    double getPricePerDay() {
        return pricePerDay;
    }
    string getBrand() {
        return brand;
    }

    string getModel() {
        return model;
    }

    double getPrice() {
        return pricePerDay;
    }

    bool getStatus() {
        return isRented;
    }
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

        if (carExists(id)) {
            cout << "Error: Car ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Brand: ";
        getline(cin, brand);

        cout << "Enter Model: ";
        getline(cin, model);

        cout << "Enter Price per day: ";
        cin >> price;

        cars.push_back(Car(id, brand, model, price));
        saveToFile();
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
        int days;

        cout << "\nEnter Car ID to rent: ";
        cin >> id;

        for (auto& c : cars) {

            if (c.getCarID() == id) {

                if (c.rentedStatus()) {
                    cout << "Car already rented.\n";
                    return;
                }

                cout << "Enter number of days: ";
                cin >> days;

                double totalCost = days * c.getPricePerDay();

                cout << "Total rental cost: " << totalCost << endl;

                c.rentCar();

                saveToFile();

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
                saveToFile();
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
    void deleteCar() {

        int id;

        cout << "\nEnter Car ID to delete: ";
        cin >> id;

        for (auto it = cars.begin(); it != cars.end(); it++) {

            if (it->getCarID() == id) {

                cars.erase(it);
                saveToFile();

                cout << "Car deleted successfully.\n";
                return;
            }
        }

        cout << "Car not found.\n";
    }
    bool carExists(int id) {

        for (auto& c : cars) {
            if (c.getCarID() == id) {
                return true;
            }
        }

        return false;
    }
    void saveToFile() {

        ofstream file("cars.txt");

        for (auto& c : cars) {

            file << c.getCarID() << " "
                << c.getBrand() << " "
                << c.getModel() << " "
                << c.getPrice() << " "
                << c.getStatus() << endl;
        }

        file.close();
    }
    void loadFromFile() {

        ifstream file("cars.txt");

        int id;
        string brand, model;
        double price;
        bool status;

        while (file >> id >> brand >> model >> price >> status) {

            Car car(id, brand, model, price);

            if (status)
                car.rentCar();

            cars.push_back(car);
        }

        file.close();
    }
};

int main() {

    RentalSystem system;
    system.loadFromFile();
    int choice;

    while (true) {

        cout << "\n--- Car Rental System ---\n";
        cout << "1. Add Car\n";
        cout << "2. Display Cars\n";
        cout << "3. Rent Car\n";
        cout << "4. Return Car\n";
        cout << "5. Search Car\n";
        cout << "6. Delete Car\n";
        cout << "7. Exit\n";
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
            system.deleteCar();
            break;

        case 7:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
