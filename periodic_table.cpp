/* 
 * File:   periodic_table.cpp
 * Author: scadars
 * 
 * Created on September 17, 2013, 11:09 PM
 */

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <ios>
#include <boost/foreach.hpp>
#include <vector>
#include <cassert>
#include <boost/lexical_cast.hpp>

#include "periodic_table.h"

using namespace std;

periodic_table::periodic_table() {

  using boost::property_tree::ptree;
  ptree pt_1;
  string fileName = "data/PeriodicTable.xml" ;
  
  cout << "Reading Isotope file: " << fileName << endl;
  boost::property_tree::read_xml(fileName, pt_1, 
          boost::property_tree::xml_parser::trim_whitespace );

  BOOST_FOREACH(const ptree::value_type &v1, pt_1.get_child("atomicNumbers"))
  {
    element element_1(v1) ;
    elements.push_back(element_1);
    
  }
}

periodic_table::periodic_table(const periodic_table& orig) {
}
periodic_table::~periodic_table() {
}

element periodic_table::get_element(int atom_number)
{
  for (int i=0 ; i<elements.size() ; i++ )
  {
    if (elements[i].get_atomNumber() == atom_number)
      return elements[i] ;
  }
  assert(false) ;
}

element periodic_table::get_element(string atom_symbol)
{
  for (int i=0 ; i<elements.size() ; i++ )
  {
    if (elements[i].get_symbol() == atom_symbol)
      return elements[i] ;
  }
  assert(false) ;
}

element::element(const boost::property_tree::ptree::value_type& ptbranch)
{
  using boost::property_tree::ptree;  
  
  atomicNumber = ptbranch.second.get_value<int>();
    
    name = ptbranch.second.get<string>("eltName");
    symbol = ptbranch.second.get<string>("eltSymbol");
    cout << "========================" << endl ;
    cout << "Atomic Number = " << atomicNumber << ", eltName = " 
            << name << ", eltSymbol = " << symbol << endl;
    cout << "========================" << endl ;    

    BOOST_FOREACH(const ptree::value_type &v2, ptbranch.second.get_child("isotopes"))
    {      
      isotope isotope_1(v2,symbol) ;
      isotopes.push_back(isotope_1) ;      
    }
}

vector <string> element::get_isotopeList()
{
  vector <string> result ;
  for (int i=0 ; i<isotopes.size() ; i++ )
    result.push_back(isotopes[i].get_name()) ;
  return result ;
}


isotope element::get_isotope(int isotope_number)
{
  for (int i=0 ; i<isotopes.size() ; i++ )
  {
    if (isotopes[i].get_isotopeNb() == isotope_number)
      return isotopes[i] ;
  }
  assert(false) ;
}

isotope element::get_isotope(string isotope_name)
{
  for (int i=0 ; i<isotopes.size() ; i++ )
  {
    if (isotopes[i].get_name() == isotope_name)
      return isotopes[i] ;
  }
  assert(false) ;
}

element::~element() {
}

isotope::isotope(const boost::property_tree::ptree::value_type& ptbranch,
        string eltSymbol_v)
{
      using boost::property_tree::ptree;
      
      eltSymbol = eltSymbol_v ;
      number = ptbranch.second.get_value<int>() ;
      nucSpin = ptbranch.second.get<double>("nucSpin");
      magGyrRatio = ptbranch.second.get<double>("magGyrRatio");
      string magGyrRatioUnit = ptbranch.second.get<string>("magGyrRatio.<xmlattr>.Unit");
      natAbundance = ptbranch.second.get<double>("natAbundance");

      cout << "* isotope # " << number << ": " << number << eltSymbol << endl ;
      cout << "  nucSpin = " << nucSpin << endl ;
      cout << "  magGyrRatio = " << magGyrRatio << " " << magGyrRatioUnit << endl;
      cout << "  natAbundance = " << natAbundance << " %" << endl;
      
      if (nucSpin > 0.5)
      {
        Q_barn = ptbranch.second.get<double>("Q");
        string Q_Unit = ptbranch.second.get<string>("Q.<xmlattr>.Unit");
        cout << "  Q_barn = " << Q_barn << " " << Q_Unit << endl;
      }
}

std::string isotope::get_name()
{
  return boost::lexical_cast<string>(number)+eltSymbol; 
}

isotope::~isotope() {
}

