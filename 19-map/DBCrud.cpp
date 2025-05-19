#include <iostream> // Include the I/O stream library
#include <map>      // Include the map library
#include <string>   // Include the string library

struct Student {
  std::string name;   // Student's name
  int age;            // Student's age
  std::string course; // Student's course
};

std::map<int, Student> DB; // Declare a map to simulate a database, with integer
                           // keys (ID) and Student values

bool exists(int id) { // Function to check if a student with the given ID exists
                      // in the DB
  return DB.find(id) != DB.end();
}

int create(
    const std::string &name, int age,
    const std::string &course) { // Function to add a new student to the DB
  int id = DB.size() + 1; // Generate ID based on the current size of the DB
  DB[id] = {name, age, course}; // Add the new student to the DB
  return id;                    // Return the ID of the newly created record
}

void read(int id) { // Function to retrieve and display a student's details from
                    // the DB
  if (exists(id)) { // Use the exists function to check if the student exists
    std::cout << "ID: " << id << ", Name: " << DB[id].name
              << ", Age: " << DB[id].age << ", Course: " << DB[id].course
              << std::endl;
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

void update(int id, const std::string &name, int age,
            const std::string
                &course) { // Function to update a student's details in the DB
  if (exists(id)) { // Use the exists function to check if the student exists
    DB[id] = {name, age, course}; // Update the student's details in the DB
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

void remove(int id) { // Function to remove a student from the DB
  if (exists(id)) {   // Use the exists function to check if the student exists
    DB.erase(id);     // Remove the student from the DB
  } else {
    std::cout << "Student with ID: " << id << " not found." << std::endl;
  }
}

int find(const std::string
             &name) { // Function to find a student by name and return their ID
  for (const auto &pair : DB) { // Loop over all elements in the DB
    if (pair.second.name ==
        name) { // If the name of the current student matches the given name
      return pair.first; // Return the ID of the student
    }
  }
  return -1; // If no student with the given name was found, return -1
}

int main() { // Main function
  int id1 =
      create("John Doe", 20, "Computer Science"); // Add a new student to the DB
  int id2 =
      create("Jane Doe", 22,
             "Electrical Engineering"); // Add another new student to the DB

  read(id1); // Retrieve and display the first student's details
  read(id2); // Retrieve and display the second student's details

  update(id1, "John Doe", 21,
         "Computer Science"); // Update the first student's details

  remove(id2); // Remove the second student from the DB

  int foundId = find("John Doe"); // Find a student by name and get their ID
  if (foundId != -1) {            // If the student was found
    std::cout << "Found student with ID: " << foundId << std::endl;
  } else { // If the student was not found
    std::cout << "Student not found." << std::endl;
  }

  return 0; // End the program
}
