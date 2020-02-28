// agagagagagagagagahhagaashgasdjshghdagshdgasjkdgasjlkhdgsajkgdkjsa
// this fucking trash, I just wan to use this in table.h and list.h wtf,
// pleas tell me there is a better way or im just doing something wrong
#ifndef MEAL_DATA_H
#define MEAL_DATA_H

// to tell if it is a restaurant
enum VenueType { Cart, Restaurant };

// the data key to match on for certain tasks like retrieve
enum DataKey {
    NameOfMeal,
    NameOfVenue,
    ApproximatePrice,
    Rating,
    Review,
    VenueTypeKey
};

// the data we are working with, its a struct to easily work with the values
struct MealData {
    MealData();
    ~MealData();
    bool copy_from_meal_data(MealData *to_add);
    bool display();
    bool is_empty();
    bool is_restaurant();
    bool match_data_key(DataKey data_key, char *sub_str);
    bool match_data_key(DataKey data_key, VenueType serching_venue);
    bool match_data_key_full(DataKey data_key, char *key);

    char *name_of_meal;
    char *name_of_venue;
    char *approximate_price;
    char *rating;
    char *review;
    VenueType venue_type;
};

#endif
