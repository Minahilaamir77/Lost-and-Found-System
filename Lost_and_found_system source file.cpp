#include <iostream>
#include <string>

using namespace std;

// Base class for items
class Item {
protected:
string itemName;
string location;
string description;
string contactInfo;
string itemType; // Lost or Found

public:
// Initialize item data members
Item(string name, string loc, string desc, string contact, string type) {
itemName = name;
location = loc;
description = desc;
contactInfo = contact;
itemType = type;
}

// Virtual destructor cleans memory
virtual ~Item() {}

// Pure virtual display function
virtual void displayDetails() const = 0;

// Returns item name
string getItemName() const { return itemName; }
// Returns item location
string getLocation() const { return location; }
// Returns item description
string getDescription() const { return description; }
// Returns person contact info
string getContactInfo() const { return contactInfo; }
// Returns lost or found
string getItemType() const { return itemType; }
};

// Child class for lost items
class LostItem : public Item {
private:
string rewardAmount; // Cash reward if any

public:
// Passes parameters to base class
LostItem(string name, string loc, string desc, string contact, string reward)
: Item(name, loc, desc, contact, "Lost") {
rewardAmount = reward;
}

// Overrides display for lost items
void displayDetails() const override {
cout << "\n--- [LOST ITEM RECORD] ---" << endl;
cout << "Item Name   : " << itemName << endl;
cout << "Lost From   : " << location << endl;
cout << "Appearance  : " << description << endl;
cout << "Contact Info: " << contactInfo << endl;
cout << "Offered Reward: " << rewardAmount << endl;
cout << "--------------------------" << endl;
}
};

// Child class for found items
class FoundItem : public Item {
private:
string storageBin; // Physical locker storage number

public:
// Passes parameters to base class
FoundItem(string name, string loc, string desc, string contact, string bin)
: Item(name, loc, desc, contact, "Found") {
storageBin = bin;
}

// Overrides display for found items
void displayDetails() const override {
cout << "\n--- [FOUND ITEM RECORD] ---" << endl;
cout << "Item Name   : " << itemName << endl;
cout << "Found Near  : " << location << endl;
cout << "Description : " << description << endl;
cout << "Claim Contact: " << contactInfo << endl;
cout << "Holding Bin : " << storageBin << endl;
cout << "---------------------------" << endl;
}
};

// Core database management engine
class LostAndFoundSystem {
private:
Item* itemDatabase[100]; // Array of base class pointers
int maxCapacity;

public:
static int totalItemsRegistered; // Global static items counter

// Sets max database capacity
LostAndFoundSystem() {
maxCapacity = 100;
}

// Deallocates all dynamic objects safely
~LostAndFoundSystem() {
for (int i = 0; i < totalItemsRegistered; i++) {
delete itemDatabase[i];
}
}

// Adds new object to pointer array
void registerItem(Item* newItem) {
if (totalItemsRegistered < maxCapacity) {
itemDatabase[totalItemsRegistered] = newItem;
totalItemsRegistered++;
cout << "\n>> System Alert: " << newItem->getItemType() 
<< " Item Entry Logged Successfully!" << endl;
} else {
cout << "\n>> System Error: Database registry storage is full!" << endl;
}
}

// Displays database using runtime polymorphism
void displayAllRecords() const {
if (totalItemsRegistered == 0) {
cout << "\n>> No entries exist in the system database currently." << endl;
return;
}

cout << "\n==========================================" << endl;
cout << "    CURRENT DATABASE REGISTERED RECORDS   " << endl;
cout << "==========================================" << endl;
for (int i = 0; i < totalItemsRegistered; i++) {
itemDatabase[i]->displayDetails(); // Dynamic binding triggers here
}
}

// Checks string names for matches
void crossReferenceDatabase() const {
if (totalItemsRegistered < 2) {
cout << "\n>> Alert: Insufficient database logs to cross-reference entries." << endl;
return;
}

bool matchFound = false;
cout << "\n==========================================" << endl;
cout << "  RUNNING CROSS-REFERENCE SEARCH ENGINE   " << endl;
cout << "==========================================" << endl;

// Compare every entry with each other
for (int i = 0; i < totalItemsRegistered; i++) {
for (int j = i + 1; j < totalItemsRegistered; j++) {

// Compare only Lost with Found types
if (itemDatabase[i]->getItemType() != itemDatabase[j]->getItemType()) {

// Simple direct text matching rule
if (itemDatabase[i]->getItemName() == itemDatabase[j]->getItemName()) {

matchFound = true;
cout << "\n🎯 MATCH DETECTED FOR VALUE: '" << itemDatabase[i]->getItemName() << "'" << endl;
cout << "------------------------------------------" << endl;

// Prints specific owner and finder info
if (itemDatabase[i]->getItemType() == "Lost") {
cout << "👤 Lost By   : " << itemDatabase[i]->getContactInfo() << endl;
cout << "🕵️ Found By  : " << itemDatabase[j]->getContactInfo() << endl;
cout << "📍 Locations : " << itemDatabase[i]->getLocation() 
<< " vs " << itemDatabase[j]->getLocation() << endl;
} else {
cout << "👤 Lost By   : " << itemDatabase[j]->getContactInfo() << endl;
cout << "🕵️ Found By  : " << itemDatabase[i]->getContactInfo() << endl;
cout << "📍 Locations : " << itemDatabase[j]->getLocation() 
<< " vs " << itemDatabase[i]->getLocation() << endl;
}
cout << "------------------------------------------" << endl;
}
}
}
}

if (!matchFound) {
cout << "\n>> Search Finished: Zero automatic matches recognized at this moment." << endl;
}
}
};

