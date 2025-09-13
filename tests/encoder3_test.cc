#include "../encoder3.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(Encoder3Test, EmptyClause) {
  Encoder3 encoder;
  std::vector<int> clause = {};
  int next_var = 1;
  EXPECT_THROW(encoder.Encode(clause, next_var), std::invalid_argument);
}

TEST(Encoder3Test, SingleLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1};
  int next_var = 2;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 3}, {1, -2, 3}, {1, 2, -3}, {1, -2, -3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 4);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 2);
}

TEST(Encoder3Test, TwoLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2};
  int next_var = 3;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{1, 2, 3}, {1, 2, -3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 2);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 1);
}

TEST(Encoder3Test, ThreeLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3};
  int next_var = 4;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{1, 2, 3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 1);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 0);
}

TEST(Encoder3Test, FourLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 4};
  int next_var = 5;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{1, 2, 5}, {-5, 3, 4}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 2);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 1);
}

TEST(Encoder3Test, FiveLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 4, 5};
  int next_var = 6;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 6}, {-6, 3, 7}, {-7, 4, 5}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 3);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 2);
}

TEST(Encoder3Test, SixLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 4, 5, 6};
  int next_var = 7;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 7}, {-7, 3, 8}, {-8, 4, 9}, {-9, 5, 6}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 4);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 3);
}

TEST(Encoder3Test, SevenLiteralClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 4, 5, 6, 7};
  int next_var = 8;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 8}, {-8, 3, 9}, {-9, 4, 10}, {-10, 5, 11}, {-11, 6, 7}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 5);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 4);
}

TEST(Encoder3Test, LargeClause) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int next_var = 11;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 11},   {-11, 3, 12}, {-12, 4, 13}, {-13, 5, 14},
      {-14, 6, 15}, {-15, 7, 16}, {-16, 8, 17}, {-17, 9, 10}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 8);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 7);
}

TEST(Encoder3Test, AverageClauseSize) {
  Encoder3 encoder;
  std::vector<int> clause1 = {1, 2, 3};
  std::vector<int> clause2 = {1, 2, 3, 4};
  std::vector<int> clause3 = {1, 2, 3, 4, 5};
  int next_var = 6;
  encoder.Encode(clause1, next_var);
  encoder.Encode(clause2, next_var + 3);
  encoder.Encode(clause3, next_var + 5);
  EXPECT_DOUBLE_EQ(encoder.GetAvgOriginalClauseSize(), 4.0);
}

TEST(Encoder3Test, OriginalNumberOfClauses) {
  Encoder3 encoder;
  std::vector<int> clause1 = {1, 2, 3};
  std::vector<int> clause2 = {1, 2, 3, 4};
  std::vector<int> clause3 = {1, 2, 3, 4, 5};
  int next_var = 6;
  encoder.Encode(clause1, next_var);
  encoder.Encode(clause2, next_var + 3);
  encoder.Encode(clause3, next_var + 5);
  EXPECT_EQ(encoder.GetOriginalNofClauses(), 3);
}

TEST(Encoder3Test, EncodeMultipleClauses) {
  Encoder3 encoder;
  std::vector<std::vector<int>> clauses = {
      {1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3, 4, 5}};
  int next_var = 6;
  auto result = encoder.Encode(clauses, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 3}, {1, 2, 6}, {-6, 3, 4}, {1, 2, 7}, {-7, 3, 8}, {-8, 4, 5}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 6);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 3);
  EXPECT_EQ(encoder.GetOriginalNofClauses(), 3);
  EXPECT_DOUBLE_EQ(encoder.GetAvgOriginalClauseSize(), 4.0);
}

TEST(Encoder3Test, EncodeMultipleClausesWithTrailingZeros) {
  Encoder3 encoder;
  std::vector<std::vector<int>> clauses = {
      {1, 2, 3, 0}, {1, 2, 3, 4, 0}, {1, 2, 3, 4, 5, 0}};
  int next_var = 6;
  auto result = encoder.Encode(clauses, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, 2, 3}, {1, 2, 6}, {-6, 3, 4}, {1, 2, 7}, {-7, 3, 8}, {-8, 4, 5}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 6);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 3);
  EXPECT_EQ(encoder.GetOriginalNofClauses(), 3);
  EXPECT_DOUBLE_EQ(encoder.GetAvgOriginalClauseSize(), 4.0);
}

TEST(Encoder3Test, ClauseWithTrailingZero) {
  Encoder3 encoder;
  std::vector<int> clause = {1, 2, 3, 0};
  int next_var = 4;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{1, 2, 3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 1);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 0);
}

TEST(Encoder3Test, ClauseWithNegativeLiterals) {
  Encoder3 encoder;
  std::vector<int> clause = {1, -2, 3};
  int next_var = 4;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{1, -2, 3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 1);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 0);
}

TEST(Encoder3Test, ClauseWithAllNegativeLiterals) {
  Encoder3 encoder;
  std::vector<int> clause = {-1, -2, -3};
  int next_var = 4;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {{-1, -2, -3}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 1);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 0);
}

TEST(Encoder3Test, ClauseWithMixedLiterals) {
  Encoder3 encoder;
  std::vector<int> clause = {1, -2, 3, -4, 5};
  int next_var = 6;
  auto result = encoder.Encode(clause, next_var);
  std::vector<std::array<int, 3>> expected = {
      {1, -2, 6}, {-6, 3, 7}, {-7, -4, 5}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(encoder.GetClausesGenerated(), 3);
  EXPECT_EQ(encoder.GetAuxVarsUsed(), 2);
}