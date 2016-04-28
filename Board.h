#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
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
  int find(vector<int> the_vector, int value);
  void missingInRow(vector<int> &curr_missing, int row_num);
  void missingInCol(vector<int> &curr_missing, int col_num);
  void missingInSquare(vector<int> &curr_missing, int row_num, int col_num);
  void subtractTwoVectors(vector<int> &larger_vector, vector<int> smaller_vector);
  bool checkForOnlyOption(int index_to_avoid1, int index_to_avoid2, int possible_good_num);
  bool initialize();
  void solve();
  void findNextUnfinishedSquare(int &curr_i, int &curr_j, int &length);
  bool guesser(int curr_i, int curr_j);
  void solveEverything();
  string print(bool &is_finished);
  string printTest(bool &is_finished);
};