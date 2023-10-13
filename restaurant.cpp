#include "main.h"
// g++ main.cpp -o main | ./main

void REG(int ID, string name, int age, restaurant *r);
void REGM(string name, int age, int num, restaurant *r);
void CLE(int ID, restaurant *r);
void PS(int num);
void PQ(int num);
void SQ(int num);
void PT(restaurant *r);
void readline(string input_str, string &input_1, string &input_2, string &input_3, string &input_4);

void readline(string input_str, string &input_1, string &input_2, string &input_3, string &input_4)
{
    string space1 = " ";
    size_t pos = 0;
    string read1;
    int i = 0;
    while ((pos = input_str.find(space1)) != std::string::npos)
    {
        read1 = input_str.substr(0, pos);
        if (i == 0)
            input_1 = read1;
        else if (i == 1)
            input_2 = read1;
        else if (i == 2)
            input_3 = read1;
        else if (i == 3)
            input_4 = read1;
        i++;
        input_str.erase(0, pos + space1.length());
    }
	if(input_1 == "")
	{
		input_1 = input_str;
	}
	else if (input_2 == "")
	{
		input_2 = input_str;
	}
    else if (input_3 == "")
	{
		input_3 = input_str;
	}
    else if (input_4 == "")
	{
		input_4 = input_str;
	}
}
// Create queue that customers can wait, don't need ID
class ntable
{
public:
	string name;
	int age;
	int dup;
	ntable *next;
	ntable(string name, int age, int dup, ntable *next = NULL)
	{
		this->name = name;
		this->age = age;
		this->dup = dup;	
		this->next = next;
	}
	~ntable()
	{
		name = "";
		age = 0;
		dup = 0;
		next = NULL;
	}
};

class queue
{
public:
	ntable *head;
	ntable *tail;
	int count;
	int dupp;
	queue()
	{
		head = NULL;
		tail = NULL;
		count = 0;
		dupp = 0;
	}
	~queue()
	{
		head = NULL;
		tail = NULL;
		count = 0;
		dupp = 0;
	}
	void clear()
	{
		if (!head)
		{
			return;
		}
		ntable* first = this->head;
		while (head)
		{
			head = head->next;
			delete first;
			first = head;
		}
		delete first;
	}
	void add(string name, int age)
	{
		if (count == MAXSIZE)
		{
			return;
		}
		ntable *newcustomer = new ntable(name, age, 0, NULL);
		if (!head)
		{
			head = tail = newcustomer;
			count++;
			dupp++;
			newcustomer->dup = dupp;
		}
		else
		{
			tail->next = newcustomer;
			tail = newcustomer;
			count++;
			dupp++;
			newcustomer->dup = dupp;
		}
	}
	ntable *pop()
	{
		if (head == NULL)
			return NULL;
		ntable *first = head;
		head = head->next;
		// delete deltable;
		count--;
		return first;
	}
	void remove(string name, int age)
	{
		if(!head)
		{
			return;
		}
		ntable *dummy = new ntable("", 0, 0, NULL);
		dummy->next = head;
		ntable *ptr = dummy;
		while (1)
		{
			if(ptr->next->name == name && ptr->next->age == age)
			{
				break;
			}
			ptr = ptr->next;
		}
		ntable *temp = ptr->next;
		ptr->next = temp->next;
		delete temp;
		head = dummy->next;
		count--;
		delete dummy;
	}
	void print(int num)
	{
		int check = 0;
		ntable *temp = head;
		if (head == NULL)
		{
			cout << "Empty" << endl;
			return;
		}
		while (temp != NULL)
		{
			cout << temp->name << endl;
			temp = temp->next;
			check++;
			if (check == num)
			{
				break;
			}
		}
	}
	void printsq(int num)
	{
		ntable *temp = head;
		if (head == NULL)
		{
			cout << "Empty" << endl;
			return;
		}
		while (temp != NULL)
		{
			cout << temp->name << endl;
			temp = temp->next;
		}
	}
	void printpriority(int num)
	{
		// Selection Sort O(N^2) and have stable!
		ntable* temp = head;
		// Traverse the List
		if (!head)
		{
			printsq(num);
			return;
		}
		int idx = 0;
		ntable* dupli = temp;
		ntable* ndupli = temp->next;
		int duplicate;
		while(dupli->next)
		{
			while(ndupli)
			{
				if (dupli->age == ndupli->age)
				{
					duplicate = dupli->age;
					idx++;
				}
				ndupli = ndupli->next;
			}
			dupli = dupli->next;
			ndupli = dupli->next;
		}
		int check1 = 1;
		int check2 = 1;
		while (temp)
		{
			ntable* max = temp;
			ntable* r = temp->next;
			// Traverse the unsorted sublist
			if (idx == 0 || num == 1)
			{
				while (r)
				{
					if (max->age < r->age)
					{
						max = r;
					}
					r = r->next;
				}
				// Swap Data
				int x = temp->age;
				temp->age = max->age;
				max->age = x;
				string y = temp->name;
				temp->name = max->name;
				max->name = y;

				if (check1 == num)
				{
					break;
				}
				check1++;
			}
			else
			{
				while (r)
				{
					if (max->age < r->age)
					{
						max = r;
					}
					r = r->next;
				}
				if(max->age == duplicate)
				{
					ntable* newtemp = max->next;
					while(newtemp)
					{
						if(max->dup > newtemp->dup)
						{
							max = newtemp;
						}
						newtemp = newtemp->next;
					}
				}
				// Swap Data
				int x = temp->age;
				temp->age = max->age;
				max->age = x;
				string y = temp->name;
				temp->name = max->name;
				max->name = y;
				int z = temp->dup;
				temp->dup = max->dup;
				max->dup = z;

				if (check2 == num)
				{
					break;
				}
				check2++;
			}
			temp = temp->next;
		}
		printsq(num);
	}
}; queue* wait = new queue();
queue* wait2 = new queue();

