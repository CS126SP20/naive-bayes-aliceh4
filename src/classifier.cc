// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <sstream>

using json = nlohmann::json;
using std::log;

namespace bayes {

// Constant to change a decimal representation to percent
const int kToPercent = 100;

double CalculatePosteriorProbability(Image image, int class_num, const json& j) {
  // Now get specific class probabilities
  std::string title = "Class " + std::to_string(class_num);
  json probability = j[title];
  json class_occurrences = j["Class occurrences"]; // Get # of class occurrences
  int prob_index = 0;
  double prob_sum = log((double) class_occurrences[class_num]); // Add the prior
  // Now add the posterior probabilities
  for (int i = 0; i < kImageSize; i++) {
    for (int j = 0; j < kImageSize; j++) {
      // Get the char at the position
      char shade = image.GetCharAtPos(i, j);
      // Check if shaded first
      if (shade == '#' || shade == '+') {
        prob_sum += log((double) probability[prob_index]);
      } else if (shade == ' ') {
        // Notice: need to subtract probability by 1 b/c unshaded
        double blank_prob = 1.0 - (double) probability[prob_index];
        prob_sum += log(blank_prob);
      }
      prob_index++;
    }
  }
  return prob_sum;
}

int GetClassIdentity(const Image& image, const json& j) {
  int max_class = 0;
  // Add the posterior probabilities into the vector
  for (int c = 1; c < kNumClasses; c++) {
    if (CalculatePosteriorProbability(image, max_class, j)
        < CalculatePosteriorProbability(image, c, j)) {
      max_class = c;
    }
  }
  return max_class;
}

double GetClassifierAccuracy(const string& image_path, const string& label_path, const string& model_path) {
  // First create JSON object
  std::ifstream file(model_path);
  json j = json::parse(file);
  // Now get images from file
  std::vector<Image> images = bayes::Model::GetClassImages(image_path);
  int sum = 0; // To keep track of how many times our model classifies right
  int num = 0; // To keep track of the total amount of images in the file
  // Loop through and see if labels match our model's predictions
  std::ifstream file_labels(label_path);
  std::string line;
  while (std::getline(file_labels, line)) {
    std::istringstream iss (line);
    int number;
    iss >> number;
    if (number == bayes::GetClassIdentity(images.at(num), j)) {
      sum++;
    }
    num++;
  }
  double accuracy = (double) sum / num * kToPercent;
  return accuracy;
}

}  // namespace bayes

