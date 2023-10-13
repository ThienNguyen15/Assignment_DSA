#include "main.h"
#include <bits/stdc++.h>
using namespace std;
void readline(string input_str, string &input_1, string &input_2);
	void readline(string input_str, string &input_1, string &input_2)
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
}
void REG(string name);
void CLE(long long num);
void printHash();
void printAVL();
void printMH();

long long ID[MAXSIZE] = { 0 };
long long avlid[MAXSIZE] = { 0 };
long long hashid[MAXSIZE] = {0};
long long m = 0;
long long av = 0; // appear in avl
long long ha = 0; // appear in hash
/* HUFF MAN */
struct infor // Save information
{
    string name;
    long long res = -1;
    long long id = -2;
	long long num = 0;
	long long appear = 0;
} info[MAXSIZE];
map<char, string> codes; // To map each character its huffman value
map<char, int> freq; // To store the frequency of character of the input data
struct MinHeapNode // A Huffman tree node
{
	char data;
	int freq;
	int appear;
	MinHeapNode* left, * right;
	MinHeapNode(char data, int freq, int appear)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
		this->appear = appear;
	}
    ~MinHeapNode()
    {
        delete left;
        delete right;
    }
    void removehuff()
    {
        data = '\0';
        freq = 0;
        appear = 0;
    }
};
struct compare // Utility function for the priority queue
{
	bool operator()(MinHeapNode* first, MinHeapNode* second)
	{
		if (first->freq == second->freq)
		{
			if (first->data != second->data)
				return first->data > second->data;
			else if (first->data == second->data)
				return first->appear > second->appear;
		}
		return first->freq > second->freq;
	}
};
void storeCodes(struct MinHeapNode* root, string str) // Utility function to store characters along with there huffman value
{
	if (root == NULL)
		return;
	if (root->data != '~')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

int HuffmanCodes(string str) // Function to build the Huffman tree and store it in minHeap
{
	codes.clear();
	freq.clear();
	// Utility function to store map each character with its frequency in input string
	int n = str.size();
	for (int i = 0; i < n; i++)
	{
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
        	return -1;
		
		freq[str[i]]++;
	}
	struct MinHeapNode* left, * right, * temp, *huff;
	for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
	{
		huff = new MinHeapNode(v->first, v->second, 0);
		minHeap.push(huff);
	}
	int appear = 0;
	if(minHeap.size() == 1)
	{
		long long res = 1;
        MinHeapNode* node = minHeap.top();
        minHeap.pop();
        delete node;
		for(int i = 0; i < MAXSIZE; i++)
		{
			if(!info[i].name.empty())
			{
				if(info[i].name == str)
					break;
			}
			if(info[i].res == -1)
			{
				info[i].name = str;
				info[i].res = res;
				info[i].appear = m +1;
				m++;
				break;
			}
		}
		return res;
	}
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		temp = new MinHeapNode('~', left->freq + right->freq, appear += 1);
		temp->left = left;
		temp->right = right;
		minHeap.push(temp);
	}
	storeCodes(minHeap.top(), "");
	string encodedString;
	for (auto i : str)
	{
		encodedString += codes[i];
	}
	if (encodedString.length() > 15)
		encodedString = encodedString.substr(encodedString.length() - 15, encodedString.length());
	int res = 0;
	for (size_t i = 0; i < encodedString.length(); i++)
	{
		if (encodedString[i] != '0')
			res += int(pow(2, encodedString.length() - i - 1));
	}
	for(int i = 0; i < MAXSIZE; i++)
	{
		if(!info[i].name.empty())
		{
			if(info[i].name == str)
				break;
		}
		if(info[i].res == -1)
		{
			info[i].name = str;
			info[i].res = (long long)res;
			info[i].appear = m + 1;
			m++;
			break;
		}
	}
    MinHeapNode* clearnode = minHeap.top();
    minHeap.pop();
    delete clearnode;
	codes.clear();
	freq.clear();
	return res;
}

