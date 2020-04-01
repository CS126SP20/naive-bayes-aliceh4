// Copyright (c) 2020 [Alice Huang]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <vector>

namespace bayes {

constexpr size_t kImageSize = 28;

class Image {
 private:
  char pixels_[kImageSize][kImageSize];
 public:

  /**
   * Constructor for Image object.
   * @param image string representation of the image (to be turned to char[][])
   */
  Image(std::string image);

  /**
   * Takes in two ints that describe a pixel location and return the char at
   * that position for the image.
   *
   * @param i the 'x' position of the pixel
   * @param j the 'y' position of the pixel
   * @return the char at pixels_[i][j]
   */
  char GetCharAtPos(int i, int j);
};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
