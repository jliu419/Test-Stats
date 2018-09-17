/*
  Exam Statistics.
 
  @author Jiaming Liu
  @date Aug 6 2018
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// CONSTANTS
const int MAXSIZE = 45;

// Function prototypes
void welcome (void);
void readfile(ifstream &input, double scores[], string identification[], int &total);
void sortID(double scores[], string identification[], int total);
void sortscore(double scores[], string identification[], int total);
void scoreout(string filename, const double scores[], const string identification[], int total);
double getaverage (const double scores[], int total);
void display(double average, int count, const double scores[], const string identification[]);
void endingmessage(void);

int main()
{
    // VARIABLES
    double score[MAXSIZE];
    string id[MAXSIZE];
    double average;
    int total;
    
    welcome(); // Display the Welcome Message
    
    // opening input files
    ifstream input;
    string name;
    cout << "enter a name for the file ";
    cin >> name;
    input.open(name);
    if (!input)
    {
        cout << "error with opening the file" << endl;
        exit(EXIT_SUCCESS);
    }
    
    // read score and id
    readfile(input, score, id, total);
    
    // Sorting/Displaying scores
    sortID(score, id, total);
    scoreout("scoresOut1.txt", score, id, total);
    sortscore(score, id, total);
    scoreout("scoresOut2.txt", score, id, total);
    
    // processing scores
    average = getaverage(score, total);
    
    // display score
    display(average, total, score, id);
    
    endingmessage();
    return 0;
}

// Display the Welcome Message
void welcome ()
{
    cout << "Welcome to Score Statistic calculator!\n";
    cout << "This will do some statistics to student's final score\n" << endl;
}

// Reading Data from file and store into Both Array
void readfile (ifstream &infile, double scores[], string id[], int &total)
{
    double studentscore;
    string studentid;
    // stop either array is full or no more data to read
    int i = 0;
    for (;(infile >> studentid >> studentscore); i ++)
    {
        id[i] = studentid;
        scores[i] = studentscore;
    }
    
    total = i;
    
    infile.close();
}

// calculate the average of students who have taken the test
double getaverage (const double scores[], int total)
{
    double sum = 0;
    double average;
    for (int i = 0; i < total; i ++)
    {
        sum += scores[i];
    }
    
    average = sum / total;
    
    return average;
}

// Display informations about the average grade, highest score,
// lowest score, and total number of test takers.
void display(double average, int count, const double scores[], const string identification[])
{
    cout << "\nOf " << count << " students, " << endl;
    
    cout << "the highest score is " << scores[0] << " here are their student ID: " << endl;
    int i = 0;
    while (scores[i] == scores[0])
    {
        cout << identification[i] << "    ";
        i ++;
    }
    
    cout << "\nthe lowest score is " << scores[count - 1] << " here are their student ID: " << endl;
    int x = count - 2;
    while (scores[x] == scores[count - 1])
    {
        cout << identification[x] << "    ";
        x ++;
    }
    
    cout << "\nThe average of this test is " << fixed << setprecision(1) << average << endl << endl;
}

// This displays an ending message before the program ends.
void endingmessage()
{
    cout << "\nThank you for using my program\n\n";
}

// This will sort the score and ID by the ID in an ascending order.
void sortID(double score[], string id[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        // look for smallest
        int min = i;
        for(int k = i + 1; k < size; k++)
        {
            if (id[k] < id[min])
                min = k;
        }
        // swap id
        string hold = id[min];
        id[min] = id[i];
        id[i] = hold;
        // swap score
        double temp = score[min];
        score[min] = score[i];
        score[i] = temp;
    }
}

// This will sort the score and ID by the score in a descending order.
void sortscore(double score[], string id[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        // look for largest
        int max = i;
        for(int k = i + 1; k < size; k++)
        {
            if (score[k] > score[max])
                max = k;
        }
        // swap score
        int hold = score[max];
        score[max] = score[i];
        score[i] = hold;
        // swap id
        string temp = id[max];
        id[max] = id[i];
        id[i] = temp;
    }
}

// This method stores the ID and Score after it is being sorted.
// They will be stored into a file.
void scoreout(string filename, const double scores[], const string identification[], int total)
{
    ofstream output;
    output.open(filename);
    if (!output)
    {
        cout << "error with opening the file" << endl;
        exit(EXIT_SUCCESS);
    }
    
    for (int index = 0; index < total; index ++)
        output << identification[index] << " " <<  scores[index] << endl;
}

/* 
 Welcome to Score Statistic calculator!
 This will do some statistics to student's final score
 
 enter a name for the file scores.txt
 
 Of 13 students,
 the highest score is 100 here are their student ID:
 2ABCD    AK323    DR123
 the lowest score is 45 here are their student ID:
 SW111    TY4XZ
 The average of this test is 81.7
 
 
 Thank you for using my program
 
 Program ended with exit code: 0
 
 */



