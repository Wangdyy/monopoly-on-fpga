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
    int mortgageValue;
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

/****************************************************************************************
* Stores square data object to be copied into the gamestate
*****************************************************************************************/

square square_Go =                                                                {"Go", Action, Go, .data.action = GoAction};
square square_MediterraneanAvenue =      {"Mediterranean Avenue", Property, MediteraneanAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 60, .mortgageValue = 30, .mortgaged = false, .coloredPropety = {.color = Brown, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {2, 10, 30, 90, 160, 250}}}};
square square_CommunityChest1 =                         {"Community Chest", Action, CommunityChest1, .data.action = CommunityChestAction};
square square_BalticAvenue =                          {"Baltic Avenue", Property, BalticAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 60, .mortgageValue = 30, .mortgaged = false, .coloredPropety = {.color = Brown, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {4, 20, 60, 180, 320, 450}}}};
square square_IncomeTax =                                    {"Income Tax", Action, IncomeTaxAction, .data.action = IncomeTaxAction};
square square_ReadingRailRoad =                {"Reading Rail Road", Property, ReadingRailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
square square_OrientalAvenue =                    {"Oriental Avenue", Property, OrientalAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 100, .mortgageValue = 50, .mortgaged = false, .coloredPropety = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {6, 30, 90, 270, 400, 550}}}};
square square_Chance1 =                                                  {"Chance", Action, Chance1, .data.action = ChanceAction};
square square_VermontAvenue =                       {"Vermont Avenue", Property, VermontAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 100, .mortgageValue = 50, .mortgaged = false, .coloredPropety = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {6, 30, 90, 270, 400, 550}}}};
square square_ConnecticutAvenue =           {"Connecticut Avenue", Property, ConnecticutAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 120, .mortgageValue = 60, .mortgaged = false, .coloredPropety = {.color = LightBlue, .houseCost = 50, .hotelCost = 50, .houseCount = 0, .hotelCount = 0, .rent = {8, 40, 100, 300, 450, 600}}}};
square square_JustVisiting =                                 {"Just Visiting", Action, JustVisiting, .data.action = FreeParkingAction};
square square_StCharlesPlace =                  {"St. Charles Place", Property, StCharlesPlace, .data.property = {.type = Colored, .owner = Bank, .price = 140, .mortgageValue = 70, .mortgaged = false, .coloredPropety = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {10, 50, 150, 450, 625, 750}}}};
square square_ElectricCompany =                 {"Electric Company", Property, ElectricCompany, .data.property = {.type = Utility, .owner = Bank, .price = 150, .mortgageValue = 75, .mortgaged = false}};
square square_StatesAvenue =                          {"States Avenue", Property, StatesAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 140, .mortgageValue = 70, .mortgaged = false, .coloredPropety = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {10, 50, 150, 450, 625, 750}}}};
square square_VirginiaAvenue =                    {"Virginia Avenue", Property, VirginiaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 160, .mortgageValue = 80, .mortgaged = false, .coloredPropety = {.color = Pink, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {12, 60, 180, 500, 700, 900}}}};
square square_PennsylvaniaRailRoad = {"Pennsylvania Rail Road", Property, PennsylvaniaRailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
square square_StJamesPlace =                        {"St. James Place", Property, StJamesPlace, .data.property = {.type = Colored, .owner = Bank, .price = 180, .mortgageValue = 90, .mortgaged = false, .coloredPropety = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {14, 70, 200, 550, 750, 950}}}};
square square_CommunityChest2 =                         {"Community Chest", Action, CommunityChest2, .data.action = CommunityChestAction};
square square_TennesseeAvenue =                 {"Tennessee Avenue", Property, TennesseeAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 180, .mortgageValue = 90, .mortgaged = false, .coloredPropety = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {14, 70, 200, 550, 750, 950}}}};
square square_NewYorkAvenue =                      {"New York Avenue", Property, NewYorkAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false, .coloredPropety = {.color = Orange, .houseCost = 100, .hotelCost = 100, .houseCount = 0, .hotelCount = 0, .rent = {16, 80, 220, 600, 800, 1000}}}};
square square_FreeParking =                                    {"Free Parking", Action, FreeParking, .data.action = FreeParkingAction};
square square_KentuckyAvenue =                    {"Kentucky Avenue", Property, KentuckyAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 220, .mortgageValue = 110, .mortgaged = false, .coloredPropety = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {18, 90, 250, 700, 875, 1050}}}};
square square_Chance2 =                                                  {"Chance", Action, Chance2, .data.action = ChanceAction};
square square_IndianaAvenue =                       {"Indiana Avenue", Property, IndianaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 220, .mortgageValue = 110, .mortgaged = false, .coloredPropety = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {18, 90, 250, 700, 875, 1050}}}};
square square_IllinoisAvenue =                    {"Illinois Avenue", Property, IllinoisAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 240, .mortgageValue = 120, .mortgaged = false, .coloredPropety = {.color = Red, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {20, 100, 300, 750, 925, 1100}}}};
square square_BAndO_RailRoad =                    {"B & O Rail Road", Property, BAndO_RailRoad, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
square square_AtlanicAvenue =                      {"Atlantic Avenue", Property, AtlanicAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 260, .mortgageValue = 130, .mortgaged = false, .coloredPropety = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {22, 110, 330, 800, 975, 1150}}}};
square square_VentnorAvenue =                       {"Ventnor Avenue", Property, VentnorAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 260, .mortgageValue = 130, .mortgaged = false, .coloredPropety = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {22, 110, 330, 800, 975, 1150}}}};
square square_WaterWorks =                                {"Water Works", Property, WaterWorks, .data.property = {.type = Utility, .owner = Bank, .price = 150, .mortgageValue = 75, .mortgaged = false}};
square square_MarvinGardens =                       {"Marvin Gardens", Property, MarvinGardens, .data.property = {.type = Colored, .owner = Bank, .price = 280, .mortgageValue = 140, .mortgaged = false, .coloredPropety = {.color = Yellow, .houseCost = 150, .hotelCost = 150, .houseCount = 0, .hotelCount = 0, .rent = {24, 120, 360, 850, 1025, 1200}}}};
square square_GoToJail =                                            {"Go To Jail", Action, GoToJail, .data.action = GoToJailAction};
square square_PacificAvenue =                       {"Pacific Avenue", Property, PacificAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 300, .mortgageValue = 150, .mortgaged = false, .coloredPropety = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {26, 130, 390, 900, 1100, 1275}}}};
square square_NorthCarolinaAvenue =    {"North Carolina Avenue", Property, NorthCarolinaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 300, .mortgageValue = 150, .mortgaged = false, .coloredPropety = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {26, 130, 390, 900, 1100, 1275}}}};
square square_CommunityChest3 =                    {"Community Chest", Action, CommunityChest3, .data.action = CommunityChestAction};
square square_PennsylvaniaAvenue =        {"Pennsylvania Avenue", Property, PennsylvaniaAvenue, .data.property = {.type = Colored, .owner = Bank, .price = 320, .mortgageValue = 160, .mortgaged = false, .coloredPropety = {.color = Green, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {28, 150, 450, 1000, 1200, 1400}}}};
square square_ShortLine =                                   {"Short Line", Property, ShortLine, .data.property = {.type = RailRoad, .owner = Bank, .price = 200, .mortgageValue = 100, .mortgaged = false}};
square square_Chance3 =                                                  {"Chance", Action, Chance3, .data.action = ChanceAction};
square square_ParkPlace =                                   {"Park Place", Property, ParkPlace, .data.property = {.type = Colored, .owner = Bank, .price = 350, .mortgageValue = 175, .mortgaged = false, .coloredPropety = {.color = Blue, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {35, 175, 500, 1100, 1300, 1500}}}};
square square_LuxuryTax =                                          {"Luxury Tax", Action, LuxuryTax, .data.action = LuxuryTaxAction};
square square_Boardwalk =                                    {"Boardwalk", Property, Boardwalk, .data.property = {.type = Colored, .owner = Bank, .price = 400, .mortgageValue = 200, .mortgaged = false, .coloredPropety = {.color = Blue, .houseCost = 200, .hotelCost = 200, .houseCount = 0, .hotelCount = 0, .rent = {50, 200, 600, 1400, 1700, 2000}}}};



