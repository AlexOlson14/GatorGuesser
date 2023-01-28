#pragma once
#include <vector>
#include "Image.h"

class ImageProvider {
private:
    vector<Image> images;
    int i = 0;
public:
    ImageProvider();
    Image getImage();
};