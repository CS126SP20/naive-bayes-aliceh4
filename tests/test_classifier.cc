// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>

// NOTE: this test case also indirectly tests GetPosteriorProbability, so it is
// really testing both of the functions in classifier.h
TEST_CASE("Test GetClassIdentity", "[classifier]") {
  bayes::Model model{};
  model.CalculateProbabilities("data/sampleimages",
      "data/samplelabels", "samplemodel.json");
  std::ifstream file("samplemodel.json");
  json j = json::parse(file);
  std::vector images = bayes::Model::GetClassImages("data/sampleimages");
  int predicted_class = bayes::GetClassIdentity(images.at(0), j);
  REQUIRE(predicted_class == 5);
}

TEST_CASE("Test GetClassifierAccuracy", "[GetClassifierAccuracy]") {
  double accuracy = bayes::GetClassifierAccuracy("data/sampleimages",
      "data/samplelabels", "samplemodel.json");
  REQUIRE(accuracy >= 70);
}
