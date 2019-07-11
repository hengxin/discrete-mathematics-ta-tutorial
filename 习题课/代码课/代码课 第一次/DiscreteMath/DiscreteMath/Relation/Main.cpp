#include "Relation.h"
#include "iostream"

int main(int argc, char** argv) {
	Relation r(20);
	r.relationInput("d:\\relation.txt");
	Relation r2 = r.getReflectiveClosure();
	Relation r3 = r.getSymmetricClosure();
	Relation r4 = r.getTranstiveClosure();
	Relation r5 = r.relationComposition(r);
	Relation r6 = r.relationInverse();
	r.relationOutput("d:\\relationOut.txt");
	r.relationOutputAsSet("d:\\relationOut.txt");
	r6.relationOutput("d:\\relationOut.txt");
	r5.relationOutput("d:\\relationOut.txt");
	r2.relationOutput("d:\\relationOut.txt");
	r3.relationOutput("d:\\relationOut.txt");
	r4.relationOutput("d:\\relationOut.txt");
	


	return 1;
}