/* AVL */
struct Node
{
    long long key;
    long long height;
    Node* left;
    Node* right;
    Node(long long val)
    {
        key = val;
        height = 1;
        left = NULL;
        right = NULL;
    }
};
class AVLTree
{
public:
    Node* root;
    long long count;
    long long height(Node* node)
    {
		if (node == NULL)
			return 0;
		long long lh = this->height(node->left);
		long long rh = this->height(node->right);
		return (lh > rh ? lh : rh) + 1;
    }
    long long balanceFactor(Node* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
	Node* rightRotate(Node* y)
	{
		Node* x = y->left;
		Node* T2 = x->right;
		x->right = y;
		y->left = T2;
		return x;
	}
	Node* leftRotate(Node* x)
	{
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		return y;
	}
    Node* balance(Node* node)
    {
        if (balanceFactor(node) > 1) // LH
        {
			// RH of LH
            if (balanceFactor(node->left) < 0)
                node->left = leftRotate(node->left);
            // LH of LH or RH of LH    
            return rightRotate(node);
        }
        else if (balanceFactor(node) < -1) // RH
        {
			// LH of RH
            if (balanceFactor(node->right) > 0)
                node->right = rightRotate(node->right);
			// RH of RH or LH of RH
            return leftRotate(node);
        }
        return node;
    }
    Node* insertNodeHelper(Node* node, long long val)
    {
        if (node == NULL)
            return new Node(val);
        if ((val/100) < (node->key /100))
            node->left = insertNodeHelper(node->left, val);
        else if ((val/100) >= (node->key /100))
            node->right = insertNodeHelper(node->right, val);

        return balance(node);
    }
    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
		// Node* current1 = node;
		// while (current1->right != NULL)
		// 	current1 = current1->right;
        // return (current->key/100) >= (current1->key/100) ? current1 : current;
		return current;
    }
    Node* deleteNodeHelper(Node* node, long long val, long long num)
    {
        if (node == NULL)
            return NULL;
        if ((val/100) < (node->key /100))
            node->left = deleteNodeHelper(node->left, val, num);
        else if ((val/100) > (node->key /100))
            node->right = deleteNodeHelper(node->right, val, num);
        else
        {
			if((node->key % 100) == num)
			{
					if (node->left == NULL && node->right == NULL)
					{
						delete node;
						return NULL;
					}
					else if (node->left == NULL)
					{
						Node* temp = node;
						node = node->right;
						delete temp;
						return node;
					} // 1 right child
					else if (node->right == NULL)
					{
						Node* temp = node;
						node = node->left;
						delete temp;
						return node;
					} // 1 left child
					else
					{
						// Node* temp = minValueNode(node->right);
						Node* temp = node->right;
						while(temp->left)	temp = temp->left;
						node->key = temp->key;
						long long num1 = (temp->key) % 100;
						node->right = deleteNodeHelper(node->right, temp->key, num1);
					}
			}
			else
			{
				node->left = deleteNodeHelper(node->left, val, num);
				node->right = deleteNodeHelper(node->right, val, num);
			}
        }
        return balance(node);
    }
public:
    AVLTree()
    {
        root = NULL;
        count = 0;
    }
	~AVLTree(){}
    long long size() 
    {
        return count;
    }
    void insertNode(long long val)
    {
        root = insertNodeHelper(root, val);
        count++;
    }
    void deleteNode(long long val, long long num)
    {
        root = deleteNodeHelper(root, val, num);
        count--;
    }
    void printTree(Node* node) // BFS
    {
		if(!node)
			return;
		Node* temp = node;
		queue<Node*> q;
		q.push(temp);
		while(!q.empty())
		{
			Node* check = q.front();
			q.pop();
			long long u = check->key;
			long long p = u % 100;
			u = (u - p) / 100;
			cout << p << "-" << u;
			for(long long i = 0; i < MAXSIZE; i++)
			{
				if(info[i].id == p)
				{
					cout << "-" << info[i].num <<endl;
					break;
				}
			}
			if(check->left)
				q.push(check->left);
			if(check->right)
				q.push(check->right);
		}
    }
    void printTree()
    {
        printTree(root);
    }
	long long findres(Node* node, long long num, long long& ans) // Search res
	{	
		if (node)
		{
			if(num == (node->key % 100))
			{
				ans = node->key;
			}
			findres(node->left, num, ans);
			findres(node->right, num, ans);
		}
		return ans;
	}
	long long findrestree(long long num, long long& ans)
	{
		findres(root, num, ans);
		return ans;
	}
}; AVLTree avl;

