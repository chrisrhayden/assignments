#!/bin/sh

find './src/' \( -name "*.cpp" -o -name '*.h' \) \
    -print \
    -exec sed -i -e 's|HouseData|MealData|g' {} \;
