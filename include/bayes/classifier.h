// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include "image.h"
#include <vector>
#include <nlohmann/json.hpp>

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

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

