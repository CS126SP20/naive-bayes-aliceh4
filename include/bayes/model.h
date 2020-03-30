// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"
#include <string>

#include <cstdlib>

using std::string;

namespace bayes {

/*
 * We've given you a starter struct to represent the model.
 * You are totally allowed to delete, change, move, rename, etc. this struct
 * however you like! In fact, we encourage it! It only exists as a starting
 * point of reference.
 *
 * In our probabilities array we have a final dimension [2], which represents
 * the individual probabilities that a pixel for a class is either shaded or
 * not shaded. Since the probability that a pixel is shaded is just
 * (1 - probability not shaded), we COULD have deleted that final dimension
 * (and you can do so if you want to), but we left it in so that you could
 * see how the model would need to change if we were to keep track of the
 * probability that a pixel is white vs. gray vs. dark gray vs. black.
 *
 * You can delete this comment once you're done with it.
 */

// 0-9 inclusive.
constexpr size_t kNumClasses = 10;
// Shaded or not shaded.
constexpr size_t kNumShades = 2;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
class Model {
  // The individual probabilities for each pixel for each class for
  // whether it's shaded or not.
  //
  // Examples:
  // probs[2][10][7][0] is the computed probability that a pixel at
  // [2][10] for class 7 is not shaded.
  //
  // probs[0][0][0][1] is the computed probability that a pixel at
  // [0][0] for class 0 is shaded.
 private:
  double probs_[kImageSize][kImageSize][kNumClasses][kNumShades];

 public:
  // Array representing the number of occurrences of a specific class
  int class_num_[kNumClasses];

  // Populate class_num_ from data from the given file
  void SetClassNum(const string& filename);

  // Get locations of a certain class (specific indexes)
  std::vector<int> GetClassLocations(const string& labels, int num);

  // Loop through the image file and split every 28 lines into an image object
  std::vector<Image> GetClassImages(const string& images);

  // Given a file, populate the probs_ matrix correctly
  // NOTE: images is "data/trainingimages" and labels is "data/traininglabels"
  void CalculateProbabilities(const string& images, const string& labels);

  // Create the model file and populate w data
  void CreateModelFile(const string& filename);

};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
