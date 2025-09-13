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

  int GetClausesGenerated() const { return clauses_generated_; }
  int GetAuxVarsUsed() const { return aux_vars_used_; }
  int GetAuxVarsUsedLast() const { return aux_vars_used_last_; }
  int GetOriginalNofClauses() const { return orignal_nof_clauses_; }
  double GetAvgOriginalClauseSize() const { return avg_original_clause_size_; }
};