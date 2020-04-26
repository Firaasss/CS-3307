#include "Manager.h"
#include "RegularEmployee.h"

int main()
{
  Employee* dean = new Manager("Pauline Barmby"); 
  Employee* chair = new Manager("Hanan Lutfiyya"); 
  Employee* manager = new Manager("Jeff Shantz");
  Employee* emp1 = new RegularEmployee("Art Mulder");
  Employee* emp2 = new RegularEmployee("Gary Molenkamp");
  Employee* emp3 = new RegularEmployee("Joe Clarke");
  Employee* emp4 = new RegularEmployee("Hisham Shoblaq");

  dean->add(chair); 
  chair->add(manager); 
  manager->add(emp1); 
  manager->add(emp2); 
  manager->add(emp3); 
  manager->add(emp4); 

  dean->print();
}
