#include <iostream>
#include <string>

int main()
{
  std::string NPC = "Turgoth";
  std::string player = "you";
  
  std::cout << player << " is fighting " << NPC << "!\n";
  
  int NPCStrength = 3;
  int playerStrength = 4;
  
  int NPChealth = 5;
  int playerHealth = 5;
  int x = rand()%10;
  std::cout << x << "\n";
  while (NPChealth > 0 && playerHealth > 0) {
      
    if (NPCStrength+rand()%10 < playerStrength+rand()%10+2) {
      NPChealth--;
      std::cout << "Here\n";
    } else {
        std::cout <<"Horr\n";
        playerHealth--;
    }
  }
  
  if (playerHealth==0) {
      std::cout << "Player has died!";
  } else {
      std::cout << "The monster has died!";
  }
}
