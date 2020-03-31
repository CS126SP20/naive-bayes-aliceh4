// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using std::log;

namespace bayes {

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

}  // namespace bayes

