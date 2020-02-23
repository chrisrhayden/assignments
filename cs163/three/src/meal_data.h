// agagagagagagagagahhagaashgasdjshghdagshdgasjkdgasjlkhdgsajkgdkjsa
// this fucking trash, I just wan to use this in table.h and list.h wtf
#ifndef MEAL_DATA_H
#define MEAL_DATA_H

enum VenueType { Cart, Restaurant };

enum DataKey {
    NameOfMeal,
    NameOfVenue,
    ApproximatePrice,
    Rating,
    Review,
    VenueTypeKey
};

struct MealData {
    MealData();
    ~MealData();
    bool copy_from_meal_data(const MealData *to_add);
    bool display();
    bool is_empty();
    bool is_restaurant();
    bool match_data_key(DataKey data_key, char *sub_str);
    bool match_data_key(DataKey data_key, VenueType serching_venue);

    char *name_of_meal;
    char *name_of_venue;
    char *approximate_price;
    char *rating;
    char *review;
    VenueType venue_type;
};

struct MealCollect {
    MealCollect(int max_length);
    ~MealCollect();

    MealData **meal_array;
    bool add(MealData *to_add);
    int length;
    int max_len;
};

#endif
