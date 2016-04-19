#pragma once
#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
// #include <cppformat>

using namespace std;

class Board
{
private:
  vector<vector<vector<int>>> the_board;
  int size;

public:
  Board(vector<vector<vector<int>>> the_board);
  ~Board(){}
  int find(vector<int> &the_vector, int value);
  void missingInRow(vector<int> &curr_missing, int row_num);
  void missingInCol(vector<int> &curr_missing, int col_num);
  void missingInSquare(vector<int> &curr_missing, int row_num, int col_num);
  void subtractTwoVectors(vector<int> &larger_vector, vector<int> &smaller_vector);
  bool checkForOnlyOption(int index_to_avoid1, int index_to_avoid2, int possible_good_num);
  bool initialize();
  void solve();
  string print(bool &is_finished);
};