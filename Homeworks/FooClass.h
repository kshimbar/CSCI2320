#include <iostream>

class FooClass {
	public:
		int a;
		double b;
		FooClass(int _a, double _b) : a{_a}, b{_b} {};
		FooClass() {};
		~FooClass() {};

		void save(FILE * f) {
			fseek(f,0,SEEK_SET);
			fwrite(&a,sizeof(int),1,f);
			fwrite(&b,sizeof(double),1,f);
		}
		void save(int ind, FILE * f) {
			fseek(f,ind*(sizeof(int)+sizeof(double)),SEEK_SET);
			fwrite(&a,sizeof(int),1,f);
			fwrite(&b,sizeof(double),1,f);
		}
		void read(FILE * f) {
			fseek(f, 0, SEEK_SET);
			fread(&a, sizeof(int),1,f);
			fread(&b, sizeof(double),1,f);
		}
		void read(int ind, FILE * f) {
			fseek(f, ind*(sizeof(int)+sizeof(double)), SEEK_SET);
			fread(&a, sizeof(int),1,f);
			fread(&b, sizeof(double),1,f);
		}
};