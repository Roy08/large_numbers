#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool check(string num1, string num2, string symbol) {			//检查数据输入的合法性
	unsigned int i = 0;
	if (num1[0] == '+' || num1[0] == '-')
		i = 1;
	for (; i < num1.length(); i++) {
		if (num1[i]>'9' || num1[i] < '0')
			return false;
	}
	i = 0;
	if (num2[0] == '+' || num2[0] == '-')
		i = 1;
	for (; i < num2.length(); i++) {
		if (num2[i]>'9' || num2[i] < '0')
			return false;
	}
	if (symbol.length() > 1)
		return false;
	else
		if (symbol[0] == '+' || symbol[0] == '-' || symbol[0] == '*' || symbol[0] == '/')
			return true;
		else
			return false;

}

string standardnumber(string num) {										//将输入数据处理一下  只要数字不要符号，首位不为0；
	int length, i = 0, first = 0;
	length = num.length();
	if (num[i] == '+' || num[i] == '-') {
		first++;
		i++;
	}
	for (; i < length - 1; i++) {
		if (num[i] == '0')
			first++;
		else
			break;
	}
	return num.substr(first, num.length());
}

string add(string num_1, string num_2) {										//加法子函数，将两个处理后的数加起来，按位一个个加
	string num_return;
	unsigned int i, l1, l2, l_max, d = 0, l_min;
	l1 = num_1.length();
	l2 = num_2.length();
	l_max = max(l1, l2);
	l_min = min(l1, l2);
	num_return.resize(l_max);
	for (i = 1; i <= l_min; i++) {												//共有的位数
		num_return[l_max - i] = (num_1[l1 - i] - '0' + num_2[l2 - i] - '0' + d) % 10 + '0';
		d = (num_1[l1 - i] - '0' + num_2[l2 - i] - '0' + d) / 10;
	}
	for (; i <= l_max; i++) {
		if (l1 > l2) {
			num_return[l_max - i] = (num_1[l1 - i] - '0' + d) % 10 + '0';
			d = (num_1[l1 - i] - '0' + d) / 10;
		}
		else {
			num_return[l_max - i] = (num_2[l2 - i] - '0' + d) % 10 + '0';
			d = (num_2[l2 - i] - '0' + d) / 10;
		}
	}
	if (d == 1)																	//进位
		num_return = '1' + num_return;
	return num_return;
}
string sub(string num_1, string num_2) {										//减法，输出前一个数减后一个数 输出有正负
	unsigned int  lmin, lmax, i;
	int d = 0, c = 0;
	string num_return;
	lmax = num_1.length();
	lmin = num_2.length();
	if (lmax < lmin)															//保证num_1比num_2大，否则调换取负
		return '-' + sub(num_2, num_1);
	if (lmin == lmax)
		if (num_1 < num_2)
			return '-' + sub(num_2, num_1);
		else
			if (num_1 == num_2)
				return "0";
	num_return.resize(lmax);
	for (i = 1; i <= lmin; i++) {
		c = num_1[lmax - i] - num_2[lmin - i] + d;
		if (c < 0) {
			d = -1;
			num_return[lmax - i] = c + 10 + '0';
		}
		else {
			d = 0;
			num_return[lmax - i] = c + '0';

		}
	}
	for (; i <= lmax; i++) {
		c = num_1[lmax - i] - '0' + d;
		if (c < 0) {
			d = -1;
			num_return[lmax - i] = c + 10 + '0';
		}
		else {
			d = 0;
			num_return[lmax - i] = c + '0';
		}
	}
	return standardnumber(num_return);
}

string multi(string num_1, string num_2) {											//乘法，输出两个处理后数的乘积，没有符号
	int i = 0, j = 0, l1, l2, length, d = 0;										//这算法实在是有些慢，中间判别太多了编完才反应过来
	string num_return;
	l1 = num_1.length();
	l2 = num_2.length();
	length = l1 + l2 - 1;
	num_return.resize(length);
	for (i = 0; i < length; i++) {
		num_return[i] = 0;
		//for (j = max(0, i - l2 + 1); j <= min(i,l1-1); j++) {
		//	num_return[i] = num_return[i] + (num_1[j]-'0') *( num_2[i - j]-'0');
		//	if (i - j == 0)
		//		break;
		//}
		for (j = i - l2 + 1; j <= i; j++) {										//类似多项式乘法，求出各项的系数，最后再进位
			if (j < 0)
				j = 0;
			num_return[i] = num_return[i] + (num_1[j] - '0')*(num_2[i - j] - '0');
			if (i - j == 0 || j == l1 - 1)
				break;
		}
	}
	for (i = 0; i < length; i++) {												//进位
		num_return[length - i - 1] = num_return[length - i - 1] + d;
		d = num_return[length - i - 1] / 10;
		num_return[length - i - 1] = (num_return[length - i - 1]) % 10 + '0';
	}
	if (d > 0) {
		num_return = '1' + num_return;
		num_return[0] = d + '0';
	}
	return num_return;

}


