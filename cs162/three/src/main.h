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

bool check_file_handle_and_more_text_for_a_long_function(ifstream &to_check);
bool open_read_file(char data_path[], ifstream &read_handle);
bool run_logic();
char display_menu();
char main_menu();
char save_menu();
int make_questions(Question fill[]);
int read_questions(ifstream &read_handle, Question fill[]);
void close_files(FileHandles &handles);
void display_loop(char display_type, char subject[], int question_amount,
                  Question questions[]);
void display_simple(Question &question);
void display_verbose(Question &question);
void question_menu();
void safe_write(FileHandles &handles, int question_amount,
                Question questions[]);
void subject_menu(int size, char subject[]);
void write_into_file(ofstream &write_handle, int questions_size,
                     Question questions[]);

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
