#include <iostream>
#include <string>
#include <map>

using namespace std;

struct item
{
    //string val
    string value;
    //next item
    item *next;
};

struct stack
{
    //top item
    item *top;
    //current count of items
    int size;
    //constructor
    stack()
    {
        //init top and top->next item
        top = new item;
        top->next = new item;
        //init size to 0
        size = 0;
    }

    void push(string val)
    {
        item *toAdd = new item;
        toAdd->value = val;
        toAdd->next = top;
        top = toAdd;
        size++;
    }

    string pop()
    {
        if (size == 0)
        {
            return "";
        }
        string result = top->value;
        top = top->next;
        size--;
        return result;
    }

    //check the value of top item
    string peek()
    {
        if (size == 0)
        {
            return "";
        }
        return top->value;
    }

    //pop all the items
    void clean()
    {
        while (size > 0)
        {
            pop();
        }
    }
};

//infix_to_postfix function
const char *infix_to_postfix(char *infixstr)
{
    //init a priority map/dictionary
    map<char, int> priorities;
    priorities['+'] = 1;
    priorities['-'] = 1;
    priorities['*'] = 2;
    priorities['/'] = 2;
    priorities['^'] = 3;

    //convert ctring to string
    string infix = infixstr;
    //init postfix str
    string postfix = "";
    //init a tmp var for char-string covert
    string tmp = "";
    //init stack
    stack *s = new stack();
    for (char &c : infix)
    {
        //filter invalid space chars
        if (c == ' ')
        {
            continue;
        }
        //determine if it is an operator
        if (priorities[c] == 0 && c != '(' && c != ')')
        {
            postfix += c; 
            continue;
        }
        if (s->size == 0 || c == '(')
        {
            tmp = c;
            s->push(tmp);
        }
        else if (c == ')')
        {
            while (s->peek() != "(")
            {
                postfix += s->pop();
            }
            s->pop();
        }
        else
        {
            //push to stack according to the priorities dictionary
            while (priorities[c] <= priorities[s->peek()[0]])
            {
                postfix += s->pop();
            }
            tmp = c;
            s->push(tmp);
        }
    }
    //final step, pop all the items to the end of postfix string
    while (s->size > 0)
    {
        postfix += s->pop();
    }
    return postfix.c_str();
}

//postfix_to_infix function
const char *postfix_to_infix(char *postfixstr)
{
    //init a operator check dictionary
    map<char, bool> priorities;
    priorities['+'] = true;
    priorities['-'] = true;
    priorities['*'] = true;
    priorities['/'] = true;
    priorities['^'] = true;
    string postfix = postfixstr;
    string infix = "";
    string tmp = "";
    //init stack
    stack *s = new stack();
    for (char &c : postfix)
    {
        //filter invalid space chars
        if (c == ' ')
        {
            continue;
        }
        //determine if it is an operator, if not, push to stack directly
        if (!priorities[c])
        {
            tmp = c;
            s->push(tmp);
        }
        else
        {
            //if the stack's size is less than 2, the expression is invalid, return NULL directly
            if (s->size < 2)
            {
                printf("%s\n", "invalid postfix expression");
                return NULL;
            }
            //pop the top two items of the stack, insert the operator between than close them with brakets
            string top = s->pop();
            string top_next = s->pop();
            tmp = "(" + top_next + c + top + ")";
            //push the composed expression to the stack
            s->push(tmp);
        }
    }
    infix = s->pop();
    return infix.c_str();
}

int main()
{
    printf("%s\n", infix_to_postfix("((A-B)/((D+E)*F))"));
    printf("%s\n", postfix_to_infix("A B * C / F G D + * F H - I ^ /+"));
    //"ABC*+DE/F*-"
    //"AB-DE+F*/"
    //"ABC*+D+"
    return 0;
}