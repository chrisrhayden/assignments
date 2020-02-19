#include "main.h"

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
    for (i = 0;
         i < QUESTION_SIZE &&
         check_file_handle_and_more_text_for_a_long_function(read_handle);
         ++i) {

        // read in each individual field to the delimiter or a \n

        read_handle >> fill[i].number;
        read_handle.clear();
        read_handle.ignore(1000, DELIMITER);

        if (!check_file_handle_and_more_text_for_a_long_function(read_handle)) {
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
bool check_file_handle_and_more_text_for_a_long_function(ifstream &to_check)
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
    return check_file_handle_and_more_text_for_a_long_function(read_handle);
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
