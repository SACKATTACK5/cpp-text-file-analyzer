#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#define NSQUARE(x) (x*x)
#define M 5
using namespace std;
/* *****project description***** */
/*classes:
rfilese : class for read files
wfiles : class for write files
WordList : a helping class for rfilese
*/
/*rfilese class:
Attributes:
path : the path of the file the user gives
rfile : the file we want to read
cop : used to create eddited file without any marks and ready to use with the wordlist class
copi : also helps with creating the eddited file.
Methods:
1.simple constructor and destructor
2.get_path : gets the file path from the user and store it in the variable path
3.printALLlines : prints the text file
4.num_of_lines : counts the number of lines in the file
5.biggest_line : prints the biggest line
6.smallest_line: prints the smallest line
8.printFrom : print s from a specefic line
9.file_size : computes the file size
10.longest_word : prints the word with the most characters
*/
/*WordList class: this class is used for tasks related to word occurrence
1.count : takes a list of unique words and counts them
2.occure : returns how many time a word occured in the file
3.create_unique : creats a list of unique words in the file
4.create_arr : create an array of words and how many each one occured
5.selSort : sort the words from the most to the least repeated
6.MostRepeated : prints the 5 most repeated words
*/
/*wfiles class:the class is used to write or append to files.
*/
class rfilese {
    char* path;
    ifstream rfile;
    ofstream cop;
    ifstream copi;
public:
    rfilese() {
        path = new char[100]; 
    }
    ~rfilese() {
        delete[] path; 
    }

    void get_path() {
        cout << "enter the file path:\n";
        //cin.ignore();
        cin.getline(path, 100);
        rfile.open(path);
        cout<<"trying...\n";
        if (!rfile) {
            cerr << "wrong path OR the file doesn't exist\n";
            exit(1);
        }
    }

    void printALLlines() {
        string buf;
        while (getline(rfile, buf)) {
            cout << buf << endl;
        }
        rfile.clear();  
        rfile.seekg(0); 
    }

    int num_of_lines() {
        int l = 0;//stores the number of lines
        string buf;//stores the current line
        while (getline(rfile, buf)) {
            l++;
        }
        rfile.clear();// clears the error flag
        rfile.seekg(0);//returns to the start of the file
        return l;
    }

    void biggest_line() {
        int lmax = 0;//the size of the biggest line
        int ln = 0;//the size of the current line
        string buf;//the current line
        string bufm;//the biggest line
        while (getline(rfile, buf)) {
            ln = buf.length();
            if (ln > lmax) {
                bufm = buf;
                lmax = ln;
            }
        }
        cout << "The biggest line is \"" << bufm << "\" with " << lmax << " characters.\n";
        rfile.clear();
        rfile.seekg(0);
    }

    void smallest_line() {
        int lmin = 10000;//size of smallest line
        string buf;//current line
        string bufm;//smallest line
        while (getline(rfile, buf)) {
            int ln = buf.length();
            if (ln < lmin) {
                bufm = buf;
                lmin = ln;
            }
        }
        cout << "The smallest line is \"" << bufm << "\" with " << lmin << " characters.\n";
        rfile.clear();
        rfile.seekg(0);
    }

    bool printFrom(int l) {
        if (l <= 0) {
            cout << "Invalid line number.\n";
            return false;
        }
        int n = 0;
        string buf;
        while (getline(rfile, buf)) {//skip the lines before the starting point
            n++;
            if (n >= l) {
                cout << buf << endl;
            }
        }
        rfile.clear();
        rfile.seekg(0);
        if (l > n) {
            cout << "Invalid line number.\n";
            return false;
        }
        return true;
    }

    double file_size(int n) {
        rfile.seekg(0, ios::end);
        double nbytes = rfile.tellg();
        rfile.seekg(0);

        if (n == 1) {
            return nbytes;
        } else if (n == 2) {
            return nbytes / 1024;
        } else if (n == 3) {
            return nbytes / NSQUARE(1024);
        }
        return 0;
    }

