#include <iostream>
#include <string>
using namespace std;

struct Customer {
    int    id;
    string name;
    string address;
    int    units;
    float  bill;
    bool   paid;
};

void  displayBanner();
void  displayMenu();
void  addCustomer(Customer customers[], int &count, int MAX);
void  calculateBill(Customer customers[], int count);
void  viewAllCustomers(Customer customers[], int count);
void  searchCustomer(Customer customers[], int count);
void  payBill(Customer customers[], int count);
void  viewUnpaidBills(Customer customers[], int count);
void  updateUnits(Customer customers[], int count);
void  deleteCustomer(Customer customers[], int &count);
void  totalRevenue(Customer customers[], int count);
float computeBill(int units);
void  printCustomerInfo(Customer c);


int main() {

    const int MAX = 50;
    Customer customers[50];
    int count = 0;
    int choice;

    displayBanner();

    do {
        displayMenu();
    cout << "Enter your choice: ";
     cin  >> choice;

        if      (choice == 1) addCustomer(customers, count, MAX);
        else if (choice == 2) calculateBill(customers, count);
        else if (choice == 3) viewAllCustomers(customers, count);
        else if (choice == 4) searchCustomer(customers, count);
        else if (choice == 5) payBill(customers, count);
        else if (choice == 6) viewUnpaidBills(customers, count);
        else if (choice == 7) updateUnits(customers, count);
        else if (choice == 8) deleteCustomer(customers, count);
        else if (choice == 9) totalRevenue(customers, count);
        else if (choice==0)   cout << "\nThank you! Goodbye!" << endl;
        else              
          cout << "\n[!] Invalid choice. Try again." << endl;

    } while (choice != 0);

    return 0;
}


void displayBanner() {
    cout << "==========================================" << endl;
    cout << "   ELECTRICITY BILL MANAGEMENT SYSTEM     " << endl;
    cout << "==========================================" << endl;
}


void displayMenu() {
    cout << "\n---------- MAIN MENU ----------" << endl;
    cout << "1. Add New Customer"            << endl;
    cout << "2. Calculate Bill"              << endl;
    cout << "3. View All Customers"          << endl;
    cout << "4. Search Customer by ID"       << endl;
    cout << "5. Pay Bill"                    << endl;
    cout << "6. View Unpaid Bills"           << endl;
    cout << "7. Update Units Consumed"       << endl;
    cout << "8. Delete Customer"             << endl;
    cout << "9. Total Revenue Collected"     << endl;
    cout << "0. Exit"                        << endl;
    cout << "-------------------------------" << endl;
}


void addCustomer(Customer customers[], int &count, int MAX)
 {
    if (count >= MAX) {
        cout << "\n[!] Customer list is full!" << endl;
        return ;
    }

    cout << "\n--- Add New Customer ---" << endl;

    customers[count].id      = count + 1;
    customers[count].paid    = false;
    customers[count].bill    = 0;
    customers[count].units   = 0;

    cout << "Enter Name    : ";
    cin  >> customers[count].name;

    cout << "Enter Address : ";
    cin  >> customers[count].address;
    count++;
    cout << " Customer added! ID = " << count << endl;
}
float computeBill(int units) {
    float bill = 0;

    if (units <= 100) {
        bill = units * 5;
    }
    else if (units <= 200) {
        bill = (100 * 5) + ((units - 100) * 8);
    }
    else if (units <= 300) {
        bill = (100 * 5) + (100 * 8) + ((units - 200) * 12);
    }
    else {
        bill = (100 * 5) + (100 * 8) + (100 * 12) + ((units - 300) * 18);
    }

    float fixed = 150;
    float gst   = bill * 0.17;
    bill        = bill + fixed + gst;

    return bill;
}


void calculateBill(Customer customers[], int count) {
    if (count == 0) {
        cout<<endl;
        cout << " No customers found." << endl;
        return ;
    }

    int id;
    cout<<endl;
    cout << "Enter Customer ID to calculate bill: ";
    cin  >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            found = true;

            cout << "Enter units consumed: ";
            cin  >> customers[i].units;

            float gst  = 0;
            int   u    = customers[i].units;
            float base = 0;

            if (u <= 100)       base = u * 5;
            else if (u <= 200)  base = (100*5) + ((u-100)*8);
            else if (u <= 300)  base = (100*5) + (100*8) + ((u-200)*12);
            else                base = (100*5) + (100*8) + (100*12) + ((u-300)*18);

            gst = base * 0.17;

            customers[i].bill = computeBill(customers[i].units);
            customers[i].paid = false;

            cout << "\n======= BILL DETAILS =======" << endl;
            cout << "Customer      : " << customers[i].name    << endl;
            cout << "Address       : " << customers[i].address << endl;
            cout << "Units         : " << u                    << endl;
            cout << "Fixed Charges : Rs. 150"                  << endl;
            cout << "GST (17%)     : Rs. " << gst              << endl;
            cout << "TOTAL BILL    : Rs. " << customers[i].bill << endl;
            cout << "=============================" << endl;
        }
    }

    if (!found) {

        cout << " Customer with ID " << id << " not found." << endl;
    }
}


