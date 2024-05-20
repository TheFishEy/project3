#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>

// Patrick Hung
//CWID: 860865329

class Stack {
    private:
        void push(std::vector<std::pair<char, int>>& a, std::pair<char, int> b) {
            a.push_back(b);
        }
        std::pair<char, int> top(std::vector<std::pair<char, int>>& a) {
            if (a.empty()) {
                return std::make_pair('\0', -1);
            }
            return a.back();
        }
        void pop(std::vector<std::pair<char, int>>& a) {
            if (!a.empty()) {
                a.pop_back();
            }
        }
        bool match(char a, char b) {
            return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
        }
        bool isOpen(char a) {
            return a == '(' || a == '[' || a == '{';
        }
        bool isClose(char a) {
            return a == ')' || a == ']' || a == '}';
        }
    public:
        void validPara(std::string pairs) {
            std::vector<std::pair<char, int>> parent_stack;

            for (int i = 0; i < pairs.length(); i++) {
                if (isOpen(pairs[i])) {
                    push(parent_stack, std::make_pair(pairs[i], i));
                } else if (isClose(pairs[i])) {
                    if (!parent_stack.empty() && match(top(parent_stack).first, pairs[i])) {
                        pop(parent_stack);
                    } else {
                        std::cout << "invalid" << std::endl;
                        return;
                    }
                }
            }
            std::cout << (parent_stack.empty() ? "valid" : "invalid") << std::endl;
        }

        int indexError(std::string pairs) {
            std::vector<std::pair<char, int>> parent_stack;

            for (int i = 0; i < pairs.length(); i++) {
                if (isOpen(pairs[i])) {
                    push(parent_stack, std::make_pair(pairs[i], i));
                } else if (isClose(pairs[i])) {
                    if (!parent_stack.empty() && match(top(parent_stack).first, pairs[i])) {
                        pop(parent_stack);
                    } else {
                        return i;
                    }
                }
            }

            return parent_stack.empty() ? -1 : parent_stack.back().second;
        }

        void minPara(std::string pairs) {
            std::vector<std::pair<char, int>> parent_stack;

            for (int i = 0; i < pairs.length(); i++) {
                if (isOpen(pairs[i])) {
                    push(parent_stack, std::make_pair(pairs[i], i));
                } else if (isClose(pairs[i])) {
                    if (!parent_stack.empty() && match(top(parent_stack).first, pairs[i])) {
                        pop(parent_stack);
                    } else {
                        push(parent_stack, std::make_pair(pairs[i], i));
                    }
                }
            }

            std::cout << "Min: " << parent_stack.size() << std::endl;
        }

        void scorePara(std::string pairs) {
            int score = 0;
            std::vector<std::pair<char, int>> parent_stack;

            for (int i = 0; i < pairs.length(); i++) {
                if (isOpen(pairs[i])) {
                    push(parent_stack, std::make_pair(pairs[i], i));
                } else if (isClose(pairs[i])) {
                    if (!parent_stack.empty() && match(top(parent_stack).first, pairs[i])) {
                        pop(parent_stack);
                        score++;
                    } else {
                        push(parent_stack, std::make_pair(pairs[i], i));
                    }
                }
            }

            std::cout << "Balance: " << score << std::endl;
        }
};

class Queue {
    private:
        std::vector<std::string> queue;
        std::string reverse(std::string s) {
            std::reverse(s.begin(), s.end());
            return s;
        }
    public:
        void enqueue(std::string s) {
            int n = s.length();
            for (int i = 0; i < n; i += 8) {
                std::string chunk = s.substr(i, 8);
                queue.push_back(reverse(chunk));
            }
        }

        void processMsg() {
            std::string message;
            while (!queue.empty()) {
                std::string chunk = queue.front();
                queue.erase(queue.begin());
                message += reverse(chunk);
            }
            std::cout << message << std::endl;
        }
};

// Remove comments before testing and do not change anything in main function
int main(){
    Stack s1;
    s1.validPara("(([]))");
    s1.minPara("(([]))");
    s1.scorePara("(([]))");
    s1.validPara("(([])");
    std::cout<<s1.indexError("(([))")<<std::endl;
    s1.minPara("(([])");
    s1.validPara("(([{}))");
    std::cout<<s1.indexError("(([[}])")<<std::endl; // This should be index 7, there is a missing ) at the very beginning
    s1.minPara("(([{}))");
    s1.scorePara("(([{}))");
    std::cout<<s1.indexError("({}[]()[)")<<std::endl;
    s1.validPara("(([))");
    s1.minPara("(([))");
    std::cout<<s1.indexError("[({)]")<<std::endl;
    s1.validPara("(([{[{({})}]}]))");
    s1.minPara("(([{[{({})}]}]))");
    s1.scorePara("(([{[{({})}]}]))");
    s1.validPara("(([[{[{({})}]))");
    s1.validPara("(([[{[{({})}]}])]))");
    s1.scorePara("(([[{[{({})}]}])]))");
    std::cout<<s1.indexError("(([[{{({})]}])]))")<<std::endl;
    s1.validPara("(())");
    s1.validPara("(())");
    s1.validPara("void function(){}");
    s1.scorePara("void function(){}");
    s1.validPara("void function(");
    s1.minPara("void function(");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.scorePara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}");
    s1.validPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    s1.minPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    std::cout<<s1.indexError("void function(std::string expre){if(expre){return 1;else{return 0;")<<std::endl;
    Queue q1;
    q1.enqueue("This is a secure message.");
    q1.processMsg();
    q1.enqueue("The product I received is damaged. What should I do?");
    q1.processMsg();
    q1.enqueue("I need assistance with setting up my new device");
    q1.processMsg();
    q1.enqueue("The website is not loading properly on my browser.");
    q1.processMsg();
    q1.enqueue("I accidentally placed the wrong order. Can it be canceled?");
    q1.processMsg();
    q1.enqueue("This is your project3. Have a happy thanksgiving!!! Hahaha");
    q1.processMsg();
    q1.enqueue("I forgot my password and can't reset it. Help, please! Do you provide technical support for mobile devices?");
    q1.processMsg();
    q1.enqueue("The software update is causing issues on my computer. The response time on your website is very slow.");
    q1.processMsg();
    return 0;
}