// Create a hisory to store all customers and a stack to store the newest customer in the table 
class stack
{
public:
	string name;
	int age;
	stack *next;
	stack(string name, int age, stack *next = NULL)
	{
		this->name = name;
		this->age = age;
		this->next = next;
	}
	~stack()
	{
		name = "";
		age = 0;
		next = NULL;
	}
};

class PSstack
{
public:
	stack *head;
	stack *tail;
	int count;
	PSstack()
	{
		head = NULL;
		tail = NULL;
		count = 0;
	}
	~PSstack()
	{
		head = NULL;
		tail = NULL;
		count = 0;
	}
	void clear()
	{
		if (!head)
		{
			return;
		}
		stack* first = this->head;
		while (head)
		{
			head = head->next;
			delete first;
			first = head;
		}
		delete first;
	}
	void add(string name, int age)
	{
		if(count == MAXSIZE * 2)
		{
			return;
		}
		stack *newcustomer = new stack(name, age, NULL);
		if (head == NULL)
		{
			head = tail = newcustomer;
			count = 1;
		}
		else
		{
			newcustomer->next = head;
			head = newcustomer;
			count++;
		}
	}
	void remove(restaurant *r)
	{
		if(!head)
		{
			return;
		}
		stack *dummy = new stack("", 0, NULL);
		dummy->next = head;
		stack *ptr = dummy;
		while (1)
		{
			if(ptr->next->name == r->recentTable->name && ptr->next->age == r->recentTable->age)
			{
				break;
			}
			ptr = ptr->next;
		}
		stack *temp = ptr->next;
		ptr->next = temp->next;
		delete temp;
		head = dummy->next;
		count--;
		delete dummy;
	}
	void print(int num)
	{
		int check = 0;
		stack *temp = head;
		if (head == NULL)
		{
			cout << "Empty" << endl;
			return;
		}
		while (temp != NULL)
		{
			cout << temp->name /*<< " " */<< endl;
			temp = temp->next;
			check++;
			if (check == num)
			{
				break;
			}
		}
	}
}; PSstack* history = new PSstack();
PSstack* pt = new PSstack();

// REG <ID> <NAME> <AGE> - O(N):
bool checkfull(table *f)
{
	// Check full table or not
	table *temp = f;
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (temp->name == "" && temp->age == 0)
			return 0;
		temp = temp->next;
	}
	return 1;
}

void REG(int ID, string name, int age, restaurant *r)
{
	if (age > 115|| ID < 0 || age < 16 || ID > MAXSIZE)
	{
		return;
	}

	// Checkfull if not full get first customer of the queue and add the new customer to the queue
	if (checkfull(r->recentTable) != 1)
	{
		{
			// If order with ID table
			if (ID > 0 && ID <= MAXSIZE)
			{

				while (r->recentTable->ID != ID)
				{
					r->recentTable = r->recentTable->next;
				}

				if (r->recentTable->name == "" && r->recentTable->age == 0)
				{
					r->recentTable->name = name;
					r->recentTable->age = age;
					history->add(name, age);
					pt->add(name, age);
					return;
				}

				while (r->recentTable->name != "" || (r->recentTable->name == "" && r->recentTable->age != 0))
				{
					r->recentTable = r->recentTable->next;
					if (r->recentTable->name == "" && r->recentTable->age == 0)
					{
						r->recentTable->name = name;
						r->recentTable->age = age;
						history->add(name, age);
						pt->add(name, age);
						return;
					}
				}
			}
			// Order without ID table
			else if(ID == 0)
			{
				while (r->recentTable->ID != 1)
				{
					r->recentTable = r->recentTable->next;
				}
				if (r->recentTable->name == "" && r->recentTable->age == 0)
				{
					r->recentTable->name = name;
					r->recentTable->age = age;
					history->add(name, age);
					pt->add(name, age);
					return;
				}
				while (r->recentTable->name != "" || (r->recentTable->name == "" && r->recentTable->age != 0))
				{
					r->recentTable = r->recentTable->next;
					if (r->recentTable->name == "" && r->recentTable->age == 0)
					{
						r->recentTable->name = name;
						r->recentTable->age = age;
						history->add(name, age);
						pt->add(name, age);
						return;
					}
				}
			}
		}
	}
	// If the table is full so add the new customer to the queue
	if (checkfull(r->recentTable) == 1)
	{
		wait->add(name, age);
		wait2->add(name, age);
		history->add(name, age);
		return;
	}
}

