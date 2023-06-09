////////////////////////////////////////////////////////////////////////////////
// Filename: tree.h
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the definition of the Tree class.
////////////////////////////////////////////////////////////////////////////////

#ifndef TREE_H
#define TREE_H

#include <vector>
#include "category.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class: Tree
// Provides the interface for a Tree.
////////////////////////////////////////////////////////////////////////////////
class Tree {
public:
////////////////////////////////////////////////////////////////////////////////
// Function: Tree
// Constructor.
////////////////////////////////////////////////////////////////////////////////
  Tree(const Category &cat);

////////////////////////////////////////////////////////////////////////////////
// Function: Tree
// Copy constructor.
////////////////////////////////////////////////////////////////////////////////
  Tree(const Tree &);

////////////////////////////////////////////////////////////////////////////////
// Function: ~Tree
// Destructor.
////////////////////////////////////////////////////////////////////////////////
  ~Tree();

////////////////////////////////////////////////////////////////////////////////
// Function: operator=
// Assignment operator.
////////////////////////////////////////////////////////////////////////////////
  void
  operator=(const Tree &);

////////////////////////////////////////////////////////////////////////////////
// Function: operator==
// Equality operator.
////////////////////////////////////////////////////////////////////////////////
  bool
  operator==(const Tree &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: operator!=
// Inequality operator.
////////////////////////////////////////////////////////////////////////////////
  bool
  operator!=(const Tree &) const;

////////////////////////////////////////////////////////////////////////////////
// Function: cat
// Return the category of the top node.
////////////////////////////////////////////////////////////////////////////////
  const Category&
  cat() const;

////////////////////////////////////////////////////////////////////////////////
// Function: clear
// Empty the tree.
////////////////////////////////////////////////////////////////////////////////
  void
  clear();

////////////////////////////////////////////////////////////////////////////////
// Function: addChild
// Add a child to the current level.
////////////////////////////////////////////////////////////////////////////////
  void
  addChild(const Tree &);

////////////////////////////////////////////////////////////////////////////////
// Function: getChildren
// Return the children of the current level.
////////////////////////////////////////////////////////////////////////////////
  CategorySequence
  getChildren() const;

////////////////////////////////////////////////////////////////////////////////
// Function: print
// Print contents on ostream.
////////////////////////////////////////////////////////////////////////////////
  void
  print(ostream &) const;

private:
////////////////////////////////////////////////////////////////////////////////
// Variable: _cat
// The Category of the current level.
////////////////////////////////////////////////////////////////////////////////
   Category _cat;

////////////////////////////////////////////////////////////////////////////////
// Variable: _children
// Children of the current level.
////////////////////////////////////////////////////////////////////////////////
   vector<Tree> _children;

}; // end of class: Tree

////////////////////////////////////////////////////////////////////////////////
// Function: operator<<
// Output operator for Tree.
////////////////////////////////////////////////////////////////////////////////
ostream &
operator<<(ostream &, const Tree &);

#endif
// end of file: tree.h
