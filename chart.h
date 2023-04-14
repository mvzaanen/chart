////////////////////////////////////////////////////////////////////////////////
// Filename: chart.h
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the Chart class.
////////////////////////////////////////////////////////////////////////////////

#ifndef CHART_H
#define CHART_H

  #include <vector>
#include "agenda.h"
#include "edge.h"
#include "rules.h"

////////////////////////////////////////////////////////////////////////////////
// Class: Chart
// Provides the interface for a Chart.
////////////////////////////////////////////////////////////////////////////////
class Chart {
public:
////////////////////////////////////////////////////////////////////////////////
// Function: Chart
// Constructor.
////////////////////////////////////////////////////////////////////////////////
  Chart(const CategorySequence &cs):_activeEdges(cs.size()+1),
      _inactiveEdges(cs.size()+1) { }

////////////////////////////////////////////////////////////////////////////////
// Function: add
// If combination is possible, then add the newly combined Edge to the
// Chart.
////////////////////////////////////////////////////////////////////////////////
  void
  add(const Edge &, Agenda &, const RuleList &);

////////////////////////////////////////////////////////////////////////////////
// Function: isIn
// Returns true if the Edge is in the Chart, false otherwise.
////////////////////////////////////////////////////////////////////////////////
  bool
  isIn(const Edge &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: success
// Returns true if the Category parses the CategorySequence, false
// otherwise.
////////////////////////////////////////////////////////////////////////////////
  EdgeList
  success(const Category &, const CategorySequence &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: print
// Prints the chart on the ostream.
////////////////////////////////////////////////////////////////////////////////
  void
  print(ostream&) const;

protected:
////////////////////////////////////////////////////////////////////////////////
// Function: Chart
// Copy Constructor.
////////////////////////////////////////////////////////////////////////////////
   Chart(const Chart &) { }

////////////////////////////////////////////////////////////////////////////////
// Function: operator=
// Assignment operator.
////////////////////////////////////////////////////////////////////////////////
  void operator=(const Chart &) { }

private:
////////////////////////////////////////////////////////////////////////////////
// Variable: _activeEdges
// The collection of active edges (in the EdgeList).
////////////////////////////////////////////////////////////////////////////////
   vector<EdgeList> _activeEdges;

////////////////////////////////////////////////////////////////////////////////
// Variable: _inactiveEdges
// The collection of inactive edges (in the EdgeList).
////////////////////////////////////////////////////////////////////////////////
   vector<EdgeList> _inactiveEdges;

}; // end of class: Chart


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the EdgeList on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &, const Chart &);


#endif
// end of file: chart.h