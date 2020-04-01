//
// Created by Alice Huang on 3/31/20.
//

#include <bayes/file_reader.h>

#include <fstream>

const size_t kImageSize = 28;

bool FileReader::DoesFileExist(const string& file_name) {
  std::ifstream ifile(file_name);
  if (ifile) {
    return true;
  }
  return false;
}

int FileReader::CountFileLines(const string& label_file) {
  std::ifstream  file(label_file);
  string line;
  int line_count = 0;
  while(getline(file, line)) {
    line_count++;
  }
  return line_count;
}

bool FileReader::IsValidImageLabelFile(const string& image_file, const string& label_file) {
  std::ifstream file(image_file);
  string line;
  int image_line_count = 0;
  while(std::getline(file, line)) {
    // Make sure each line is 28 characters long
    if (line.length() != kImageSize) {
      return false;
    }
    for (int i = 0; i < kImageSize; i++) {
      // Check for invalid characters
      if (line[i] != ' ' && line[i] != '+' && line[i] != '#') {
        return false;
      }
    }
    image_line_count++;
  }
  // Make sure that total number of lines in image file is valid
  if (image_line_count % kImageSize != 0) {
    return false;
  }
  int label_line_count = CountFileLines(label_file);
  return image_line_count / kImageSize == label_line_count;
}
