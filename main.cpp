#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <limits>
#include <vector>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
    #define PAUSE_COMMAND "pause"
#else
    #define CLEAR_COMMAND "clear"
    #define PAUSE_COMMAND "read"
#endif

using namespace std;

/**
 * @brief Capitalizes the first letter of a string and lowercase the rest.
 * 
 * @param str The string to be modified.
 * @return Modified string.
*/
string capitalizeFirstLetter(const string& str) {
    if (str.empty()) {
        return str;
    }

    string result = str;
    result[0] = toupper(result[0]);   // Capitalize first letter

    for (int i = 1; i < result.length(); i++) {
        if (isspace(result[i])) {
            i += 1;
            if (isdigit(result[i])) {
                // do nothing
            } else {
                result[i] = toupper(result[i]);
            }
        } else if (isdigit(result[i])) {
            // do nothing
        } else {
            result[i] = tolower(result[i]);   // Lowercase the rest of the letters
        }
    }

    return result;
}

/**
 * @brief Prompts the user for an integer input and validates it.
 * 
 * @param prompt The message to prompt the user.
 * @return Valid integer input.
*/
int getValidIntegerInput(const string& prompt) {
    int value;
    cout << prompt;

    while (!(cin >> value)) {
        cout << "Please enter your selection's number: ";
        cin.clear(); // clears error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards the invalid input
    }
    return value;
}

/**
 * @brief Prompts the user for a string input and validates it.
 * 
 * @param prompt The message to prompt the user.
 * @return Valid string input.
*/
string getValidStringInput(const string& prompt) 
{
    string input;
    cout << prompt;
    getline(cin >> ws, input); // Read the whole line including spaces
    input = capitalizeFirstLetter(input);   // Capitalizes the first letter of each word within the string
    return input;
}

void calculateGPA(unordered_map<string, unordered_map<string, unordered_map<string, string> > >& passed_unordered_map)
{
    if (passed_unordered_map.empty()) {
        cout << "You have not entered any classes, please enter your classes first" << endl;
        system(PAUSE_COMMAND);
        return;
    }

    unordered_map<string, unordered_map<string, unordered_map<string, string> > >::iterator semester;
    unordered_map<string, unordered_map<string, string> >::iterator classes;

    cout << "Which term would you like to view the GPA? To exit enter \"Quit\"" << endl;
    cout << "-------------------------------" << endl;
    for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
        cout << semester->first << endl;
    }
    cout << "-------------------------------" << endl;
    string term = getValidStringInput("");

    cout << term << endl;
    cout << "Course          Credit Hours          Grade" << endl;
    cout << "------------------------" << endl;
    for (classes = passed_unordered_map[term].begin(); classes != passed_unordered_map[term].end(); classes++) {
        cout << classes->first << "             " << classes->second["Credit Hours"] << "             " << classes->second["Grade"] << endl;
    }
    cout << "------------------------" << endl << endl;
    cout << "Your GPA is: " << endl;
}

