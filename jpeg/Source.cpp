#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<memory>
#include<stack>
#include<cassert>
#include<unordered_map>


using namespace std;

class Node {
public:


	Node(char c, int f);
	Node(char c, int f, Node* lt, Node* rt);
	Node(const Node&) = delete;
	~Node();

	Node& operator=(const Node&) = delete;

	bool isInternal() const { return isInternalNode; }
	int getFreq() const { return freq; }
	char getSymbol() const { return symbol; }

	Node* getLeft() const { return left; }
	Node* getRight() const { return right; }
private:
	char symbol;
	int freq;
	Node* left;
	Node* right;
	bool isInternalNode;
	string code;
};

void printSpace(double n, const Node* removed)
{
	for (int i = 0; i < n; ++i) {
		cout << "\t";
	}
	if (removed == nullptr) {
		cout << " ";
	}
	else {
		cout << "(" << removed->getFreq() << ',' << removed->getSymbol() << ')';
	}
}

void printBinaryTree(const Node* root)
{
	if (root == nullptr) {
		return;
	}

	queue<const Node*> q;
	q.push(root);
	int level = 0;
	int nodesInCurrentLevel = 1;
	int nodesInNextLevel = 0;

	while (!q.empty()) {
		const Node* node = q.front();
		q.pop();

		printSpace(level, node);

		if (node != nullptr) {
			q.push(node->getLeft());
			q.push(node->getRight());

			nodesInNextLevel += 2;
		}

		if (--nodesInCurrentLevel == 0) {
			cout << endl;
			level++;
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
}



unordered_map<char, int> getFrequencyTable(string st)
{
	unordered_map<char, int> freqTable;

	for (char s : st)
	{
		if (freqTable.find(s) == freqTable.end())
		{
			freqTable[s] = 1;
		}
		else
		{
			freqTable[s]++;
		}
	}
	return freqTable;
}

Node::Node(char c, int f)
	: symbol(c), freq(f), left(nullptr), right(nullptr), isInternalNode(false) {}

Node::Node(char c, int f, Node* lt, Node* rt)
	: symbol(c), freq(f), left(lt), right(rt), isInternalNode(true) {}


Node::~Node() {}




class compare {
public:
	bool operator()(Node* l1, Node* l2) {
		return l1->getFreq() > l2->getFreq();
	}
};



int main()
{
	
	string input = "abracadabra";

	auto freqTable = getFrequencyTable(input);
	priority_queue<Node*, vector<Node*>, compare>pq;
	for (auto charFreq : freqTable) {
		Node* node = new Node(charFreq.first, charFreq.second);
		pq.push(node);
	}

	while (pq.size() > 1) {
		//logic
		Node* l1 = pq.top();
		pq.pop();

		Node* l2 = pq.top();
		pq.pop();

		Node* internalNode = new Node('$', l1->getFreq() + l2->getFreq(), l1, l2);


		pq.push(internalNode);


	}




	Node* root = pq.top();


	unordered_map<char, string> huffmanCode;

	//code for dfs
	stack<pair<Node*, string>>s;
	s.push({ root,"" });
	while (!s.empty()) {
		Node* n = s.top().first;
		string code = s.top().second;
		s.pop();
		Node* l = n->getLeft();
		Node* r = n->getRight();
		if (l != nullptr)s.push({ l,code + "0" });
		if (r != nullptr)s.push({ r,code + "1" });
		if (!n->isInternal()) huffmanCode[n->getSymbol()] = code;
	}
	for (auto i : huffmanCode) {
		char c = i.first;
		string code = i.second;
		cout << c << ": " << code << endl;
	}

	return 0;
}

