#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

class API
{
    std::string input;
    std::string res;
    int error;

public:
    API() = default;
    API(std::string in) : input(in) {}

    void eval()
    {
        Lexer lex(input);
        if(this->input == "history")
        {
          history_cout();
        }else{
        error = lex.lex();
        if (error == 1)
        {
            return;
        }
        else
        {
            lex.ans(prev_ans);
            Parser p(lex);
            p.evaluate();
            res = p.res();
            _history_.push(input);
            prev_ans.push(res);
        }
        }
    }

    std::string get_res()
    {
        return res;
    }
};