/**
 * @brief Allows the user to add or remove or modify their classes.
 * 
 * @param passed_unordered_map The unordered map representing the semester data.
*/
void manageClasses(unordered_map<string, unordered_map<string, unordered_map<string, string> > >& passed_unordered_map) {
    int choice;
    unordered_map<string, unordered_map<string, unordered_map<string, string> > >::iterator semester;
    unordered_map<string, unordered_map<string, string> >::iterator classes;

    do {
        system(CLEAR_COMMAND);
        cout << "Select an option by entering 1-3:" << endl;
        cout << "(1). Add classes\n"
                "(2). Remove classes\n"
                "(3). Modify grade\n"
                "(4). Quit" << endl << endl;
        
        choice = getValidIntegerInput("");
        switch (choice) {
            case 1:
            {
                while(true) {
                    system(CLEAR_COMMAND);
                    cout << "Which term would you like to add a class to? If empty, type in the term you would like to add (e.g., Spring/Fall/Summer Year). To exit enter \"Quit\"" << endl;
                    cout << "-------------------------------" << endl;
                    for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
                        cout << semester->first << endl;
                    }
                    cout << "-------------------------------" << endl << endl;

                    string term = getValidStringInput("");

                    if (term == "Quit") { break; }
                    while (true) {
                        string course;
                        string creditHours;
                        string grade;

                        do {
                            course = getValidStringInput("Enter the name of the course you are adding: ");
                            if (passed_unordered_map[term].find(course) != passed_unordered_map[term].end()) {
                                cout << "Course name already exist. Enter a different name" << endl;
                            }
                        } while (passed_unordered_map[term].find(course) != passed_unordered_map[term].end());

                        creditHours = getValidStringInput("Enter the credit hours for " + course + ": ");
                        grade = getValidStringInput("Enter your letter grade for " + course + ": ");

                        // Insert class name
                        passed_unordered_map[term].insert(make_pair(course, unordered_map<string, string>()));

                        // Insert class info
                        passed_unordered_map[term][course].insert(make_pair("Credit Hours", creditHours));
                        passed_unordered_map[term][course].insert(make_pair("Grade", grade));

                        cout << "Would you like to enter another class? Enter 1-2" << endl;
                        cout << "(1). Yes\n"
                                "(2). No" << endl << endl;
                        cin >> choice;
                        system(CLEAR_COMMAND);
                        if (choice == 2) { break; }
                    }
                }
                break;
            }
            case 2:
            {
                system(CLEAR_COMMAND);
                while(true) {
                    cout << "Which term would you like to remove a class from? To exit enter \"Quit\"" << endl;
                    cout << "-------------------------------" << endl;
                    for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
                        cout << semester->first << endl;
                    }
                    cout << "-------------------------------" << endl << endl;

                    string term = getValidStringInput("");

                    if (term == "Quit") { break; }
                    if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
                        system(CLEAR_COMMAND);
                        cout << "You have not entered any classes for " + term + ". Enter a term you have entered classes" << endl;
                        continue;
                    }

                    while (true) {
                        string course;

                        cout << "Class              Grade" << endl;
                        cout << "------------------------" << endl;
                        for (classes = passed_unordered_map[term].begin(); classes != passed_unordered_map[term].end(); classes++) {
                            cout << classes->first << "             " << classes->second["Grade"] << endl;
                        }
                        cout << "------------------------" << endl << endl;

                        do {
                            course = getValidStringInput("Enter the name of the course you are removing. if you want to cancel type \"Cancel\": ");
                            if (course == "Cancel") { 
                                system(CLEAR_COMMAND); 
                                break;
                            }
                            if (passed_unordered_map[term].find(course) == passed_unordered_map[term].end()) {
                                cout << "Course name does not exist for this term." << endl;
                            }
                        } while (passed_unordered_map[term].find(course) == passed_unordered_map[term].end());

                        passed_unordered_map[term].erase(course);

                        cout << "Would you like to remove another class? Enter 1-2" << endl;
                        cout << "(1). Yes\n"
                                "(2). No" << endl << endl;
                        cin >> choice;
                        system(CLEAR_COMMAND);
                        if (choice == 2) { break; }
                    }
                }
                break;
            }
            case 3:
            {
                system(CLEAR_COMMAND);
                while(true) {
                    cout << "Which term would you like to modify? To exit enter \"Quit\"" << endl;
                    cout << "-------------------------------" << endl;
                    for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
                        cout << semester->first << endl;
                    }
                    cout << "-------------------------------" << endl;

                    string term = getValidStringInput("");

                    if (term == "Quit") { break; }
                    if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
                        system(CLEAR_COMMAND);
                        cout << "You have not entered any classes for " + term + ". Enter a term you have entered classes" << endl;
                        continue;
                    }

                    while (true) {
                        string course;
                        string grade;

                        cout << "Class              Grade" << endl;
                        cout << "------------------------" << endl;
                        for (classes = passed_unordered_map[term].begin(); classes != passed_unordered_map[term].end(); classes++) {
                            cout << classes->first << "             " << classes->second["Grade"] << endl;
                        }
                        cout << "------------------------" << endl << endl;

                        do {
                            course = getValidStringInput("Enter the name of the course you are modifing: ");
                            if (passed_unordered_map[term].find(course) == passed_unordered_map[term].end()) {
                                cout << "Course name does not exist. Enter a valid name" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (passed_unordered_map[term].find(course) == passed_unordered_map[term].end());

                        cout << "What should " + course + " letter grade be: ";
                        grade = getValidStringInput("");
                        
                        classes = passed_unordered_map[term].find(course);
                        classes->second["Grade"] = grade;

                        cout << "Would you like to remove another class? Enter 1-2" << endl;
                        cout << "(1). Yes\n"
                                "(2). No" << endl << endl;
                        
                        cin >> choice;
                        system(CLEAR_COMMAND);
                        if (choice == 2) { break; }
                    }
                }
                break;
            }
            case 4:
            {
                break;
            }
            default:
            {
                system(CLEAR_COMMAND);
                cout << "Invalid choice you dumdum >:T" << endl;
            }
        }
    } while (choice != 4);
    system(CLEAR_COMMAND);
}

