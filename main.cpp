/* 
 * File:   main.cpp
 * Author: scadars
 *
 * Created on September 19, 2013, 10:18 AM
 */

#include <cstdlib>
#include "periodic_table.h"
#include <vector>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
  periodic_table pTab_1 ;
  
  cout << "Testing periodic_tab functions:" << endl ;
  
  vector <string> isotopList = pTab_1.get_element("Ga").get_isotopeList();
  for (int i=0 ; i<isotopList.size() ; i++ )
    cout << isotopList[i] << endl ;
  return 0;
}

