#ifndef LEXER_HH
#define LEXER_HH

#include "fart_containers.hpp"
#include <iostream>

#define check              \
  if (pos >= input.size()) \
  {                        \
    break;                 \
  }
bool isoper(char s) {return (s == '+' || s == '-' || s == '*' || s == '/');}
bool isdigit(char s) {return ((s >= '0' && s <= '9') || (s == '.'));}

enum Toks
{
  ADD,
  SUB,
  DIV,
  MUL,
  FLOAT,
  INT,
  Error
};

Toks type(std::string num)
{
  int dot_count = 0;
  int p = 0;
  int count = 0;
  while (p < num.size())
  {
    if (num[p] == '.')
      dot_count++;
    else if (isdigit(num[p]))
    {
      count++;
    }
    p++;
  }
  if (dot_count == 1)
  {
    return Toks::FLOAT;
  }
  if(count == num.size() && dot_count == 0){return Toks::INT;}
  return Toks::Error;
}

Toks type_oper(char op)
{
  switch (op)
  {
  case '+':
    return Toks::ADD;
  case '-':
    return Toks::SUB;
  case '*':
    return Toks::MUL;
  case '/':
    return Toks::DIV;
  }
  return Toks::Error;
}

class Lexer
{
  std::string input;
  Fart_pair<Toks, std::string> lexed;

public:
  Lexer() = default;
  Lexer(std::string _in_) {
    this->input = _in_;
  }  

  void lex()
  {
    int pos = 0;
    while (pos < input.size())
    {
      if (input[pos] == ' ')
        pos++;
      else if(isdigit (input[pos]))
      {
        std::string temp;
        while(isdigit(input[pos]))
          {
            check
            temp += input[pos];
            pos++;
          }
        lexed.push(std::make_pair(type(temp), temp));
      }
      else if(isoper (input[pos]))
      {
        std::string temp;
        temp += input[pos];
        lexed.push(std::make_pair(type_oper(temp[0]), temp));
        pos++;
      }
      else
      {
        std::cout << "Error: Unknown Token: " << input[pos] << std::endl;
        pos++;
      }
    }
  }

  Fart_pair<Toks, std::string>& get_lexed()
  {
    return lexed;
  }

  void print()
  {
   for (int i = 0; i < lexed.get_size(); i++)
    {
      if (lexed[i].first == Toks::Error)
      {
        std::cout << "Error Token: " << lexed[i].second << std::endl;
      }
      else
      {
        std::cout << "Token type: " << lexed[i].first << std::endl;
        std::cout << "Token value: " << lexed[i].second << std::endl;
      }
    }
  }
};
#endif
