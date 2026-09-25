#include <iostream>
#include <array>
using namespace std;

int main()
{
  using std::string;

  array<int, 3> color1 = {0, 0, 0};
  array<int, 3> color2 = {0, 0, 0};
  array<string, 3> channels = {"R", "G", "B"};

  cout << "Enter your R,G,B values for Color 1: " << endl;
  for (int index = 0; index < 3; index++)
  {
      cout << channels[index] << ": ";
      cin >> color1[index];
  };

  cout << "Color 1 RGB: "
        << color1[0] << ", "
        << color1[1] << ", "
        << color1[2] << endl;

  cout << "Enter your R,G,B values for Color 2: " << endl;
  for (int index = 0; index < 3; index++)
  {
      cout << channels[index] << ": ";
      cin >> color2[index];
  };

  cout << "Color 2 RGB: "
        << color2[0] << ", "
        << color2[1] << ", "
        << color2[2] << endl;


  /* OLD CODE
  array<int, 3> color1 = {0, 0, 0};
  array<int, 3> color2 = {0, 0, 0};

  cout << "Enter R: ";
  cin >> color1[0];

  cout << "Enter G: ";
  cin >> color1[1];

  cout << "Enter B: ";
  cin >> color1[2];

  cout << "Color 1 RGB: "
        << color1[0] << ", "
        << color1[1] << ", "
        << color1[2] << endl;

  cout << "Enter R: ";
  cin >> color2[0];

  cout << "Enter G: ";
  cin >> color2[1];

  cout << "Enter B: ";
  cin >> color2[2];

  cout << "Color 2 RGB: "
        << color2[0] << ", "
        << color2[1] << ", "
        << color2[2] << endl;
  */

  return 0;
}