////////////////////////////////////////////////////////////////////////////////
// Filename: edge.cpp
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the Edge and EdgeList classes.
////////////////////////////////////////////////////////////////////////////////

#include "edge.h"

////////////////////////////////////////////////////////////////////////////////
// Function: combine 
// Returns the Edge that combines both arguments.
////////////////////////////////////////////////////////////////////////////////
Edge
combine(const Edge &edge1, const Edge &edge2) {
  const Edge *ap;
  const Edge *ip;
  if (edge1.isActive()) {
    ap=&edge1;
    ip=&edge2;
  }
  else {
    ip=&edge1;
    ap=&edge2;
  }

  Tree tmp(ap->_tree);
  tmp.addChild(ip->_tree);

  return Edge(ap->_start, ip->_finish, tmp, ap->_toFind.rest(),
      ap->_logProb+ip->_logProb);
} // end of function: combine


////////////////////////////////////////////////////////////////////////////////
// Function: operator=
// Assignment operator.
////////////////////////////////////////////////////////////////////////////////
void
Edge::operator=(const Edge &edge) {
   _start=edge._start;
   _finish=edge._finish;
   _tree=edge._tree;
   _toFind=edge._toFind; 
   _logProb=edge._logProb; 
} // end of function: operator=


////////////////////////////////////////////////////////////////////////////////
// Function: operator==
// Equality operator.
////////////////////////////////////////////////////////////////////////////////
bool
Edge::operator==(const Edge &edge) const {
  return(_start==edge._start  &&
         _finish==edge._finish  &&
         _tree==edge._tree  &&
         _toFind==edge._toFind);
} // end of function: operator==


////////////////////////////////////////////////////////////////////////////////
// Function: canCombineWith 
// Returns true if the two Edges can be combined, false otherwise.
////////////////////////////////////////////////////////////////////////////////
bool
Edge::canCombineWith(const Edge &edge) const {
  const Edge *ap, *ip;

  if (isActive()) {
    ip = &edge;
    ap = this;
  }
  else {
    ip = this;
    ap = &edge;
  }

  if (!ap->isActive() || ip->isActive()) {
    return false;
  }      
  else {
    Category cat = ap->_toFind.front();
     return (ip->_start == ap->_finish ) && ( ip->_tree.cat() == cat );
  }
} // end of function: canCombineWith


////////////////////////////////////////////////////////////////////////////////
// Function: isActive
// Returns true if the Edge is active.
////////////////////////////////////////////////////////////////////////////////
bool 
Edge::isActive() const {
  return !_toFind.empty();
} // end of function: isActive


////////////////////////////////////////////////////////////////////////////////
// Function: start 
// Returns the start value.
////////////////////////////////////////////////////////////////////////////////
CategorySequence::size_type
Edge::start() const {
  return _start;
} // end of function: start


////////////////////////////////////////////////////////////////////////////////
// Function: finish 
// Returns the finish value.
////////////////////////////////////////////////////////////////////////////////
CategorySequence::size_type
Edge::finish() const {
  return _finish;
} // end of function: finish


////////////////////////////////////////////////////////////////////////////////
// Function: label 
// Returns the category of the Edge.
////////////////////////////////////////////////////////////////////////////////
Category
Edge::label() const {
  return _tree.cat();
} // end of function: label


////////////////////////////////////////////////////////////////////////////////
// Function: found 
// Returns the CategorySequence of the children in the tree.
////////////////////////////////////////////////////////////////////////////////
CategorySequence
Edge::found() const {
  return _tree.getChildren();
} // end of function: found


////////////////////////////////////////////////////////////////////////////////
// Function: toFind
// Returns the CategorySequence of the toFind Categories.
////////////////////////////////////////////////////////////////////////////////
const CategorySequence &
Edge::toFind() const {
  return _toFind;
} // end of function: toFind


////////////////////////////////////////////////////////////////////////////////
// Function: logProb
// Returns the log of the probability of the Edge.
////////////////////////////////////////////////////////////////////////////////
double
Edge::logProb() const {
  return _logProb;
} // end of function: logProb


////////////////////////////////////////////////////////////////////////////////
// Function: parse
// Returns the parse tree.
////////////////////////////////////////////////////////////////////////////////
const Tree &
Edge::parse() const {
  return _tree;
} // end of function: parse


////////////////////////////////////////////////////////////////////////////////
// Function: print 
// Prints the Edge on the ostream.
////////////////////////////////////////////////////////////////////////////////
void
Edge::print(ostream &os) const {
  os << "<" << _start << "," << _finish << ","
     << _tree.cat() << ",";
  os << _tree.getChildren() << "." << _toFind << ":" << _logProb << ">";
} // end of function: print


////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Output operator for Edge.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &os, const Edge &edge) {
  edge.print(os);
  return os;
} // end of function: operator<<


////////////////////////////////////////////////////////////////////////////////
// Function: canCombineWith 
// Returns true if the two Edges can be combined, false otherwise.
////////////////////////////////////////////////////////////////////////////////
bool
EdgeList::isMember(const Edge& edge) const {
   return (find(begin(), end(), edge)!=end());
} // end of function: isMember


////////////////////////////////////////////////////////////////////////////////
// Function: operator<< 
// Print the EdgeList on the ostream.
////////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream &os, const EdgeList &el) {
  for (EdgeList::const_iterator i=el.begin(); i!=el.end(); ++i) {
    os << *i << endl;
  }
  return os;
} // end of function: operator<<

// end of file: edge.cpp