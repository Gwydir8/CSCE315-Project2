#include "grammar.h"

#include <boost/algorithm/string.hpp>

#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

template <typename It, typename Skipper>
Grammar<It, Skipper>::Grammar()
    : Grammar::base_type(program) {
  using boost::spirit::qi::as;
  using boost::spirit::qi::as_string;
  using boost::spirit::qi::lit;
  using boost::spirit::qi::lexeme;
  using boost::spirit::qi::hold;
  using boost::spirit::qi::no_case;
  using boost::spirit::qi::attr;
  using boost::spirit::qi::_1;
  using boost::spirit::qi::_2;
  using boost::spirit::qi::_3;
  using boost::spirit::qi::_4;
  using boost::spirit::qi::_5;

  using boost::spirit::ascii::char_;
  using boost::spirit::ascii::string;
  using boost::spirit::ascii::alnum;
  using boost::spirit::ascii::digit;
  using namespace boost::spirit::qi::labels;

  using boost::phoenix::at_c;
  using boost::phoenix::push_back;

  // open, close, write and exit
  io_cmd = ((hold[no_case[string("open")]] | hold[no_case[string("close")]] |
             no_case[string("write")]) >>
            relation_name)[_val = boost::phoenix::construct<Command>(_1, _2)];

  // exit
  exit_cmd =
      (no_case[string("exit")])[_val = boost::phoenix::construct<Command>(_1)];

  // show-cmd := SHOW atomic-expr
  show_cmd =
      (no_case[string("show")] >>
       atomic_expressions)[_val = boost::phoenix::construct<Command>(_1, _2)];

  // create-cmd := CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY
  // KEY ( attribute-list )
  create_cmd =
      ((no_case[string("create table")]) >> (relation_name) >>
       ("(" >> typed_attribute_list >> ")") >> no_case["primary key"] >>
       ("(" >> attribute_list >>
        ")"))[_val = boost::phoenix::construct<Command>(_1, _2, _3, _4)];

  // update-cmd := UPDATE relation-name SET attribute-name = literal { ,
  // attribute-name = literal } WHERE condition
  update_cmd =
      (no_case[string("update")] >> (relation_name) >> no_case["set"] >>
       as<std::vector<std::string>>()[(
           (attribute_name >> "=" >> literal) >>
           *(',' >> attribute_name >> "=" >> literal))] >>
       no_case["where"] >>
       conditions)[_val = boost::phoenix::construct<Command>(_1, _2, _3, _4)];

  // insert-cmd := INSERT INTO relation-name VALUES FROM ( literal { , literal
  // } ) | INSERT INTO relation-name VALUES FROM RELATION expr
  insert_cmd =
      (no_case[string("insert into")] >> (relation_name) >>
       (no_case["values from"] >> !no_case["relation"] >> "(" >>
        as<std::vector<std::string>>()[((literal) >> *(',' >> literal))] >>
        ")"))[_val = boost::phoenix::construct<Command>(_1, _2, _3)] |
      (no_case[string("insert into")] >> (relation_name) >>
       (no_case["values from relation"] >>
        expressions))[_val = boost::phoenix::construct<Command>(_1, _2, _3)];

  // delete-cmd := DELETE FROM relation-name WHERE condition
  delete_cmd =
      (no_case[string("delete from")] >> relation_name >> no_case["where"] >>
       conditions)[_val = boost::phoenix::construct<Command>(_1, _2, _3)];

  // command := ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd |
  // create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
  command = (hold[io_cmd] | hold[exit_cmd] | hold[show_cmd] | hold[create_cmd] |
             hold[update_cmd] | hold[insert_cmd] | delete_cmd) -
            ';';

  // condition := conjunction { || conjunction }
  conditions =
    attr("OR") >> (conjunctions >>
       *("||" >> conjunctions));

  // conjunction := comparison { && comparison }
  conjunctions =
      (comparisons >>
       *("&&" >> comparisons))[_val = boost::phoenix::construct<Condition>(
                                   "AND", _1, _2)];
  // comparison := operand op operand | ( condition )
  comparisons =
      (!lit("(") >>
       (operand >> op >>
        operand))[_val = boost::phoenix::construct<Condition>(_2, _1, _3)] |
      ("(" >> conditions >>
       ")")[_val = boost::phoenix::construct<Condition>(_1)];

  // // op := == | != | < | > | <= | >=
  op = hold[string("==")] | hold[string("!=")] | hold[string("<")] |
       hold[string(">")] | hold[string("<=")] | string(">=");

  // operand := attribute-name | literal
  operand = hold[attribute_name] | literal;

  // attribute-name := identifier
  attribute_name = identifier.alias();

  // literal := intentionally left unspecified (strings, numbers, etc.)
  literal = lexeme[as_string[-lit('"') >> +(char_(" 0-9a-zA-Z_&")) >>
                             *(char_(" 0-9a-zA-Z_&")) >> -lit('"')]];

  // type := VARCHAR ( integer ) | INTEGER
  type = hold[(no_case[string("varchar")] >> string("(") >> +digit >>
               string(")"))] |
         no_case[string("integer")];

  // identifier := alpha { ( alpha | digit ) }
  identifier = lexeme[as_string[!lit('"') >> *(char_("a-zA-Z_-")) >>
                                *(char_("0-9a-zA-Z_-"))]];

  // relation-name := identifier
  relation_name = identifier.alias();

  // attribute-list := attribute-name { , attribute-name }
  attribute_list = (attribute_name >> *(',' >> attribute_name)) - ')';

  // typed-attribute-list := attribute-name type { , attribute-name type }
  typed_attribute_list =
      (attribute_name >> type >> *(',' >> attribute_name >> type)) - ')';

  // atomic-expr := relation-name | ( expr )
  atomic_expressions = hold[("(" >> expressions >> ")")] | relation_name;

  // selection := select ( condition ) atomic-expr
  selection = (no_case[string("select")] >> ("(" >> conditions >> ")") >>
               atomic_expressions)[_val = boost::phoenix::construct<Expression>(
                                       _1, _2, _3)];

  // projection := project ( attribute-list ) atomic-expr
  projection =
      (no_case[string("project")] >> ("(" >> attribute_list >> ")") >>
       atomic_expressions)[_val = boost::phoenix::construct<Expression>(_1, _2,
                                                                        _3)];
  // renaming := rename ( attribute-list ) atomic-expr
  renaming = (no_case[string("rename")] >> ("(" >> attribute_list >> ")") >>
              atomic_expressions)[_val = boost::phoenix::construct<Expression>(
                                      _1, _2, _3)];

  // setunion := atomic-expr + atomic-expr
  setunion = (atomic_expressions >> '+' >>
              atomic_expressions)[_val = boost::phoenix::construct<Expression>(
                                      "union", _1, _2)];
  // difference := atomic-expr - atomic-expr
  difference =
      (atomic_expressions >> '-' >>
       atomic_expressions)[_val = boost::phoenix::construct<Expression>(
                               "difference", _1, _2)];
  // product := atomic-expr * atomic-expr
  product = (atomic_expressions >> '*' >>
             atomic_expressions)[_val = boost::phoenix::construct<Expression>(
                                     "product", _1, _2)];

  // expr := atomic-expr | selection | projection | renaming | union |
  // difference // | product
  expressions =
      (hold[selection] | hold[projection] | hold[renaming] | hold[setunion] |
       hold[difference] | hold[product] | atomic_expressions) -
      ';';

  // query := relation-name <- expr ;
  query = (relation_name >> "<-" >> (expressions)) - ';';

  // program := { ( query | command ) }
  program = (hold[query] | command) >> ';';

  BOOST_SPIRIT_DEBUG_NODE(program);
  BOOST_SPIRIT_DEBUG_NODE(command);
  BOOST_SPIRIT_DEBUG_NODE(query);
  BOOST_SPIRIT_DEBUG_NODE(relation_name);
  // BOOST_SPIRIT_DEBUG_NODE(expression);
  BOOST_SPIRIT_DEBUG_NODE(expressions);
  // BOOST_SPIRIT_DEBUG_NODE(atomic_expression);
  BOOST_SPIRIT_DEBUG_NODE(atomic_expressions);
  BOOST_SPIRIT_DEBUG_NODE(selection);
  BOOST_SPIRIT_DEBUG_NODE(projection);
  BOOST_SPIRIT_DEBUG_NODE(renaming);
  BOOST_SPIRIT_DEBUG_NODE(setunion);
  BOOST_SPIRIT_DEBUG_NODE(difference);
  BOOST_SPIRIT_DEBUG_NODE(product);
  BOOST_SPIRIT_DEBUG_NODE(identifier);
  BOOST_SPIRIT_DEBUG_NODE(conditions);
  BOOST_SPIRIT_DEBUG_NODE(conjunctions);
  BOOST_SPIRIT_DEBUG_NODE(comparisons);
  BOOST_SPIRIT_DEBUG_NODE(op);
  BOOST_SPIRIT_DEBUG_NODE(operand);
  BOOST_SPIRIT_DEBUG_NODE(attribute_name);
  BOOST_SPIRIT_DEBUG_NODE(attribute_list);
  BOOST_SPIRIT_DEBUG_NODE(typed_attribute_list);
  BOOST_SPIRIT_DEBUG_NODE(type);
  BOOST_SPIRIT_DEBUG_NODE(literal);
  BOOST_SPIRIT_DEBUG_NODE(io_cmd);
  BOOST_SPIRIT_DEBUG_NODE(exit_cmd);
  BOOST_SPIRIT_DEBUG_NODE(show_cmd);
  BOOST_SPIRIT_DEBUG_NODE(create_cmd);
  BOOST_SPIRIT_DEBUG_NODE(update_cmd);
  BOOST_SPIRIT_DEBUG_NODE(insert_cmd);
  BOOST_SPIRIT_DEBUG_NODE(delete_cmd);
}
