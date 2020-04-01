//
// Created by Alice Huang on 3/31/20.
//

#ifndef BAYES_FILE_READER_H
#define BAYES_FILE_READER_H

#include <string>

using std::string;

class FileReader {
 public:
  /**
   * Takes a string file name and returns if the file exists or not.
   *
   * @param file_name the name of the file
   * @return true if the file exists, false if not
   */
  static bool DoesFileExist(const string& file_name);

  /**
   * Return the number of lines in a file.
   *
   * @param label_file the file to be examined
   * @return the number of lines in the file
   */
  static int CountFileLines(const string& label_file);

  /**
   * Takes an image and label file and makes sure that they are both valid
   * according to the assignment specifications (matching number of images and
   * labels, no invalid characters, right length of each row in image file).
   *
   * @param image_file the name of the image file
   * @param label_file the name of the label file
   * @return true if both are valid, false otherwise
   */
  static bool IsValidImageLabelFile(const string& image_file,
                                    const string& label_file);
};

#endif  // BAYES_FILE_READER_H
