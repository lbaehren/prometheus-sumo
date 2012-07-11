
#ifndef COMMON_H
#define COMMON_H

/*!
  \file Common.h
  \ingroup prmetheus
  \author Lars B&auml;hren

  \brief Collection of commly used routines and functionality
*/

#include <iostream>
#include <set>
#include <vector>

//_______________________________________________________________________________
//                                                                           show

/*!
  \brief Write elements of an array/vector/set to an output stream
  
  \param os    -- Stream to which the output is written.
  \param start -- Iterator pointing to the first element.
  \param end   -- Iterator pointing to the position after the last element.
*/
template <typename T>
std::ostream& show (std::ostream& os,
                    T start,
                    T end)
{
  T it;
  
  os << "[";
  
  for (it=start; it!=end; ++it) {
    os << " " << *it;
  }
  
  os << " ]";
  
  return os;
}

//_______________________________________________________________________________
//                                                                     operator<<

/*!
  \brief Overloading of output operator to display std::vector<T>
  
  \param os  -- Output stream to which the result will be written to
  \param vec -- The vector to be displayed
*/
template <typename T>
std::ostream& operator<< (std::ostream &os,
                          const std::vector<T> &vec)
{
  return show (os, vec.begin(), vec.end());
}

//_______________________________________________________________________________
//                                                                     operator<<

/*!
  \brief Overloading of output operator to display std::set<T>
  
  \param os  -- Output stream to which the result will be written to
  \param vec -- The set to be displayed
*/
template <typename T>
std::ostream& operator<< (std::ostream &os,
                          const std::set<T> &s)
{
  return show (os, s.begin(), s.end());
}

#endif
