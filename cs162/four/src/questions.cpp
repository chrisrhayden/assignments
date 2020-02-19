#include <cstring>
#include <iostream>

#include "questions.h"

using namespace std;

// Question constructor, set all data to 0/NULL
Question::Question() {
    question_num = 0;
    subject[0] = '\0';
    text[0] = '\0';
    date_completed[0] = '\0';
}

// read in data in a very basic way
void Question::read_in_question(int number) {
    // take in a number to let the number be made by the outer loop, in another
    // iteration we could use this number to let the user sort the order
    question_num = number;

    // read a message
    cout << "pleas give a subject\n -> ";
    // take in data to the right variable
    cin.get(subject, FIELD_SIZE, '\n');
    // clear all error flags
    cin.clear();
    // ignore / clear the rest of the input buffer
    cin.ignore(FIELD_SIZE, '\n');

    cout << "pleas give question text\n -> ";
    cin.get(text, FIELD_SIZE, '\n');
    cin.clear();
    cin.ignore(FIELD_SIZE, '\n');

    cout << "pleas give completion date\n -> ";
    cin.get(date_completed, FIELD_SIZE, '\n');
    cin.clear();
    cin.ignore(FIELD_SIZE, '\n');
}

// a simple display message
void Question::display() {
    cout << "Number: " << question_num << "\nsubject: " << subject
         << "\nQuestion: " << text << "\ncompleted on " << date_completed;
}

bool Question::compare_subject(char to_compare[]) {
    // return true if the two string are the same
    return strcmp(subject, to_compare) == 0;
}

// the list constructor, as normal set data to 0
QuestionList::QuestionList() {
    list = NULL;
    length = 0;
    max_length = 0;
}

// destructor, delete the manually allocated array
QuestionList::~QuestionList() { delete list; }

// read in all the needed data from the user
void QuestionList::read_in_all_questions() {
    int amount = 0;
    cout << "how many questions will you enter\n -> ";

    cin >> amount;
    cin.ignore(FIELD_SIZE, '\n');

    max_length = amount;

    // allocate an array sized only to what we will need
    list = new Question[amount];

    // iterate the given amount calling read_in_question() on each element
    for (int i = 0; i < amount; ++i) {
        cout << "\nQuestion " << i + 1 << endl;
        list[i].read_in_question(i + 1);
        ++length;
    }
}

// display all
void QuestionList::display_all() {
    for (int i = 0; i < length; ++i) {
        list[i].display();
        cout << endl;
    }
}

// display only if the given string matches
void QuestionList::display_type(char to_compare[]) {
    for (int i = 0; i < length; ++i) {
        // call compare_subject()
        if (list[i].compare_subject(to_compare)) {
            list[i].display();
            // so each message appears on its own
            cout << endl;
        }
    }
}
