#include"TreeNode.h"
#include "Student.h"
using namespace std;

#include <iostream>

/************ Gilad Meir - 313416562 ******************/
/************ Shahar Ariel - 314868977 ***************/
int main()
{
	Student s1("gilad", 26);
	Student s2("adam", 28);
	Student s3("shiran", 27);
	Student s4("dovi", 3);
	Student arr[4] = { s1,s2,s3,s4 };
	TreeNode<Student> s(arr);
	Student amir("AmirV", 18);
	Student karmit("Karmit", 21);
	Student nitay("NitayX", 25);
	Student hanan("HananX", 29);
	Student boaz("Boaz", 4);
	Student arr2[4] = { amir, karmit, nitay, boaz };
	TreeNode<Student> tree(&s, arr2);
	Student* a = &amir;
	Student *st;
	tree.addChild(arr2);
	st = tree.getData();
	int n = tree.findChildIndx(a);
	cout<<"\data of children num 1: " << st[1].getName();
	cout << "\n" << n;
	cout<<"\nnumber of childern: " <<tree.getNumChildren();
	tree.removeChild();

	
}