// REGM <NAME> <AGE> <NUM> - O(N):
bool checkREGM(int num, restaurant *r)
{
	// Check if there are num adjacent empty tables
	int check = 1;
	int ne = 1;
	while(r->recentTable->ID != MAXSIZE)
	{
		r->recentTable = r->recentTable->next;
	}
	table* tmp = r->recentTable;
	while (1)
	{
		if (tmp->name != "")
		{
			check = 1;
			tmp = tmp->next;
		}
		if (tmp->name == "" && tmp->age == 0)
		{
			tmp = tmp->next;
			check++;
			if (check == num)
			{
				return 1;
				break;
			}
			// check++;
		}
		ne++;
		if (ne == MAXSIZE)
		{
			return 0;
			break;
		}
	}
}

int findID(int num, restaurant *r)
{
	// find the main ID to regm which have name and age of the VIP customer
	while (r->recentTable->ID != MAXSIZE)
	{
		r->recentTable = r->recentTable->next;
	}
	int count = 0;
	table *find_ID = NULL;
	table *end = r->recentTable;
	table *temp = r->recentTable;
	// MAXZISE is null
	while (temp->name == "" && temp->age == 0)
	{
		count++;
		temp = temp->next;
		if (count == num)
		{
			find_ID = r->recentTable;
			return find_ID->ID;
			break;
		}
	}
	count = 0;
	while (temp->name != "")
	{
		temp = temp->next;
	}
	table *newtemp = temp;
	while (1)
	{
		if (temp == end)
		{
			if (end->name == "" && end->age == 0 && count >= num - 1)
			{
				count++;
				newtemp = newtemp->next;
				find_ID = newtemp;
			}
			if (count >= num)
			{
				return find_ID->ID;
				break;
			}
		}
		if (temp->name == "" && temp->age == 0)
		{
			count++;
			temp = temp->next;
			if (count == num)
			{
				find_ID = newtemp;
			}
			if (count > num)
			{
				newtemp = newtemp->next;
				find_ID = newtemp;
			}
		}
		if (temp->name != "" && temp != r->recentTable)
		{
			count = 0;
			temp = temp->next;
			newtemp = temp;
		}
	}
}

void REGM(string name, int age, int num, restaurant *r)
{
	// ID_need have name and age of the VIP customer and the next num-1 tables assgin name == "" and age = ID_need
	if (num < 1 || age < 16 || age > 115 || num > MAXSIZE)
	{
		return;
	}
	if(num == 1)
	{
		REG(0, name, age, r);
		return;
	}
	if (num > MAXSIZE)
	{
		num = MAXSIZE;
	}
	int count = 1;
	while (count <= MAXSIZE)
	{
		if (r->recentTable->name == "" && r->recentTable->age != 0)
		{
			return;
			break;
		}
		r->recentTable = r->recentTable->next;
		count++;
	}
	if (checkREGM(num, r) == 1)
	{
		int ID_need = findID(num, r);
		int check = 1;
		while (r->recentTable->ID != ID_need)
		{
			r->recentTable = r->recentTable->next;
		}
		r->recentTable->name = name;
		r->recentTable->age = age;
		table *temp = r->recentTable;
		history->add(name, age);
		pt->add(name, age);
		while (1)
		{
			check++;
			r->recentTable = r->recentTable->next;
			r->recentTable->name = "";
			r->recentTable->age = ID_need;
			if (check == num)
			{
				r->recentTable = temp;
				break;
			}
		}
	}
	else
	{
		return;
	}
}