/* Hash */
class HashMap
{
public:
	long long count = 0;
	long long* keys;
	long long* values;
	HashMap()
	{
		this->count = count;
		keys = new long long[MAXSIZE];
		values = new long long[MAXSIZE];
		for (long long i = 0; i < MAXSIZE; i++)
		{
			keys[i] = -1;
			values[i] = -2;
		}
	}
	~HashMap(){}
public:
	long long Hash(long long key)
	{
		long long Hash = 0;
		Hash = key % (MAXSIZE / 2);
		return Hash;
	}
	void insertH(long long key, long long value)
	{
		if (count == MAXSIZE / 2)
			return;
		long long index = Hash(key);
		while (keys[index] != -1)
		{
			index = (index + 1) % (MAXSIZE / 2);
		}
		keys[index] = key;
		values[index] = value;
		count++;
	}
	void deleteH(long long value)
	{
        for(long long i = 0; i < MAXSIZE; i++)
        {
            if(values[i] == value)
            {
				for(long long k = 0; k < MAXSIZE; k++)
				{
					if(info[k].id == value)
					{
						info[k].name = "";
						info[k].res = -1;
						info[k].id = -2;
						info[k].num = 0;
						info[k].appear = 0;
						break;
					}
				}
                keys[i] = -1;
                values[i] = -2;
				hashid[value - 1] = 0;
				ID[value - 1] = 0;
                count--;
                break;
				return;
            }
        }
        return;
	}
	void print()
	{
		for (long long i = 0; i < MAXSIZE; i++)
		{	
			if(keys[i] != -1)
			{
				cout << values[i] << "-" << keys[i];
				long long k = values[i];
				for(long long j = 0; j < MAXSIZE; j++)
				{
					if(info[j].id == k)
					{
						cout<< "-" << info[j].num << endl;
						break;
					}
				}
			}
		}
	}
}; HashMap hashmap;

/* LRCO (Least Recently Customer Order) */
class LRCO
{
	list<long long> dq; // store keys
	unordered_map<long long, list<long long>::iterator> ma; // store references of key
	long long cap; // maximum capacity

public:
	LRCO(long long n) { cap = n; } // Declare the size
	void refer(long long x) // Refers key x with in the LRCO
	{
		if (ma.find(x) == ma.end()) // not present
		{
			if (static_cast<unsigned int>(dq.size()) == cap) //full
			{
				long long id = dq.back(); // delete least recently used element
				dq.pop_back(); // pops the last element
				ma.erase(id); // erase the last
			}
		}
		else // present
			dq.erase(ma[x]);

		dq.push_front(x); // update reference
		ma[x] = dq.begin();
	}
	long long leastnum()
	{
  		if (static_cast<unsigned int>(dq.size()) == cap)
	   		return dq.back();
	
		throw std::runtime_error("LRCO is not at full capacity");
	}
// void display() // Function to display contents
// {	// Iterate in the deque and print all the elements in it
// 	for (auto it = dq.begin(); it != dq.end(); it++) 	{ cout << (*it) << " "; }
// }
}; LRCO lrco(MAXSIZE);

