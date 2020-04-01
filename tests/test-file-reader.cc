//
// Created by Alice Huang on 3/31/20.
//
#include <catch2/catch.hpp>
#include <bayes/file_reader.h>


TEST_CASE("Test nonexistent file", "[invalid][file]") {
  REQUIRE_FALSE(FileReader::DoesFileExist("data/weuhfwiu"));
}

TEST_CASE("Test existing file", "[exist][file]") {
  REQUIRE(FileReader::DoesFileExist("data/sampleimages"));
}

TEST_CASE("Test CountFileLines", "[CountFileLines]") {
  REQUIRE(FileReader::CountFileLines("data/samplelabels") == 3);
}

TEST_CASE("Test invalid char in image", "[invalid-char][image]") {
  REQUIRE_FALSE(FileReader::IsValidImageLabelFile("data/invalidimagechar",
      "data/validlabels"));
}

TEST_CASE("Incorrect image line length", "[line-length][incorrect]") {
  REQUIRE_FALSE(FileReader::IsValidImageLabelFile("data/invalidlinelength",
                                                  "data/validlabels"));
}

TEST_CASE("Label and image don't match", "[label][image][match]") {
  REQUIRE_FALSE(FileReader::IsValidImageLabelFile("data/sampleimages",
                                                  "data/incorrectlabels"));
}

// NOTE: This does not work because files are not allowed to have empty spaces
TEST_CASE("Label and image match", "[label][image][match]") {
  REQUIRE(FileReader::IsValidImageLabelFile("data/validimages",
                                            "data/validlabels"));
}

