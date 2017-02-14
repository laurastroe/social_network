###################################
# socialNetwork Project description
###################################
The program builds a social network based on entries available in
SocialNetwork.txt. Each line in the file provides the names of two people who
are friends.
The program
1.	determines the total number of people in the social network
2.	determines the distance between A and B where the distance between two
members of the network can be defined as the minimum number of ties required to
connect two people in the social network

#############
#Installation
#############
Red Hat 5.3.1-2
>sudo dnf -y install git
>git clone https://github.com/laurastroe/social_network.git
>cd social_network/
>make

###################################
#Command Line Options and Arguments
###################################
Example:  ./socialNetwork -s -f STACEY_STRIMPLE -t RICH_OMLI
            -s - Display the total number of people in the social network
            -f Name1 Specify the starting point
            -t Name2 Specify the destination point

##########################################
#Design, Data Structure Decisions & Issues
##########################################
The social Network was designed as a Graph in which each person is
represented with a node. Each line from the file SocialNetwork.txt (name1,name2)
forms a graph's edge.
For the implementation of the Graph Algorithms was used only Standard Library
and more specific a map in which the key value is the name and the mapped value
is the adjacent  list of friends.
The methods of the class are the operations that can be performed on a graph:
    add a vertice CSocialNetwork::(addPerson)
    add an edge CSocialNetwork::(addFriendship)
    find the shortest paths between the nodes was done by implmenting
    Dijkstra's algorithm int CSocialNetwork::shortestPath
