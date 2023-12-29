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
void matrix_multiply_tiles(const vector<vector<int>>&,
                           const vector<vector<int>>&, vector<vector<int>>&,
                           int, int, int, int, int);
vector<vector<int>> matrix_multiply_with_tiles(vector<vector<int>>&,
                                               vector<vector<int>>&);