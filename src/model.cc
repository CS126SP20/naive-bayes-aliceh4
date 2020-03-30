// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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
  for (int i = 0; i < kNumClasses; i++) {
    class_locations.clear(); // Clear contents of vector each time
    class_locations = GetClassLocations(labels, i); // Populate vector
  }
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
    if (line_num != 0 && line_num % kImageSize == 0) {
      image_vector.emplace_back(image_lines); // Add image if is n*28th line
      image_lines.clear(); // clear the lines
    }
    image_lines.append(line); // Add the line
    line_num++; // Keep track of line number
  }
  return image_vector;
}

void Model::CreateModelFile(const string& filename) {
  // Some of the following code derived from:
  // https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
  std::ofstream file("model.csv");
}

}  // namespace bayes

