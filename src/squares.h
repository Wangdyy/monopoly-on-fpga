/****************************************************************************************
 * squares.h
 * This file contains the struct defininition of the all the squares,
 * which are either properties or action squares
 *****************************************************************************************/
#pragma once
#define MAX_PROPERTY_SET 3

enum SquareType
{
    Property,
    Action
};

enum PropertyType
{
    Colored,
    RailRoad,
    Utility
};

enum ActionType
{
    ChanceAction,
    CommunityChestAction,
    IncomeTaxAction,
    LuxuryTaxAction,
    GoToJailAction,
    GoAction,
    FreeParkingAction,
    JailAction
};

enum Colors
{
    Brown,
    LightBlue,
    Pink,
    Orange,
    Red,
    Yellow,
    Green,
    DarkBlue,
    NUM_COLORS
};

char colorStrings[][20] = {
    "Brown",
    "Light Blue",
    "Pink",
    "Orange",
    "Red",
    "Yellow",
    "Green",
    "Dark Blue"};

enum Owners
{
    Player1,
    Player2,
    Player3,
    Player4,
    Bank
};

/*Used to access square array*/
enum SquareNames
{
    Go,
    MediteraneanAvenue,
    CommunityChest1,
    BalticAvenue,
    IncomeTax,
    ReadingRailRoad,
    OrientalAvenue,
    Chance1,
    VermontAvenue,
    ConnecticutAvenue,
    JustVisiting,
    StCharlesPlace,
    ElectricCompany,
    StatesAvenue,
    VirginiaAvenue,
    PennsylvaniaRailRoad,
    StJamesPlace,
    CommunityChest2,
    TennesseeAvenue,
    NewYorkAvenue,
    FreeParking,
    KentuckyAvenue,
    Chance2,
    IndianaAvenue,
    IllinoisAvenue,
    BAndORailRoad,
    AtlanticAvenue,
    VentnorAvenue,
    WaterWorks,
    MarvinGardens,
    GoToJail,
    PacificAvenue,
    NorthCarolinaAvenue,
    CommunityChest3,
    PennsylvaniaAvenue,
    ShortLine,
    Chance3,
    ParkPlace,
    LuxuryTax,
    Boardwalk
};

typedef struct ColoredProperty
{
    const enum Colors color;
    const int houseCost;
    const int hotelCost;
    int houseCount;
    int hotelCount;
    const int rent[6];
} coloredProperty;

typedef struct propertySquare
{
    const enum PropertyType type;
    enum Owners owner;
    const int price;
    const int mortgageValue;
    bool mortgaged;
    coloredProperty coloredProperty;
} propertySquare;

typedef struct square
{
    const char name[40];
    const enum SquareType type;
    const enum SquareNames squareName;
    union Square
    {
        propertySquare property;
        enum ActionType action;
    } data;
} square;
