
// Student Grade Report Generation Program


#include <iostream>         // Include the input-output stream library.
#include <fstream>          // Include the file stream library.
#include <iomanip>          // Include the input-output manipulation library.
#include <string>           // Include the string library.

using namespace std;            // Use the standard namespace for convenience.

const int MAX_RECORDS = 10;     // Define a constant maximum number of records.

// Define a struct to store information about a student's record.
struct StudentRecord {
    string lastName;        // Store the student's last name.
    double scores[5];       // Store an array of 5 scores for the student.
    double average;         // Store the average score for the student.
    char grade;             // Store the grade calculated based on the average.
};

// Declare a function to calculate the grade based on an average score.
char calculateGrade(const double average);

// Declare a function to get a filename as input.
string getFilename();

// Declare a function to read data from a file
// into an array of StudentRecord objects.
bool readData(const string& fn, StudentRecord students[], int& recordCount);

// Declare a function to calculate the average score for each student.
void calculateRecordAverages(StudentRecord students[], int recordCount);

// Declare a function to convert average scores to letter grades.
void recordAverages2LetterGrades(StudentRecord students[], int recordCount);

// Declare functions for printing various components of the report.
void printSepLine();
void printHeader();
void printRow(const StudentRecord students[], int row);
void printClassAverage(const double sum);
void printBestPerformance(const StudentRecord students[]);
void printPoorestPerformance(const StudentRecord students[]);

// Declare functions to find the index of the maximum and minimum average scores
int findMaxAve(const StudentRecord students[]);
int findMinAve(const StudentRecord students[]);

// Declare a function to print the entire report.
void printReport(const StudentRecord students[], int recordCount);


// Main function of the program
int main() {
    StudentRecord students[MAX_RECORDS];
    // Declare an array of StudentRecord objects to store student data

    int recordCount = 0;

    // Declare and initialize a variable to keep track of
    // the number of records

    const string fileName = getFilename();
    // Get the input filename from the user

    if (readData(fileName, students, recordCount)) {
        // If data reading is successful

        calculateRecordAverages(students, recordCount);
        // Calculate average scores for each student

        recordAverages2LetterGrades(students, recordCount);
        // Convert average scores to letter grades

        printReport(students, recordCount);
        // Print the student grade report
    }

    return 0;       // Indicate successful program execution by returning 0
}

// Function implentations

char calculateGrade(const double average) {
    char grade;             // Declare a variable to store the calculated grade

    if (average >= 90) {
        grade = 'A';    // If the average is 90 or above, assign 'A' grade.
    } else if (average >= 80) {
        grade = 'B';   // If the average is between 80 and 89, assign 'B' grade.
    } else if (average >= 70) {
        grade = 'C';   // If the average is between 70 and 79, assign 'C' grade.
    } else if (average >= 60) {
        grade = 'D';   // If the average is between 60 and 69, assign 'D' grade.
    } else {
        grade = 'F';   // If the average is below 60, assign 'F' grade.
    }

    return grade;      // Return the calculated grade based on the average.
}


string getFilename() {
    string fileName;        // Declare a variable to store the entered filename
    cout << "Enter the name of your data file: ";
    // Display a prompt for the user

    cin >> fileName;        // Read the entered filename from the user
    return fileName;        // Return the entered filename
}


bool readData(const string& fn, StudentRecord students[], int& recordCount) {
    ifstream inputFile(fn);
    // Create an input file stream using the provided filename

    bool success = true;
    // Declare and initialize a variable to track the
    // success state of reading data.

    if (!inputFile.is_open()) {     // Check if the input file failed to open
        cout << "\nError opening file: " << fn << "\n\n";
        // Display an error message indicating the failed file opening

        success = false;    // Update the success state to indicate failure
    } else {
        while (recordCount < MAX_RECORDS && inputFile >>
        students[recordCount].lastName) {
            // Read the last name of the student from the
            // file and check if recordCount is within limits
            for (int i = 0; i < 5; ++i) {
                inputFile >> students[recordCount].scores[i];
                // Read scores for each student
            }
            ++recordCount;
            // Increment the record count after processing each student's data
        }

        inputFile.close();
        // Close the input file stream after reading
    }

    return success;
    // Return the success state indicating whether data reading was successful
}



// Function to calculate the average scores for each student's record
void calculateRecordAverages(StudentRecord students[], int recordCount) {
    for (int i = 0; i < recordCount; ++i) {
        // Iterate through each student's record

        double sum = 0.0;
        // Declare and initialize a variable to
        // store the sum of scores for a student.

        for (int j = 0; j < 5; ++j) {
            // Iterate through each score for a student

            sum += students[i].scores[j];
            // Accumulate the scores to calculate the sum
        }

        students[i].average = sum / 5.0;
        // Calculate and assign the average score for the student
    }
}

// Function to convert average scores to letter grades for each student's record
void recordAverages2LetterGrades(StudentRecord students[], int recordCount) {
    for (int i = 0; i < recordCount; ++i) {
        // Iterate through each student's record

        students[i].grade = calculateGrade(students[i].average);
        // Calculate and assign the letter grade using the average score
    }
}

// Function to print a separator line
void printSepLine() {
    cout << string(69, '-') << endl;
    // Print a line of 69 dashes for separation
}

