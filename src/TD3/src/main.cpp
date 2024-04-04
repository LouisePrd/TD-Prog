#include "token.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <cctype>

std::vector<std::string> split_string(std::string const &s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

float npi_evaluate(std::vector<std::string> const &tokens)
{
    std::vector<float> stack;
    for (std::string const &token : tokens)
    {
        if (is_floating(token))
        {
            stack.push_back(std::stof(token));
        }
        else
        {
            float rightOperand = stack.back();
            stack.pop_back();
            float leftOperand = stack.back();
            stack.pop_back();
            switch (token[0])
            {
            case '+':
                stack.push_back(leftOperand + rightOperand);
                break;
            case '-':
                stack.push_back(leftOperand - rightOperand);
                break;
            case '*':
                stack.push_back(leftOperand * rightOperand);
                break;
            case '/':
                stack.push_back(leftOperand / rightOperand);
                break;
            default:
                break;
            }
        }
    }
    return stack.back();
}

size_t operator_precedence(Operator const op)
{
    switch (op)
    {
    case Operator::ADD:
        return 1;
    case Operator::SUB:
        return 1;
    case Operator::MUL:
        return 2;
    case Operator::DIV:
        return 2;
    case Operator::OPEN_PAREN:
        return 0;
    case Operator::CLOSE_PAREN:
        return 0;
    case Operator::PUISS:
        return 3;
    default:
        return 0;
    }
}

std::vector<Token> infix_to_npi_tokens(std::string const &expression)
{
    std::vector<Token> result;
    std::vector<Token> output;
    std::vector<Token> stackOperator;

    output = tokenize(split_string(expression));

    for (Token const &token : output)
    {
        if (token.type != TokenType::OPERATOR)
            result.push_back(token);
        else
        {
            if (token.op == Operator::OPEN_PAREN)
            {
                stackOperator.push_back(token);
            }

            else if (token.op == Operator::CLOSE_PAREN)
            {
                while (stackOperator.back().op != Operator::OPEN_PAREN)
                {
                    result.push_back(stackOperator.back());
                    stackOperator.pop_back();
                }
                stackOperator.pop_back();
            }

            else
            {
                if (!stackOperator.empty() && operator_precedence(stackOperator.back().op) >= operator_precedence(token.op))
                {
                    result.push_back(stackOperator.back());
                    stackOperator.pop_back();
                    stackOperator.push_back(token);
                } else {
                    stackOperator.push_back(token);
                }
            }
        }
    }

    // on dépile les opérateurs restants
    while (!stackOperator.empty())
    {
        result.push_back(stackOperator.back());
        stackOperator.pop_back();
    }

    for (Token const &token : result)
    {
        if (token.type == TokenType::OPERATOR)
            std::cout << to_string(token.op) << " ";
        else
            std::cout << token.value << " ";
    }

    return result;
}

void calculatriceNPI(std::vector<std::string> elements)
{
    std::vector<Token> tokens = infix_to_npi_tokens(elements[0]);
}

int main()
{
    // Exercice 1
    /*std::string operation;
    std::cout << "Entrez l'operation a evaluer en NPI V1 : ";
    getline(std::cin, operation);
    std::vector<std::string> elements = split_string(operation);
    std::cout << "Resultat : " << npi_evaluate(elements) << std::endl;*/

    // Exercice 2
    /*std::string operation2;
    std::cout << "Entrez l'operation a evaluer en NPI V2 : ";
    getline(std::cin, operation2);
    std::vector<std::string> elements2 = split_string(operation2);
    std::cout << "Resultat : " << npi_evaluate(tokenize(elements2)) << std::endl;*/

    //  Exercice 3
    std::string operation3;
    std::cout << "Conversion en NPI : ";
    getline(std::cin, operation3);
    std::vector<std::string> elements3 = split_string(operation3);
    infix_to_npi_tokens(operation3);
    return 0;
}