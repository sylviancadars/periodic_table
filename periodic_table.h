/* 
 * File:   periodic_table.h
 * Author: scadars
 *
 * Created on September 17, 2013, 11:09 PM
 */

#ifndef PERIODIC_TABLE_H
#define	PERIODIC_TABLE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>

class isotope 
{
public:
    isotope(const boost::property_tree::ptree::value_type& ptbranch, std::string eltSymbol_v);
    std::string get_name() ;
    
    int get_isotopeNb()
    { return number ; } ;
    double get_nucSpin()
    { return nucSpin ;} ;
    double get_magGyrRatio()
    { return magGyrRatio ; } ;
    double get_natAbundance()
    { return natAbundance ; } ;
    double get_Q()
    { return Q_barn ; } ;
    
    virtual ~isotope();
    
private:

protected:
    int number ;
    std::string eltSymbol ;
    double nucSpin;
    double magGyrRatio;
    double natAbundance;
    double Q_barn;

};

class element
{
public:
    element(const boost::property_tree::ptree::value_type& ptbranch);
    
    int get_atomNumber()
      {return atomicNumber ;  };    
    std::string get_symbol()
      {return symbol ;  };
    std::string get_name()
      {return name ;  };

    isotope get_isotope(int isotope_number) ;
    isotope get_isotope(std::string isotope_name) ;
    
    std::vector <std::string> get_isotopeList(); 
    
    virtual ~element();
private:
    
protected:    
    int atomicNumber;
    std::string name;
    std::string symbol;
    std::vector <isotope> isotopes;
};

class periodic_table {
public:
    periodic_table();
    
    periodic_table(const periodic_table& orig);
    virtual ~periodic_table();
    
    element get_element(int atom_number) ;
    element get_element(std::string atom_symbol) ;
private:
    
protected:
    std::vector <element> elements;
};

#endif	/* PERIODIC_TABLE_H */
