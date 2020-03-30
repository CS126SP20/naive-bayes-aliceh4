//
// Created by Alice Huang on 3/29/20.
//
#include <catch2/catch.hpp>
#include <bayes/model.h>

TEST_CASE("Test SetClassNum", "[SetClassNum]") {
  bayes::Model model{};
  model.SetClassNum("data/samplelabels");
  bool state = true;
  int to_compare[] = {1, 0, 0, 0, 1, 1, 0, 0, 0, 0};
  for (int i = 0; i < 10; i++) {
    if (to_compare[i] != model.class_num_[i]) {
      state = false;
    }
  }
  REQUIRE(state);
}

TEST_CASE("Test GetClassLocations", "[GetClassLocations]") {
  bayes::Model model;
  std::vector loc = model.GetClassLocations("data/samplelabels", 0);
  bool state = true;
  // Test to see if method returns what we expect
  if (loc.size() != 1 || loc.at(0) != 1) {
    state = false;
  }
  REQUIRE(state);
}

TEST_CASE("Test GetClassImages", "[GetClassImages]") {
  bayes::Model model;
  std::vector images = model.GetClassImages("data/sampleimages");
  bool state = true;
  if (images.size() != 3) {
    state = false;
  }
  REQUIRE(state);
}

TEST_CASE("Test GetProbabilityAtLocation", "[GetProbabilityAtLocation]") {
  bayes::Model model;
  std::vector images = model.GetClassImages("data/sampleimages");
  std::vector loc = model.GetClassLocations("data/samplelabels", 0);
  bool state = true;
  double prob_shaded =
      model.GetProbabilityAtLocation(3, 15, 0,loc, images);
  double prob_unshaded =
      model.GetProbabilityAtLocation(0, 15, 0, loc, images);
  if (prob_shaded != 1 && prob_unshaded != 1) {
    state = false;
  }
  REQUIRE(state);
}