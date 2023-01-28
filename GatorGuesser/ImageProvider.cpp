#include <algorithm>
#include <fstream>
#include "ImageProvider.h"

ImageProvider::ImageProvider() {
    srand(time(nullptr));
    ifstream file("imageCoords.csv");
    if (file.is_open()) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            int firstComma = line.find(',');
            int secondComma = line.find(',', firstComma + 1);
            string name = line.substr(0, firstComma);
            double lat = stod(line.substr(firstComma + 1, secondComma));
            double lon = stod(line.substr(secondComma + 1));
            int x = (int)((29.654237097667277 - lat) * 35524.4451797);
            int y = (int)((82.3757603017955 - lon) * 30811.2543576);
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