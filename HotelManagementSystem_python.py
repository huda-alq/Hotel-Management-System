import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 

#total room numbers
allrooms = 25  

#this is to restore the rooms information
roomdata = {
    "Room Number": list(range(1, allrooms + 1)),
    "Type": ["Single room"] * 5 + ["Double room"] * 5 + ["Deluxe Room"] * 5 + ["Suite"] * 5 + ["Villa"] * 5, 
    "Status": ["Available"] * allrooms,
    "Price": [149.99] * 5 + [179.99] * 5 + [199.99] * 5 + [249.99] * 5 + [299.99] * 5, 
    "Guest Name": [""] * allrooms,
    "Credit Info": [""] * allrooms,
    "Rating": [np.nan] * allrooms  #its nan because there is no ratings yet
}

#changed the dictionary into DataFrame
df = pd.DataFrame(roomdata)

def reserveroom():
    print("\nHotel Rooms Information:")
    #this format is to display the title of each information
    print("{:<12} {:<15} {:<12} {:<10} {:<15}".format(
        "Room Number", "Type", "Status", "Price", "Guest Name"
    ))
    #this format is to display the actual information
    for i in range(allrooms):
        print("{:<12} {:<15} {:<12} {:<10} {:<15}".format(
            df.loc[i, "Room Number"],
            df.loc[i, "Type"],
            df.loc[i, "Status"],
            df.loc[i, "Price"],
            df.loc[i, "Guest Name"]
        ))
    
    guestname = input("\nEnter your name: ")
    roomnumber = int(input("Enter desired room's number: "))
    paymentmethod = input("Choose payment method (cash/credit): ")
    
    if paymentmethod not in ["cash", "credit"]:
        print("Invalid payment method.")
        return
    elif paymentmethod == "credit":
        credit = input("Enter your credit information: ")
        df.loc[roomnumber - 1, "Credit Info"] = credit
    #if statement to change the occupation from available into occupied
    if 1 <= roomnumber <= allrooms:
        if df.loc[roomnumber - 1, "Status"] == "Available":
            df.loc[roomnumber - 1, "Status"] = "Occupied"
            df.loc[roomnumber - 1, "Guest Name"] = guestname
            print(f"Room {roomnumber} has been reserved for {guestname}.")
        else:
            print(f"Room {roomnumber} is already occupied.")
    else:
        print("Invalid room number.")

def listavailableservices():
    #dictionary to list available services for each room
    services = {
        "Single room": ["Free Wi-Fi and TV", "Room Service", "Free Dinner Buffet (3:30 PM everyday)", "Shared Entertainment Space", "Public Pools (8:00AM - 8:00PM)", "Additional Fees for Gym and Spa Services"],
        "Double room": ["Free Wi-Fi and TV", "Room Service", "Free Dinner Buffet (3:30 PM everyday)", "Shared Entertainment Space", "Public Pools (8:00AM - 8:00PM)", "Additional Fees for Gym and Spa Services"],
        "Deluxe Room": ["Free Wi-Fi and TV", "Room Service", "24/7 Dining Services", "Private Lounge", "Public Pools (8:00AM - 8:00PM)", "Additional Fees for Gym and Spa Services"],
        "Suite": ["Free Wi-Fi and TV", "Room Service", "24/7 Dining Services", "Private Lounge", "Public Pools (8:00AM - 8:00PM)", "Additional Fees for Gym and Spa Services"],
        "Villa": ["Free Wi-Fi and TV", "Room Service", "24/7 Dining Services", "Private Lounge", "Private Pool with a View", "Free Gym and Spa Services"]
    }
    
    print("\nHotel Rooms Services Information:")
    #loop to go through all services
    for roomtype, servicelist in services.items():
        print(f"\n{roomtype}:")
        result = "Provided Services: "
        for service in servicelist:
            result += service + ", "
        result = result.rstrip(", ")  
        print(result)

def calculatebalance(roomNumber, n):
    if 1 <= roomNumber <= allrooms:
        #loc is to check if the room is occupied and if so to calculate the balance
        if df.loc[roomNumber - 1, "Status"] == "Occupied":
            price = df.loc[roomNumber - 1, "Price"]
            print(f"Balance for Room {roomNumber}: {price * n} JDs")
            return price
        else:
            print(f"Room {roomNumber} is not occupied.")
            return 0.0
    else:
        print("Invalid room number.")
        return -1.0

def checkout():
    roomnum = int(input("Enter the room number to check-out: "))
    if 1 <= roomnum <= allrooms:
        #loc here to see if it's occupied and if so let the user rate the visit and check out
        if df.loc[roomnum - 1, "Status"] == "Occupied":
            while True:
                rating = int(input("Please rate your stay (1 to 5): "))
                if 1 <= rating <= 5:
                    break
                else:
                    print("Invalid rating. Please enter a number between 1 and 5.")

            #here is the updated status
            df.loc[roomnum - 1, "Status"] = "Available"
            df.loc[roomnum - 1, "Guest Name"] = ""
            df.loc[roomnum - 1, "Credit Info"] = ""
            df.loc[roomnum - 1, "Rating"] = rating  #this saves the rating to do the pie chart

            print(f"Checking out from Room {roomnum}... We hope you enjoyed your stay!")
        else:
            print(f"Room {roomnum} is not occupied.")
    else:
        print("Invalid room number.")

def plotdraw():
    #this to change the rating value from nan to a number
    actualrating = [not np.isnan(x) for x in df["Rating"]]
    
    #saves the value of rating to draw the pie chart
    saverating = df["Rating"][actualrating]
    
    if saverating.empty:
        print("No ratings available to display.")
        return
    
    #counts the ratings
    counts = saverating.value_counts().sort_index()
    
    #information to draw the chart
    plt.figure(figsize=(8, 8))
    plt.pie(counts, labels=counts.index, autopct='%1.1f%%', startangle=140)
    plt.title("Rating Distribution")
    plt.show()

def main():
    print("Welcome to our Hotel Management System!")
    while True:
        print("\n1) Make a Reservation")
        print("2) List Available Services")
        print("3) Calculate Balance")
        print("4) Check-out from a Room")
        print("5) Display Rating Distribution")
        print("6) Exit\n")
        x = int(input("Choose a number: "))
        
        if x == 1:
            reserveroom()
        elif x == 2:
            listavailableservices()
        elif x == 3:
            roomNumber = int(input("Enter the room number: "))
            n = int(input("Enter the number of nights spent to check the balance: "))
            calculatebalance(roomNumber, n)
        elif x == 4:
            checkout()
        elif x == 5:
            plotdraw()  
        elif x == 6:
            print("Exiting hotel system...")
            break
        else:
            print("Please enter a valid option.")

if __name__ == "__main__":
    main()
