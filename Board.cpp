#include "Board.h"

Board::Board(vector<vector<vector<int>>> the_board)
{
  this->the_board = the_board;
  size = the_board.size();
}

int Board::find(vector<int> &the_vector, int value)
{
  //cout << "Here20"  ;
  // cout << "Here2: " << the_vector.size() << endl;
  // cout << "Here3: " << value << endl;
  for (int i = 0; i < the_vector.size(); i++)
  {
    //cout << "Here18"  ;
    if (the_vector[i] == value) return i;
    //cout << "Here19"  ;
  }
  //cout << "Here21"  ;
  return -1;
}

void Board::missingInRow(vector<int> &curr_missing, int row_num)
{
  // Initializing the vector with all the possible numbers.
  // for (int i = 1; i <= size; i++) curr_missing.push_back(i);
  int found = -1;
  // Iterating through each row in the board.
  for (int i = 0; i < the_board[row_num].size(); i++)
  {
    if (the_board[row_num][i].size() == 1) found = find(curr_missing, the_board[row_num][i][0]);
    if (found != -1) curr_missing.erase(curr_missing.begin()+found);
    found = -1;
  }
}

void Board::missingInCol(vector<int> &curr_missing, int col_num)
{
  // Initializing the vector with all the possible numbers.
  // for (int i = 1; i <= size; i++) curr_missing.push_back(i);
  int found = -1;
  // Iterating through each row in the board.
  for (int i = 0; i < the_board.size(); i++)
  {
    if (the_board[i][col_num].size() == 1) found = find(curr_missing, the_board[i][col_num][0]);
    if (found != -1) curr_missing.erase(curr_missing.begin()+found);
    found = -1;
  }
}

void Board::missingInSquare(vector<int> &curr_missing, int row_num, int col_num)
{
  int size_sqrt = sqrt(size);
  row_num -= row_num % size_sqrt;
  col_num -= col_num % size_sqrt;
  int found = -1;

  for (int i = row_num; i < (row_num + size_sqrt); i++)
  {
    for (int j = col_num; j < (col_num + size_sqrt); j++)
    {
      if (the_board[i][j].size() == 1) found = find(curr_missing, the_board[i][j][0]);
      if (found != -1) curr_missing.erase(curr_missing.begin()+found);
      found = -1;
    }
  }
}

void Board::subtractTwoVectors(vector<int> &larger_vector, vector<int> &smaller_vector)
{
  int found = -1;
  for (int i = 0; i < smaller_vector.size(); i++)
  {
    //cout << "Here1" << endl;
    found = find(larger_vector, smaller_vector[i]);
    // cout << "Here16: " << found << endl;
    if (found != -1) larger_vector.erase(larger_vector.begin()+found);
    //cout << "Here17"  ;
  }
}

bool Board::checkForOnlyOption(int index_to_avoid1, int index_to_avoid2, int possible_good_num)
{
  vector<int> possible_good_nums;
  for (int k = 1; k <= size; k++) possible_good_nums.push_back(k);
  for (int i = 0; i < size; i++)
  {
    if (i != index_to_avoid2) subtractTwoVectors(possible_good_nums, the_board[index_to_avoid1][i]);
  }
  if (find(possible_good_nums, possible_good_num) != -1) return true;
  possible_good_nums.clear();
  for (int k = 1; k <= size; k++) possible_good_nums.push_back(k);
  for (int i = 0; i < size; i++)
  {
    if (i != index_to_avoid1) subtractTwoVectors(possible_good_nums, the_board[i][index_to_avoid2]);
  }
  if (find(possible_good_nums, possible_good_num) != -1) return true;
  possible_good_nums.clear();
  for (int k = 1; k <= size; k++) possible_good_nums.push_back(k);
  for (int i = index_to_avoid1-(index_to_avoid1%3); i < (index_to_avoid1-(index_to_avoid1%3))+sqrt(size); i++)
  {
    for (int j = index_to_avoid2-(index_to_avoid2%3); j < (index_to_avoid2-(index_to_avoid2%3))+sqrt(size); j++)
    {
      if (i != index_to_avoid1 || j != index_to_avoid2)
      {
        //cout << "Here14"  ;
        subtractTwoVectors(possible_good_nums, the_board[i][j]);
        //cout << "Here13"  ;
      }
    }
  }
  if (find(possible_good_nums, possible_good_num) != -1) return true;
  return false;
}

