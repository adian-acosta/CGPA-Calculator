#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <limits>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
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
        cout << "Please enter a valid integer: ";
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
string getValidStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin >> ws, input); // Read the whole line including spaces
    input = capitalizeFirstLetter(input);
    return input;
}

/**
 * @brief Allows the user to add or remove classes.
 * 
 * @param passed_unordered_map The unordered map representing the semester data.
*/
void manageClasses(unordered_map<string, unordered_map<string, int>>& passed_unordered_map) {
    int choice;

    do {
        system(CLEAR_COMMAND);
        cout << "Select an option by entering 1-3:" << endl;
        cout << "(1). Add classes\n"
                "(2). Remove classes\n"
                "(3). Modify grade\n"
                "(4). Quit" << endl << endl;
        
        cin >> choice;
        switch (choice) {
            case 1:
            {
                while(true) {
                    system(CLEAR_COMMAND);
                    string term = getValidStringInput("Which term would you like to add a class (e.g., Spring/Fall/Summer Year)? To exit enter \"Quit\":\n");
                    if (term == "Quit") { break; }
                    while (true) {
                        string course;
                        int grade;

                        do {
                            course = getValidStringInput("Enter the name of the course you are adding: ");
                            if (passed_unordered_map[term].find(course) != passed_unordered_map[term].end()) {
                                cout << "Course name already exist. Enter a different name" << endl;
                            }
                        } while (passed_unordered_map[term].find(course) != passed_unordered_map[term].end());

                        grade = getValidIntegerInput("Enter the grade for " + course + ": ");

                        passed_unordered_map.insert(make_pair(term, unordered_map<string, int>()));
                        passed_unordered_map[term].insert(make_pair(course, grade));

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
                    string term = getValidStringInput("Which term would you like to remove a class (e.g., Spring/Fall/Summer Year)? To exit enter \"Quit\": ");
                    if (term == "Quit") { break; }
                    if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
                        system(CLEAR_COMMAND);
                        cout << "You have not entered any classes for " + term + ". Enter a term you have entered classes" << endl;
                        continue;
                    }

                    while (true) {
                        string course;

                        unordered_map<string, int>::iterator ptr;

                        cout << "Class              Grade" << endl;
                        cout << "------------------------" << endl;
                        for (ptr = passed_unordered_map[term].begin(); ptr != passed_unordered_map[term].end(); ptr++) {
                            cout << ptr->first << "             " << ptr->second << endl;
                        }
                        cout << "------------------------" << endl;

                        do {
                            course = getValidStringInput("Enter the name of the course you are removing: ");
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
                    string term = getValidStringInput("Which term would you like to modify a class (e.g., Spring/Fall/Summer Year)? To exit enter \"Quit\": ");
                    if (term == "Quit") { break; }
                    if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
                        system(CLEAR_COMMAND);
                        cout << "You have not entered any classes for " + term + ". Enter a term you have entered classes" << endl;
                        continue;
                    }

                    while (true) {
                        string course;
                        int grade;

                        unordered_map<string, int>::iterator ptr;

                        cout << "Class              Grade" << endl;
                        cout << "------------------------" << endl;
                        for (ptr = passed_unordered_map[term].begin(); ptr != passed_unordered_map[term].end(); ptr++) {
                            cout << ptr->first << "             " << ptr->second << endl;
                        }
                        cout << "------------------------" << endl;

                        do {
                            course = getValidStringInput("Enter the name of the course you are modifing: ");
                            if (passed_unordered_map[term].find(course) == passed_unordered_map[term].end()) {
                                cout << "Course name does not exist. Enter a valid name" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (passed_unordered_map[term].find(course) == passed_unordered_map[term].end());

                        cout << "What should " + course + " grade be: ";
                        cin >> grade;

                        unordered_map<string, int>::iterator itr = passed_unordered_map[term].find(course);
                        itr->second = grade;

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

void generateReport(unordered_map<string, unordered_map<string, int>>& passed_unordered_map)
{
    system(CLEAR_COMMAND);
    int choice;

    while (true) {
        string term = getValidStringInput("WHich term would you like to see (e.g., Spring/Fall/Summer Year)? To exit enter \"Quit\"\n");
        if (term == "Quit") { break; }

        if (passed_unordered_map.find(term) == passed_unordered_map.end()) {
            system(CLEAR_COMMAND);
            cout << "You have not entered any classes for " + term + ". Please select a term you have added classes to" << endl;
            continue;
        }

        unordered_map<string, int>::iterator ptr;

        system(CLEAR_COMMAND);
        cout << term << endl;
        cout << "Class             Grade" << endl;
        cout << "-------------------------------" << endl;
        for (ptr = passed_unordered_map[term].begin(); ptr != passed_unordered_map[term].end(); ptr++) {
            cout << ptr->first << "      " << ptr->second << endl;
        }
        cout << "-------------------------------" << endl;
        cout << "Would you like to see another term? Enter 1-2\n"
             << "(1). Yes\n"
             << "(2). No" << endl << endl;

        cin >> choice;
        if (choice == 2) { break; }
        system(CLEAR_COMMAND);
    }
    system(CLEAR_COMMAND);
}

void run() {
    cout << "This is a CGPA calculator." << endl;
    unordered_map<string, unordered_map<string, int> > semester;

    int choice;
    do
    {
        system(CLEAR_COMMAND);
        cout << "Please select what you would like to do by entering 1-5:" << endl;
        cout << "(1). Show classes and grades\n"
             << "(2). Add/remove/modify classes and grades\n"
             << "(3). Show GPA per semester\n"
             << "(4). Show CGPA\n"
             << "(5). Quit" << endl << endl;;
        
        cin >> choice;

        switch (choice) {
            case 1:
            {
                generateReport(semester);
                break;
            }
            case 2:
            {
                manageClasses(semester);
                break;
            }
            case 3:
            {
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

