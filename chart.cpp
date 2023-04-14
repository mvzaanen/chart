////////////////////////////////////////////////////////////////////////////////
// Filename: chart.cpp
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the implementation of the Chart class.
////////////////////////////////////////////////////////////////////////////////

#include "agenda.h"
#include "category.h"
#include "chart.h"
#include "edge.h"
#include "rules.h"

////////////////////////////////////////////////////////////////////////////////
// Function: add
// If combination is possible, then add the newly combined Edge to the
// Chart.
////////////////////////////////////////////////////////////////////////////////
void
Chart::add(const Edge &edge, Agenda &agenda, const RuleList &rules) {
  if(edge.isActive()){
    // If edge is active, try to combine it with inactive edges
    _activeEdges[edge.finish()].push_back(edge);
    EdgeList temp=_inactiveEdges[edge.finish()];
    while (!temp.empty()) {
      Edge e=temp.front();
      temp.pop_front();
      if (e.canCombineWith(edge)) {
        Edge combination=combine(e, edge);
        if (!isIn(combination)) {
          agenda.add(combination);
        }
      }
    }
  }
  else {
    // If edge is inactive, try to combine it with active edges
    _inactiveEdges[edge.start()].push_back(edge);
    EdgeList temp=_activeEdges[edge.start()];
    while (!temp.empty()) {
      Edge e=temp.front();
      temp.pop_front();
      if (e.canCombineWith(edge)) {
        Edge combination=combine(e, edge);
        if (!isIn(combination)) {
          agenda.add(combination);
        }
      }
    }
    // Also, for inactive edge, see if any rules apply to create new
    // edges.  If so, add these to agenda for processing.
    for (RuleList::const_iterator i=rules.begin(); i!=rules.end(); ++i) {
      if (i->appliesTo(edge)) {
        Edge applied=i->apply(edge);
        if (!isIn(applied)) {
          agenda.add(applied);
        }
      }
    }
  }
} // end of function: add


////////////////////////////////////////////////////////////////////////////////
// Function: isIn
// Returns true if the Edge is in the Chart, false otherwise.
////////////////////////////////////////////////////////////////////////////////
bool
Chart::isIn(const Edge &edge) const {
  if (edge.isActive()) {
    return _activeEdges[edge.finish()].isMember(edge);
  }
  else {
    return _inactiveEdges[edge.start()].isMember(edge);
  }
}


////////////////////////////////////////////////////////////////////////////////
// Function: success
// Returns true if the Category parses the CategorySequence, false
// otherwise.
////////////////////////////////////////////////////////////////////////////////
EdgeList
Chart::success(const Category &goal, const CategorySequence &str) const {
  EdgeList temp=_inactiveEdges[0];
  EdgeList result;
  while (!temp.empty()) {
    Edge edge=temp.front();
    temp.pop_front();
    Category cat=edge.label();
    if (edge.start()==0 &&
        edge.finish()==str.size() && 
        cat==goal) {
      result.push_back(edge);
    }
  }
  return result;
} // end of function: success


////////////////////////////////////////////////////////////////////////////////
// Function: print
// Prints the chart on the ostream.
////////////////////////////////////////////////////////////////////////////////
void
Chart::print(ostream &os) const {
  // Print out the active chart
  os << "ACTIVE CHART:\n";
  for (vector<EdgeList>::const_iterator i=_activeEdges.begin();
      i!=_activeEdges.end(); ++i) {
    os << *i;
  }
  os << endl;

  // Print out the inactive chart
  os << "INACTIVE CHART:\n";
  for (vector<EdgeList>::const_iterator i=_inactiveEdges.begin();
      i!=_inactiveEdges.end(); ++i) {
    os << *i;
  }
} // end of function: print

////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the EdgeList on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &os, const Chart &chart) {
  chart.print(os);
  return os;
} // end of function: operator<<


// end of file: chart.cpp
