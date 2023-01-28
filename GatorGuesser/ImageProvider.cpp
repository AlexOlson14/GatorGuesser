#include <algorithm>
#include <fstream>
#include "ImageProvider.h"

ImageProvider::ImageProvider() {
    ifstream file("ImageInfo.csv");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int firstComma = line.find(',');
            int secondComma = line.find(',', firstComma + 1);
            string name = line.substr(0, firstComma);
            int x = stoi(line.substr(firstComma + 1, secondComma));
            int y = stoi(line.substr(secondComma + 1));
            images.emplace_back(name, x, y);
        }
        file.close();
    }
}

Image ImageProvider::getImage() {
    if (i % images.size() == 0)
        random_shuffle(images.begin(), images.end());
    return images[i++ % images.size()];
}