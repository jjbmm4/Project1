#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

/*
Character Substitution Chart
-- D
++ I
== E
&& A
|| O
>= G
<= L
!= N (totally forgot about this one, lol)
- (subtraction minus) ~
*/


//INPUT: Raw string input
int evaluate(string input);
//OUTPUT: Finished Problem

//INPUT:Raw string input
string stringCondenser(string input);
//OUTPUT:String with no spaces

//INPUT:Condensed String Input
string stringSpacer(string input);
//OUTPUT:puts spaces in the right places

//INPUT: Char that might be operator
bool isOperator(char input);
//OUTPUT: T/F if it is operator

//INPUT: Formatted String with character Substitiuion
int pushToStacksAndCalculate(string input);
//OUTPUT: Finished Problem

//INPUT: Char of oppertion
int precedenceLevel(char input);
//OUTPUT: Power level

//INPUT: 1-2 numbers and an job to do
int useOperator(int a, char operand, int b = 0);
//OUTPUT: finished math

//INPUT: Formatted String
void errorWithFormat(string input);
//OUTPUT: Tested Formatted String


int main() {



	cout << "Expression 1: ";
	string input = "++++2-5*(3^2)";
	cout << evaluate(input) << endl;


}


//TODO //pushtostackandcalculate
//INPUT: Raw string input
int evaluate(string input)
{
	string condensedInput = stringCondenser(input);
	cout << condensedInput << endl;
	string spacedInDigits = stringSpacer(condensedInput);
	cout << spacedInDigits << endl;

	string testerString = stringCondenser(spacedInDigits);
	errorWithFormat(testerString);

	int a = pushToStacksAndCalculate(spacedInDigits);
	return a;
}
//OUTPUT:Finished Problem


//COMPLETE
//INPUT:Raw string input
string stringCondenser(string input) {
	string outputString = "";
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {
			outputString += input[i];
		}
	}
	return outputString;
}
//OUTPUT:String with no spaces

//COMPLETE
//INPUT:Condensed String Input
string stringSpacer(string input) {
	string outputString;
	for (int i = 0; i < input.size(); i++) {
		if (isdigit(input[i]) && isdigit(input[i + 1])) {//00
			outputString += input[i]; //no space
		}
		else if (isdigit(input[i]) && (isOperator(input[i + 1]))) {//01
			if (input[i + 1] == '-') {
				outputString = outputString + input[i] + ' ' + '~' + ' ';
				i++;
			}
			else {
				outputString = outputString + input[i] + ' '; //yes space
			}
		}

		else if (isOperator(input[i]) && (isdigit(input[i + 1]))) {//10
			outputString = outputString + input[i] + ' ';
		}

		else if (isOperator(input[i]) && (isOperator(input[i + 1]))) {//11
		//case of comparison of <= or >= or != or ==
			if (input[i] == '>' && input[i + 1] == '=') {
				outputString = outputString + 'G' + ' ';
				i++;
			}
			else if (input[i] == '<' && input[i + 1] == '=') {
				outputString = outputString + 'L' + ' ';
				i++;
			}
			else if (input[i] == '!' && input[i + 1] == '=') {
				outputString = outputString + 'N' + ' ';
				i++;
			}
			else if (input[i] == '=' && input[i + 1] == '=') {
				outputString = outputString + 'E' + ' ';
				i++;
			}
			//end	
			else if ((i == 0 || isOperator(input[i - 1])) && (input[i] == input[1 + i])) {
				switch (input[i]) {
				case '-':
					outputString = outputString + 'D' + ' ';
					break;
				case '+':
					outputString = outputString + 'I' + ' ';
					break;
				case '&':
					outputString = outputString + 'A' + ' ';
					break;
				case '|':
					outputString = outputString + 'O' + ' ';
					break;
				}
				i++;
			}

			else {
				outputString = outputString + input[i] + ' ';
			}
		}
		else {
			outputString += input[i]; //no space
		}
	}
	return outputString;
}
//OUTPUT:puts spaces in the right places

//COMPLETE(could be better)
//INPUT: Char that might be operator
bool isOperator(char input) {
	string operators = "!+-^*/%<>+&|()=DIEAOGLN";
	for (int i = 0; i < operators.size(); i++) {
		if (input == operators[i]) {
			return true;
		}
	}
	return false;
}
//OUTPUT: T/F if it is operator

