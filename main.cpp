////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
// This file is part of the chart package.
////////////////////////////////////////////////////////////////////////////////
// This file contains the implementation of the main function.
////////////////////////////////////////////////////////////////////////////////

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "category.h"
#include "config.h"
#include "parse.h"
#include "rules.h"

using namespace std;
using namespace boost::program_options;
using namespace boost::iostreams;

////////////////////////////////////////////////////////////////////////////////
// Function: main
// This is the main function.
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char *argv[]) {
  string programName=argv[0];
  // Specify program options
  options_description options("Options");
  options.add_options()
    ("help,h",
      "produce help message and exit")
    ("version,v",
      "produce version information and exit")
    ("input,i",
      value<string>()->default_value("-"),
      "specify an input file, use - for stdin")
    ("output,o",
      value<string>()->default_value("-"),
      "specify an output file, use - for stdout")
    ("grammar,g",
      value<string>(),
      "specify a grammar file");
  // Parse program options
  variables_map vm;
  store(parse_command_line(argc, argv, options), vm);
  notify(vm);

  if (vm.count("help")) {
    cout << options << endl;
    exit(0);
  }
  if (vm.count("version")) {
    cout << "This is the parser program." << endl;
    cout << "It is contained in the " << PACKAGE_STRING << " package";
    cout << endl;
    exit(0);
  }

  // Handle grammar
  if (!vm.count("grammar")) {
    cerr << "A grammar file has to be specified" << endl;
    cerr << options << endl;
    exit(1);
  }
  ifstream grStream(vm["grammar"].as<string>().c_str());
  RuleList grammar;
  grammar.read(grStream);

  // Handle input
  filtering_istream is;
  if (vm["input"].as<string>()=="-") {
    is.push(cin);
  }
  else {
    is.push(file_descriptor_source(vm["input"].as<string>().c_str()));
  }

  // Handle output
  filtering_ostream os;
  if (vm["output"].as<string>()=="-") {
    os.push(cout);
  }
  else {
    os.push(file_descriptor_sink(vm["output"].as<string>().c_str()));
  }

  string line;
  while (getline(is, line)) {
    istringstream ss(line);
    CategorySequence input;
    ss >> input;
    EdgeList result=parse(grammar, grammar.startNonterm(), input);
    for (EdgeList::const_iterator i=result.begin(); i!=result.end(); ++i) {
      os << i->parse() << " : " << i->logProb() << endl;
    }
    if (result.size()==0) {
      os << "Sentence is unparsable." << endl;
    }
  }
  exit(0);
} // end of function: main

// end of file: main.cpp
