#pragma once
#include <string>
using namespace std;

class Image {
public:
    Image(string name, int x, int y) : name(std::move(name)), location(x, y) {}
    string name;
    pair<int, int> location;
};