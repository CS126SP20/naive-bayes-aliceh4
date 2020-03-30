// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>
#include <string>

namespace bayes {

Image::Image(std::string image) {
  int pixel_index = 0;
  for (int i = 0; i < kImageSize; i++) {
    for (int j = 0; j < kImageSize; j++) {
      pixels_[i][j] = image[pixel_index];
      pixel_index++;
    }
  }
}

char Image::GetCharAtPos(int i, int j) {
  return pixels_[i][j];
}

}  // namespace bayes