bool Board::initialize()
{
  bool changed = false;
  vector<int> curr_missing;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (the_board[i][j].size() != 1)
      {
        curr_missing.clear();
        for (int k = 1; k <= size; k++) curr_missing.push_back(k);
        missingInRow(curr_missing, i);
        missingInCol(curr_missing, j);
        missingInSquare(curr_missing, i, j);
        if (the_board[i][j] != curr_missing)
        {
          the_board[i][j] = curr_missing;
          changed = true;
        }
      }
    }
  }
  return changed;
}

void Board::solve()
{
  bool changed = true;

  while(changed)
  {
    // cout << "Here1" << endl;
    // changed = false;
    changed = initialize();
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        if (the_board[i][j].size() != 1)
        {
          // Check if the current location is the only one that can be any particular number.
          for (int k = 0; k < the_board[i][j].size(); k++)
          {
            if (checkForOnlyOption(i, j, the_board[i][j][k]))
            {
              the_board[i][j].clear();
              the_board[i][j].push_back(the_board[i][j][k]);
              // changed = true;
              // break;
            }
          }
        }
      }
    }
    // if (changed == false) cout << "HOORAY!" << endl;
  }
}

void Board::findNextUnfinishedSquare(int &curr_i, int &curr_j, int &length)
{
  for (int i = curr_i; i < size; i++)
  {
    for (int j = curr_j; j < size; j++)
    {
      if (the_board[i][j].size() > 1)
      {
        curr_i = i;
        curr_j = j;
        return;
      }
    }
  }
}

bool Board::guesser(int curr_i, int curr_j)
{
  int original_curr_i = curr_i;
  int original_curr_j = curr_j;
  solve();
  bool is_finished = true;
  print(is_finished);
  if (is_finished) return true;
  vector<int> temp_vec = the_board[curr_i][curr_j];
  int length = temp_vec.size();
  for (int i = 0; i < length; i++)
  {
    the_board[curr_i][curr_j].clear();
    the_board[curr_i][curr_j].push_back(temp_vec[i]);
    findNextUnfinishedSquare(curr_i, curr_j, length);
    is_finished = guesser(curr_i, curr_j);
    if (is_finished) return true;
  }
  the_board[original_curr_i][original_curr_j] = temp_vec;
  return false;
}

void Board::solveEverything()
{
  // Uncomment the next line to add guessing capabilities (and you can comment out the "solve()" line)
  guesser(0, 0);
  // solve();
}

string Board::print(bool &is_finished)
{
  is_finished = true;
  stringstream ss;
  // for (int i = 0; i < size; i++) ss << " _";
  for (int i = 0; i < size; i++)
  {
    // ss << "\n|";
    // ss  ;
    for (int j = 0; j < size; j++)
    {
      if (the_board[i][j].size() == 1) ss << the_board[i][j][0] << " ";// << "|";
      else
      {
        // ss << "\033[4m";
        ss << "_ ";
        //cout << "\033[0m";
        // ss << "|";
        is_finished = false;
      }
    }
    ss << endl;
    // for (int j = 0; j < size; j++) ss << " _";
  }
  return ss.str();
}

string Board::printTest(bool &is_finished)
{
  is_finished = true;
  stringstream ss;
  // for (int i = 0; i < size; i++) ss << " _";
  for (int i = 0; i < size; i++)
  {
    // ss << "\n|";
    // ss  ;
    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < the_board[i][j].size(); k++)
      {
        ss << the_board[i][j][k] << " ";
      }
      ss << endl;
      if (the_board[i][j].size() != 1) is_finished = false;
    }
    ss << endl;
    // for (int j = 0; j < size; j++) ss << " _";
  }
  return ss.str();
}