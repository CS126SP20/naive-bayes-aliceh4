// Copyright (c) 2020 [Alice Huang]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"
#include <string>

#include <cstdlib>

using std::string;

namespace bayes {

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

  /**
   * Takes a file and populates class_num_ with the number of occurrences of
   * each label.
   *
   * @param filename the name of the file
   */
  void SetClassNum(const string& filename);

  /**
   * Get locations of a certain class (specific indexes) and returns a vector
   * of the locations.
   *
   * @param labels the name of the label file
   * @param num the class to be examined
   * @return a vector of the locations for this specific class
   */
  static std::vector<int> GetClassLocations(const string& labels, int num);

  /**
   * Loops through an image file and split every 28 lines into an Image object,
   * then returns a vector of these Image objects.
   *
   * @param images the name of the image file
   * @return an image vector representation of the file
   */
  static std::vector<Image> GetClassImages(const string& images);

  /**
   * Returns the probability of being shades given that they are in a certain
   * class at the specified point. Also populates the probs_ matrix accordingly.
   *
   * @param                 i the 'x' location
   * @param                 j the 'y' location
   * @param                 class_num the class being examined
   * @param class_locations a vector of the locations of the given class
   * @param image_vector    a vector of all training images
   * @return the probability of being shaded at the specified parameters
   */
  double GetProbabilityAtLocation(int i, int j, int class_num,
                                  const std::vector<int>& class_locations,
                                  const std::vector<Image>& image_vector);

  /**
   * Takes in two file names, representing the image file and label files
   * respectively, and populates the probs_ matrix according to its description
   * above.
   *
   * @param images name of the image file
   * @param labels name of the label file
   * @param name   the name the user wants the model to have
   */
  void CalculateProbabilities(const string& images, const string& labels, const string& name);

  /**
   * Creates a JSON file to save our model, using information from probs_ and
   * class_num_.
   * @param name what the user wants the file to be named
   */
  void CreateJsonFile(const string& name);

};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
