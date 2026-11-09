#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct color {
    double r = 255;
    double g = 255;
    double b = 255;
};

enum class colorRating { HIGHRISK, CAUTION, SAFE };

struct pairResult {
    std::size_t color1;
    std::size_t color2;
    double normal;
    double modeled;
    double distinguishability;
    colorRating rating;
};

using palette = std::vector<color>;
using resultList = std::vector<pairResult>;

/*
    The largest possible distance between two RGB values is from black to white. If we use a cube
   for reference, the diagonal between 0 and 255 is roughly 255 * sqrt(3). Dividing a distance by
   this length gives scale from 0-100%. This scale tells us that if two colors have a percentage of
   100%, it's as different as black and white. If it has a percentage of 0% the colors are almost
   identical. The red-green model elaves black and white unchanged, so the same maximum applies to
   my modeled distance.
*/
const double maxDistance = 255 * std::sqrt(3.0);
/*
    The cutoffs (which are 17% and 34%) were chosen so that every pair that becomes
    nearly indistinguishabile per the Machado (2009) simulation is flagged as at *least*
    Caution. These values were tested against every respective pair in the Okabe-Ito and
    Matplotlib tab10 palettes.
*/
const double riskThreshold = 17;
const double cautionThreshold = 34;

palette readPalette() {
    palette colors;

    std::cout << "All color channel values can be integers or decimals, entered in comma separated "
                 "formatting (e.g. 255.0, 128.5, 0).\n";
    std::cout << "Press 'Enter' on an empty line to finish the palette.\n\n";

    while (true) {
        std::cout << "Enter Color " << colors.size() + 1 << " as r, g, b:\n";

        std::string line;
        if (!std::getline(std::cin, line) || line.empty()) {
            break;
        }

        std::istringstream in(line);
        color currentColor;
        char firstComma;
        char secondComma;

        if (!(in >> currentColor.r >> firstComma >> currentColor.g >> secondComma >>
              currentColor.b)) {
            std::cout << "RGB values must be comma-separated numeric values.\n";
            continue;
        } else if (firstComma != ',' || secondComma != ',') {
            std::cout << "RGB values must be comma separated.\n";
            continue;
        } else if (
            currentColor.r < 0 || currentColor.r > 255 || currentColor.g < 0 ||
            currentColor.g > 255 || currentColor.b < 0 || currentColor.b > 255
        ) {
            std::cout << "RGB values must be between 0 and 255.\n";
            continue;
        }

        colors.push_back(currentColor);
    }

    return colors;
}

double distance(const color& color1, const color& color2) {
    return std::sqrt(
        (color1.r - color2.r) * (color1.r - color2.r) +
        (color1.g - color2.g) * (color1.g - color2.g) +
        (color1.b - color2.b) * (color1.b - color2.b)
    );
}

colorRating rateDistinguishability(double distinguishability) {
    if (distinguishability < riskThreshold) {
        return colorRating::HIGHRISK;
    } else if (distinguishability < cautionThreshold) {
        return colorRating::CAUTION;
    }

    return colorRating::SAFE;
}

resultList comparePalette(const palette& colors) {
    resultList results;

    // Compare 1 color index against the others.
    for (std::size_t index1 = 0; index1 < colors.size(); index1++) {
        // Compare everything after the current index so redundant checks are avoided.
        for (std::size_t index2 = index1 + 1; index2 < colors.size(); index2++) {
            const color& color1 = colors[index1];
            const color& color2 = colors[index2];

            const double average1 = (color1.r + color1.g) / 2;
            const double average2 = (color2.r + color2.g) / 2;

            const color modeledColor1 = {average1, average1, color1.b};
            const color modeledColor2 = {average2, average2, color2.b};

            const double normalDistance = distance(color1, color2);
            const double modeledDistance = distance(modeledColor1, modeledColor2);

            const double distinguishability = (modeledDistance / maxDistance) * 100;

            colorRating rating = rateDistinguishability(distinguishability);

            results.push_back(
                {index1, index2, normalDistance, modeledDistance, distinguishability, rating}
            );
        }
    }

    return results;
}

std::string getRatingName(colorRating rating) {
    switch (rating) {
    case colorRating::HIGHRISK:
        return "High Risk";
    case colorRating::CAUTION:
        return "Caution";
    case colorRating::SAFE:
        return "Safe";
    }
    return "";
}

void printResults(colorRating rating, const resultList& results) {
    int count = 0;

    for (const pairResult& result : results) {
        if (result.rating == rating) {
            count++;
        }
    }

    if (count <= 0) {
        return;
    }

    const std::string ratingName = getRatingName(rating);

    std::cout << ratingName << " (" << count << ")\n";
    for (const pairResult& result : results) {
        if (result.rating == rating) {
            std::cout << "  Color " << result.color1 + 1 << " vs Color " << result.color2 + 1
                      << " (" << std::round(result.distinguishability * 100) / 100 << "%)\n";
        }
    }
    std::cout << "\n";
}

int main() {
    const palette colors = readPalette();

    if (colors.size() < 2) {
        std::cout << "Please input at least 2 colors to compare.\n";
        return 1;
    }

    const resultList results = comparePalette(colors);

    std::cout << "Compared (" << colors.size() << ") colors.\n\n";
    printResults(colorRating::HIGHRISK, results);
    printResults(colorRating::CAUTION, results);
    printResults(colorRating::SAFE, results);

    return 0;
}