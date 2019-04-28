#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template<typename type>
type decode(type s){
	type retval;
	retval.resize(s.size());

	int diagonals = (-1 + int(sqrt(1 + 8 * s.size()))) / 2;
    // diagonals - количество полных диагоналей
    int back = s.size() - (diagonals * (diagonals + 1) / 2);
    // back - количество символов в неполной диагонали
    bool backtop = (diagonals + 1) % 2 == 0;
    // backtop - заполняется ли последняя диагональ сверху
    

    int line = 0, change = 0;
    // line - вертикальная координата
    // change - горизонтальная координата
    for(int i = 0; i < s.size(); i++) {
    	int index = change 
    		+ (diagonals + 1) * 
    		(backtop ? min(back, line) : max(back + line - diagonals - 1, 0)) 
    		+ diagonals * 
    		(backtop ? max(line - back, 0) : min(line, diagonals + 1 - back)) 
    		- (line - 1) * line / 2;
    	// index - индекс символа на данной позиции в декодируемой строке

    	retval[i] = s[index];

    	if((line + change) % 2 == 0) {
			if(line > 0) line--;
			change++;
		}
		else {
			if(change > 0) change--;
			line++;
		}
		// проходимся по диагоналям
    }

    return retval;
}

template<typename type>
type encode(type s){
	type retval;
	retval.resize(s.size());

	int line = 0, change = 0; 
    // line - вертикальная координата
    // change - горизонтальная координата

    for(int i = 0; i < s.size();) {
        int diagonal = line + change;
        // diagonal - номер диагонали
        int index = (diagonal + 1) * diagonal / 2 + 
        			(diagonal % 2 == 0 ? change : line);
        // index - индекс символа с этими координатами в исходной строке
        // (diagonal + 1) * diagonal / 2 - сумма натурального ряда
        // diagonal % 2 == 0 - начинается заполнение диагонали сверху или снизу
        // change : line - смещение в диагонали

        if(index < s.size()) {
            retval[i++] = s[index];
            change++;
        }
        else {
            line++;
            change = 0;
        }
        // проходимся построчно
    }
    return retval;
}

void help(string name){
	cout<<"Usage: "<<endl
		<<name<<" <encoding string> "<<endl
		<<name<<" -d <decoding string> "<<endl;
}

int main(int argc, char* argv[])
{
    if(argc == 1 || argc > 3) {
    	help(string(argv[0]));
    }
    else if(argc == 2) {
    	cout<<encode(string(argv[1]))<<endl;
    }
    else {
    	if(string(argv[1]) == "-d") 
    		cout<<decode(string(argv[2]))<<endl;
    	else
    		help(argv[0]);
    }
}