/* LFCO (Least Frequently Customer Order) */
class minheap
{
public:
	long long* val;
	long long count = 0;
	minheap()
	{
		this->count = 0;
		// this->val = new long long[MAXSIZE];
		val = new long long[MAXSIZE];
		for (long long i = 0; i < MAXSIZE; i++)
		{
			val[i] = -1;
		}
	}
	~minheap(){}
public:
	void insert(long long res, long long id)
	{
		long long  k = 0;
		long long l = 0;
		for(long long i = 0; i < MAXSIZE; i++)
		{
			if(info[i].id == id)
			{
				k = info[i].num;   // num
				l = info[i].appear; // appear
				break;
			}
		}
		long long  a;
		long long b;
		a = res*1000 + l;
		b = a*100 + k;
		val[count] = b;
		reheapup(count);
		count++;
	}
	void reheapup(long long pos)
	{
		if(pos <= 0) return;
		long long parent = (pos-1)/2;
		if((val[pos] % 100) < (val[parent] % 100)) // num
		{
			long long temp = val[pos];
			val[pos] = val[parent];
			val[parent] = temp;

			reheapup(parent);
		}
	}
	void reheapdown(long long pos)
	{
		if(pos < 0 || pos >= count) return;
		long long leftc = 2*pos + 1;
		long long rightc = 2*pos + 2;
		long long last = count - 1;

		if(leftc <= last)
		{
			long long smallc = leftc;
			if(rightc <= last)
			{
				if((val[rightc] % 100) < (val[leftc] % 100)) // num
					smallc = rightc;
				else if((val[rightc] % 100) == (val[leftc] % 100) && ((val[rightc] / 100) % 1000) < ((val[leftc] / 100) % 1000)) // appear
					smallc = rightc;
			}
			if(((val[smallc] % 100) < (val[pos] % 100)) || ((val[smallc] % 100) == (val[pos] % 100) && ((val[smallc] / 100) % 1000) < ((val[pos] / 100) % 1000)))
			{
				long long temp = val[pos];
				val[pos] = val[smallc];
				val[smallc] = temp;

				reheapdown(smallc);
			}
		}
	}
	long long findres(long long& ans) // num min and appear min
	{
		ans = val[0];
		for(long long i = 0; i < count; i++)
		{
			if((ans % 100) > (val[i] % 100) && val[i] != -1) // num min
			{
				ans = val[i];
			}
		}
		for(long long i = 0; i < count; i++)
		{
			if(((ans % 100) == (val[i] % 100)) && (((ans / 100) % 1000)  > ((val[i] / 100) % 1000)) && val[i] != -1) // appear min
			{
				ans = val[i];
			}
		}
		return ans;
	}
	long long findres1(long long ans) // find res = appear
	{
		long long abc = 0;
		for(long long i = 0; i < count; i++)
		{
			if((val[i] / 100) % 1000 == ans)
			{
				abc = val[i];
				break;
			}
		}
		return abc;
	}
	long long findid(long long res)
	{
		long long a;
		for(long long i = 0; i < MAXSIZE; i++)
		{
			if((info[i].res == (res / 100000)) && (info[i].appear == ((res / 100) % 1000)))
			{
				a = info[i].id;
				break;
			}
		}
		return a;
	}
	void remove(long long res)
	{
    	for(long long i = 0; i < count; i++)
    	{
       		if(val[i] == res)
        	{
            	val[i]=val[count - 1];
				val[count - 1] = -1;
				count--;
            	reheapdown(i);
				break;
        	}
    	}
	}
	void print(long long& pos)
	{
		if(pos >= count) return;
		long long a = findid(val[pos]);
		cout<< a << "-";
		for(long long i = 0; i < MAXSIZE; i++)
		{
			if(info[i].id == a)
			{
				cout<< info[i].num << endl;
				break;
			}
		}
		long long o = pos*2 + 1;
		long long p = pos*2 + 2;
		print(o);
		print(p);
		return;
	}
}; minheap mheap;