void generateReport(unordered_map<string, unordered_map<string, unordered_map<string, string> > >& passed_unordered_map)
{
    int choice;
    unordered_map<string, unordered_map<string, unordered_map<string, string> > >::iterator semester;
    unordered_map<string, unordered_map<string, string> >::iterator classes;

    do {
        system(CLEAR_COMMAND);
        cout << "Please select what you would like to do by entering 1-5:" << endl;
        cout << "(1). Show all classes and grades\n"
             << "(2). Show classes and grades by term\n"
             << "(3). Quit" << endl << endl;
        
        choice = getValidIntegerInput("");

        switch (choice) {
            case 1:
            {
                system(CLEAR_COMMAND);
                if (passed_unordered_map.empty()) {
                    cout << "You have not entered any classes please enter your classes first" << endl;
                    system(PAUSE_COMMAND);
                    break;
                }

                for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
                    cout << semester->first << endl;
                    cout << "Course          Credit Hours          Grade" << endl;
                    cout << "-------------------------------------------" << endl;
                    for (classes = passed_unordered_map[semester->first].begin(); classes != passed_unordered_map[semester->first].end(); classes++) {
                        cout << classes->first << "             " << classes->second["Credit Hours"] << "             " << classes->second["Grade"] << endl;
                    }
                    cout << "-------------------------------------------" << endl << endl;
                }

                system(PAUSE_COMMAND);
                break;
            }
            case 2:
            {
                system(CLEAR_COMMAND);
                if (passed_unordered_map.empty()) {
                    cout << "You have not entered any classes, please enter your classes first" << endl;
                    system(PAUSE_COMMAND);
                    break;
                }

                while (true) {
                    system(CLEAR_COMMAND);

                    cout << "Which term would you like to see? To exit enter \"Quit\"" << endl;
                    cout << "-------------------------------" << endl;
                    for (semester = passed_unordered_map.begin(); semester != passed_unordered_map.end(); semester++) {
                        cout << semester->first << endl;
                    }
                    cout << "-------------------------------" << endl << endl;

                    string term = getValidStringInput("");
                    if (term == "Quit") { break; }

                    if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
                        system(CLEAR_COMMAND);
                        cout << "You have not entered any classes for " + term + ". Please select a term you have added classes to" << endl;
                        continue;
                    }

                    system(CLEAR_COMMAND);
                    cout << term << endl;
                    cout << "Course          Credit Hours          Grade" << endl;
                    cout << "-------------------------------------------" << endl;
                    for (classes = passed_unordered_map[term].begin(); classes != passed_unordered_map[term].end(); classes++) {
                        cout << classes->first << "             " << classes->second["Credit Hours"] << "             " << classes->second["Grade"] << endl;
                    }
                    cout << "-------------------------------------------" << endl << endl;

                    cout << "Would you like to see another term? Enter 1-2\n"
                        << "(1). Yes\n"
                        << "(2). No" << endl << endl;

                    cin >> choice;
                    if (choice == 2) { break; }
                }
                break;
            }
            case 3:
            {
                break;
            }
            default:
            {
                cout << "Invalid choice" << endl;
            }
        }
    } while (choice != 3);

    system(CLEAR_COMMAND);
}

void run() {
    cout << "This is a CGPA calculator." << endl;
    // Grade-------------------------------------------------------------
    // Class info (credit hours, current grade)------------------       |
    // Class name--------------------------                     |       |
    // Term---------                      |                     |       |
    unordered_map<string, unordered_map<string, unordered_map<string, string> > > dataOfClasses;

    int choice;
    do
    {
        system(CLEAR_COMMAND);
        cout << "Please select what you would like to do by entering 1-5:" << endl;
        cout << "(1). Show classes and grades\n"
             << "(2). Add/remove/modify classes and grades\n"
             << "(3). Show GPA per semester\n"
             << "(4). Show CGPA\n"
             << "(5). Quit" << endl << endl;
        
        choice = getValidIntegerInput("");

        switch (choice) {
            case 1:
            {
                generateReport(dataOfClasses);
                break;
            }
            case 2:
            {
                manageClasses(dataOfClasses);
                break;
            }
            case 3:
            {
                calculateGPA(dataOfClasses);
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                cout << "You are leaving me.... Q_Q" << endl;
                break;
            }
            default:
            {
                cout << "Enter a valid input you dingus >:U" << endl;
                break;
            }
        }
    } while (choice != 5);
}

int main() {
    system(CLEAR_COMMAND);
    run();
    return 0;
}

