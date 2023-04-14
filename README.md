# README INTRO

This is the chart package.  This is a simple implementation of a chart
parser.  This implementation is based on code by David Perelman-Hall
and Jamshid Afshar.

This package is maintained by
    Menno van Zaanen (menno@ics.mq.edu.au)
and the latest version of this package can be found on his homepage:
    http://www.ics.mq.edu.au/~menno
Please contact him if you have any questions, remarks, bugs,
improvements, donations or any other matters of concern about this
package.


# USAGE

The parser requires a context-free grammar and sentences as input.
The program knows the following options:
  -h [ --help ]            produce help message and exit
  -v [ --version ]         produce version information and exit
  -i [ --input ] arg (=-)  specify an input file, use - for stdin
  -o [ --output ] arg (=-) specify an output file, use - for stdout
  -g [ --grammar ] arg     specify a grammar file

The grammar file should be in the following format:
    <rule_num> <log_prob> <lhs> <rhs>
<rule_num> is the rule number.  This should be a unique number to
identify the grammar rule.  <log_prob> is the logarithm of the
probability of the rule.  <lhs> is the left hand side of the rule.
This is a single non-terminal.  All non-terminals should start with an
underscore.  No spaces are allowed in terminals or non-terminals.
<rhs> is a sequence of terminals and/or non-terminals.  Non-terminals
are not allowed to start with an underscore.  There is one grammar
rule per line.

Sentences are provided in the input file.  They should be space
separated tokens with one sentence per line.

The output is a tree structure of the input sentence.  If no parse of
the sentence using the grammar is possible, the output is
    Sentence is unparsable.
otherwise, a bracketed version of the sentence is returned.  If the
sentence is ambiguous, all analyses are returned.  Following the tree
structure a colon followed by the logarithm of the probability of the
parse is present.


# OTHER FILES

Please read the following files:
COPYING: information on copying and using the package and its contents
INSTALL: information on installing the package
NEWS:    what's new this version


# TESTED SYSTEMS

The package has been found working on the following systems:
linux

Could you please notify me if you found it working on other systems
(or if you found any problems on certain systems, preferably with
patches :).