    void build_copy() {
        copi.open(path, ios::in);
        cop.open("d:/copy.txt", ios::out);
        char c;
        while (copi.get(c)) {
            if (!isalpha(c))
                cop << ' ';
            else
                cop << c;
        }
        copi.close();
        cop.close();
    }//preparing the copy that we will use

    void longest_word() {
    	copi.open("d:/copy.txt",ios::out);
        string s, s1;//s for current s1 for biggest
        int l;//current word size
		int l1 = 0;//biggest word size
        while (copi>>s){
            l = s.length();
            if (l > l1) {
                l1 = l;
                s1 = s;
            }
            copi.get();
        }
        cout << "The longest word is \"" << s1 << "\" with " << l1 << " characters.\n";
        copi.seekg(0);
        copi.close();
    }

    int removing() {//deleting the copy we used
        return remove("d:/copy.txt");
    }

    void closeF() {//closing the file
        rfile.close();
    }

    friend class WordList;
};

class WordList {
    struct node {
        int occured;
        string word;
        node* next;
    };
	struct element{
		int occ;
		string wor;
	};
public:
    int count(node* head) {
        node* p = head;//the list of unique words
        int i = 0;//the number of the unique words in the file
        while (p) {
            i++;
            p = p->next;
        }
        return i;
    }
    int occure(rfilese& f, string w) {
        f.copi.open(f.path);
        string chk;//a string to read the words in the file
        node* wo = new node;//counts the occurrence of this word
        wo->word = w;
        wo->occured = 0;
        wo->next = nullptr;
        while (f.copi >> chk) {
            if (lower(chk) == lower(w)) {//check if the word in the file matches the searched one
                wo->occured++;
            }
        }
        int num = wo->occured;
        delete wo;
        f.copi.close();
        return num;
    }

    bool IsinList(node* h, string s) {
        node* n = h;
        while (n) {
            if (n->word == s) {
                return true;
            }
            n = n->next;
        }
        return false;
    }//search if the new word need to be added to the list of unique words
    void create_unique(rfilese& f) {
    	//f.copi.close();
    	string k;
   		f.copi.open("d:\\copy.txt");
   		f.copi.seekg(0);
    	node* head = nullptr;//the head
    	node* t = nullptr;//temporary
    	node* t1=nullptr;//need to be added
    	while (f.copi >> k) {
        	k=lower(k);
        	if (!IsinList(head, k)) {
            	t = new node;
            	t->word = k;
            	t->occured = 1; 
            	if (head == nullptr) {
                	t->next=head;
                	head=t;
            	} else {
            		t->next =head;
            		t1=t;
            		head=t1;
            	}
        	}
			//cout<<"still" ;
    	}
    	//t1->next=nullptr;
    	f.copi.close();
    	
		int j = count(head);
    	//cout<<j;
    	create_arr(head,j,f);
    	node* temp;
    	while (head != nullptr) {//delete the created linked list
        	temp = head;
        	head = head->next;
        	delete temp;
    	}
	}
	void create_arr(node* head,int l,rfilese& f){
		element uniq[l];//the array of the words in the file
		int i=0;//the current element index
		while(i<l&&head!=nullptr){
			uniq[i].occ=head->occured;
			uniq[i].wor=head->word;
			i++;
			head=head->next;
		}
		for(int i=0;i<l;i++){//count the occurence of each word in the file
			string s;//a string to read the words in the file
			f.copi.open("d:/copy.txt",ios::in);
			uniq[i].occ=0;
			while(f.copi>>s){//how many times the current word occured
				if(s==uniq[i].wor){
					uniq[i].occ++;
				}
			}
			f.copi.seekg(0);
			f.copi.close();
		}
		selSort(uniq,l);
	}
    string lower(string s) {
        for (int i=0;i<s.length();i++) {
            if (isupper(s[i])) s[i] = tolower(s[i]);
        }
        return s;
    }// string to lower case
	void selSort(element* arr, int n) {
		for(int i=0;i<n-1;i++){
			int max=arr[i].occ;
			int pos=i;
			for(int j=i+1;j<n;j++){
				if(arr[j].occ>max){
					max=arr[j].occ;
					pos=j;
				}
			}
			element e=arr[pos];
			arr[pos]=arr[i];
			arr[i]=e;
		}
		MostRepeated(arr);
	}
    void MostRepeated(element* a) {
        cout << "  word:-\toccured:-\n";
        for (int i = 0; i < M; i++) {
            cout <<endl<< i+1 << "- " << a[i].wor << "\t" << a[i].occ << endl;
        }
    }
};

