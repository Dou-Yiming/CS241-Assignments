#include "std_lib_facilities.h"
#include "Huffman_Exercise_1.h"
#include "Huffman_Exercise_2.h"
int main()
{
  /********** Begin **********/
  bool exercise_1 = 0;
  if (exercise_1)
  {
    //第一关执行代码
    //Please fix Huffman_Exercise_1.h and Huffman_Exercise_1.cpp
    string str;
    string tmp;
    Huffman1 huf;
    while (getline(cin, tmp))
    {
      str += tmp;
      huf.num_letter[199]++;
    }
    huf.num_letter[199]--;
    huf.get_letter(str);
    huf.encode();
    huf.print();
  }
  else
  {
    //Please fix Huffman_Exercise_2.h and Huffman_Exercise_2.cpp
    string str;
    string tmp;
    Huffman2 huf;
    while (getline(cin, tmp))
    {
      str += tmp;
      huf.num_not_letter++;
    }
    huf.num_not_letter--;
    huf.get_words(str);
    huf._sort();
    huf.encode();
    huf.print();
  }
  /********** End **********/
  return 0;
}
