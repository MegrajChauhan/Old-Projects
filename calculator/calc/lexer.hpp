#ifndef LEXER_HH
#define LEXER_HH

#include "fart_containers.hpp"
#include <iostream>

Fart_arr<std::string> _glob_funcs = {"history","ans"};
Fart_arr<std::string> _history_;
Fart_arr<std::string> prev_ans;

void history_cout()
{
  for(int i = 0; i<_history_.get_size(); i++)
  {
    std::cout<<_history_[i]<<std::endl;
  }
}

void add_history(std::string his)
{
  if(_history_.get_size() == 5)
  {
    _history_.pop(0);
  _history_.push(his);
  }else{
  _history_.push(his);
  }
}

void add_ans(std::string ans)
{
  if(_history_.get_size() == 5)
  {
    prev_ans.pop(0);
  prev_ans.push(ans);
  }else{
  prev_ans.push(ans);
  }
}

void func_access(std::string fu)
{
  if(fu == "history")
     history_cout();
  else if(fu == "ans")
     std::cout<<prev_ans[prev_ans.get_size() - 1]<<std::endl;
}

#define check              \
  if (pos >= input.size()) \
  {                        \
    break;                 \
  }
bool isoper(char s) {return (s == '+' || s == '-' || s == '*' || s == '/' || s == '^' || s == '%');}
bool isdigit(char s) {return ((s >= '0' && s <= '9') || (s == '.'));}
bool isalpha(char s){return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');}

enum Toks
{
  ADD,
  SUB,
  DIV,
  MUL,
  EXPO,
  FLOAT,
  INT,
  Error,
  LPAREN,RPAREN, EXPR, N_FLOAT, N_INT, MODU
};

Toks type_eval(std::string num)
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
  case '^':
    return EXPO;
  case '%':
    return MODU;
  }
  return Toks::Error;
}

class Lexer
{
  std::string input;
  Fart_pair<Toks, std::string> lexed;
  Fart_arr<std::string> anss;
public:
  Lexer() = default;
  Lexer(std::string _in_) {
    this->input = _in_;
  }  
  
  void ans(Fart_arr<std::string> cool)
  {
    this->anss = cool;
  }

  int lex()
  {
    int pos = 0;
    int o_num, c_num2;
    o_num = c_num2 = 0;
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
          if(lexed.get_size() == 1 && lexed[0].first == SUB)
          {
            Toks t = type_eval(temp);
            Toks x = (t == INT)? N_INT: N_FLOAT;
            lexed.push(std::make_pair(x, temp));
            lexed.pop(0);
          }else if(lexed.get_size() >= 2 && lexed[lexed.get_size() - 1].first == SUB && (lexed[lexed.get_size() - 2].first == DIV ||lexed[lexed.get_size() - 2].first == MUL || lexed[lexed.get_size() - 2].first == ADD || lexed[lexed.get_size() - 2].first == EXPO))
          {
            Toks t = type_eval(temp);
            Toks x = (t == INT)? N_INT: N_FLOAT;
            lexed.pop(lexed.get_size() - 1); 
            lexed.push(x, temp);
          }else{
            lexed.push(std::make_pair(type_eval(temp), temp));
          }
      }
      else if(isoper (input[pos]))
      {
        std::string temp;
        temp += input[pos];
        lexed.push(std::make_pair(type_oper(temp[0]), temp));
        pos++;
      }else if(input[pos] == '(')
      {
        o_num++;
        std::string temp;
        pos++;
        while(true)
        {
          if(input[pos] == '(')
          {
            o_num++;
            temp += input[pos];
            pos++;
          }else if(input[pos] == ')')
          {
            c_num2++;
            temp += input[pos];
            pos++;
          }else{
            temp += input[pos];
            pos++;
          }
          if(c_num2 == o_num)
          {
            break;
          }else if(pos >= input.size() && c_num2 != o_num)
          {
            std::cout<<"Error: Stray \'(\' or \')\'"<<std::endl;
            return 1;
          }
        }
        temp.erase(temp.size() - 1);
        lexed.push(EXPR, temp);
        pos++;
      }else if(isalpha(input[pos]))
      {
        std::string temp;
        while(isalpha(input[pos]))
        {
          temp += input[pos];
          pos++;
        }
        if (temp == "ans")
        {
          lexed.push(type_eval(prev_ans[prev_ans.get_size() - 1]), prev_ans[prev_ans.get_size() - 1]);   
        }else{
          std::cerr<<"Error: Unknown function or keyword; Expected a function or a keyword; Got \""<<temp<<"\" instead;"<<std::endl;
          return 1;
        }
      }
      else
      {
        std::cout << "Error: Unknown Token: " << input[pos] << std::endl;
        pos++;
      }
    }
    return 0;
  }

  Fart_pair<Toks, std::string>& get_lexed()
  {
    return lexed;
  }
};
#endif