class wfiles {
    string path;//file path to write to it
    ofstream wfile;//an object to deal with the file
public:
    void get_path() {
        string inp;
        ifstream check_file;//checks if the file exists
        cout << "enter the file path:\n";
        getline(cin, path);
        check_file.open(path, ios::in);
        if (!check_file) {
            char c;
            cout << "The file doesn't exist\n";
            cout << "Do you want to create a new one? (y/n)\n";
            cin >> c;
            if (c == 'y' || c == 'Y') {
                wfile.open(path, ios::out);
                if (!wfile) {
                    cerr << "wrong path\n";
                    exit(1);
                }
            } else {
                cout << "Ending program...\n";
                exit(1);
            }
        } else {
            int choice;
            cout << "Do you want to 1. overwrite the file or 2. append to it: ";
            cin >> choice;
            if (choice == 1) {
                char c = 'n';
                wfile.open(path, ios::out);
                while (c != 'y' && c != 'Y') {
                    cout << "Write:\n";
                    cin.ignore(); 
                    getline(cin, inp);
                    wfile << inp << endl;
                    cout << "Do you want to quit? (y/n): ";
                    cin >> c;
                }
            } else {
                char c = 'n';
                wfile.open(path, ios::app);
                while (c != 'y' && c != 'Y') {
                    cout << "Append:\n";
                    cin.ignore(); 
                    getline(cin, inp);
                    wfile << inp << endl;
                    cout << "Do you want to quit? (y/n): ";
                    cin >> c;
                }
            }
        }
        check_file.close();
    }

    void close_file() {
        wfile.close();
    }
};

void startProg();
int main() {
    startProg();
    return 0;
}

void startProg() {
    char c, ch;
    do {
        cout << "Please choose the file mode: r OR w: ";
        cin >> c;
        cin.ignore(); 
    } while (tolower(c) != 'r' && tolower(c) != 'w');

    if (c == 'r') {
        rfilese refil;
        refil.get_path();
        string s;
        do {
            cout << "Choose an operation:\n";
            cout << "1- The most repeated 5 words\n2- The biggest line\n3- The smallest line\n4- The longest word\n5- The number of lines\n";
            cout << "6- How many times a word occurred\n7- Print all lines\n8- Print all lines starting from a given line\n";
            cout << "9- The size of the txt file\nq- Quit\n";
            cin >> ch;
            cin.ignore();
            refil.build_copy();
            WordList fr;
            switch (ch) {
                case '1':
                    fr.create_unique(refil);
                    break;
                case '2':
                    refil.biggest_line();
                    break;
                case '3':
                    refil.smallest_line();
                    break;
                case '4':
                    refil.longest_word();
                    break;
                case '5':
                    cout << refil.num_of_lines() << endl;
                    break;
                case '6':
                    cout << "Enter the word: ";
                    cin >> s;
                    cout << fr.occure(refil, s)+1 << endl;
                    break;
                case '7':
                    refil.printALLlines();
                    break;
                case '8':
                    cout << "Enter the starting line number: ";
                    int n;
                    cin >> n;
                    refil.printFrom(n);
                    break;
                case '9':
                    cout << "Enter 1 for bytes, 2 for Kbytes, 3 for Mbytes: ";
                    int size_choice;
                    cin >> size_choice;
                    cout << refil.file_size(size_choice) << endl;
                    break;
                case 'q':
                    refil.removing();
                    refil.closeF();
                    exit(0);
                default:
                    cout << "Invalid choice\n";
            }
        } while (ch != 'q');
    } else {
        wfiles wf;
        wf.get_path();
        wf.close_file();
    }
}
