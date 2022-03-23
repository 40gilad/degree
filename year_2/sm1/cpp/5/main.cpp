									/* PROGRAMMING EX 5 */
								/* SHAHAR ARIEL - 314868977 */
								/* GILAD MEIR - 313416562  */

#include "teacher.h"
using namespace std;

int main() {
	student s1("Shahar", 26, 1.8, 80, "Software Engeneering", "Yonit", 2, 150, 85, "Student1@gmail.com", 36);
	student s2("Gilad", 26, 1.7, 67, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student2@gmail.com", 35);
	student s3("Shlomo", 23, 1.6, 60, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student3@gmail.com", 36);
	student s4("Roey", 27, 1.8, 73, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student4@gmail.com", 27);
	student s5("Inbal", 21, 1.5, 60, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student5@gmail.com", 34);
	student s6("Gal", 24, 1.6, 52, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student6@gmail.com", 36);
	student s7("Liliya", 25, 1.7, 61, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student7@gmail.com", 31);
	student s8("Noam", 25, 1.7, 65, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student8@gmail.com", 36);
	student s9("Yuval", 25, 1.7, 67, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student9@gmail.com", 36);
	student s10("Hila", 22, 1.5, 48, "Sofware Engeneering", "Yonit", 2, 150, 85, "Student10@gmail.com", 36);
	student students[10] = { s1,s2,s3,s4,s5,s6,s7,s8,s9,s10 };
	// -------------------------------------------------------------------------------------------------------------------------
	course c1("Data structs", 5);
	course c2("Programming", 3);
	course c3("EMI", 2);
	// -------------------------------------------------------------------------------------------------------------------------
	//teacher(name, age, hight, weight, Faculty name, faculty head name, floor, faculty credits, scholarship grade, mail, salary, course)
	teacher t1("marchelo", 50, 1.80, 70, "Sofware Engeneering", "Yonit", 2, 150, 85, "marcelo@gmail.com", 12000, c2);
	teacher t2("Avivit", 43, 1.62, 62, "Software Engeneering", "Yonit", 2, 150, 85, "Avivit@gmail.com", 15000, c1);
	teacher t3("Yigal", 48, 1.78, 71, "Software Engeneering", "Yonit", 2, 150, 85, "Yigal@gmail.com", 12001, c3);
	teacher teachers[3] = { t1,t2,t3 };
	// -------------------------------------------------------------------------------------------------------------------------
	t_assistant a1("Yonantan", 33, 1.75, 75, "Software Engeneering", "Yonit", 2, 150, 85, "Yonatan@gmail.com", 8500, c2);
	t_assistant a2("Yifat", 39, 1.58, 47, "Software Engeneering", "Yonit", 2, 150, 85, "Yifat@gmail.com", 9500, c1);
	t_assistant a3("Peer", 31, 1.85, 83, "Software Engeneering", "Yonit", 2, 150, 85, "Peer@gmail.com", 8000, c3);
	t_assistant ass[3] = { a1,a2,a3 };
	// -------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < 10; i++)
	{
		students[i].setCorse(c2);
	}
	for (int i = 0; i < 10; i++)
	{
		if (students[i].IsStudying("Programming"))
			cout << students[i].getPname() << " is studiying the course Programming" << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		ass[0].WriteHomework(students[i]);

	}

	// -------------------------------------------------------------------------------------------------------------------------
	students[0].DoHomeWork(c2);
	students[2].DoHomeWork(c2);
	students[4].DoHomeWork(c2);
	students[5].DoHomeWork(c2);
	students[8].DoHomeWork(c2);

	// -------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < 10; i++)
	{
		teachers[0].gradeStudent(students[i], rand() % 20 + 80);
	}

	// -------------------------------------------------------------------------------------------------------------------------

	for (int i = 0; i < 10; i++)
	{
		cout << students[i].getPname() << " avarage is : " << students[i].AVG();
		if (students[i].AVG() < students[i].getsch_grade())
			cout << " and is not applicable for scholarship!" << endl;
		else
			cout << " and is applicable for shcolarship!" << endl;
	}
}