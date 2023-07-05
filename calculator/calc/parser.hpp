#ifndef PARSER_HH
#define PARSER_HH

#include "lexer.hpp"
#include <sstream>
#include<math.h>

class Evaluate
{
  std::string inp;
  std::string res;

public:
  Evaluate() = default;
  Evaluate(std::string str) : inp{str} {}
  void eval();
  std::string get_res();
};

int to_int(std::string num)
{
  return std::stoi(num);
}

float to_float(std::string num)
{
  float f;
  sscanf(num.c_str(), "%f", &f);
  return f;
}

bool isvalid(Toks tok) { return tok == INT || tok == FLOAT || tok == N_FLOAT || tok == N_INT; }

template <typename T, typename U>
auto divide(T x, U y)
{
  if(y == 0)
  {
    std::cerr<<"Error: Division By Zero"<<std::endl;
    return x * 0;
  }
  return x / y;
}

template <typename T, typename U>
auto mul(T x, U y)
{
  return x * y;
}

template <typename T, typename U>
auto add(T x, U y)
{
  return x + y;
}

template <typename T, typename U>
auto sub(T x, U y)
{
  return x - y;
}

template <typename T, typename U>
auto modu(T x, U y)
{
  try{
    if(y == 0)
    {
      throw x;
    }
  }catch (int x)
  {
    std::cerr<<"Error: The divisor must be non-zero"<<std::endl;
    return 0;
  }
    return x % y;
}

template <typename T, typename U>
T expo(T x, U y)
{
  auto res = std::pow(x, y);
  return res;
}

std::string to_str(auto in)
{
  std::stringstream stream;
  std::string str;
  stream << in;
  stream >> str;
  return str;
}

double evaluate_res(std::pair<Toks, std::string> num1, std::pair<Toks, std::string> num2, char oper)
{
  auto a = num1.first;
  auto b = num2.first;
  auto x = (a == INT) ? to_int(num1.second) : (a == FLOAT) ? to_float(num1.second)
                                          : (a == N_FLOAT) ? 0 - to_float(num1.second)
                                                           : 0 - to_int(num1.second);
  auto y = (b == INT) ? to_int(num2.second) : (b == FLOAT) ? to_float(num2.second)
                                          : (b == N_FLOAT) ? 0 - to_float(num2.second)
                                                           : 0 - to_int(num2.second);
  switch (oper)
  {
  case '+':
    return add(x, y);
  case '/':
    return divide(x, y);
  case '*':
    return mul(x, y);
  case '-':
    return sub(x, y);
  case '%':
  {
    int w = to_int(num1.second);
    int z = to_int(num2.second);
    return modu(w, z);
  }
  case '^':
  {
    return expo(x, y);
  }
  }
  return 0.0;
}

double mul(std::string num1, std::string num2)
{
  return to_float(num1) * to_float(num2);
}

class Parser
{
  Fart_pair<Toks, std::string> lexed_arr;

public:
  Parser() = default;
  Parser(Lexer &lexed) { this->lexed_arr = lexed.get_lexed(); }

  void evaluate()
  {
    std::vector<int> arr_of_exprs = lexed_arr.array_of_occurences(EXPR);
    if (is_empty(arr_of_exprs) == false)
    {
      expr_eval(arr_of_exprs);
    }
    std::vector<int> arr_of_expo = lexed_arr.array_of_occurences("^");
    eval(arr_of_expo, '^');
    std::vector<int> arr_of_div = lexed_arr.array_of_occurences("/");
    eval(arr_of_div, '/');
    std::vector<int> arr_of_mul = lexed_arr.array_of_occurences("*");
    eval(arr_of_mul, '*');
    std::vector<int> arr_of_modu = lexed_arr.array_of_occurences("%");
    eval(arr_of_modu, '%');
    std::vector<int> arr_of_sub = lexed_arr.array_of_occurences("-");
    eval(arr_of_sub, '-');
    std::vector<int> arr_of_add = lexed_arr.array_of_occurences("+");
    eval(arr_of_add, '+');
  }

  void eval(std::vector<int> arr_of_smth, char oper)
  {
    Fart_arr<int> to_delete;
    int p = 0;
    if (is_empty(arr_of_smth) == true)
    {
      return;
    }
    else
    {
      for (int i = 0; i < arr_of_smth.size(); i++)
      {
        std::string num1 = lexed_arr[arr_of_smth[i] - 1].second;
        std::string num2 = lexed_arr[arr_of_smth[i] + 1].second;
        if (isvalid(lexed_arr[arr_of_smth[i] - 1].first))
        {
          if (isvalid(lexed_arr[arr_of_smth[i] + 1].first))
          {}
          else
          {
            std::cerr << "Error: Expected a Number" << std::endl;
            return;
          }
        }
        else
        {
          std::cerr << "Error: Expected a Number" << std::endl;
          return;
        }
        to_delete.push(arr_of_smth[i]);
        to_delete.push(arr_of_smth[i] - 1);
        lexed_arr[arr_of_smth[i] + 1] = std::make_pair(type_eval(to_str(evaluate_res(lexed_arr[arr_of_smth[i] - 1], lexed_arr[arr_of_smth[i] + 1], oper))), to_str(evaluate_res(lexed_arr[arr_of_smth[i] - 1], lexed_arr[arr_of_smth[i] + 1], oper)));
      }
    }
    lexed_arr.pop(to_delete);
  }

  void expr_eval(std::vector<int> list)
  {
    for (int i = 0; i < list.size(); i++)
    {
      Evaluate e(lexed_arr[list[i]].second);
      e.eval();
      lexed_arr[list[i]] = std::make_pair(type_eval(to_str(e.get_res())), to_str(e.get_res()));
    }
  }

  std::string res()
  {
    return lexed_arr[lexed_arr.get_size() - 1].second;
  }

  bool is_empty(std::vector<int> arr)
  {
    if (arr[0] == -1)
      return true;
    return false;
  }
};

void Evaluate::eval()
{
  Lexer temp(this->inp);
  temp.lex();
  Parser p(temp);
  p.evaluate();
  this->res = p.res();
}

std::string Evaluate::get_res()
{
  return this->res;
}

#endif
