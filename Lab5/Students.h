/* A student data record class. A user ID number is used to associate between student names and phone numbers and grades.
   This would probably be better done as some kind of struct or class that is mapped to the name.

   Author: David E. Johnson
   Date: Oct. 2 2015
   Institution: University of Utah
*/

#ifndef _STUDENTS_H
#define _STUDENTS_H
#include <map>
#include <string>
#include <vector>

class Students {
	// The main underlying data structure is a map. Read about maps. Maps
	// internally store the pairs in order by key as determined by <.
  // Key is Name, value is unsigned int ID number
  std::map<std::string, unsigned int> userIDs;
  // Key is ID number and value is a string form phone number "801-585-1726" 
  std::map<unsigned int, std::string> phoneNumbers;
  // Key is ID and value is a grade character
  std::map<unsigned int, char> grades;

 public:

  // Add a string name and id number to the map
  void addUser(const std::string& user, unsigned int id);

  // Add a phone number to a given id number
  void addPhoneNumbers(unsigned int id, const std::string& phone);

  // Add a grade for a given id number
  void addGrade(unsigned int id, char grade);

  // Find the id for a name.
  // Throws an out_of_range exception if name not in the records.
  unsigned int idForName(const std::string& name);

  // Find the grade for a name using the associated id.
  // Throws an out_of_range exception if name not in the records or no grade associated
  // with name's id. 
  char gradeForName(const std::string& name);

  // Find the phone for a name using the associated id.
  // Throws an out_of_range exception if name not in the records or no phone associated
  // with name's id. 
  std::string phoneForName(const std::string& name);

  // Returns true if name is in the map, else false.
  bool nameExists(const std::string& name);

  // If all the records associated with a name are set, store them in the ref parameters and return true, else return false
  bool fullRecord(const std::string& name, unsigned int& id, std::string& phone, char& grade);

  // Return the number of names stored in the map
  size_t numberOfNames();

  // given a name, deletes the name and any phone number and grade associated with the id, then removes the name:id record. Throws an out_of_range exception if name is not a key, else no change.
  void removeStudent(const std::string& name);

  // Removes each name in names from userIDs and removes any phone or grade with the id
  // associate with that name. Unlike removeStudent, does not throw any exceptions so the
  // list will be traversed.
  unsigned int removeList(std::vector<std::string> names);
  
  // Clears all data from the class.
  void clearAll();
};

#endif

  
  
  
  
