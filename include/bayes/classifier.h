// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include "image.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <string>

using std::string;
using json = nlohmann::json;

namespace bayes {

/**
 * Calculates the posterior probability for an image being in the specified
 * class.
 *
 * @param image     the image to be analyzed
 * @param class_num the class the image is to be compared to
 * @return the posterior probability that image belongs to class_num
 */
double CalculatePosteriorProbability(Image image, int class_num, const json& model);

/**
 * Returns the class identity for an image.
 *
 * @param image the image being examined
 * @return an int representation of the class with the highest probability
 */
int GetClassIdentity(const Image& image, const json& j);

/**
 * Returns the accuracy of the classifying model after we have already trained
 * it.
 *
 * @param image_path the file path of our testing images
 * @param label_path the file path of our testing labels
 * @param model_path the file path of our generated model from training
 * @return the accuracy of our model in classifying (represented as a percent)
 */
double GetClassifierAccuracy(const string& image_path, const string& label_path, const string& model_path);

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