// CLE <ID> - O(N):
void CLE(int ID, restaurant *r)
{
	// Clear the table which customer have finished the dishes
	// If wrong ID so return
	if (ID < 1 || ID > MAXSIZE)
	{
		return;
	}
	// Go to the ID requested
	while (r->recentTable->ID != ID)
	{
		r->recentTable = r->recentTable->next;
	}
	if (r->recentTable->name != "" && r->recentTable->next->age == ID && r->recentTable->next->name == "")
	{
		history->remove(r);
		pt->remove(r);
		r->recentTable->name = "";
		r->recentTable->age = 0;
		table *temp = r->recentTable;
		r->recentTable = r->recentTable->next;
		while (r->recentTable->age == ID && r->recentTable->name == "")
		{
			r->recentTable->name = "";
			r->recentTable->age = 0;
			r->recentTable = r->recentTable->next;
		}
		while (temp->name == "" && temp->age == 0)
		{
			if (wait->count != 0)
			{
				ntable *getfirst1;
				getfirst1 = wait->pop();
				r->recentTable->name = getfirst1->name;
				r->recentTable->age = getfirst1->age;
				wait2->remove(getfirst1->name, getfirst1->age);
				pt->add(getfirst1->name, getfirst1->age);
				delete getfirst1;
			}
			else if (wait->count == 0)
			{
				break;
			}
			temp = temp->next;
		}
		return;
	}
	while (1)
	{
		// Table have info so delete it
		if (r->recentTable->name != "")
		{
			history->remove(r);
			pt->remove(r);
			r->recentTable->name = "";
			r->recentTable->age = 0;
			break;
		}
		// Table don't have info so don't do anything
		else
		{
			break;
		}
	}
	if (r->recentTable->name == "" && r->recentTable->age == 0)
	{
		if (wait->count != 0)
		{
			ntable *getfirst1;
			getfirst1 = wait->pop();
			r->recentTable->name = getfirst1->name;
			r->recentTable->age = getfirst1->age;
			wait2->remove(getfirst1->name, getfirst1->age);
			pt->add(getfirst1->name, getfirst1->age);
			delete getfirst1;
		}
	}
}

// PS[NUM] - O(N):
void PS(int num)
{
	// Print stack the customer has currently go to the table 
	if (num < 1 || num > MAXSIZE*2)
	{
		return;
	}
	if (num <= history->count || (num > history->count && num <= MAXSIZE * 2) )
	{
		history->print(num);
	}
}

// PQ [NUM] - O(N):
void PQ(int num /*, restaurant* r*/)
{
	// Print queue the customer(s) in the queue
	if (num < 1 || num > MAXSIZE)
	{
		return;
	}
	if (num <= wait2->count || (num > wait2->count && num <= MAXSIZE))
	{
		wait2->print(num);
	}
}

// PT - O(N)
void PT(restaurant *r)
{
	// Print all the information of the table in the restaurant
	PSstack *getfirst = new PSstack();
	getfirst->head = pt->head;
	while (r->recentTable->name != getfirst->head->name)
	{
		r->recentTable = r->recentTable->next;
	}
	delete getfirst;
	table* temp = r->recentTable;
	for (int i = 1; i <= MAXSIZE; i++)
	{
		if (temp->name != "")
		{
			cout << temp->ID << "-" << temp->name << endl;
		}
		temp = temp->next;
	}
}

// SQ <NUM> - O(N^2):
void SQ(int num /*, restaurant* r*/)
{
	// Sort queue who is elder and the staff will arrange them to the first queue
	if (num < 1 || num > MAXSIZE)
	{
		return;
	}
	if (num <= wait->count || (num > wait->count && num <= MAXSIZE))
	{
		wait->printpriority(num);
	}
}


void simulate(string filename, restaurant *r)
{
	// std::ifstream file("test.txt");
	std::ifstream file;
	file.open(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            // Process the line
            string input_1 = "";
            string input_2 = "";
            string input_3 = "";
            string input_4 = "";
            readline(line, input_1, input_2, input_3, input_4);
            //cout << input_1 << " " << input_2 << " " << input_3 << " " << input_4 << endl;
            if(input_1 == "REGM")
                REGM( input_2, stoi(input_3), stoi(input_4) , r);
            else if (input_1 == "REG")
			{
                if(input_4 == "")
				{
                    REG(0, input_2, stoi(input_3), r);
				}
				else
				{
                    REG(stoi(input_2), (input_3), stoi(input_4), r);
				}
			}
			else if(input_1 == "CLE")
			{
				CLE(stoi(input_2), r);
			}
			else if(input_1 == "PS")
			{
				if(input_2 == "")
				{
					PS((MAXSIZE*2));
				}
				else
				{
					PS(stoi(input_2));
				}
			}
			else if(input_1 == "PQ")
			{
				if(input_2 == "")
				{
					PQ(MAXSIZE);
				}
				else
				{
					PQ(stoi(input_2));
				}
			}
			else if(input_1 == "PT")
			{
				if(input_2 == "")
				{
					PT(r);
				}
			}
			else if(input_1 == "SQ")
			{
				SQ(stoi(input_2));
			}
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

	wait->clear();
	wait2->clear();
	history->clear();
	pt->clear();	

	table* ptr = r->recentTable->next;
	while (ptr != r->recentTable)
	{
		table* delptr = ptr;
		ptr = ptr->next;
		delete delptr;
	}
}