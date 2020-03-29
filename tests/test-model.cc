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