#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    // check overload constructors
    ClapTrap clara("Clara");
    ScavTrap sara("Sara");

    // check basic functions
    sara.attack("Clara");
    clara.attack("Sara");
    sara.takeDamage(5);
    sara.takeDamage(4);
    sara.guardGate();
    // clara.guardGate(); // should not work, base ClapTrap does not have this function

    // test copy constructors
    ClapTrap Cat(sara);       // --> can make parent from child
    //ScavTrap Sergio(clara); // --> cannot make child from parent becasue child has something extra and object slicing would happen

    // tseting copy assignment
    ClapTrap Corgi;
    ScavTrap Sergi;
    Corgi = sara;   // --> can make parent from child
    // Sergi = clara;  // --> cannot make child from parent becasue child has something extra and object slicing would happen

    return 0;
}