/*
 * debug.cc
 *
 *  Created on: 8 mars 2013
 *      Author: hadrien
 */

#include "parser.hh"


// We need to tell fusion about our struct
// to make it a first-class fusion citizen. This has to
// be in global scope according to official Boost Spirit tutorial.

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::shapeInfo,
			  (std::string, name)
			  (std::vector<std::string>, attributes)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::screenInfo,
			  (int, height)
			  (int, width)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::trialInfo,
			  (int, time)
			  (std::string, name)
			  (std::vector<configuration::shapeInfo>, shapes)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::sessionInfo,
			  (std::string, name)
			  (std::string, comment)
			  (int, polarCoordonates)
			  (std::vector<configuration::screenInfo>, screens)
			  (std::vector<configuration::trialInfo>, trials)
			  )

namespace configuration
{
  ///////////////////////////////////////////////////////////////////////////////
  //  Our moses parser
  ///////////////////////////////////////////////////////////////////////////////
  template <typename Iterator>
  struct moses_parser : qi::grammar<Iterator, sessionInfo(), standard::space_type>
  {
    moses_parser() : moses_parser::base_type(session)
    {
      using qi::int_;
      using qi::lit;
      using qi::double_;
      using qi::lexeme;
      using standard::char_;
      using boost::fusion::vector;
      using qi::eol;

      word %= lexeme[ +(char_ - ' ' - "|" - ">" - ";" - "\n")];

      shape %= ">"
	>> word
	>> +word
	;

      trial %= "|"
	>> -int_
	>> word
	>> +shape
	>> ";"
	;

      screen %= int_ >> "x" >> int_ >> "|";

      session %=
	"session name="
	>> word
	>> "comment="
	>> word
	>> "polar="
	>> int_
	>> "screens="
	>> +screen
	>> +trial
	;

    }

    qi::rule<Iterator, std::string(), standard::space_type> word;
    qi::rule<Iterator, configuration::shapeInfo(), standard::space_type> shape;
    qi::rule<Iterator, configuration::trialInfo(), standard::space_type> trial;
    qi::rule<Iterator, configuration::screenInfo(), standard::space_type> screen;
    qi::rule<Iterator, configuration::sessionInfo(), standard::space_type> session;
  };

  ////////////////////////////////////////////////////////////////////////////
  //  Main program
  ////////////////////////////////////////////////////////////////////////////
  bool	createConfiguration(char const* filename,
			    sessionInfo &res)
  {
    std::ifstream in(filename, std::ios_base::in);
    if (!in)
      {
        std::cerr << "Error: Could not open input file: "
		  << filename << std::endl;
        return 1;
      }
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::string storage; // We will read the contents here.
    std::copy(
	      std::istream_iterator<char>(in),
	      std::istream_iterator<char>(),
	      std::back_inserter(storage));

    using boost::spirit::standard::space;

    typedef std::string::const_iterator iterator_type;
    typedef configuration::moses_parser<iterator_type> moses_parser;

    moses_parser g; // Our grammar


    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();
    bool r = boost::spirit::qi::phrase_parse(iter, end, g, space, res);

    return (r);
  }

}

