// Chris Hayden, algorithm 3
//
// Algorithm 3 will be for a flash card program to help study on the weekends.
// The basic idea will be to take in input from the user about a concept to be
// quizzed on and display it with the answer hidden to be revealed when the
// user wishes. The first iteration of the program will be to hold 10 questions
// in memory, then if the user chooses they can write the questions to a file.
// Lastly the program will be able to read said files and display them back to
// the user in the quiz format.
//
// The first part will be to read in input from the user as stated above. We
// will be using a struct to store the info as that would be the most
// convenient way to distinguish the different fields. Before taking input We
// will tell the user what they are to input so not to confuse them. We will
// use the cin variable to receive input from the user and save it to a given
// struct. The struct will probably be named something like Question. Before we
// continue to the next part of the program we will echo the given information
// to the user to see if it is correct, if it is we will continue.
//
// Once we know that we have a correct struct containing the users information
// we will then add it to an array of other structs that contain the users
// correct information. The array will probably be instantiated without any
// structs and maybe named QuestionArray.
//
// We will add more questions to what might be called QuestionArray in a loop.
// At the end of each iteration of the loop we will ask the user if they would
// like to stop iterating and continue to the next portion. Else we will
// continue looping until we reach the max amount of questions to be added to
// the what might be called QuestionArray. For the first version of the program
// the max will be 10.
//
// The user will have the chance to save the current collection of questions to
// an external data file. The first program will only write to a specific at
// the moment. The name might be question_data. This file will be a plane text
// file but with the extension of .txt. We will start by opening the file in
// truncate mode, it will be left a another iteration of the program to add in
// the ability to read in arbitrary large files by implementing a lazy loader
// to read in a few line at a time and store the current position of the file
// to pick up when we reach the last question in the buffer. After making sure
// we have a handle on it we will write the given data to the file. Each
// question will be on its own line, or '\n' separated. At the moment the
// specified fields are; the number, the subject, the question text, and the
// date completed though I might add an optional answer field. The individual
// sections of the file will be delimited by '|'. The format plus the optional
// field might look like `1|loop|it gooos|\n2|functions|what is a function|a
// repeatable block of code\n`.
//
//
// Furthermore we will need to read the data file back in to the program if it
// is ever actually to be useful. For now well start by reading in line by line
// adding to the array until EOF or array bounds meat. Well parse the lines one
// char at a time until we get to the '|' adding the current collected
// characters to the right part of the struct.
//
// Finally give the user the options to display all questions (and answers),
// use the quiz like format to display each question individually or display by
// only a given subject.

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// static sizes for arrays
const int FIELD_SIZE = 1000;
const int QUESTION_SIZE = 10;
const int DATA_PATH_SIZE = 14;

// to conveniently change the delimiter
const char DELIMITER = '$';

// a struct to meaningfully group data together
struct Question {
    int number;
    char subject[FIELD_SIZE];
    char question[FIELD_SIZE];
    char answer[FIELD_SIZE];
};

// an easy handle on file streams
struct FileHandles {
    char data_path[DATA_PATH_SIZE];
    ifstream read_handle;
    ofstream write_handle;
};

// prototypes for functions defined later in the program
bool run_logic();
bool check_file_handle(ifstream &to_check);
void close_files(FileHandles &handles);
void display_loop(char display_type, char subject[], int question_amount,
                  Question questions[]);
char display_menu();
void display_simple(Question &question);
void display_verbose(Question &question);
char main_menu();
int make_questions(Question fill[]);
bool open_read_file(char data_path[], ifstream &read_handle);
int read_questions(ifstream &read_handle, Question fill[]);
void safe_write(FileHandles &handles, int question_amount,
                Question questions[]);
char save_menu();
void subject_menu(int size, char subject[]);
void write_into_file(ofstream &write_handle, int questions_size,
                     Question questions[]);

// the main function
int main()
{
    char user_input;

    bool error = false;

    do {
        // run the program
        if (!run_logic()) {
            cerr << "error when running" << endl;
            error = true;
        } else {
            cout << "\nwould you like to run the program again\n (y|n) -> ";
            cin >> user_input;
        }

        // loop until user_input == n or found an error
    } while (tolower(user_input) != 'n' && !error);

    // if we ran in to an error, tell the os
    if (error) {
        return 1;
    } else {
        return 0;
    }
}

