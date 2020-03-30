// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Indeces of being shaded or not in our probs_ matrix
const int kShadedIndex = 1;
const int kWhiteIndex = 0;

namespace bayes {

void Model::SetClassNum(const string& filename) {
  // First empty array (in case it has been populated)
  std::fill_n(class_num_, kNumClasses, 0);

  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss (line);
    int number;
    iss >> number;
    // Increase the corresponding class index by one
    class_num_[number]++;
  }
}

void Model::CalculateProbabilities(const string& images, const string& labels) {
  std::vector<int> class_locations;
  std::vector<Image> image_vector = GetClassImages(images);
  // Loop through each class
  for (int c = 0; c < kNumClasses; c++) {
    class_locations.clear(); // Clear contents of vector each time
    class_locations = GetClassLocations(labels, c); // Populate vector
    // Now loop thru the pixels
    for (int j = 0; j < kImageSize; j++) {
      for (int k = 0; k < kImageSize; k++) {
        // Populate every vector?? I have no idea ahhhh
        GetProbabilityAtLocation(j, k, c, class_locations, image_vector);
      }
    }
  }
}

double Model::GetProbabilityAtLocation(int i, int j, int class_num,
                                       std::vector<int> class_locations,
                                       std::vector<Image> image_vector) {
  double shaded_sum = 0;
  for (int index : class_locations) {
    Image image = image_vector.at(index);
    char pixel_shade = image.GetCharAtPos(i, j);
    if (pixel_shade == '+' || pixel_shade == '#') {
      shaded_sum++; // If pixel is shaded, increment shaded_sum
    }
  }
  double probability = shaded_sum / class_locations.size();
  // populate probs_ accordingly
  probs_[i][j][class_num][kShadedIndex] = probability;
  probs_[i][j][class_num][kWhiteIndex] = kShadedIndex - probability;
  return probability;
}


std::vector<int> Model::GetClassLocations(const string& labels, int num) {
  // Create new vector
  std::vector<int> class_locations;

  int line_num = 0;
  std::ifstream file(labels);
  std::string line;
  while(std::getline(file, line))
  {
    std::istringstream iss (line);
    int number;
    iss >> number; // Turn line into an int
    if (number == num) {
      class_locations.push_back(line_num);
    }
    line_num++;
  }
  return class_locations;
}

std::vector<Image> Model::GetClassImages(const string& images) {
  std::vector<Image> image_vector; // Create vector

  int line_num = 0; // Keep track of line number
  std::ifstream file(images);
  std::string line;
  std::string image_lines; // New string
  while(std::getline(file, line))
  {
    if (line_num != 0 && (line_num + 1) % kImageSize == 0) {
      image_vector.push_back(image_lines); // Add image if is n*28th line
      image_lines.clear(); // clear the lines
    }
    image_lines.append(line); // Add the line
    line_num++; // Keep track of line number
  }
  return image_vector;
}

void Model::CreateJsonFile() {
  // Create an empty json object
  nlohmann::json j;
  // Go through our classes and put in corresponding matrices?
  for (int i = 0; i < kNumClasses; i++) {
    
  }
}

}  // namespace bayes

