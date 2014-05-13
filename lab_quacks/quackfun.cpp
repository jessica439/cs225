/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T QuackFun::sum(stack<T> & s)
{
	if(s.empty())
		return T();
	T temp = s.top();
	T tsum;
	s.pop();
	tsum = temp + sum(s);
	s.push(temp);

    return tsum; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
    stack<T> s;
    queue<T> q2;
	int size = q.size();
	int block = 1;
	int blocki = 1;
	int i = 0;
	int newi = 0;
	while(i<size){
		if((block%2)==0){
			for(blocki=block; blocki>0; blocki--){
		//		std::cout<<"no segfault yet "<<i<<std::endl;
				if(i<size){
				s.push(q.front());
//				std::cout<<"q.front() == "<<q.front()<<std::endl;
				q.pop();
				i++;
				}
		//		std::cout<<"no segfault yet "<<i<<std::endl;
			}
			for(blocki=block; blocki>0; blocki--){
		//		std::cout<<"no segfault yet "<<i<<std::endl;
				if(newi<size){
				q.push(s.top());
		//		std::cout<<"no segfault yet "<<i<<std::endl;
				s.pop();
		//		std::cout<<"no segfault yet "<<i<<std::endl;
				newi++;
				}
			}
			//s.push(q.front());
			//q.pop();
			//blocki--;
		//	std::cout<<"no segfault yet "<<block<<std::endl;
		}else if((block%2)==1){
			for(blocki=block; blocki>0; blocki--){
		//		std::cout<<"no segfault yet "<<i<<std::endl;
				if(i<size){
				q2.push(q.front());
//				std::cout<<"q.front() == "<<q.front()<<std::endl;
				q.pop();
				i++;
				}
		//		std::cout<<"no segfault yet "<<i<<std::endl;
			}
			for(blocki=block; blocki>0; blocki--){
				if(newi<size){
				q.push(q2.front());
		//		std::cout<<"no segfault yet "<<block<<std::endl;
				q2.pop();
		//		std::cout<<"no segfault yet "<<block<<std::endl;
		//		std::cout<<"no segfault yet "<<block<<std::endl;
				newi++;
				}
			}	

			//q2.push(q.front());
			//q.pop();
			//blocki--;
		}
		block++;
	}
	
}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{
    bool retval = true; // optional
	T temp1; // rename me
    T temp2; // rename :) 
	if(s.size()==0)
		return true;
	temp1 = s.top();
	s.pop();
	retval=verifySame(s,q);
	temp2 = q.front();
	q.pop();
	retval = (retval&&(temp1==temp2));
	q.push(temp2);
	s.push(temp1);
    return retval;
}