// the main branching and error handling is done here
bool run_logic()
{
    int question_amount = 0;

    // get the users answer
    char user_input = main_menu();

    // instantiate streams with a path and empty file descriptors
    FileHandles handles = {"questions.txt"};

    // instantiate array of questions
    Question question_array[QUESTION_SIZE];

    // get data from the user or try and open a file and get data from there
    if (tolower(user_input) == 'e') {
        question_amount = make_questions(question_array);
    } else if (open_read_file(handles.data_path, handles.read_handle)) {
        // read questions into the given structs
        question_amount = read_questions(handles.read_handle, question_array);
    } else {
        cerr << "cant get input, probably a bad file" << endl;

        // error, close file handles
        close_files(handles);
        return false;
    }

    // if we received questions
    if (question_amount) {
        char subject[FIELD_SIZE];
        subject[0] = '\0';
        subject_menu(FIELD_SIZE, subject);

        char display_type = display_menu();

        // run the display questions logic
        display_loop(display_type, subject, question_amount, question_array);

    } else {
        // we ran in to an error, most likely reading a file,
        // just close the files
        close_files(handles);
        return false;
    }

    // ask to save
    if (save_menu() == 'y') {
        // write into the data file safely, mostly just close the read_handle
        safe_write(handles, question_amount, question_array);
    }

    // no mater what close_files()
    close_files(handles);

    return true;
}

// the main_menu
char main_menu()
{
    char user_input = 'e';
    char lower_input = 'e';

    // ask the user how to get the questions
    cout << "welcome, do you want to read from a file or enter in data "
            "yourself";
    do {
        cout << "\nonly f or e\n -> ";
        cin >> user_input;
        cin.ignore(1000, '\n');

        lower_input = tolower(user_input);
    } while (lower_input != 'e' && lower_input != 'f');

    // return users answer
    return lower_input;
}

// ask if we should save
char save_menu()
{
    char user_input;
    char lower_input;
    cout << "do you want to save questions back in to the file";

    do {

        cout << "\n (y|n) -> ";
        cin >> user_input;
        cin.ignore(1000, '\n');

        lower_input = tolower(user_input);

    } while (lower_input != 'y' && lower_input != 'n');

    return tolower(user_input);
}

// the question_menu, mostly to keep make_questions() clean
void question_menu()
{
    cout << "\npleas give up to " << QUESTION_SIZE
         << " questions\nenter a END in the subject field when you are done "
            "entering questions\n"
         << endl;
}

