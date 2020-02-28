#include <cstring>
#include <iostream>

#include "meal_data.h"

using namespace std;

// MealData constructor
MealData::MealData() {
    name_of_meal = 0;
    name_of_venue = 0;
    approximate_price = 0;
    rating = 0;
    review = 0;
    venue_type = Restaurant;
}

// MealData deconstructor
MealData::~MealData() {
    // delete all data if it exists
    if (name_of_meal) {
        delete[] name_of_meal;
    }

    if (name_of_venue) {
        delete[] name_of_venue;
    }

    if (approximate_price) {
        delete[] approximate_price;
    }

    if (rating) {
        delete[] rating;
    }

    if (review) {
        delete[] review;
    }
}

// copy data from a given MealData in to the current one
bool MealData::copy_from_meal_data(MealData *to_add) {
    name_of_meal = new char[strlen(to_add->name_of_meal)];
    strcpy(name_of_meal, to_add->name_of_meal);

    name_of_venue = new char[strlen(to_add->name_of_venue)];
    strcpy(name_of_venue, to_add->name_of_venue);

    approximate_price = new char[strlen(to_add->approximate_price)];
    strcpy(approximate_price, to_add->approximate_price);

    rating = new char[strlen(to_add->rating)];
    strcpy(rating, to_add->rating);

    review = new char[strlen(to_add->review)];
    strcpy(review, to_add->review);

    venue_type = to_add->venue_type;

    return is_empty() == false;
}

// match self with a sub_str and data key
bool MealData::match_data_key(DataKey data_key, char *sub_str) {
    if (is_empty()) {
        return false;
    }

    // match off the data_key
    switch (data_key) {
        case NameOfMeal: {
            // strstr returns a ptr so a test for NULL will see if it has data
            return strstr(name_of_meal, sub_str) != NULL;
        }
        case NameOfVenue: {
            return strstr(name_of_venue, sub_str) != NULL;
        }
        case ApproximatePrice: {
            return strstr(approximate_price, sub_str) != NULL;
        }
        case Rating: {
            return strstr(rating, sub_str) != NULL;
        }
        case Review: {
            return strstr(review, sub_str) != NULL;
        }
        default: {
            return false;
        }
    }
}

// match self with full string
bool MealData::match_data_key_full(DataKey data_key, char *sub_str) {
    if (is_empty()) {
        return false;
    }

    switch (data_key) {
        case NameOfMeal: {
            // cmp full string, 0 is success
            return strcmp(name_of_meal, sub_str) == 0;
        }
        case NameOfVenue: {
            return strcmp(name_of_venue, sub_str) == 0;
        }
        case ApproximatePrice: {
            return strcmp(approximate_price, sub_str) == 0;
        }
        case Rating: {
            return strcmp(rating, sub_str) == 0;
        }
        case Review: {
            return strcmp(review, sub_str) == 0;
        }
        default: {
            return false;
        }
    }
}

// check if data is empty
bool MealData::is_empty() {
    // values are not instantiated
    if (!name_of_meal || !name_of_venue || !approximate_price || !rating ||
        !review) {
        return true;
        // see if all data is empty but instantiated
    } else if (name_of_meal[0] == '\0' && name_of_venue[0] == '\0' &&
               approximate_price[0] == '\0' && rating[0] == '\0' &&
               review[0] == '\0') {
        return true;
    } else {
        return false;
    }
}

// check if a restaurant
bool MealData::is_restaurant() {
    return venue_type == Restaurant;
}

// display the data
bool MealData::display() {
    if (is_empty()) {
        return false;
    }

    // i would rather
    // const char *v_type = venue_type == Restaurant ? "restaurant" : "cart";
    // but im unsure if this would count agents the no static arrays
    char *v_type = new char[50];
    strcpy(v_type, venue_type == Restaurant ? "restaurant" : "cart");

    std::cout << "meal name: " << name_of_meal
              << "\nvenue name: " << name_of_venue
              << "\naprx price: " << approximate_price
              << " \nrating: " << rating << "\nreview: " << review
              << "\nit is a: " << v_type << std::endl;

    delete[] v_type;

    return true;
}
