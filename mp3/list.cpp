/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
 #include<iostream>
 using namespace std;
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	ListNode * del = this->head;
	ListNode * next = NULL;
	while(del!=NULL){
		next = del->next;
		delete del;
		del = next;
		if(del==this->tail){
			delete del;
			head=NULL;
			tail=NULL;
			del=NULL;
			length = 0;
		}
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{

    ListNode* addition = new ListNode(ndata);
	if(length==0){
		head=addition;
		tail=addition;
	}else{
		head->prev = addition;
		addition->next = head;
		head = addition;
		addition->prev=NULL;
	}
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    ListNode* addition = new ListNode(ndata);
	if(length==0){
		head=addition;
		tail=addition;
	}else{
		tail->next = addition;
		addition->prev = tail;
		tail = addition;
		addition->next=NULL;
	}
	length++;

}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
//	cout<<head->data<<endl;
//	cout<<tail->data<<endl;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	if(length==0||startPoint==endPoint){
		return;
	}
	int i = 0;
	ListNode* current = startPoint;
	ListNode* temp = NULL;
	ListNode* counter = startPoint;
	ListNode* prevstart=startPoint->prev;
	ListNode* start = startPoint;
	ListNode* endP = endPoint;
	while(counter!=endPoint->next){
		i++;
		counter=counter->next;
	}
	//while(current!=endPoint->next){
	//yo i have to make sure the node after endpoint has a changed prev.  also make sure the prev for the new startPoint is correct.FIXED
	for(int n=0;n<i;n++){
		if (/*(startPoint==head&&endPoint==tail)||*/(n!=0)){//do we need that check?
			temp=current->prev;
		}else{
			temp=endPoint->next;
		}
		current->prev=current->next;
		current->next=temp;
		current=current->prev;
//		cout<<"stuff "<<i<<endl;
//		i++;
	}
	if(startPoint==head){
		head=endP;
	}
	if(endPoint==tail){
		tail=start;
	}
	//temp=start;
	startPoint=endP;
	endPoint=start;
	if(endPoint->next!=NULL){
		endPoint->next->prev=endPoint; //changes the prev of the next item to the new end.
	}
	startPoint->prev=prevstart;
	if(startPoint->prev!=NULL){
		startPoint->prev->next=startPoint;//changes the next of last item to new start.
	}
	temp = NULL;
	current=NULL;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
	if(length==0)
		return;
	ListNode* stuff=head;
	ListNode* morestuff = head;
	for(int i=0;i<length/n;i++){
		//cout<<"iterativenessman "<<i<<" out of "<<length/n<<endl;
		for(int j=1;j<n;j++){
			//cout<<"iteration number "<<j<<endl;
			stuff=stuff->next;
			//cout<<"iteration number "<<j<<endl;
		}
		//cout<<"iterativenessman "<<i<<endl;
		reverse(morestuff,stuff);
		//ListNode* temp= stuff;  //why is this code here?
		morestuff=stuff->next;
		//stuff=temp; //not sure why i did this
		stuff=stuff->next;
	}
	while((stuff!=tail)&&(stuff!=NULL)){
		stuff=stuff->next;
	//	cout<<"stuff isn't tail or NULL, weird"<<endl;
	}
	reverse(morestuff, stuff);
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if (length==0){
		return;
	}
	ListNode* curr = head->next;
	ListNode* temp = NULL;
	while(curr!=NULL&&curr->next!=NULL){
		curr->next->prev=curr->prev;
		curr->prev->next=curr->next;
		curr->prev=tail;
		temp = curr->next->next;
		curr->next=NULL;
		tail->next=curr;
		tail = curr;
		curr = temp;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	ListNode* temp = start;
	for(int i = 0; i<splitPoint; i++){
		if (temp!=NULL){
			temp = temp->next;
		}else{
			return NULL;
		}
	}
	temp->prev->next=NULL;
	temp->prev=NULL;

    return temp; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	ListNode* temp = NULL;
	ListNode* temp2 = NULL;
	ListNode* newstart = NULL;
	//ListNode* newend = NULL;
	if((second->data)<(first->data)){
		newstart=second;
		temp = second;
		temp2 = first;
	}
	else{ //if firstdata<=seconddata not sure what to do for equal though...
		temp = first;
		newstart = first;
		temp2 = second;
	}
/*	while(first->next!=NULL){
		first=first->next;
	}
	while(second->next!=NULL){
		second=second->next;
	}
	if(first->data<second->data)
		newend = second;
	else
		newend = first; */
	while((temp!=NULL)&&(temp2!=NULL)){//keep going to the end(cant stop this infinite loop sadface)	
		while((temp->next!=NULL)&&(temp->next->data)<(temp2->data)){
			temp=temp->next;
		}
		if(temp->next==NULL){
			temp->next=temp2;
			temp2->prev=temp;
			break;
		}
		ListNode* temp3 = temp->next;
		temp->next->prev=NULL;
		temp->next = temp2;
		temp2->prev = temp;
		temp=temp2;
		temp2=temp3;
//		if ((temp == newend) || (temp2->next == newend))
//			break;
//		cout<<"infinite loop bitches"<<endl;
	}
    return newstart;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
	if(chainLength<=1){
		return start;
	}
	ListNode* list2 = split(start,chainLength/2);
	start = mergesort(start, chainLength/2);
	list2 = mergesort(list2, chainLength-chainLength/2);
//	cout<<chainLength<<endl;
	
    return merge(start,list2);
}
