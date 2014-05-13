template <class T>
void ParallelSort::psort(vector<T>* array){
	if(array->size()<75000)
		psort(array, 0, array->size()-1);
	else{
# 		pragma omp parallel
		{
#			pragma omp single
			psort(array, 0, array->size()-1);
		}
	}
}

template <class T>
void ParallelSort::psort(vector<T>* array, int left, int right){
	int len = right - left;
	T x;

	if(len<17){//insertion sort for smaller lists
		for(int i = left + 1; i<=right; i++){
			for(int j = i; j>left&&array->at(j)<array->at(j-1);j--){
				x=array->at(j-1);
				array->at(j-1)=array->at(j);
				array->at(j)=x;
			}
		}
		return;
	}
	//median indexes
	int sixth = len/6;
	int m1 = left+sixth;
	int m2 = m1+sixth;
	int m3 = m2+sixth;
	int m4 = m3+sixth;
	int m5 = m4 + sixth;

	//5-element sorting network
	if(array->at(m1)>array->at(m2)) {x=array->at(m1); array->at(m1)=array->at(m2); array->at(m2)=x;}
	if(array->at(m4)>array->at(m5)) {x=array->at(m4); array->at(m4)=array->at(m5); array->at(m5)=x;}
	if(array->at(m1)>array->at(m3)) {x=array->at(m1); array->at(m1)=array->at(m3); array->at(m3)=x;}
	if(array->at(m2)>array->at(m3)) {x=array->at(m2); array->at(m2)=array->at(m3); array->at(m3)=x;}
	if(array->at(m1)>array->at(m4)) {x=array->at(m1); array->at(m1)=array->at(m4); array->at(m4)=x;}
	if(array->at(m3)>array->at(m4)) {x=array->at(m3); array->at(m3)=array->at(m2); array->at(m4)=x;}
	if(array->at(m2)>array->at(m5)) {x=array->at(m2); array->at(m2)=array->at(m5); array->at(m5)=x;}
	if(array->at(m2)>array->at(m3)) {x=array->at(m2); array->at(m2)=array->at(m3); array->at(m3)=x;}
	if(array->at(m4)>array->at(m5)) {x=array->at(m4); array->at(m4)=array->at(m5); array->at(m5)=x;}

	//pivots
	T pivot1 = array->at(m2);
	T pivot2 = array->at(m4);

	bool diffPivots = pivot1 != pivot2;

	array->at(m2) = array->at(left);
	array->at(m4) = array->at(right);

	int less = left +1;
	int great = right - 1;

	if(diffPivots){
		for(int k = less; k<=great; k++){
			x=array->at(k);

			if(x<pivot1) {
				array->at(k)=array->at(less);
				array->at(less++) = x;
			}else if(x>pivot2){
				while(array->at(great)>pivot2&&k<great){
					great--;
				}
				array->at(k) = array->at(great);
				array->at(great--) = x;
				x=array->at(k);

				if(x<pivot1){
					array->at(k)=array->at(less);
					array->at(less++) = x;
				}
			}
		}
	}else{
		for(int k = less; k<=great; k++){
			x=array->at(k);

			if(x==pivot1){
				continue;
			}
			if(x<pivot1) {
				array->at(k)=array->at(less);
				array->at(less++)=x;
			}else{
				while(array->at(great)>pivot2&&k<great){
					great--;
				}
				array->at(k)=array->at(great);
				array->at(great--)=x;
				x=array->at(k);

				if(x<pivot1){
					array->at(k) = array->at(less);
					array->at(less++) = x;
				}
			}
		}
	}
	//swap
	array->at(left) = array->at(less-1);
	array->at(less-1) = pivot1;

	array->at(right) = array->at(great+1);
	array->at(great+1)=pivot2;

	//left and right parts
#	pragma omp task
	psort(array,left,less-2);
#	pragma omp task
	psort(array,great+2,right);

	//equal elements
	if(great-less>len-13&&diffPivots){
			for(int k = less; k<=great; k++){
				x=array->at(k);

				if(x==pivot1){
					array->at(k)=array->at(less);
					array->at(less++) = x;
				}else if(x==pivot2){
					array->at(k)=array->at(great);
					array->at(great--) = x;
					x = array->at(k);
					if(x==pivot1){
						array->at(k)=array->at(less);
						array->at(less++)=x;
					}
				}
			}
	}
	//center part
	if(diffPivots){
		psort(array, less, great);
	}
}