// Definition of external static counter
int LostAndFoundSystem::totalItemsRegistered = 0;

// Main execution entry point
int main() {
LostAndFoundSystem campusSystem; // Instantiate central management system
int primaryChoice;

cout << "===============================================" << endl;
cout << "    CAMPUS LOST AND FOUND MANAGEMENT SYSTEM    " << endl;
cout << "===============================================" << endl;

// Standard dashboard interactive loops
do {
cout << "\n----- MAIN MENU -----" << endl;
cout << "1. Report a Lost Possession" << endl;
cout << "2. Log a Found Item Entry" << endl;
cout << "3. View All Registered Logs" << endl;
cout << "4. Run Match Identification Cross-Reference" << endl;
cout << "5. Exit Application" << endl;
cout << "Select Operation Option (1-5): ";
cin >> primaryChoice;

// Handles accidental stream crash failures
if (cin.fail()) {
cin.clear();
string clearingBuffer;
cin >> clearingBuffer;
continue;
}
cin.ignore(); // Flush stray newline markers

// Block handles lost entry inputs
if (primaryChoice == 1) {
string name, loc, desc, contact, reward;

cout << "\n--- ENTER LOST ITEM METADATA ---" << endl;
cout << "Identify Item Name (e.g. Ring, Phone, Wallet): ";
getline(cin, name);
cout << "Estimated Location Lost At: ";
getline(cin, loc);
cout << "Describe Appearance Details: ";
getline(cin, desc);
cout << "Provide Personal Contact Information: ";
getline(cin, contact);
cout << "Enter Offered Monetary Reward (or None): ";
getline(cin, reward);

// Dynamically register new lost object
campusSystem.registerItem(new LostItem(name, loc, desc, contact, reward));

// Block handles found entry inputs
} else if (primaryChoice == 2) {
string name, loc, desc, contact, bin;

cout << "\n--- ENTER FOUND ITEM METADATA ---" << endl;
cout << "Identify Item Name Found: ";
getline(cin, name);
cout << "Location Identified At: ";
getline(cin, loc);
cout << "Describe Object Physical Condition: ";
getline(cin, desc);
cout << "Provide Finder's Contact Information: ";
getline(cin, contact);
cout << "Assigned Secure Holding Storage Bin #: ";
getline(cin, bin);

// Dynamically register new found object
campusSystem.registerItem(new FoundItem(name, loc, desc, contact, bin));

// Display all records block
} else if (primaryChoice == 3) {
campusSystem.displayAllRecords();

// Run match engine block
} else if (primaryChoice == 4) {
campusSystem.crossReferenceDatabase();

// Graceful exit choice routine
} else if (primaryChoice == 5) {
cout << "\nThank you for using Campus Lost and Found System. Terminating Program..." << endl;
cout << "Total Database Logs Processed: " << LostAndFoundSystem::totalItemsRegistered << endl;
} else {
cout << "\n>> Selection Invalid! Input an integer index from 1 up to 5." << endl;
}

} while (primaryChoice != 5); // Exit when value equals 5

return 0; // Execution successful termination
}