// algorithm
//
// 1. greet the user and tell them the function of the program
//
// 2. ask if the user would like to calculate for only on term or several
//
// 3. if the user wants to calculate only one term pressed o for one
//    else press m for many (or anythig else)
//
// 4a. calculate a gpa for a single term
// 	1. ask the user for the amount of class's
// 	2. ask the user for the amount of credit hours
// 	3. ask the user for an individual grade
// 	5. ask the user for the grades +/-
// 	6. get the grade value from the letter grad and +/-
// 	7. multiply the grade value by the number of credit hours equaling the
// 	   grade points
// 	8. repeat step two to here adding each one to a total for the term
// 	9. divide the total quality points by the total credit hours for the
// 	   term equaling the terms gpa
// 	10. display the gpa to the user
//
// 4b. calculate the cumulative gpa for several terms
// 	1. ask the user for the number of term to calculate
// 	2. run the single term calculator the given amount of times
// 	3. total each result equaling the cumulative gpa
// 	4. display the gpa to the user

// declare/import the needed library's
#include <cctype>
#include <cstdio>
#include <iostream>

// declare/use the namespace std, so `std::` can be left out
using namespace std;

// a struct to conveniently gather grade data
struct Grade {
    float quality_points;
    float hours;
};

float get_letter_value(char letter, char modifier)
{
    float offset = 0.0;

    // set the number value for the modifier
    if (modifier == '-') {
        offset = -0.33;
    } else if (modifier == '+') {
        offset = 0.33;
    }

    // case the latter for the right grade score
    switch (tolower(letter)) {
        case 'd': {
            return 1.00 + offset;
        }
        case 'c': {
            return 2.00 + offset;
        }
        case 'b': {
            return 3.00 + offset;
        }
        case 'a': {
            // make sure an 'a' can never be more the 4.0
            if (0 > offset) {
                return 4.00 + offset;
            } else {
                return 4.00;
            }
        }
        case 'f': {
            return 0.0;
        }
        default: {
            // so this function will never be invalid
            return 0.0;
        }
    }
}

Grade calculate_single()
{
    // make a grade struct for a single term
    Grade term = {quality_points : 0.0, hours : 0.0};
    int class_amount = 0;

    cout << "\n\npleas give the amount of classes that will be calculated"
         << "\n -> " << flush;

    cin >> class_amount;

    for (int i = 0; i < class_amount; i++) {
        char letter = 'f';
        char modifier = 'n';
        float total = 0.0;
        float hours = 0.0;
        float letter_value = 0.0;

        cout << "\n\ninfo for class " << i + 1
             << "\n\npleas give the amount credit hours\n -> " << flush;

        cin >> hours;

        cout << "\npleas give a letter grade\n (e.g. a|B|c) -> " << flush;

        cin >> letter;

        cout << "\npleas give a grade modifier (n for none)\n (e.g. -|n|+) -> "
             << flush;

        cin >> modifier;

        // if the modifier was bad say so and start again
        if (modifier != '-' && modifier != '+' && modifier != 'n') {
            cout << "bad modifier " << modifier << endl;
        }

        letter_value = get_letter_value(letter, modifier);

        if (0 > letter_value) {
            cout << "pleas give a valid grade" << endl;
            continue;
        }

        cout << "\n\ndebug -- class quality_points: " << letter_value * hours
             << " -- hours: " << hours << endl;

        // add this class to the total
        term.quality_points += letter_value * hours;
        ;
        term.hours += hours;
    }

    cout << "\n\ndebug -- term quality_points: " << term.quality_points
         << " -- hours: " << term.hours << endl;

    // return the grade struct for the term
    return term;
}

Grade calculate_many()
{
    int terms = 0;
    Grade many_terms = {0.0, 0.0};

    cout << "how many terms would you like to calculate for\n (1|3|5) -> "
         << flush;

    cin >> terms;

    // run calculate_single() s many times given
    // adding each total to a running total
    for (int i = 0; i < terms; i++) {
        cout << "\n\nterm " << i + 1 << endl;

        // get a single term
        Grade iner_grade = calculate_single();

        // add it to the total
        many_terms.quality_points += iner_grade.quality_points;
        many_terms.hours += iner_grade.hours;
    }

    // return the Grade struct containing the total
    return many_terms;
}

void run(float terms[])
{
    // instantiate all variables to ovoid garbage values
    float total = 0;
    char single_term = 'o';
    Grade main_grade = {0.0, 0.0};

    cout << "welcome to the gpa maker"
            "\ndo you want to calculate for one term or many"
            "\nenter o for one term or m for may (or anything else)"
            "\n (o|m) -> "
         << flush;

    cin >> single_term;

    // if the user selects an o char proses only a single term
    if (tolower(single_term) == 'o') {
        main_grade = calculate_single();
        // if the user selects anything else run for many terms
    } else {
        main_grade = calculate_many();
    }

    // calculate the main total after all the data has been collected
    total = main_grade.quality_points / main_grade.hours;

    terms[0] = total;
    terms[1] = main_grade.hours;
    return;

}

// the main program logic
int main()
{
    char restart = 'n';

    float terms[3] = {0.0, 0.0};

    do {

        run(terms);

        cout << "do you want to run this again\n (y|n) -> " << flush;

        cin >> restart;

        // run the loop until the user chooses the char n
    } while (tolower(restart) == 'y');

    // return 0 to let the os know it was a success
    return 0;
}
