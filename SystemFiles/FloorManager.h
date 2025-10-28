#ifndef FLOORMANAGER_H
#define FLOORMANAGER_H

#include "FloorStaff.h" 
#include<vector>

class FloorManager: public FloorStaff{
    private:
        std::vector<std::string>responsibilities;
    
    public:
        FloorManager(std::string name);
        virtual ~FloorManager();
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif // !FLOORMANAGER_H