#include <cstring>
#include <iostream>

#include "meal_data.h"

using namespace std;

MealData::MealData() {
    name_of_meal = 0;
    name_of_venue = 0;
    approximate_price = 0;
    rating = 0;
    review = 0;
    venue_type = Restaurant;
}

MealData::~MealData() {
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

bool MealData::match_data_key(DataKey data_key, char *sub_str) {
    if (is_empty()) {
        return false;
    }

    // TODO: make all the same as name_of_meal
    switch (data_key) {
        case NameOfMeal: {
            char *found = strstr(name_of_meal, sub_str);

            if (!found) {
                return false;
            } else {
                return true;
            }
        }
        case NameOfVenue: {
            return strstr(name_of_venue, sub_str) == 0;
        }
        case ApproximatePrice: {
            return strstr(approximate_price, sub_str) == 0;
        }
        case Rating: {
            return strstr(rating, sub_str) == 0;
        }
        case Review: {
            return strstr(review, sub_str) == 0;
        }
        default: {
            return false;
        }
    }
}

bool MealData::is_empty() {
    if (!name_of_meal || !name_of_venue || !approximate_price || !rating ||
        !review) {
        return true;
    } else if (name_of_meal[0] == '\0' && name_of_venue[0] == '\0' &&
               approximate_price[0] == '\0' && rating[0] == '\0' &&
               review[0] == '\0') {
        return true;
    } else {
        return false;
    }
}

bool MealData::is_restaurant() {
    return venue_type == Restaurant;
}

bool MealData::display() {
    if (is_empty()) {
        return false;
    }

    // i would rather
    const char *v_type = venue_type == Restaurant ? "restaurant" : "cart";
    // but im unsure if this would count agents the no static arrays
    // char *type = new char[50];
    // strcpy(type, venue_type == Restaurant ? "restaurant" : "cart");

    std::cout << "meal name: " << name_of_meal
              << "\nvenue name: " << name_of_venue
              << "\naprx price: " << approximate_price
              << " \nrating: " << rating << "\nreview: " << review
              << "\nit is a: " << v_type << std::endl;

    return true;
}
