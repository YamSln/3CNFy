#include <array>
#include <vector>

class Encoder3 {
 private:
  int clauses_generated_ = 0;
  int aux_vars_used_ = 0;
  int aux_vars_used_last_ = 0;
  int orignal_nof_clauses_ = 0;
  double avg_original_clause_size_ = 0;

 public:
  // Encodes a single clause into 3-literal clauses.
  std::vector<std::array<int, 3>> Encode(const std::vector<int>& clause,
                                         int next_var);

  // Encodes multiple clauses into 3-literal clauses.
  std::vector<std::array<int, 3>> Encode(
      const std::vector<std::vector<int>>& clauses, int next_var);

  int get_clauses_generated() const { return clauses_generated_; }
  int get_aux_vars_used() const { return aux_vars_used_; }
  int get_aux_vars_used_last() const { return aux_vars_used_last_; }
  int get_original_nof_clauses() const { return orignal_nof_clauses_; }
  double get_avg_original_clause_size() const {
    return avg_original_clause_size_;
  }
};