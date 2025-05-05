#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global simulation variables:
vector<bool> train;  // Each element represents a cabin's light state (true = ON, false = OFF)
int currentPosition = 0; // Our current position in the train

// Helper functions simulating allowed operations:
void setLight(bool state) {
    train[currentPosition] = state;
}

bool getLight() {
    return train[currentPosition];
}

void moveForward() {
    currentPosition = (currentPosition + 1) % train.size();
}

void moveBackward() {
    currentPosition = (currentPosition - 1 + train.size()) % train.size();
}

// In our simulation, we use the fact that the starting cabin is at index 0.
bool isBaseCabin() {
    return (currentPosition == 0);
}

// The main algorithm for counting cabins.
// Assumptions:
// - You have an internal memory of the starting cabin (base), which is at index 0.
// - At start, we mark the base by turning its light ON and leave it unchanged.
// - For every other cabin you visit, you standardize it by switching its light OFF.
// - After each new cabin, you perform a backtracking probe: move backward "count" steps
//   and if you land at the base (with its light still ON), then you have completed a full cycle.
int countCabins() {
    // Step 1: Mark the starting (base) cabin.
    setLight(true); // Mark base as ON.
    int count = 1;  // We start counting with the base.
    
    while (true) {
        // Move forward to the next cabin.
        moveForward();
        count++; // A new cabin is encountered.
        
        // Standardize the current cabin: if it isn’t the base and its light is ON,
        // set it to OFF.
        if (!isBaseCabin() && getLight()) {
            setLight(false);
        }
        
        // --- Backtracking Probe ---
        // From the current cabin, move backward exactly 'count' steps.
        int steps = count;
        // Backup current position.
        // (For simulation purposes, we will restore our forward position after probing.)
        for (int i = 0; i < steps; i++) {
            moveBackward();
        }
        
        // Check if we reached the starting cabin (base) and if its light is still ON.
        if (isBaseCabin() && getLight() == true) {
            // We have successfully made a complete cycle.
            // Turn off the base light to finalize the result.
            setLight(false);
            // Restore the forward position (although not needed once we return).
            for (int i = 0; i < steps; i++) {
                moveForward();
            }
            return count;
        } else {
            // Restore forward position to continue with the next cabin.
            for (int i = 0; i < steps; i++) {
                moveForward();
            }
        }
    }
}

int main() {
    // For testing, we simulate a train with a random number of cabins.
    // (In practice, your algorithm does not know the number.)
    srand(time(0));
    int numCabins = 10 + rand() % 11;  // Random train size between 10 and 20.
    
    // Initialize the train with random ON (true) / OFF (false) states.
    train.resize(numCabins);
    for (int i = 0; i < numCabins; i++) {
        train[i] = (rand() % 2 == 0);  // Random true/false.
    }
    
    // For clarity in debugging, output the initial light states.
    cout << "Initial light states (cabin 0 is the starting cabin):\n";
    for (int i = 0; i < numCabins; i++) {
        cout << "Cabin " << i << ": " << (train[i] ? "ON" : "OFF") << endl;
    }
    cout << "\nCounting cabins...\n";
    
    // Reset position to 0 (our starting cabin).
    currentPosition = 0;
    int totalCabins = countCabins();
    
    cout << "\nTotal cabins counted: " << totalCabins << endl;
    // (For verification, print the actual number too.)
    cout << "Actual number of cabins: " << numCabins << endl;
    
    return 0;
}
