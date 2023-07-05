#include<iostream>
#include"lexer.hpp"
#include"parser.hpp"

int main()
{
	/*
  std::cout << "Add = 0" << std::endl;
  std::cout << "Sub = 1" << std::endl;
  std::cout << "Div = 2" << std::endl;
  std::cout << "Mul = 3" << std::endl;
  std::cout << "Float = 4" << std::endl;
  std::cout << "Int = 5" << std::endl;
    */
 while(true)
 {
  std::cout<<">>>";
  std::string in;
  std::getline(std::cin, in);
  Lexer l(in);
  l.lex();
  Parser p(l);
  p.parse();
  p.sort();
  std::string r = p.evaluate();
  std::cout<<r<<std::endl;
  // p.print();
  //l.print();
 }
}
