/*
 * <COPYRIGHT_TAG>
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <stdio.h>
#include <unistd.h>

using namespace std;
typedef enum {ERROR = -1, OK} STATUS;
struct person {
	typedef pair<int, person *> ve; 
    list<ve> adj; //Adjiacent list of vertices
    string name;
    person(string s) : name(s) {}
};

typedef pair<int, person *> ve; 
typedef map<string, person *> vmap;
 
class CSocialNetwork
{
private:
	vmap work;
	int size;
public:
	STATUS addPerson(const string&);
	STATUS addFriendship(const string& from, const string& to, double cost);
	int shortestPath(const string& start, const string& end, int cost = 0);
	CSocialNetwork() : size(0){ };
	int Size() { return size; }
	~CSocialNetwork() {
		vmap::iterator it = work.begin();
		while(it != work.end()) {
			delete it->second;
			work.erase(it++);
		}
	}
};

STATUS CSocialNetwork::addPerson(const string& name)
{
	vmap::iterator itr = work.find(name);
	if (itr == work.end())
	{
		person *v;
		v = new person(name);
		work[name] = v;
		size++;
		return OK;
	}
	return ERROR;
}

STATUS CSocialNetwork::addFriendship(const string& from, const string& to, double cost)
{
	person *f = (work.find(from)->second);
	person *t = (work.find(to)->second);
	pair<int, person *> edge = make_pair(cost, t);
	f->adj.push_back(edge);
	return OK;
}

int CSocialNetwork::shortestPath(const string& from, const string& to, int cost)
{
	static int found = -1;
	person *f = (work.find(from)->second);
	if (from.compare(to) == 0)
		return 0;
	// Visited nodes
	map <ve, bool> visited;
	list<ve> queue;
	list<ve>::iterator i; 

	ve from_vert = make_pair(cost, f);
	visited[from_vert] = true;
	queue.push_back(from_vert);
	while (!queue.empty()) {
		from_vert = queue.front();
		queue.pop_front();

		for (i = from_vert.second->adj.begin();
		      i != from_vert.second->adj.end(); ++i) {
			(*i).first = from_vert.first+1; 
			if ((*i).second->name.compare(to) == 0) {
				found = (*i).first;
				return found;
			}
			if(visited[(*i)] == false) {
				visited[(*i)] = true;
				queue.push_back(*i);
			}
		}
	}
	map<string, person *> ::iterator goThroughAllperson;

	for (goThroughAllperson = work.begin(); goThroughAllperson != work.end();
	  ++goThroughAllperson) {
	    if ((*goThroughAllperson).first.compare(from) == 0)
		    continue;
	    list<ve>::iterator goThroughAllAdj;
	    for (goThroughAllAdj = (*goThroughAllperson).second->adj.begin();
		    goThroughAllAdj != (*goThroughAllperson).second->adj.end();
		    ++goThroughAllAdj) {
		    if ((*goThroughAllAdj).second->name.compare(from) == 0) {
			    cost++;
			    shortestPath(((*goThroughAllperson).second)->name.c_str(),
				    to, cost);
		    }
	    }
	}
	return (found);
}

static void show_usage()
{
	cerr << "Usage: socialNetwork -s -f name1 -t name2 "<<endl;
}

int main(int argc, char* argv[]) {
	
	string line, from, to;
	int c;
	ifstream input ("SocialNetwork.txt");
	CSocialNetwork socialNework;

	if (input.is_open()) {
	while ( getline (input,line) ) {
		stringstream to_split(line);
		string name;
		vector <string> connection;
		while (getline(to_split, name, ',')) {
			connection.push_back(name.c_str()); 
			socialNework.addPerson(name.c_str());
		}
		socialNework.addFriendship(connection[0], connection[1], 0);
	}
	input.close();
	}
	else
	  cout << "Unable to open file"; 
	while ((c = getopt(argc, argv, ":sf:t:")) != -1) {
		switch (c) {
		case 's':
			cout << "The number of persons in the social network is "
				<< socialNework.Size()<<endl;
			break;
		case 'f':
			from.append(optarg);
			break;
		case 't':
			to.append(optarg);
			break;
		case '?':
			show_usage();
			return -1;
		}
	}
	if (!from.empty() || !from.empty()) {
		cout << "Distance between " << from << " and " << to << " is "
			<< socialNework.shortestPath(from, to)<<endl;
	}
	return 0;
}
