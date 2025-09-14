#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "encoder3.h"

using namespace std;

const string DEFAULT_OUTPUT_FILENAME = "cnf3.cnf";

int main(int argc, char* argv[]) {
  cout << "==============================================" << endl;
  cout << "         3-CNFy: CNF to 3-CNF Encoder         " << endl;
  cout << "==============================================" << endl;

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input_cnf_file> [output_cnf3_file]"
         << endl;
    return 1;
  }
  string cnf_path = argv[1];
  string output_path;
  if (argc >= 3) {
    output_path = argv[2];
  } else {
    cout << "No output file specified. Using default "
         << DEFAULT_OUTPUT_FILENAME << "." << endl;
    output_path = DEFAULT_OUTPUT_FILENAME;
  }

  if (filesystem::exists(output_path)) {
    cout << "Warning: Output file '" << output_path
         << "' already exists. Are you sure you want to overwrite it? [Y/N] ";
    char response;
    cin >> response;
    if (response != 'Y' && response != 'y') {
      cout << "Aborting." << endl;
      return 0;
    }
    cout << "Overwriting file '" << output_path << "'." << endl;
  }
  ifstream cnf_file(cnf_path);

  if (!cnf_file) {
    cerr << "Error opening file: " << cnf_path << endl;
    return 1;
  }

  int max_var = 0;
  int line_num = 0;
  size_t line_index = 0;

  auto ParseNumber = [&](const string& line) {
    while (line[line_index] == ' ') line_index++;
    if (line_index >= line.size())
      throw invalid_argument(
          "No number found after whitespaces at line number " +
          to_string(line_num));
    bool neg = line[line_index] == '-';
    if (neg) line_index++;
    int num = 0;
    while ('0' <= line[line_index] && line[line_index] <= '9') {
      num = num * 10 + (long long)(line[line_index] - '0');
      line_index++;
    }
    if (num > max_var) max_var = num;
    if (neg) num = -num;
    return num;
  };

  auto ParseClause = [&](const string& line) {
    vector<int> clause;
    long long lit = 1;
    line_num++;
    line_index = 0;

    while (lit != 0) {
      lit = ParseNumber(line);
      if (lit < numeric_limits<int>::min() || lit > numeric_limits<int>::max())
        throw invalid_argument("Literal out of range at line number " +
                               to_string(line_num));
      clause.push_back(lit);
    }

    return clause;
  };

  vector<vector<int>> clauses;
  string line;
  while (getline(cnf_file, line)) {
    vector<int> clause = ParseClause(line);
    clauses.emplace_back(move(clause));
  }
  cnf_file.close();

  Encoder3 encoder;
  vector<array<int, 3>> cnf3 = encoder.Encode(clauses, max_var + 1);

  ofstream output_file(output_path);
  if (!output_file) {
    cerr << "Error creating file: " << output_path << endl;
    return 1;
  }

  for (size_t i = 0; i < cnf3.size(); i++) {
    for (int lit : cnf3[i]) {
      output_file << lit << " ";
    }
    output_file << "0";
    if (i != cnf3.size() - 1) output_file << "\n";
  }
  output_file.close();

  cout << "------------------------------" << endl;
  cout << std::left << std::setw(35) << "Result" << std::right << std::setw(15)
       << "Value" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << std::left << std::setw(35) << "Output written to:" << std::right
       << std::setw(15) << output_path << endl;
  cout << std::left << std::setw(35)
       << "Original number of clauses:" << std::right << std::setw(15)
       << encoder.GetOriginalNofClauses() << endl;
  cout << std::left << std::setw(35)
       << "Average original clause size:" << std::right << std::setw(15)
       << encoder.GetAvgOriginalClauseSize() << endl;
  cout << std::left << std::setw(35)
       << "Number of clauses generated:" << std::right << std::setw(15)
       << encoder.GetClausesGenerated() << endl;
  cout << std::left << std::setw(35)
       << "Auxiliary variables introduced:" << std::right << std::setw(15)
       << encoder.GetAuxVarsUsed() << endl;
  cout << std::left << std::setw(35)
       << "Maximal auxiliary variable used:" << std::right << std::setw(15)
       << max_var + encoder.GetAuxVarsUsed() << endl;
  cout << "-----------------------------------------------" << endl;

  return 0;
}