void REG(string name)
{
	long long z = 0;
	for (long long i = 0; i < MAXSIZE; i++) // Check if customer order more than one 
	{
		if (!info[i].name.empty())
		{
			if (info[i].name == name)
			{
				z = i + 1; // ID
				break;
			}
		}
	}
	long long res = HuffmanCodes(name);
	if (res < 0)
		return;

	if (z != 0) // ID
	{
		long long k;
		long long i;
		long long j;
		k = (info[z - 1].res * 1000);
		i = (k + info[z - 1].appear) * 100;
		j = i + info[z - 1].num;
		long long s = info[z - 1].id;
		info[z - 1].num++;
		mheap.remove(j);
		mheap.insert(res, s);
		lrco.refer(s);
		return;
	}
	// Assign values and divide 2 area 
	if ((avl.size() < MAXSIZE / 2 && z == 0) || (hashmap.count < MAXSIZE / 2 && z == 0))
	{
		long long i = res % MAXSIZE + 1;
		long long k = i;
		long long l = 0;
		//  ID [] = 1 -> khu 1, ID [] = 2 -> khu 2
		if (ID[i - 1] != 0)
		{
			for (long long j = i; j < MAXSIZE; j++)
			{
				if (ID[j] == 0)
				{
					if ((res % 2 == 1 && hashmap.count < MAXSIZE / 2) || (avl.size() == MAXSIZE / 2 && hashmap.count < MAXSIZE / 2))
						ID[j] = 1;
					else
						ID[j] = 2;

					l = j + 1;
					break;
				}
				k++;
			}
			if (k == MAXSIZE)
			{
				for (long long o = 0; o < i; o++)
				{
					if (ID[o] == 0)
					{
						if ((res % 2 == 1 && hashmap.count < MAXSIZE / 2) || (avl.size() == MAXSIZE / 2 && hashmap.count < MAXSIZE / 2))
							ID[o] = 1;
						else
							ID[o] = 2;

						l = o + 1;
						break;
					}
					k++;
				}
			}
			if (k == MAXSIZE + i)
				return;
		}
		else
		{
			if ((res % 2 == 1 && hashmap.count < MAXSIZE / 2) || (avl.size() == MAXSIZE / 2 && hashmap.count < MAXSIZE / 2))
				ID[i - 1] = 1;
			else
				ID[i - 1] = 2;

			l = i;
		}

		for (long long i = 0; i < MAXSIZE; i++)
		{
			if (!info[i].name.empty())
			{
				if (info[i].name == name)
				{
					info[i].num = 1;
					info[i].id = l;
					lrco.refer(l);
					break;
				}
			}
		}
		mheap.insert(res, l);
		if ((res % 2 == 0 && avl.size() < MAXSIZE / 2) || (hashmap.count == MAXSIZE / 2 && avl.size() < MAXSIZE / 2))
		{
			long long ress = res * 100 + l;
			avl.insertNode(ress);
			avlid[l - 1] = av + 1;
			av++;
		}
		else if ((res % 2 == 1 && hashmap.count < MAXSIZE / 2) || (avl.size() == MAXSIZE / 2 && hashmap.count < MAXSIZE / 2))
		{
			hashmap.insertH(res, l);
			hashid[l - 1] = ha + 1;
			ha++;
		}
	}
	else if (avl.size() == MAXSIZE / 2 && hashmap.count == MAXSIZE / 2) // 2 area full
	{
		long long opt = res % 3;
		if (opt == 0) // FIFO
		{
			long long min;
			long long number;
			for (long long i = 0; i < MAXSIZE; i++)
			{
				if (info[i].appear != 0)
				{
					min = info[i].appear;
					break;
				}
			}
			for (long long k = 0; k < MAXSIZE; k++)
			{
				if (min > info[k].appear && info[k].appear > 0)
				{
					min = info[k].appear;
				}
			}
			for (long long j = 0; j < MAXSIZE; j++)
			{
				if (min == info[j].appear)
				{
					number = info[j].id;
					break;
				}
			}
			CLE(number);
			REG(name);
		}
		else if (opt == 1) // LRCO
		{
			long long out = lrco.leastnum();
			CLE(out);
			REG(name);
		}
		else if (opt == 2) // LFCO
		{
			long long ans = 0;
			long long resss = mheap.findres(ans); // min num and min appear
			mheap.remove(resss);
			long long id = mheap.findid(resss);
			CLE(id);
			REG(name);
		}
	}
	return;
}
	
void printAVL()		{ avl.printTree(); }
void printHash()	{ hashmap.print(); }
void printMH()		{ long long pos = 0;	mheap.print(pos); }

