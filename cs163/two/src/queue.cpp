#include <cstring>
#include <fstream>

#include <iostream>

#include "queue.h"
#include "route.h"

QNode::QNode() {
    next = 0;
    route = 0;
}

QNode::~QNode() {
    next = 0;

    delete route;
}

Route::Route() {
    street = 0;
    length = 0;
    traffic = 0;
    note = 0;
    construction = 0;
}

Route::~Route() {
    delete[] street;
    street = 0;

    delete[] length;
    length = 0;

    delete[] traffic;
    traffic = 0;

    delete[] note;
    note = 0;

    delete[] construction;
    construction = 0;
}

Queue::Queue() {
    head = 0;
    tail = 0;
}

Queue::~Queue() {
    QNode *temp = 0;
    QNode *current = head;

    if (current) {
        temp = current->next;
        delete current;

        current = temp;
    }

    while (current && current != head) {
        temp = current->next;

        delete current;

        current = temp;
    }

    head = 0;
    tail = 0;
}

bool Queue::enqueue(Route *data) {
    Route *n_route = new Route();

    bool success = data->copy_into(n_route);

    if (success) {
        QNode *n_node = new QNode();

        n_node->route = n_route;

        if (!head) {
            head = n_node;
        }

        if (tail) {
            tail->next = n_node;
        }

        tail = n_node;

        tail->next = head;
    } else {
        delete n_route;
    }

    return success;
}

bool Queue::dequeue(Route *&to_fill) {
    if (!head) {
        return false;
    }

    if (head->route->copy_into(to_fill)) {
        tail->next = 0;

        QNode *temp = head->next;

        delete head;

        head = temp;

        tail->next = head;

        return true;
    } else {
        return false;
    }
}

bool Queue::peek(Route *&to_fill) {
    if (!head) {
        return false;
    }

    return head->route->copy_into(to_fill);
}

bool Queue::is_empty() {
    if (!head) {
        return true;
    }

    return head->route->is_empty();
}

bool Queue::display() {
    bool success = true;
    QNode *current = head;

    if (current) {
        success = current->route->display();

        current = current->next;
    }

    while (current && current != head && success) {
        success = current->route->display();

        current = current->next;
    }

    return success;
}

// these functions kinda suck but oh well ---------->

// fill a sting until a pattern
int fill_from_str(char pattern, char *&to_fill, char *source, int start) {
    if (start == -1) {
        return -1;
    }

    // make a temporary array to hold the data from the source string
    char *temp = new char[1000];
    // get the full source length as a default stopping condition
    int parse_len = strlen(source);

    // instantiate i and target outside the loop to use later in the function
    int i = 0;
    int end = start;
    for (; i < parse_len && source[end] != '$'; ++i, ++end) {
        temp[i] = source[end];
    }

    // if i is 0 then noting was done and so an error is in the file
    if (i == 0) {
        end = -1;

    } else {
        // cap off the string
        temp[i] = '\0';

        // now make a perfectly fitting array for the segment
        to_fill = new char[strlen(temp)];

        // copy the segment in to the given array
        strcpy(to_fill, temp);
    }

    // remove the temporary array
    delete[] temp;

    // return new end
    return end;
}

// fill a sting until a pattern
int fill_from_str(char *&to_fill, char *from_str, int start) {
    // just call fill_from_str with the default pattern
    return fill_from_str('$', to_fill, from_str, start);
}

// add the data to a temp route to then add to the queue when done
bool parse_and_add(Queue *&to_enqueue, char *to_parse) {
    // make a temporary Route to gather data
    Route *route = new Route();

    int stopped = -1;

    bool success = true;

    // add 1 to the stopped variable to skip the last $ char
    stopped = fill_from_str(route->street, to_parse, stopped + 1);
    stopped = fill_from_str(route->length, to_parse, stopped + 1);
    stopped = fill_from_str(route->traffic, to_parse, stopped + 1);
    stopped = fill_from_str(route->note, to_parse, stopped + 1);
    stopped = fill_from_str(route->construction, to_parse, stopped + 1);

    // is fill_from_str returned a -1 then there was an error
    // if all was successful then enqueue the route
    if (stopped == -1) {
        success = false;
    } else {
        success = to_enqueue->enqueue(route);
    }

    // delete the temporary route
    delete route;

    // return whether all was successful
    return success;
}

bool load_queue_from_file(char *path, Queue *&queue_one, Queue *&queue_two) {
    // get a handle on the input file
    std::ifstream input_file;

    // open the file
    input_file.open(path);

    // check if there is data and we really do have a handle o the file
    if (!input_file.peek()) {
        // close to be sure
        input_file.close();
        return false;
    }

    // make a temporary array to hold the data from the file
    char *temp = new char[1000];

    bool success = true;

    Queue *to_enqueue = queue_one;

    // while its not the end of the file, we can still get data and the parsing
    // worked last time
    while (input_file.peek() && !input_file.eof() && success) {
        // get characters until a \n or 1000
        input_file.getline(temp, 1000);

        if (strcmp(temp, "-----") == 0) {
            to_enqueue = queue_two;
        } else {
            // parse the data and add to the queue
            success = parse_and_add(to_enqueue, temp);
        }
    }

    // close as were done
    input_file.close();

    // delete the temporary array
    delete[] temp;

    return success;
}
// <----------
