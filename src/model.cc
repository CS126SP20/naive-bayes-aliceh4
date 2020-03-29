// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>


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
  
}


void Model::CreateModelFile(const string& filename) {
  // Some of the following code derived from:
  // https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
  std::ofstream file("model.csv");
}

}  // namespace bayes

