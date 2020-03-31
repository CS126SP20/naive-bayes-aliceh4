// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>


// TODO(you): Remove this unnecessary test case.
TEST_CASE("Sanity Check", "[addition]") {
  REQUIRE(1 + 1 == 2);
}

TEST_CASE("bleh Check", "[addition]") {
  bayes::Model model;
  std::vector images = model.GetClassImages("data/sampleimages");
  bayes::CalculatePosteriorProbability(images.at(0), 5);

  REQUIRE(1 + 1 == 2);
}
