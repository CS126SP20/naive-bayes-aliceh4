// Copyright (c) 2020 [Alice Huang]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/model.h>
#include <gflags/gflags.h>
#include <nlohmann/json.hpp>

#include <string>
#include <cstdlib>
#include <iostream>

using json = nlohmann::json;

DEFINE_string(image_path, "data/testimages", "The images filepath.");
DEFINE_string(label_path, "data/testlabels", "The labels filepath.");
DEFINE_bool(is_training, true, "Whether we are training or not.");
DEFINE_string(model_path, "data/model.json", "The model filepath.");

int main(int argc, char** argv) {
  gflags::SetUsageMessage(
      "Should either train your model or classify the given file sets"
             ". Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_image_path.empty() || FLAGS_label_path.empty()) {
    std::cerr << "Please provide filepaths via the --image_path and "
                 "--label_path flag." << std::endl;
    return EXIT_FAILURE;
  }
  if (FLAGS_is_training) {
    bayes::Model model{};
    model.CalculateProbabilities(FLAGS_image_path, FLAGS_label_path,
        FLAGS_model_path);
    std::cout << "Training finished!" << std::endl;
    return EXIT_SUCCESS;
  }
  double accuracy = bayes::GetClassifierAccuracy(FLAGS_image_path,
      FLAGS_label_path, FLAGS_model_path);
  std::cout << "Classifier accuracy: " << accuracy  << "%" << std::endl;
  return EXIT_SUCCESS;
}
