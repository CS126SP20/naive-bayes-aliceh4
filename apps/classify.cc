// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>
#include <nlohmann/json.hpp>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
// TODO(you): Change the code below for your project use case.

DEFINE_string(name, "Clarice", "Your first name");
DEFINE_bool(happy, false, "Whether the greeting is a happy greeting");


int main(int argc, char** argv) {
  /*gflags::SetUsageMessage(
      "Greets you with your name. Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_name.empty()) {
    std::cerr << "Please provide a name via the --name flag." << std::endl;
    return EXIT_FAILURE;
  }

  const std::string punctuation = FLAGS_happy ? "!" : ".";

  std::cout << "Hello, " << FLAGS_name << punctuation << std::endl;
  return EXIT_SUCCESS; */

  std::ifstream file("data/model.json");
  json j = json::parse(file);
  bayes::Model model;
  std::vector images = model.GetClassImages("data/testimages");

  int sum = 0;
  int num = 0;
  std::ifstream file_labels("data/testlabels");
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
  double accuracy = (double) sum / num * 100.0;
  std::cout << accuracy << std::endl;

  // Create model

  /*bayes::Model model;
  model.CalculateProbabilities("data/trainingimages", "data/traininglabels");*/

  // Classify:
  // Now that we have the probabilities, run thru the images in testimages and
  // compare what we get with what the labels are...
  // NOTE: accuracy = double (# correct) / (5000) * 100
}
