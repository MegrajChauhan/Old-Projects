#ifndef PARSER_HH
#define PARSER_HH

#include"lexer.hpp"
#include"fart_containers.hpp"
#include<sstream>

int compare(char temp)
{
  switch(temp)
  {
    case '+':return 3;
    case '-': return 4;
    case '/': return 1;
    case '*': return 2;
  }
}

bool gg(char a, char b)
{
  return compare(a) > compare(b);
}

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

template<typename T, typename U>
auto divide(T x, U y)
{
  return x/y;
}

template<typename T, typename U>
auto mul(T x, U y)
{
  return x*y;
}

template<typename T, typename U>
auto add(T x, U y)
{
  return x+y;
}

template<typename T, typename U>
auto sub(T x, U y)
{
  return x-y;
}

std::string to_str(auto in)
{
  std::stringstream stream;
  std::string str;
  stream<<in;
  stream>>str;
  return str;
}

double eval(std::pair<int, std::string> num1, std::pair<int, std::string> num2, char oper)
{
  auto a = type(num1.second);
  auto b = type(num2.second);
  auto x = (a == Toks::INT)? to_int(num1.second): to_float(num1.second);
  auto y = (b == Toks::FLOAT)? to_int(num2.second): to_float(num2.second);
  switch(oper)
  {
    case '+': return add(x,y);
    case '/': return divide(x,y);
    case '*': return mul(x,y);
    case '-': return sub(x,y);
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
 Fart_pair<int, std::string> _val_arr;
 Fart_pair<int, char> _oper_arr;
 public:
 Parser() = default;
 Parser(Lexer& lexed){this->lexed_arr = lexed.get_lexed();}

 void parse()
 {
  int pos = 0;
  while(pos < lexed_arr.get_size())
  {
   if(lexed_arr[pos].first == Toks::INT ||lexed_arr[pos].first == Toks::FLOAT)
   {
     _val_arr.push(std::make_pair(pos, lexed_arr[pos].second));
  }else if(isoper(lexed_arr[pos].second[0]))
  {
	  _oper_arr.push(std::make_pair(pos, lexed_arr[pos].second[0]));
  }
  pos++;
 }
 }

  void sort()
  {
    for(int i = 0; i< _oper_arr.get_size(); i++)
    {
      for(int j = i + 1; j < _oper_arr.get_size(); j++)
      {
        if(gg(_oper_arr[i].second, _oper_arr[j].second))
        {
          _oper_arr.swap(i, j);
        }
      }
    }
  }
  
  std::string evaluate()
  {
    for(int i = 0; i < _oper_arr.get_size(); i++)
    {
      if(_oper_arr[i].second == '/')
      {
        std::pair<int, std::string> num1, num2;
        num1 = _val_arr[_val_arr.position_of(_oper_arr[i].first -1)];
        num2 = _val_arr[_val_arr.position_of(_oper_arr[i].first +1)];
        _val_arr[_val_arr.position_of(_oper_arr[i].first +1)] = std::make_pair(num2.first, to_str(eval(num1, num2, '/'))); 
      }else if(_oper_arr[i].second == '*')
      {
        std::pair<int, std::string> num1, num2;
        num1 = _val_arr[_val_arr.position_of(_oper_arr[i].first -1)];
        num2 = _val_arr[_val_arr.position_of(_oper_arr[i].first +1)];
        _val_arr[_val_arr.position_of(_oper_arr[i].first +1)] = std::make_pair(num2.first, to_str(eval(num1, num2, '*'))); 
      }else if(_oper_arr[i].second == '+')
      {
        std::pair<int, std::string> num1, num2;
        num1 = _val_arr[_val_arr.position_of(_oper_arr[i].first -1)];
        num2 = _val_arr[_val_arr.position_of(_oper_arr[i].first +1)];
        _val_arr[_val_arr.position_of(_oper_arr[i].first +1)] = std::make_pair(num2.first, to_str(eval(num1, num2, '+'))); 
      }else if(_oper_arr[i].second == '-')
      {
        std::pair<int, std::string> num1, num2;
        num1 = _val_arr[_val_arr.position_of(_oper_arr[i].first -1)];
        num2 = _val_arr[_val_arr.position_of(_oper_arr[i].first +1)];
        _val_arr[_val_arr.position_of(_oper_arr[i].first +1)] = std::make_pair(num2.first, to_str(eval(num1, num2, '-'))); 
      }
    }
    return _val_arr[_val_arr.get_size() - 1].second;
  }

  // void print()
  // {
	//   std::cout<<"Pos  Value"<<std::endl;
	//   for(int i = 0; i < _val_arr.get_size(); i++)
	//   {
	// 	std::cout<<_val_arr[i].first<<"    "<<_val_arr[i].second<<std::endl;
	//   }
	//   std::cout<<std::endl;
  //         std::cout<<"Pos  Oper"<<std::endl;
	//   for(int i = 0; i < _oper_arr.get_size(); i++)
	//   {
	// 	std::cout<<_oper_arr[i].first<<"    "<<_oper_arr[i].second<<std::endl;
	//   }
  // }
};

#endif
// 2 + 3 - 4
/*
  [0:2, 2:3, 4:4]
  [1:+, 3:-]
  1)execute +
  [2:5, 4:4]
  [3:-]
*/