//TODO
//INPUT: Formatted String with character Substitiuion
int pushToStacksAndCalculate(string input) {
	stack <int> numbers;
	stack <char> operators;
	int x, y;
	char op;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			continue;
		}
		else if (input[i] == '(') {
			operators.push(input[i]);
		}
		else if (isdigit(input[i])) {
			int val = 0;
			while (i < input.length() &&
				isdigit(input[i]))
			{
				val = (val * 10) + (input[i] - '0');
				i++;
			}

			numbers.push(val);
		}

		else if (input[i] == ')') {
			while (operators.top() != '(' && (operators.size() != 0)) {
				op = operators.top();
				operators.pop();
				x = numbers.top();
				numbers.pop();
				y = numbers.top();
				numbers.pop();
				numbers.push(useOperator(y, op, x));
			}
			if (operators.empty()) {
				cout << "Expression can't start with a closing parenthesis @0";
				return -1;
			}
			operators.pop();
		}
		else {
			if (precedenceLevel(input[i]) == 8) {
				operators.push(input[i]);
				continue;

			}
			else {
				while (!operators.empty() && (precedenceLevel(operators.top()) >= precedenceLevel(input[i]))) {
					if (precedenceLevel(operators.top()) == 8) {
						op = operators.top();
						operators.pop();
						x = numbers.top();
						numbers.pop();
						numbers.push(useOperator(x, op));
					}
					else {
						op = operators.top();
						operators.pop();
						x = numbers.top();
						numbers.pop();
						y = numbers.top();
						numbers.pop();
						numbers.push(useOperator(y, op, x));
					}
				}
				operators.push(input[i]);
			}
		}
	}
	while (!operators.empty()) {

		op = operators.top();
		operators.pop();
		if (precedenceLevel(op) == 8) {
			y = numbers.top();
			numbers.pop();
			numbers.push(useOperator(y, op));
		}
		else {
			x = numbers.top();
			numbers.pop();
			y = numbers.top();
			numbers.pop();
			numbers.push(useOperator(y, op, x));
		}
	}

	int correct = numbers.top();
	numbers.pop();
	return correct;
}
//OUTPUT: Finished Problem

//COMPLETE
//INPUT: Char of oppertion
int precedenceLevel(char input) {

	if (input == '!' || input == 'I' || input == 'D' || input == '-') {
		return 8;
	}
	else if (input == '^') {
		return 7;
	}
	else if (input == '*' || input == '/' || input == '%') {
		return 6;
	}
	else if (input == '+' || input == '~') {
		return 5;
	}
	else if (input == '>' || input == '<' || input == 'G' || input == 'L') {
		return 4;
	}
	else if (input == 'E' || input == 'N') {
		return 3;
	}
	else if (input == 'A') {
		return 2;
	}
	else if (input == 'O') {
		return 1;
	}
	return 0;
}
//OUTPUT: Power level

//COMPLETE
//INPUT: 1-2 numbers and an job to do
int useOperator(int a, char operand, int b) {
	switch (operand) {
	case '!':
		if (a == 0) {
			return 1;
		}
		else {
			return 0;
		}
	case 'I': return (a + 1);
	case 'D': return (a - 1);
	case '-': return (-a);
	case '^': return (pow(a, b));
	case '*': return (a * b);
	case '/': return (a / b);
	case '%': return (a % b);
	case '+': return (a + b);
	case '~': return (a - b);
	case '>': return (a > b);
	case '<': return (a < b);
	case 'G': return (a >= b);
	case 'L': return (a <= b);
	case 'E': return (a == b);
	case 'N': return (a != b);
	case 'A': return (a && b);
	case 'O': return (a || b);
	}
}
//OUTPUT: finished math


//INPUT:formatted string
void errorWithFormat(string input) {


	for (int i = 0; i < input.size(); i++) {

		if (input[0] == ')') {
			cout << "Expression cant start with a closing parenthesis";
			exit(0);
			system("pause");
		}
		else if (isOperator(input[0])) {
			if (input[0] != '(') {
				if (precedenceLevel(input[0]) < 8) {
					cout << "Cant start with a binary operator" << endl;
					exit(0);
					system("pause");
				}
			}
		}


		if (input[i] == '/') {
			if (input[i + 1] == '0') {
				cout << "devide by zero error";
				exit(0);
				system("pause");
			}
		}

		if (input[i] == '(' || input[i] == ')' || input[i + 1] == '(' || input[i + 1] == ')') {
			continue;
		}
		else if (isOperator(input[i])) {

			if (isOperator(input[i + 1])) {

				if (precedenceLevel(input[i]) < 8) {
					if (precedenceLevel(input[i + 1]) < 8) {
						cout << "Cant have two binary operators in a row" << endl;
						exit(0);
						system("pause");
					}
				}
				else if ((precedenceLevel(input[i]) == 8) && (precedenceLevel(input[i + 1]) < 8)) {
					cout << "A unary operand can’t be followed by a binary operator" << endl;
					exit(0);
					system("pause");
				}
			}

		}



	}

}

//OUTPUT: i couldnt come up with a good way to handle errors well. this is the best i could think of. sorry!

