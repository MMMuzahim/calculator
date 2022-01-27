#include <iostream>
#include <sstream>
#include <stack>
#include <iomanip>

using namespace std;

//форматирование входной строки: выделение пробелами операторов и чисел
string format(const string& s) {
    string temp = "";
    bool last_is_number = false;
    for (size_t i = 0; i < s.size(); i++) {
        switch (s[i]) {
        case '*':
        case '/':
        case '+':
        case '(':
        case ')':
            temp = temp + ' ' + s[i] + ' ';
            last_is_number = false;
            break;
        
        case '-':
            temp = temp + ' ' + s[i];
            if (last_is_number) {
                temp = temp + ' ';
                last_is_number = false;
            } else {
                last_is_number = true;
            }
            break;

        case ',':
            temp = temp + '.';
            break;

        default:
            temp = temp + s[i];
            last_is_number = true;
            break;
        }
    }

    return temp;
}

//проверка строки на число
bool is_number(const string& s) {
    size_t i = 0;
    if (s[i] == '-' && s.size() > 1) ++i;
    while (i != s.size() && (isdigit(s[i]) || s[i] == '.')) ++i;
    return !s.empty() && i == s.size();
}

//преобразует тип string в double
double string_to_double(const string& s) {
    stringstream ss(s);
    double result;
    ss >> result;
    return result;
}

//функция, которая производит расчеты
bool maths(stack <double>& stack_number, stack <char>& stack_operation) {
    double a = stack_number.top();
	stack_number.pop();
	double b;
    
    switch (stack_operation.top()) {
    case '+':
        b = stack_number.top();
        stack_number.pop();
        stack_number.push(a + b);
        stack_operation.pop();
        break;

    case '-':
        if (stack_number.size() > 0) {
            b = stack_number.top();
            stack_number.pop();
        } else {
            b = 0;
        }
        stack_number.push(b - a);
        stack_operation.pop();
    break;

    case '*':
        b = stack_number.top();
        stack_number.pop();
        stack_number.push(a * b);
        stack_operation.pop();
        break;

    case '/':
        b = stack_number.top();
        if (a == 0) {
            cerr << "Деление на 0" << endl;
                return false;
            }
        else {
            stack_number.pop();
            stack_number.push(b / a);
            stack_operation.pop();
            break;
        }
    default:
        cerr << "Ошибка при вычислении" << endl;
        return false;
        break;
    }
	return true;
}

//функция возвращает приоритет операции
int get_operation_rang(const char& operation) {
	if (operation == '+' || operation == '-')
        return 1;
	if (operation == '*' || operation == '/')
        return 2;
	return 0;
}

bool check_invalid_argument(const string& s) {
    for (const char& c : s) {
        switch (c) {
        case '0': break;
        case '1': break;
        case '2': break;
        case '3': break;
        case '4': break;
        case '5': break;
        case '6': break;
        case '7': break;
        case '8': break;
        case '9': break;
        case '-': break;
        case '+': break;
        case '*': break;
        case '/': break;
        case '(': break;
        case ')': break;
        case '.': break;

        default: return false;
        }
    }
    return true;
}

string calculator(string s)
{
    string result;
    s = format(s);

    stringstream ss(s);
    string item;
    stack<double> stack_number;
    stack<char> stack_operation;
    while (ss >> item) {
        if (!check_invalid_argument(item)) {
            result = "некорректный ввод, строка содержит недопустимое выражение " + item;
            return result;
        }
        if (is_number(item)) {
            stack_number.push(string_to_double(item));
            continue;
        }
        if (item == "+" || item == "-" || item == "*" || item == "/") {
            char operation = item[0];
            if (stack_operation.size() == 0) {
                stack_operation.push(operation);
                continue;
            }
            if (stack_operation.size() != 0 && get_operation_rang(operation) > get_operation_rang(stack_operation.top())) {
                stack_operation.push(operation);
                continue;
            }
            if (stack_operation.size() != 0 && get_operation_rang(operation) <= get_operation_rang(stack_operation.top())) {
                if (!maths(stack_number, stack_operation)) {
					return "некорректный ввод";
				}
                stack_operation.push(operation);
				continue;
            }
        }
        if (item == "(") {
			stack_operation.push(item[0]);
			continue;
		}
		if (item == ")") {
			while (stack_operation.top() != '(') {
				if (!maths(stack_number, stack_operation)) {
					return "некорректный ввод";
				}
			}
			stack_operation.pop();
			continue;
		}
    }

    while (stack_operation.size() != 0) {
		if (!maths(stack_number, stack_operation)) {
			return "некорректный ввод";
		}
	}
    
    ostringstream streamObj;
    streamObj << setprecision(2);
    streamObj << stack_number.top();
    result = streamObj.str();
    return result;
}

/*int main() {
    string s;
    getline(cin, s);
    cout << calculator(s) << endl;
    return 0;
}*/
