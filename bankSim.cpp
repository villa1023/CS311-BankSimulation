//Oscar Villa
//004961877
//villa291@cougars.csusm.edu
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;


struct EventNode //struct for events
{
  int occurTime;
  int type;
  EventNode* next;
};

class EventList //linked list for events
{
public:
  EventNode* head;

  EventList()//constructor
  {
    head = NULL;
  }
  
  void append(int occurT, int eventT)//function to append node
  {
    EventNode* newNode;
    EventNode* nodePtr;
    newNode = new EventNode;//create a node
    //set attributes
    newNode->occurTime = occurT;
    newNode->type = eventT;
    //new node willbe end of list
    newNode->next = NULL;

    //if list is empty insert node
    if (head == NULL)
      head = newNode;

    else //traverse list
      {
	nodePtr = head;

	while (nodePtr->next != NULL)
	  {
	    nodePtr = nodePtr->next;
	  }

	nodePtr->next = newNode;
      }
  }

  void insert(int occurT, int eventT)//function inserts node into list
  {
    EventNode* newNode;
    EventNode* nodePtr;
    EventNode* prevNode;

    newNode = new EventNode; //create node
    //attributes
    newNode->occurTime = occurT;
    newNode->type = eventT;
        if (isEmpty())//if list empty insert in begin
      {
	head = newNode;
	newNode->next = NULL;
      }
    else // traverse the list
      {
	nodePtr = head;
	prevNode = head;	
	while (nodePtr != NULL && nodePtr->occurTime < occurT)
	  {
	    prevNode = nodePtr;
	    nodePtr = nodePtr->next;
	  }
	if (prevNode == NULL)//
	  {
	    head = newNode;
	    newNode->next = nodePtr;
	  }
	else//insert before current
	  {
	    prevNode->next = newNode;
	    newNode->next = nodePtr;
	  }
      }
  }

  void removeFront(int &occurT, int &eventT)//removes the front event
  {
    EventNode* nodePtr;
    nodePtr = head;
    
    if (head == NULL)
      {
	cout << "EMPTY" << endl;
      }
    else
      {
	occurT = nodePtr->occurTime;
	eventT = nodePtr->type;
	head = head->next;
	delete nodePtr;
      }
  }

  bool isEmpty()
  {
    if (head == NULL)
      {
	return true;
      }
    else
      {
	return false;
      }
  }

  void print()
  {
    EventNode* nodePtr = head;//start of list
    int pos = 1;

    if (head == NULL)
      {
	cout << "[Empty]" << endl;
      }
    else
      {
	while (nodePtr)//while not at end of list
	  {
	    cout << pos << ". Occur Time:" << nodePtr->occurTime << " Event Type: "<< nodePtr->type << endl;
	    nodePtr = nodePtr->next;//go to next node
	    pos++;
	  }
      }
  }

};

struct CustomerNode//struct for customers
{
  int arrivalTime;
  int serviceTime;
  CustomerNode* next;
};

class CustomerQueue//queue for customers
{
public:
  CustomerNode* front;
  CustomerNode* rear;
  int count;

  CustomerQueue()
  {
    front = NULL;
    rear = NULL;
    count = 0;
  }

  

  void enqueue(int aT, int sT)
  {
    CustomerNode* newNode;
    newNode = new CustomerNode;
    newNode->arrivalTime = aT;
    newNode->serviceTime = sT;
    newNode->next = NULL;

    if (isEmpty())
      {
	front = newNode;
	rear = newNode;
      }
    else
      {
	rear->next = newNode;
	rear = newNode;
      }
    count++;
  }

  void dequeue(int &aT, int &sT)
  {
    CustomerNode* nodePtr = front;

    if (isEmpty())
      cout << "[Queue EMPTY]" << endl;

    else
      {
	aT = nodePtr->arrivalTime;
	sT = nodePtr->serviceTime;
	front = front->next;
	delete nodePtr;

	count--;
      }
  }

  bool isEmpty()
  {
    if (count == 0)
      return true;
    else
      return false;
  }

  void displayAll()
  {
    CustomerNode* nodePtr = front;

    if (isEmpty()) //no nodes in queue
      cout << "[QUEUE EMPTY]\n";
    else
      {
	while (nodePtr)
	  {
	    cout << "Arrival Time: " << nodePtr->arrivalTime << "Service Time: " << nodePtr->serviceTime << endl;
	    nodePtr = nodePtr->next;
	  }
      }
  }
};

int main()
{
  srand((int)time(0));//rand()
  CustomerQueue custQ;//queue
  EventList evnt; //Event list
  int arrNextCust = 0;//arrival of next cust
  int serveTimeCurrCust = 0;//service time
  int numCustomers = 0;//stores number of customers
  int currentTime = 0;//stores time
  int waitTime = 0;//stores wait time for each customer
  int deqArrTime;
  int deqServTime;
  
  cout << "Initializing EventList\n";
  evnt.insert(0, 0); //Initialize event list
  while (!evnt.isEmpty()) //While evnt is not empty
    {
      int tempOccurT;//to hold current event occur time 
      int eventType;//to hold current event type
      
      evnt.removeFront(tempOccurT, eventType);//remove event from front of event list
   
      if (eventType == 0)//if arrival
	{
	  if (currentTime <= 28800)//if next cust arrives while bank open create arrival event for new cust
	    {
	      numCustomers += 1;//increase customer count by 1
	      cout << endl << endl << "Number  Of Customers: " << numCustomers << endl << endl;
 
	      cout << "Current Time " << currentTime << endl;
	      serveTimeCurrCust = rand() % 600 + 1;//random service time of current cust <= 10 min      
	      cout << "Service Time " << serveTimeCurrCust << endl;

	      arrNextCust = (rand() % 300 + 1); //randon interval time of next cust arrival <= 5 min
	      cout << "Interval time " << arrNextCust << endl;
	      currentTime+= arrNextCust;
	      waitTime = serveTimeCurrCust + arrNextCust;
	      if(currentTime <= 28800)
		{
		  evnt.insert(arrNextCust, 0);//insert arrival of next customer and type
		}
	      custQ.enqueue(tempOccurT,serveTimeCurrCust);//add into customer queue
	      //  evnt.insert(serveTimeCurrCust, 1);//insert next departure
	    }      
	}      
      else  if(eventType == 1)
	{    
	  cout << "DEPART" << endl;
	  custQ.dequeue(deqArrTime, deqServTime);//dequeue
	  waitTime += currentTime + deqServTime - deqArrTime;
	  cout << "Wait time: " << waitTime << endl;
	  if (!custQ.isEmpty())
	    {
	      evnt.insert(currentTime + custQ.front->serviceTime, 1);
	    }
	}      
    }      
  cout << endl << endl << "----------End of Day Results----------" << endl;
  cout << setprecision(2)<< "Number of customers served = " << numCustomers << "\nTotal wait time = " << waitTime << "\nAverage wait time =  "
       <<(double)waitTime/numCustomers << endl;
return 0;
}