void CLE(long long NUM)
{
	if (NUM < 1)
	{
		long long min;
		while(hashmap.count != 0)
		{
			for(long long i = 0; i < MAXSIZE; i++)
			{
				if(hashid[i] > 0)
				{
					min = hashid[i];
					break;
				}
			}
			for(long long j = 0; j < MAXSIZE; j++)
			{

				if(min > hashid[j] && hashid[j] > 0)
				{
					min = hashid[j];
				}	
			}
			for(long long i = 0; i < MAXSIZE; i++)
			{
				if(hashid[i] == min)
				{
					for(long long k = 0; k < MAXSIZE; k++)
					{
						if(info[k].id == i + 1)
						{
							long long ans1 = 0;
							ans1 = info[k].appear;
							long long res1 = mheap.findres1(ans1);
							mheap.remove(res1);

							info[k].name = "";
							info[k].res = -1;

							for(long long p = 0; p < MAXSIZE; p++)
							{
								if(hashmap.values[p] == i + 1)
								{
									hashmap.keys[p] = -1;
									hashmap.values[p] = -2;
									break;
								}
							}
							hashid[i] = 0;
							ID[i] = 0;
							info[k].id = -2;
							info[k].num = 0;
							info[k].appear = 0;
							break;
						}
					}
					break;
				}			
			}
			hashmap.count--;
		}
		return;
	}
	if (NUM > MAXSIZE)
	{
		long long min;
		while (avl.size() != 0)
		{
			for (long long i = 0; i < MAXSIZE; i++)
			{
				if (avlid[i] > 0)
				{
					min = avlid[i];
					break;
				}
			}
			for (long long j = 0; j < MAXSIZE; j++)
			{

				if (min > avlid[j] && avlid[j] > 0)
				{
					min = avlid[j];
				}
			}
			for (long long i = 0; i < MAXSIZE; i++)
			{
				if (avlid[i] == min)
				{
					for(long long k = 0; k < MAXSIZE; k++)
					{
						if(info[k].id == i + 1)
						{
							long long ans1 = 0;
							ans1 = info[k].appear;
							long long res1 = mheap.findres1(ans1);
							mheap.remove(res1);

							info[k].name = "";
							info[k].res = -1;
							info[k].id = -2;
							info[k].num = 0;
							info[k].appear = 0;
							break;
						}
					}
					long long ans;
					long long res = avl.findrestree(i+1, ans);
					avl.deleteNode(res, i+1);
					avlid[i] = 0;
					ID[i] = 0;
					break;
				}
			}
		}
		return;
	}

	long long l = 0;
	long long o = 0;
	for (long long i = 0; i < MAXSIZE; i++)
	{
		if (i + 1 == NUM  && ID[i] != 0)
		{
			l = ID[i];
			o = i + 1;
			break;
		}
	}
	if (l == 1)
	{
		long long ans = 0;
		for (long long j = 0; j < MAXSIZE; j++)
		{
			if (NUM == info[j].id)
			{
				ans = info[j].appear;
				break;
			}
		}
		long long res = mheap.findres1(ans);
		mheap.remove(res);
		hashmap.deleteH(NUM);
	}
	else if (l == 2)
	{
		long long ans1 = 0;
		for (long long j = 0; j < MAXSIZE; j++)
		{
			if (NUM == info[j].id)
			{
				ans1 = info[j].appear;
				break;
			}
		}
		long long res1 = mheap.findres1(ans1);
		mheap.remove(res1);
		for(long long k = 0; k < MAXSIZE; k++)
		{
			if(info[k].id == o)
			{
				info[k].name = "";
				info[k].res = -1;
				info[k].id = -2;
				info[k].num = 0;
				info[k].appear = 0;
				break;
			}
		}
		long long ans = 0;
		long long res = avl.findrestree(NUM, ans);
		avl.deleteNode(res, NUM);
		avlid[o-1] = 0;
		ID[o-1] = 0;
	}
	return;
}

void simulate(string filename)
{
	std::ifstream file;
	file.open(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {	// Process the line
            string input_1 = "";
            string input_2 = "";
            readline(line, input_1, input_2);

            if(input_1 == "REG")
                REG( input_2);
			else if(input_1 == "CLE")
				CLE(stoi(input_2));
			else if(input_1 == "PrintHT")
				printHash();
			else if(input_1 == "PrintAVL")
				printAVL();
			else if(input_1 == "PrintMH")
				printMH();
        }
        file.close();
    }
    else
	{
        std::cout << "Unable to open file" << std::endl;
	}
	return;
}