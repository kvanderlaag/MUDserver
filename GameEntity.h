#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include <string>

/**Header file for GameEntity*/
class GameEntity
{

/**Private variables store a permanent ID for a game entity, a name, and a brief description for this entity*/
private:
    int id_;
    std::string name_;
    std::string description_;

/**The public functions have a default constructor, a standard constructor that can set description, a destructor that can remove the entity, and a print function
 *that displays the ID, name and description for the entity.
 *Other functions can get the ID of the entity, get the name of the entity, and get the description of the entity as well as set a new descroption to the entity.
*/
public:
    GameEntity(int id, std::string name);
    GameEntity(int id, std::string name, std::string description);
    ~GameEntity();

    virtual void Print();

    virtual int GetId();
	virtual std::string GetName();
    virtual std::string GetDescription();
	virtual void SetId(int id);
	virtual void SetName(std::string name);
    virtual void SetDescription(std::string description);

};

#endif // __GAMEENTITY_H__
