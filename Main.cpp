#include <fstream>
#include <locale>
#include <sys/resource.h>
#include "Board.h"

using namespace std;

bool isdigits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int check(string file_name)
{
  fstream file(file_name);
  string item_str;
  int item_int = -1;
  // For checking that numbers aren't too high.
  int greatest_num = -1;
  // For checking that the input is a perfect square of a perfect square.
  int counter = 0;
  // For checking that everything is a digit (or a ";").
  bool is_good = true;
  while(file >> item_str)
  {
    if (isdigits(item_str))
    {
      item_int = stoi(item_str);
      // For checking that numbers aren't too low.
      if (item_int < 1)
      {
        is_good = false;
        break;
      }
      if (item_int > greatest_num) greatest_num = item_int;
      counter++;
    }
    else if (item_str == ";")
    {
      counter++;
    }
    else if (item_str[0] == '#')
    {
      getline(file, item_str);
      file.ignore();
    }
    else
    {
      is_good = false;
      break;
    }
  }
  // For checking that the input is a perfect square of a perfect square.
  double size_doub = sqrt(sqrt(counter));
  int size_int = size_doub;
  if (!is_good || size_doub != size_int || greatest_num > sqrt(counter))// || counter < ((counter*2)-1))
  {
    file.close();
    return -1;
  }
  file.close();
  return sqrt(counter);
}

int main(int argc, char* argv[])
{
  vector<vector<vector<int>>> board_vec;
  ofstream output(argv[2]);
  int size = check(argv[1]);
  if (size == -1)
  {
    output << "Sorry, that file's invalid." << endl;
    return 0;
  }
  ifstream input(argv[1]);
  string item_str;
  int item_int = -1;
  for (int i = 0; i < size; i++)
  {
    vector<vector<int>> one_row;
    for (int j = 0; j < size; j++)
    {
      vector<int> one_spot;
      input >> item_str;
      // if (item_str == ";") one_row.push_back(-1);
      // else one_row.push_back(stoi(item_str));
      while (item_str[0] == '#')
      {
        getline(input, item_str);
        input.ignore();
        input >> item_str;
      }
      if (item_str != ";") one_spot.push_back(stoi(item_str));
      one_row.push_back(one_spot);
    }
    board_vec.push_back(one_row);
  }

  Board board(board_vec);
  bool is_finished = true;
  output << board.print(is_finished);
  // for (int i = 0; i < board.size; i++) output << " _";
  // for (int i = 0; i < board.size; i++)
  // {
  //   output << "\n|";
  //   for (int j = 0; j < board.size; j++)
  //   {
  //     if (board.the_board[i][j] != -1) output << board.the_board[i][j] << "|";
  //     else
  //     {
  //       output << "\033[4m";
  //       output << " ";
  //       output << "\033[0m";
  //       output << "|";
  //     }
  //   }
  //   // output << endl;
  //   // for (int j = 0; j < board.size; j++) output << " _";
  // }
  output << "\nSolving....\n\n";
  board.solveEverything();
  output << board.print(is_finished);
  if (is_finished) output << "\nI\'m Finished!";
  else output << "\nHmmm...I couldn\'t quite figure that one out.";

  output.close();
  input.close();
  return 0;
}
