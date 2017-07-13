#include "select_node.h"
#include <ilcplex/ilocplex.h>
#include "branching/branching.h"

int FirstFractional::IndexOfNextVariableToFix(const IloNumArray &numbers) {
	int FracVar = -1;
    for (int i = 0; i < numbers.getSize(); i++) {
	if (IsFractional(numbers[i])!=0) {
	    FracVar = i;
	    break;
	}
    }
    return FracVar;
}


int CloseHalf::IndexOfNextVariableToFix(const IloNumArray &numbers) {
    int maxIndex=-1;
    double bestValue=1,temp;

    for (int i = 0; i < numbers.getSize(); i++) {
	temp=IsFractional(numbers[i]);
	if (temp!=0) {
	    temp=std::abs(temp-0.5);
	    if (temp<bestValue){

		bestValue=temp;
		maxIndex=i;
	    }
	}
    }
    return maxIndex;
}


CloseHalfExpensive::CloseHalfExpensive(const std::vector <double> coef_, const double float_precision, const double delta_) : coef(coef_),delta(delta_), Branching(float_precision){}

int CloseHalfExpensive::IndexOfNextVariableToFix(const IloNumArray &numbers) {
    int bestIndex=-1,indexIgnoringDelta=-1;
    double maxValue=-1,maxValueIgnoringDelta=-1,temp;

    for (int i = 0; i < numbers.getSize(); i++) {
	temp=IsFractional(numbers[i]);
	if (temp!=0){
	    if (std::abs(temp-0.5)<delta) {
	    	if (std::abs(coef[i])>maxValue){
	    		maxValue=std::abs(coef[i]);
	    		bestIndex=i;
		}}
	    else{
		if (std::abs(coef[i])>maxValueIgnoringDelta){
		    maxValueIgnoringDelta=std::abs(coef[i]);
		    indexIgnoringDelta=i;
		}
		//				if (std::abs(temp-0.5)>maxValueIgnoringDelta){
		//					maxValueIgnoringDelta=std::abs(temp-0.5);
		//					indexIgnoringDelta=i;
		//				}
	    }
	}
    }

    int RetVar = -1;
    if(bestIndex!=-1) RetVar=bestIndex;
    else RetVar=indexIgnoringDelta;
    return RetVar;
}

int StrongBranching::IndexOfNextVariableToFix(const IloNumArray &numbers) {
    int StrongestVar;
//    for (int i = 0; i < numbers.getSize(); i++) {
//	if (IsFractional(numbers[i])!=0) {
//	    indizes.insert(indizes.end(),i);
//	}
//    }
//    std::cout<<"allfrac "<<indizes.size()<<std::endl;
    return StrongestVar;
}
