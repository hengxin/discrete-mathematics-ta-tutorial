#include "Set.h"
#include "cstring"

int main(int argc, char** argv) {

		Set a, b;
		
		a.setInput("d:\\set.txt");
		a.setOutput("d:\\setOutput.txt");
		b.setInput("d:\\set2.txt");
		b.setOutput("d:\\setOutput.txt");
		Set f = a.setIntersect(b);
		Set e = a.setUnion(b);
		Set g = a.setComplement(b);
		Set h = a.setComplement();
		f.setOutput("d:\\setOutput.txt");
		e.setOutput("d:\\setOutput.txt");
		g.setOutput("d:\\setOutput.txt");
		h.setOutput("d:\\setOutput.txt");
	return 1;
}