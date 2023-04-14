////////////////////////////////////////////////////////////////////////////////
// Filename: rules.h
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the Rule and RuleList classes.
////////////////////////////////////////////////////////////////////////////////

#include <boost/regex.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "rules.h"

using namespace std;
using namespace boost;

//                            rule_id   log_prob          lhs      rhs
const regex grammarRule("^\\s*(\\d+)\\s+([\\d\\.eE-]+)\\s+(_[^\\s]*)\\s+(.*)\\s*$");

////////////////////////////////////////////////////////////////////////////////
// Function: appliesTo
// Returns true if the Edge applies to the Rule.
////////////////////////////////////////////////////////////////////////////////
bool
Rule::appliesTo(const Edge &edge) const {
  return edge.label()==_rhs.front();
} // end of function: appliesTo


////////////////////////////////////////////////////////////////////////////////
// Function: read
// Read a rule from the istream.
////////////////////////////////////////////////////////////////////////////////
void
Rule::read(istream &is) {
  string line;
  getline(is, line);
  smatch matchInfo;
  if (!regex_search(line, matchInfo, grammarRule)) {
    cerr << "Error reading grammar rule:" << endl;
    cerr << line;
    exit(1);
  }
  _lhs=matchInfo.str(3);
  // rhs
  istringstream rhsStream(matchInfo.str(4));
  while (rhsStream.good()) {
    string cat;
    rhsStream >> cat;
    _rhs+=Category(cat);
  }
  // ruleId
  istringstream ruleIdStream(matchInfo.str(1));
  ruleIdStream >> _ruleId;
  // logProb
  istringstream logProbStream(matchInfo.str(2));
  logProbStream >> _logProb;
} // end of function: read


////////////////////////////////////////////////////////////////////////////////
// Function: print
// Prints the rule on the ostream.
////////////////////////////////////////////////////////////////////////////////
void
Rule::print(ostream &os) const {
   os << _ruleId << " " << _logProb << " " << _lhs << " " << _rhs;
} // end of function: print


////////////////////////////////////////////////////////////////////////////////
// Function: apply
// Insert the Rule in the Edge.
////////////////////////////////////////////////////////////////////////////////
Edge
Rule::apply(const Edge &edge) const {
  return Edge(edge.start(), edge.start(), _lhs, _rhs, _logProb);
} // end of function: apply


////////////////////////////////////////////////////////////////////////////////
// Function: getLhs
// Return the lhs of the Rule.
////////////////////////////////////////////////////////////////////////////////
Category
Rule::getLhs() const {
  return _lhs;
} // end of function: getLhs


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the Rule on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &os, const Rule &rule) {
  rule.print(os);
  return os;
} // end of function: operator<<


////////////////////////////////////////////////////////////////////////////////
// Function: read
// Read a RuleList from the istream.
////////////////////////////////////////////////////////////////////////////////
void
RuleList::read(istream &file) {
  string line;
  while (file.good()) {
    getline(file, line);
    if (file.eof()) {
      break;
    }

    istringstream ruleStream(line);
    Rule r;
    r.read(ruleStream);
    push_back(r);
  }
} // end of function: read


////////////////////////////////////////////////////////////////////////////////
// Function: startNonterm
// Return the lhs of the first Rule in the RuleList.
////////////////////////////////////////////////////////////////////////////////
Category
RuleList::startNonterm() const {
  if (size()==0) {
    return Category();
  }
  return begin()->getLhs();
} // end of function: startNonterm


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the RuleList on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &os, const RuleList &rl) {
  for (RuleList::const_iterator i=rl.begin(); i!=rl.end(); ++i) {
    os << *i << endl;
  }
  return os;
} // end of function: operator<<

// end of file: rules.cpp