string divv(string num_1, string num_2) {										//除法，计算num_1除以num_2，输出商及余数，中间空格
	string num_return, num_temp;
	num_return.resize(num_1.length());
	int lmax, lmin, d = 0, i, j, r;
	lmax = num_1.length();
	lmin = num_2.length();
	if (lmax < lmin)
		return "0";
	if (lmin == lmax)
		if (num_1 < num_2)
			return "0";
	while (num_1.length()>num_2.length()) {									//将num_2补0加长到和num_1相同
		num_2 = num_2 + '0';
	}
	i = 0;
	while (num_2.length() >= lmin) {
		d = 0;
		while ((num_1.length() == num_2.length() && num_1 >= num_2) || num_1.length()>num_2.length()) {   //计算每次相减的次数，即时商，num_1自身迭代，最终即是余数
			d = d + 1;
			num_1 = sub(num_1, num_2);
		}
		num_return[i] = d + '0';
		i = i + 1;
		num_2 = num_2.substr(0, num_2.length() - 1);												//num_2降位
	}
	return num_return.substr(0, i) + ' ' + num_1;

}



int main() {
	//string num_1(1000, '1'), num_2(1, '1'), symbol, num_return;
	string num_1, num_2, symbol, num_return;

	while (getline(cin, num_1)) {														//输入两个数，一个符号
		getline(cin, num_2);
		getline(cin, symbol);
		if (check(num_1, num_2, symbol) == 0) {										//检查输入合法性
			cout << "Error input" << endl;
			continue;
		}
		if (symbol[0] == '+') {														//如果是加，则分类计算
			if (num_1[0] != '-'&&num_2[0] != '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = add(num_1, num_2);
			}
			if (num_1[0] == '-'&&num_2[0] == '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = add(num_1, num_2);
				num_return = '-' + num_return;
			}
			if (num_1[0] == '-'&&num_2[0] != '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = sub(num_2, num_1);
			}
			if (num_1[0] != '-'&&num_2[0] == '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = sub(num_1, num_2);
			}
		}
		if (symbol[0] == '-') {																//减法同样分类
			if (num_1[0] != '-'&&num_2[0] != '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = sub(num_1, num_2);
			}
			if (num_1[0] == '-'&&num_2[0] == '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = sub(num_2, num_1);
			}
			if (num_1[0] == '-'&&num_2[0] != '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = add(num_2, num_1);
				num_return = '-' + num_return;
			}
			if (num_1[0] != '-'&&num_2[0] == '-') {
				num_1 = standardnumber(num_1);
				num_2 = standardnumber(num_2);
				num_return = add(num_1, num_2);
			}
		}
		if (symbol[0] == '*') {											//乘法   记录符号变化
			int s_temp = 0;
			if (num_1[0] == '-') s_temp = s_temp + 1;
			if (num_2[0] == '-') s_temp = s_temp + 1;
			num_1 = standardnumber(num_1);
			num_2 = standardnumber(num_2);
			num_return = multi(num_1, num_2);
			if (s_temp == 1)  num_return = '-' + num_return;

		}
		if (symbol[0] == '/') {											//除法
			int s_temp = 0;
			if (num_1[0] == '-') s_temp = s_temp + 1;
			if (num_2[0] == '-') s_temp = s_temp + 1;
			num_1 = standardnumber(num_1);
			num_2 = standardnumber(num_2);
			if (num_2[0] == '0') {
				cout << "Error input" << endl;
				system("pause");
				return 0;
			}

			num_return = divv(num_1, num_2);
			num_return = standardnumber(num_return);
			if (s_temp == 1)  num_return = '-' + num_return;

		}
		cout << num_return << endl;
		//system("pause");
	}
	return 0;
}





