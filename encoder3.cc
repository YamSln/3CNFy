#include "encoder3.h"

#include <iostream>

using namespace std;

vector<array<int, 3>> Encoder3::Encode(const vector<int>& clause,
                                       int next_var) {
  orignal_nof_clauses_++;
  aux_vars_used_last_ = 0;
  std::vector<std::array<int, 3>> result;
  size_t n = clause.size();
  if (n == 0) {
    throw std::invalid_argument("Clause cannot be empty");
  }
  if (clause[n - 1] == 0) n--;

  switch (n) {
    case 0:
      throw std::invalid_argument("Clause cannot be empty");

    case 1:
      aux_vars_used_last_ = 2;
      clauses_generated_ += 4;
      result = {{clause[0], next_var, next_var + 1},
                {clause[0], -next_var, next_var + 1},
                {clause[0], next_var, -(next_var + 1)},
                {clause[0], -next_var, -(next_var + 1)}};
      break;

    case 2:
      aux_vars_used_last_ = 1;
      clauses_generated_ += 2;
      result = {{clause[0], clause[1], next_var},
                {clause[0], clause[1], -next_var}};
      break;

    case 3:
      clauses_generated_ += 1;
      result = {{clause[0], clause[1], clause[2]}};
      break;

    default:
      result.push_back({clause[0], clause[1], next_var});
      aux_vars_used_last_ = 1;
      clauses_generated_++;
      for (size_t i = 2; i < n - 2; i++) {
        result.push_back({-next_var, clause[i], next_var + 1});
        next_var++;
        aux_vars_used_last_++;
        clauses_generated_++;
      }
      result.push_back({-next_var, clause[n - 2], clause[n - 1]});
      clauses_generated_++;
  }
  aux_vars_used_ += aux_vars_used_last_;
  avg_original_clause_size_ =
      (avg_original_clause_size_ * (orignal_nof_clauses_ - 1) + n) /
      orignal_nof_clauses_;

  return result;
}

vector<array<int, 3>> Encoder3::Encode(const vector<vector<int>>& clauses,
                                       int next_var) {
  vector<array<int, 3>> result;
  for (const auto& clause : clauses) {
    auto encoded = Encode(clause, next_var);
    for (const auto& c : encoded) {
      result.emplace_back(move(c));
    }
    next_var += aux_vars_used_last_;
  }
  return result;
}