//Hotel Management System


#include <iostream>
#include <string>
using namespace std;

// These arrays and variables collectively store information about all 25 hotel rooms
const int allrooms = 25;
string name[allrooms], creditnumb[allrooms];
bool occupation[allrooms];
double roomprice[allrooms];
int i;

void reserveroom()
{
    cout << "\nHotel Rooms Information:" << endl;
    for (i = 0; i < allrooms; ++i)
    {

        /* This loop keeps repeating until it prints out details about all the rooms in the hotel.
        For each room, it prints out details including the room's number, room type, occupancy status,
        guest's name, and the price per night. */

        cout << "Room Number: " << i + 1;

        //This if statement helps keep the text neat when room information is listed.
        if (i < 9)
            cout << " ";

        // This if statement categorizes the room types based on the value of i.
        cout << "   | Type: ";
        if (i < 5)
            cout << "Single room";
        else if (i < 10)
            cout << "Double room";
        else if (i < 15)
            cout << "Deluxe Room";
        else if (i < 20)
            cout << "Suite      ";
        else if (i <= 24)
            cout << "Villa      ";

        /* The following line prints the status of the room. We used (? :)
       to output "Occupied" if occupation[i] is true, and "Available" if false. */

        cout << "   | Status: " << (occupation[i] ? "Occupied" : "Available");

        // This if statement prints the guest's name only if the room is occupied.

        if (occupation[i]) {
            cout << "    | Guest Name: " << name[i];
        }
        cout << "   | Price: " << roomprice[i] << " JDs per night" << endl;
    }


    /* The following block of code stores the guest's name, the chosen payment method
    and credit info (only for credit card payments)*/

    string guestname, credit, paymentmethod;
    int roomnumber;

    cout << "\nEnter your name: ";
    cin >> guestname;

    cout << "Enter desired room's number: ";
    cin >> roomnumber;

    cout << "Choose payment method (cash/credit): ";
    cin >> paymentmethod;

    if (paymentmethod != "cash" && paymentmethod != "credit")
    {
        cout << "Invalid payment method." << endl;
        return;
    }
    else if (paymentmethod == "credit") {
        cout << "Enter your credit information: ";
        cin >> credit;
    }

    /* This nested if statement firstly ensures that the inputted room number is valid, then it reserves the room
    only if the room us available. If the room is available, it reserves the room, updates the occupation status,
     and stores the guest's name. */

    if (roomnumber >= 1 && roomnumber <= 25) {
        if (!occupation[roomnumber - 1])
        {
            cout << "Room " << roomnumber << " has been reserved for " << guestname << "." << endl;
            occupation[roomnumber - 1] = true;
            name[roomnumber - 1] = guestname;
        }
        else
        {
            cout << "Room " << roomnumber << " is already occupied." << endl;
        }
    }
    else
    {
        cout << "Invalid room number." << endl;
    }

}
void listavailableservices() {

    //This line declares an array roomtype containing the names of the five different room types to be printed out later.

    string roomtype[] = { "Single room", "Double room", "Deluxe Room", "Suite", "Villa" };

    /* The 2D array "services" stores information about services for each room type. It's a 5x3 array where
  each row corresponds to a room type, and each column corresponds to a service.*/

    int r, c;
    string services[5][6] =
    { {"Free Wi-Fi and TV", "Room Service" , "Free Dinner Buffet (3:30 PM everyday)", "\nShared Entertainment Space ", "Public Pools (8:00AM - 8:OOPM)", "Additional Fees for Gym and Spa Services"},
     {"Free Wi-Fi and TV", "Room Service" , "Free Dinner Buffet (3:30 PM everyday)", "\nShared Entertainment Space ", "Public Pools (8:00AM - 8:OOPM)", "Additional Fees for Gym and Spa Services"},
     {"Free Wi-Fi and TV", "Room Service" , "24/7 Dining Services" , "Private Lounge", "\nPublic Pools (8:00AM - 8:OOPM)", "Additional Fees for Gym and Spa Services"},
     {"Free Wi-Fi and TV", "Room Service" , "24/7 Dining Services" , "Private Lounge", "\nPublic Pools (8:00AM - 8:OOPM)","Additional Fees for Gym and Spa Services"},
     {"Free Wi-Fi and TV", "Room Service" , "24/7 Dining Services" , "Private Lounge", "\nPrivate Pool with a View","Free Gym and Spa Services"} };

    cout << "\nHotel Rooms Services Information:" << endl;

    /*This nested loop structure ensures that the code goes through each room type then prints out the available services
    for each room type. The outer loop manages different room types, and the inner loop manages services for each room type.*/

    for (r = 0; r < 5; r++)
    {
        cout << "\n" << roomtype[r] << ":" << endl;
        cout << "Provided Services: ";

        for (c = 0; c < 6; c++)
        {
            cout << services[r][c];

            // This if statement adds a comma if it's not the last service
            if (c < 5)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

double calculatebalance(int roomNumber, int n) {

    /* This function is defined to calculate and display the balance for a specific room based on
  the number of nights stayed and room type only if the room is occupied and room number is valid. */

    if (roomNumber >= 1 && roomNumber <= 25) {
        if (occupation[roomNumber - 1])
        {
            cout << "Balance for Room " << roomNumber << ": " << roomprice[roomNumber - 1] * n << " JDs" << endl;
            return roomprice[roomNumber - 1];
        }
        else
        {
            cout << "Room " << roomNumber << " is not occupied." << endl;
            return 0.0;
            // Return 0 if the room is not occupied
        }
    }
    else {
        cout << "Invalid room number." << endl;
        return -1.0;
        // Return -1 for an invalid room number (room number out of range)
    }
}

void checkout() {
    /* This function asks the user for the room number they want to check out from then
  in makes sure the room number is valid and  the room is occupied. If yes, it checks
  out the guest and updates the occupation status. */
    int roomnum;

    cout << "Enter the room number to check-out: ";
    cin >> roomnum;
    if (roomnum >= 1 && roomnum <= allrooms) {
        if (occupation[roomnum - 1]) {
            cout << "Checking out from Room " << roomnum << "... We hope you enjoyed your stay!" << endl;
            occupation[roomnum - 1] = false;
        }
        else {
            cout << "Room " << roomnum << " is not occupied." << endl;
        }
    }
    else {
        cout << "Invalid room number." << endl;
    }
}
int main() {

    // This loop is used to initialize details about each hotel room.

    for (i = 0; i < allrooms; ++i) {
        occupation[i] = false;
        /*this statement initializes the occupation of the room to false
        meaning that the room is initially available.*/
        if (i < 5) {
            // Price for a single room in JDs per night
            roomprice[i] = 149.99;
        }
        else if (i < 10) {
            // Price for a double room in JDs per night
            roomprice[i] = 179.99;
        }
        else if (i < 15) {
            // Price for a deluxe room in JDs per night
            roomprice[i] = 199.99;
        }
        else if (i < 20) {
            // Price for a suite in JDs per night
            roomprice[i] = 249.99;
        }
        else if (i < 25) {
            // Price for a Villa in JDs per night
            roomprice[i] = 299.99;
        }
    }
    int x;
    cout << "Welcome to our Hotel Management System!" << endl;
    //the following loop excutes over and over until the user exits the system by entering the choice 4.
    do {
        cout << "\n1) Make a Reservation" << endl;
        cout << "2) List Available Services" << endl;
        cout << "3) Calculate Balance" << endl;
        cout << "4) Check-out from a Room" << endl;
        cout << "5) Exit\n" << endl;
        cout << "Choose a number: ";
        cin >> x;

        //each case here corresponds to a function defined above

        switch (x) {
        case 1:
            reserveroom();
            break;
        case 2:
            listavailableservices();
            break;
        case 3:
            int roomNumber, n;
            cout << "Enter the room number: ";
            cin >> roomNumber;
            cout << "Enter the number of nights spent to check the balance: ";
            cin >> n;
            calculatebalance(roomNumber, n);
            break;
        case 4:
            checkout();
            break;
        case 5:
            cout << "Exiting hotel system..." << endl;
            break;
        default:
            cout << "Please enter a valid option." << endl;
        }
    } while (x != 5);

    return 0;
}
