#include <vector>

using namespace std;

vector<vector<int>> matrix_multiply(vector<vector<int>>&, vector<vector<int>>&);
vector<vector<int>> matrix_multiply_no_buffer(vector<vector<int>>&,
                                              vector<vector<int>>&);
vector<vector<int>> matrix_transpose(vector<vector<int>>&);
vector<vector<int>> matrix_multiply_with_transpose(vector<vector<int>>&,
                                                   vector<vector<int>>&);
vector<vector<int>> matrix_multiply_parallel(vector<vector<int>>&,
                                             vector<vector<int>>&);