// make Question structs from suer input
int make_questions(Question fill[])
{
    bool break_loop = false;

    // display the menu
    question_menu();

    // instantiate i here so we can use it after the loop
    int i;
    for (i = 0; i < QUESTION_SIZE && !break_loop; ++i) {
        // add the number to the struct for the user
        cout << "question " << i + 1 << endl;
        fill[i].number = i + 1;

        cout << "enter the subject:\n -> ";

        // fill the character array
        cin.get(fill[i].subject, FIELD_SIZE, '\n');
        // reset any errors
        cin.clear();
        // ignore anything leftover in the buffer
        cin.ignore(1000, '\n');

        // check if we are to end
        if (strcmp(fill[i].subject, "END") == 0) {
            break_loop = true;
            // pass the rest of the loop
            continue;
        }

        cout << "enter the question:\n -> ";

        cin.get(fill[i].question, FIELD_SIZE, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "enter the answer (optional):\n -> ";

        cin.get(fill[i].answer, FIELD_SIZE, '\n');
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // return the amount of questions
    // if break_loop is false then we reached the full amount questions
    if (!break_loop) {
        return i;

        // END was entered in so we are one over bounds
    } else {
        return i - 1;
    }
}

// read each field into the right member by the DELIMITER
int read_questions(ifstream &read_handle, Question fill[])
{
    // loop until we reach the question size or the file reached the end
    int i;
    for (i = 0; i < QUESTION_SIZE && check_file_handle(read_handle); ++i) {

        // read in each individual field to the delimiter or a \n

        read_handle >> fill[i].number;
        read_handle.clear();
        read_handle.ignore(1000, DELIMITER);

        if (!check_file_handle(read_handle)) {
            cerr << "malformed or empty file" << endl;

            return 0;
        }

        read_handle.get(fill[i].subject, 1000, DELIMITER);
        read_handle.clear();
        read_handle.ignore(1000, DELIMITER);

        read_handle.get(fill[i].question, 1000, DELIMITER);
        read_handle.clear();
        read_handle.ignore(1000, DELIMITER);

        read_handle.get(fill[i].answer, 1000, '\n');
        read_handle.clear();
        read_handle.ignore(1000, '\n');
    }

    return i;
}

// a convenience function to close both file handles
void close_files(FileHandles &handles)
{
    handles.read_handle.close();
    handles.write_handle.close();
}

// check if a file exits and we have access
bool check_file_handle(ifstream &to_check)
{
    // read with peek and check if we have reached the end of file
    if (to_check.peek() && !to_check.eof()) {
        return true;
    } else {
        return false;
    }
}

// open a file into the variable we give it
bool open_read_file(char data_path[], ifstream &read_handle)
{
    // open the file
    read_handle.open(data_path);

    // return if we have access
    return check_file_handle(read_handle);
}

// safely write a file
void safe_write(FileHandles &handles, int question_amount, Question questions[])
{
    // make sure the read_handle is closed
    handles.read_handle.close();

    // open the write_handle explicitly in truncate mode
    handles.write_handle.open(handles.data_path, ios::trunc);

    // write the data into file
    write_into_file(handles.write_handle, question_amount, questions);
}

// write the structs in to the files by delimiter
void write_into_file(ofstream &write_handle, int questions_size,
                     Question questions[])
{
    // iterate over the questions writing each in to the file with the given
    // delimiter
    for (int i = 0; i < questions_size; ++i) {
        write_handle << questions[i].number << DELIMITER << questions[i].subject
                     << DELIMITER << questions[i].question << DELIMITER
                     << questions[i].answer << endl;
    }
}

// the display logic
void display_loop(char display_type, char subject[], int question_amount,
                  Question questions[])
{
    // loop for the given amount of questions
    for (int i = 0; i < question_amount; ++i) {

        // if there is data in the array we have a subject to filter by
        if (subject[0] && strcmp(questions[i].subject, subject) != 0) {
            continue;
        }

        // print the wanted out put
        if (display_type == 's') {
            display_simple(questions[i]);
        } else if (display_type == 'v' || display_type == 'f') {
            display_verbose(questions[i]);
        }

        // if display_type dose not == f then ask the user to hit enter
        if (display_type != 'f') {
            cout << "hit enter to continue" << endl;
            cin.ignore(1000, '\n');
        }
    }
}

// to keep display_questions clean
char display_menu()
{
    char user_input;
    // a variable to only run tolower once
    char lower_input;

    cout
        << "\nhow do you want to display the questions\n\n(S)imple is just the "
           "questions, (V)erbose includes the answer and \n(F)ull prints all "
           "the questions at once\n (S|V|F) -> ";

    do {
        cin >> user_input;
        cin.ignore(1000, '\n');

        // lower case the input to more easily work with the char
        lower_input = tolower(user_input);

        // run the selected display function
        // loop if given a wrong character
    } while (lower_input != 's' && lower_input != 'v' && lower_input != 'f');

    return lower_input;
}

// ask the user for a subject to filer by
void subject_menu(int size, char subject[])
{
    char user_input = 'n';
    char lower_input = 'n';

    cout << "\ndo you wan to filter questions by subject";

    do {
        cout << "\n(y|n) -> ";
        cin >> user_input;
        cin.ignore(1000, '\n');

        lower_input = tolower(user_input);

    } while (lower_input != 'y' && lower_input != 'n');

    if (lower_input == 'n') {
        return;
    }

    // if we want to filter by a subject, fill an array of characters
    do {
        cout << "\nwhat subject do you want to filter by\n -> ";
        cin.get(subject, size, '\n');
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "\ndo you wan to filter by `" << subject << "`\n (y|n) -> ";

        cin >> user_input;
        cin.ignore(1000, '\n');
        lower_input = user_input;
    } while (lower_input != 'y');
}

// out put the wanted fields
void display_simple(Question &question)
{
    cout << "\n# Question: " << question.number
         << " -- subject: " << question.subject << "\n " << question.question
         << '\n'
         << endl;
}

// display the question with an answer
void display_verbose(Question &question)
{
    cout << "\n# Question: " << question.number
         << " -- subject: " << question.subject << "\n " << question.question
         << "\n\n# Answer\n " << question.answer << '\n'
         << endl;
}