void printCustomerInfo(Customer c) {
    cout << "----------------------------" << endl;
    cout << "ID      : " << c.id          << endl;
    cout << "Name    : " << c.name        << endl;
    cout << "Address : " << c.address     << endl;
    cout << "Units   : " << c.units       << endl;
    cout << "Bill    : Rs. " << c.bill    << endl;
    if (c.paid)
        cout << "Status  : PAID"   << endl;
    else
        cout << "Status  : UNPAID" << endl;
}


void viewAllCustomers(Customer customers[], int count) {
    if (count == 0) {
        cout << "\n[!] No customers found." << endl;
        return;
    }

    cout << "\n===== ALL CUSTOMERS =====" << endl;
    for (int i = 0; i < count; i++) {
        printCustomerInfo(customers[i]);   
    }
    cout << "----------------------------" << endl;
}


void searchCustomer(Customer customers[], int count) {
    int id;
    cout << "\nEnter Customer ID to search: ";
    cin  >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            found = true;
            cout << "\n--- Customer Found ---" << endl;
            printCustomerInfo(customers[i]);  
        }
    }

    if (!found) {
        cout << " Customer not found." << endl;
    }
}


void payBill(Customer customers[], int count) {
    int id;
    cout<<endl;
    cout << "Enter Customer ID to pay bill: ";
    cin  >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            found = true;

            if (customers[i].paid) {
                cout << "[!] Bill already paid." << endl;
            }
            else if (customers[i].bill == 0) {
                cout << " Bill not calculated yet. Please calculate first." << endl;
            }
            else {
                float amount;
                cout << "Total Bill : Rs. " << customers[i].bill << endl;
                cout << "Enter amount paid: Rs. ";
                cin  >> amount;

                if (amount >= customers[i].bill) {
                    customers[i].paid  = true;
                    float change       = amount - customers[i].bill;
                    cout << " Bill paid successfully!" << endl;
                    if (change > 0)
                        cout << "Change returned: Rs. " << change << endl;
                }
                else {
                    cout << " Insufficient amount. Please pay full bill." << endl;
                }
            }
        }
    }

    if (!found) {
        cout << " Customer not found." << endl;
    }
}

void viewUnpaidBills(Customer customers[], int count) {
    cout<<endl;
    cout << "===== UNPAID BILLS =====" << endl;
    bool anyUnpaid = false;

    for (int i = 0; i < count; i++) {
        if (!customers[i].paid && customers[i].bill > 0) {
            anyUnpaid = true;
            cout << "ID   : " << customers[i].id    << endl;
            cout << "Name : " << customers[i].name  << endl;
            cout << "Bill : Rs. " << customers[i].bill << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!anyUnpaid){
        cout << " No unpaid bills found." << endl;
    }
}

void updateUnits(Customer customers[], int count) {
    int id;
    cout<<endl;
    cout << "Enter Customer ID to update units: ";
    cin  >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            found = true;
            cout << "Current Units: " << customers[i].units << endl;
            cout << "Enter new units: ";
            cin  >> customers[i].units;

            customers[i].bill = computeBill(customers[i].units);  
            
            customers[i].paid = false;

            cout << " Units updated. New Bill: Rs. " << customers[i].bill << endl;
        }
    }

    if (!found) {
        cout << " Customer not found." << endl;
    }
}


void deleteCustomer(Customer customers[], int &count) {
    int id;
    cout<<endl;
    cout << "Enter Customer ID to delete: ";
    cin  >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            found = true;

            for (int j = i; j < count - 1; j++) {
                customers[j]    = customers[j + 1];
                customers[j].id = j + 1;
            }

            count--;
            cout << "[OK] Customer deleted successfully." << endl;
        }
    }

    if (!found) {
        cout << " Customer not found." << endl;
    }
}

void totalRevenue(Customer customers[], int count) {
    float total    = 0;
    int paidCount  = 0;

    for (int i = 0; i < count; i++) {
        if (customers[i].paid) {
            total += customers[i].bill;
            paidCount++;
        }
    }
    cout<<endl;
    cout << "===== REVENUE SUMMARY =====" << endl;
    cout << "Total Customers : " << count      << endl;
    cout << "Paid Bills      : " << paidCount  << endl;
    cout << "Total Revenue   : Rs. " << total  << endl;
    cout << "===========================" << endl;
}
