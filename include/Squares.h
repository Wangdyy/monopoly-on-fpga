/****************************************************************************************
 * Squares.h
 * This file contains the struct defininition of the all the squares, 
 * which are either properties or action squares
*****************************************************************************************/
#pragma once

enum SquareType {Property, Action};

enum PropertyType{Colored, RailRoad, Utility};

enum ActionType{ChanceAction, CommunityChestAction, IncomeTaxAction, LuxuryTaxAction, GoToJailAction, GoAction, FreeParkingAction, JailAction};

enum Colors{Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue};

enum Owners{Player1, Player2, Player3, Player4, Bank};

/*Used to access square array*/
enum SquareNames{Go, MediteraneanAvenue, CommunityChest1, BalticAvenue, IncomeTax, ReadingRailRoad, 
OrientalAvenue, Chance1, VermontAvenue, ConnecticutAvenue, JustVisiting, 
StCharlesPlace, ElectricCompany, StatesAvenue, VirginiaAvenue, PennsylvaniaRailRoad, 
StJamesPlace, CommunityChest2, TennesseeAvenue, NewYorkAvenue, FreeParking, 
KentuckyAvenue, Chance2, IndianaAvenue, IllinoisAvenue, BAndORailRoad, 
AtlanticAvenue, VentnorAvenue, WaterWorks, MarvinGardens, GoToJail, 
PacificAvenue, NorthCarolinaAvenue, CommunityChest3, PennsylvaniaAvenue, ShortLine, 
Chance3, ParkPlace, LuxuryTax, Boardwalk};

typedef struct ColoredProperty {
    enum Colors color;
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
    coloredProperty coloredPropety;
} propertySquare;

typedef struct square{
    char name[20];
    enum SquareType type;
    enum SquareNames squareName;
    union Square{
        propertySquare property;
        enum ActionType action;
    } data;
} square;
