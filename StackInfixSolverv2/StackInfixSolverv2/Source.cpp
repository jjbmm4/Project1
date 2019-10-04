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
string evaluate(string input);
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



int main() {
	cout << "Hello world UWU \n";

	cout << "Expression List\n";
	cout << "Expression 1: ";
	string input = "1+2*3 != 4*5  ";
	cout << evaluate(input) << endl;
	cout << "Expression 2: ";
	input = "2+2^2*3 ";
	cout << evaluate(input) << endl;
	cout << "Expression 3: ";
	input = "1==2 ";
	cout << evaluate(input) << endl;
	cout << "Expression 4: ";
	input = "1+3 > 2 ";
	cout << evaluate(input) << endl;
	cout << "Expression 5: ";
	input = "(4>=4) && 0  ";
	cout << evaluate(input) << endl;
	cout << "Expression 6: ";
	input = "(1+2)*3 ";
	cout << evaluate(input) << endl;
	cout << "Expression 7: ";
	input = "++++2-5*(3^2) ";
	cout << evaluate(input) << endl;
	cout << "Expression 8: ";
	input = "----2----5*(3^2) ";
	cout << evaluate(input) << endl;

}


//TODO //pushtostackandcalculate
//INPUT: Raw string input
string evaluate(string input)
{
	string condensedInput = stringCondenser(input);
	cout << condensedInput <<endl;
	string spacedInDigits = stringSpacer(condensedInput);
	return spacedInDigits;
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
		if (isdigit(input[i]) && isdigit(input[i+1])) {//00
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
		else if (isOperator(input[i]) && (isdigit(input[i+1]))) {//10
			outputString = outputString + input[i] + ' ';
		}
		else if (isOperator(input[i]) && (isOperator(input[i + 1]))) {//11
			if ((i == 0||isOperator(input[i - 1])) && (input[i] == input[1 + i])) {
				switch (input[i]) {
				case '-':
					outputString = outputString + 'D' + ' ';
					break;
				case '+':
					outputString = outputString + 'I' + ' ';
					break;
				case '=':
					outputString = outputString + 'E' + ' ';
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
			//case of comparison of <= or >= or !=
			else if (input[i] == '>' && input[i+1] == '=') {
				outputString = outputString + 'G' + ' ';
				i++;
			}
			else if (input[i] == '<' && input[i+1] == '=') {
				outputString = outputString + 'L' + ' ';
				i++;
			}
			else if (input[i] == '!' && input[i + 1] == '=') {
				outputString = outputString + 'N' + ' ';
				i++;
			}
			//end
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
	string operators = "!+-^*/%<>+&|()=";
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
	stack <string> operators;



	return 0;
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

//TODO
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
	case '^': return (pow(a,b));
	case '*': return (a*b);
	case '/': return (a/b);
	case '%': return (a%b);
	case '+': return (a+b);
	case '~': return (a-b);
	case '>': return (a>b);
	case '<': return (a<b);
	case 'G': return (a>=b);
	case 'L': return (a<=b);
	case 'E': return (a==b);
	case 'N': return (a!=b);
	case 'A': return (a&&b);
	case 'O': return (a||b);
	}
}
//OUTPUT: finished math