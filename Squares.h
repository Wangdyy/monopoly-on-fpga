/****************************************************************************************
 * Squares.h
 * This file contains the struct defininition of the all the squares, 
 * which are either properties or action squares
*****************************************************************************************/

enum SquareType {Property, Action};

enum PropertyType{Colored, RailRoad, Utility};

enum ActionType{Chance, CommunityChest, IncomeTax, LuxuryTax, GoToJail, Go, FreeParking, Jail};

enum Colors{Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue};

enum Owners{Player1, Player2, Player3, Player4, Bank};

typedef struct ColoredProperty {
    int houseCost;
    int hotelCost;
    int houseCount;
    int hotelCount;
    int rent[6];
} coloredProperty;

typedef struct propertySquare {
    enum PropertyType type;
    enum Owners owner;
    int price;
    bool mortgaged;
    union Properties{
        ColoredProperty colored;
        int railRoadRent;
    } properties;
} propertySquare;

typedef struct square{
    enum SquareType type;
    union Square{
        propertySquare property;
        enum ActionType action;
    } data;
    char name[20];
} square;
