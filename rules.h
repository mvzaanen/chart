////////////////////////////////////////////////////////////////////////////////
// Filename: rules.h
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the Rule and RuleList classes.
////////////////////////////////////////////////////////////////////////////////

#ifndef RULES_H
#define RULES_H

#include "category.h"
#include "edge.h"


////////////////////////////////////////////////////////////////////////////////
// Class: Rule
// Provides the interface for a Rule.
////////////////////////////////////////////////////////////////////////////////
class Rule {
public:
////////////////////////////////////////////////////////////////////////////////
// Function: Rule
// Constructor.
////////////////////////////////////////////////////////////////////////////////
  Rule() { }

////////////////////////////////////////////////////////////////////////////////
// Function: Rule
// Constructor.
////////////////////////////////////////////////////////////////////////////////
  Rule(const Category &lhs, const CategorySequence &rhs, const int ruleId,
      const double logProb)
      :_lhs(lhs), _rhs(rhs), _ruleId(ruleId), _logProb(logProb) { }

////////////////////////////////////////////////////////////////////////////////
// Function: appliesTo
// Returns true if the Edge applies to the Rule.
////////////////////////////////////////////////////////////////////////////////
  bool
  appliesTo(const Edge &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: read
// Read a rule from the istream.
////////////////////////////////////////////////////////////////////////////////
  void
  read(istream&);

////////////////////////////////////////////////////////////////////////////////
// Function: print
// Prints the rule on the ostream.
////////////////////////////////////////////////////////////////////////////////
  void
  print(ostream&) const;

////////////////////////////////////////////////////////////////////////////////
// Function: apply
// Insert the Rule in the Edge.
////////////////////////////////////////////////////////////////////////////////
  Edge
  apply(const Edge &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: getLhs
// Return the lhs of the Rule.
////////////////////////////////////////////////////////////////////////////////
  Category
  getLhs() const;

private:
////////////////////////////////////////////////////////////////////////////////
// Variable: _lhs
// Left hand side of the rule.
////////////////////////////////////////////////////////////////////////////////
   Category _lhs;

////////////////////////////////////////////////////////////////////////////////
// Variable: _rhs
// Right hand side of the rule.
////////////////////////////////////////////////////////////////////////////////
   CategorySequence _rhs;

////////////////////////////////////////////////////////////////////////////////
// Variable: _ruleId
// Id of the rule.
////////////////////////////////////////////////////////////////////////////////
   int _ruleId;

////////////////////////////////////////////////////////////////////////////////
// Variable: _logProb
// Log probability of the rule.
////////////////////////////////////////////////////////////////////////////////
   double _logProb;

}; // end of class: Rule


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the Rule on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &, const Rule &);


////////////////////////////////////////////////////////////////////////////////
// Class: RuleList
// Provides the interface for a RuleList.
////////////////////////////////////////////////////////////////////////////////
class RuleList:public vector<Rule> {
public:
////////////////////////////////////////////////////////////////////////////////
// Function: read
// Read a RuleList from the istream.
////////////////////////////////////////////////////////////////////////////////
  void
  read(istream&);

////////////////////////////////////////////////////////////////////////////////
// Function: startNonterm
// Return the lhs of the first Rule in the RuleList.
////////////////////////////////////////////////////////////////////////////////
  Category
  startNonterm() const;
protected:
private:
}; // end of class: RuleList


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Print the RuleList on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &, const RuleList &);


#endif

// end of file: rules.h
