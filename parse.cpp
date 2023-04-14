////////////////////////////////////////////////////////////////////////////////
// Filename: parse.cpp
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the parse function.
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "agenda.h"
#include "chart.h"
#include "edge.h"
#include "parse.h"
#include "rules.h"

////////////////////////////////////////////////////////////////////////////////
// Function: parse
// Return true if the CategorySequence can be parsed up to the
// Category using the RuleList, false otherwise.
////////////////////////////////////////////////////////////////////////////////
EdgeList
parse(const RuleList &rules, const Category &goal,
    const CategorySequence &sentence ) {
  Agenda agenda;
  Chart chart(sentence);
  CategorySequence::size_type vertex=0; 
  CategorySequence remaining=sentence;

  // Initialise
  for (CategorySequence::const_iterator i=remaining.begin();
      i!=remaining.end(); ++i) {
    Edge newE(vertex, vertex+1, *i, log(1));
    if (!chart.isIn(newE)) {
      agenda.add(newE);
    }
    vertex+=1;
  }

  // Handle agenda
  while (!agenda.empty()) {
    // Grab an edge off the agenda
    Edge edge=agenda.getNext();

    // Add edge to chart.  Try to combine edge with others in chart,
    // then add any application of fundamental rule to agenda.
    // If edge is inactive, try to apply grammar rules to result in
    // an application of fundamental rule--and add any application to
    // agenda.
    chart.add(edge, agenda, rules);
  }
  return chart.success(goal, sentence);
} // end of function: parse

// end of file: parse.cpp