// Function to print the header of the report
void printHeader() {
    // Print column headers with appropriate formatting
    cout << "Name" << setw(14) << "Test 1" << setw(8) << "Test 2" << setw(8)
         << "Test 3" << setw(8) << "Test 4" << setw(8) << "Test 5" << setw(10)
         << "Average" << setw(8) << "Grade" << endl;
    // Print a line of dashes below the column headers
    cout
    << "-------     ------  ------  ------  ------  ------   -------   -----\n";
}

// Function to print a row of data for a student's record
void printRow(const StudentRecord students[], int row) {
    cout << students[row].lastName << setw(13);
    // Print the last name with appropriate formatting

    for (int i = 0; i < 5; ++i) {
        // Iterate through each test score for the student

        cout << fixed << setprecision(0) << students[row].scores[i]
        << setw(8);      // Print scores with formatting
    }

    cout << setw(10) << fixed << setprecision(2) << students[row].average
    << setw(6) << students[row].grade << endl;
    // Print average and grade with formatting and move to the next line
}

// Function to print the class average
void printClassAverage(const double sum) {
    const double classAverage = sum / MAX_RECORDS;
    // Calculate the class average by dividing the sum by
    // the maximum number of records
    cout << setw(55) << "Class average:   " << fixed << setprecision(2)
    << classAverage << endl;
    // Print the class average with formatting
}

// Function to print the best performance
void printBestPerformance(const StudentRecord students[]) {
    const int bestIndex = findMaxAve(students);
    // Find the index of the student with the best performance

    cout << "\nBest Performance:" << endl;
     // Print a label for the best performance section

    printSepLine();         // Print a separator line
    printHeader();          // Print the header for the report
    printRow(students, bestIndex);
    // Print the row for the student with the best performance

    printSepLine();         // Print a separator line
}

// Function to print the poorest performance
void printPoorestPerformance(const StudentRecord students[]) {
    const int poorestIndex = findMinAve(students);
    // Find the index of the student with the poorest performance

    cout << "\nPoorest Performance:" << endl;
    // Print a label for the poorest performance section

    printSepLine();         // Print a separator line
    printHeader();          // Print the header for the report
    printRow(students, poorestIndex);
    // Print the row for the student with the poorest performance
    printSepLine();         // Print a separator line
}

// Function to find the index of the student with the maximum average score
int findMaxAve(const StudentRecord students[]) {
    int maxIndex = 0;
    // Declare and initialize a variable to store the
    // index of the student with the maximum average score.

    for (int i = 1; i < MAX_RECORDS; ++i) {
    // Iterate through each student's record starting from the second student

        if (students[i].average > students[maxIndex].average) {
        // Compare the average score of the current
        // student with the maximum average score found so far.

            maxIndex = i;
        // Update the index to the current student if
        // their average score is higher.
        }
    }

    return maxIndex;
    // Return the index of the student with the maximum average score
}

// Function to find the index of the student with the minimum average score
int findMinAve(const StudentRecord students[]) {
    int minIndex = 0;
    // Declare and initialize a variable to store
    // the index of the student with the minimum average score.

    for (int i = 1; i < MAX_RECORDS; ++i) {
        // Iterate through each student's record starting
        // from the second student.

        if (students[i].average < students[minIndex].average) {
        // Compare the average score of the current student
        //  with the minimum average score found so far.

            minIndex = i;
            // Update the index to the current student if
            // their average score is lower.
        }
    }

    return minIndex;
    // Return the index of the student with the minimum average score
}


// Function to print the entire student grade report
void printReport(const StudentRecord students[], int recordCount) {
    cout << "\n\nStudent Grade Report" << endl;
    // Print a header for the report

    printSepLine();
    // Print a separator line

    // Print column headers with appropriate formatting
    cout << "Name" << setw(14) << "Test 1" << setw(8) << "Test 2" << setw(8)
         << "Test 3" << setw(8) << "Test 4" << setw(8) << "Test 5" << setw(10)
         << "Average" << setw(8) << "Grade" << endl;
    // Print a line of dashes below the column headers
    cout
    << "-------     ------  ------  ------  ------  ------   -------   -----\n";

    for (int i = 0; i < recordCount; ++i) {
        // Iterate through each student's record

        const int COL_WIDTH = 9;
        // Define a constant for column width.

        const int NAME_LENGTH = static_cast<int>(students[i].lastName.length());
        // Calculate the length of the student's last name
        cout << students[i].lastName;
        // Print the student's last name.

        const int NUM_SPACES = COL_WIDTH - NAME_LENGTH;
        // Calculate the number of spaces needed for formatting.

        cout << setw(NUM_SPACES + 1) << " ";
        // Print spaces for formatting.

        for (int j = 0; j < 5; ++j) {
             // Iterate through each test score for the student.
            cout << right << setw(8) << fixed << setprecision(0)
            << students[i].scores[j];
            // Print scores with formatting.
        }

        cout << setw(10) << fixed << setprecision(2) << students[i].average
        << setw(6) << students[i].grade << endl;
        // Print average and grade with formatting and move to the next line
}

    printSepLine();         // Print a separator line

    double sum = 0.0;
    // Declare and initialize a variable to store the sum of average scores.
    for (int i = 0; i < recordCount; ++i) {
        // Iterate through each student's record.

        sum += students[i].average;
        // Accumulate average scores to calculate the sum.
}

    printClassAverage(sum);
    // Print the class average using the calculated sum.

    printSepLine();                     // Print a separator line
    printBestPerformance(students);     // Print the best performance section
    printPoorestPerformance(students);  // Print the poorest performance section
    cout << endl;                       // Print an extra line for formatting
}
