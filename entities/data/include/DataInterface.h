#ifndef DATAINTERFACE
#define DATAINTERFACE

struct DataInterface {
    void (*m_destroyData)(void*);
    void (*m_copyData)(void*, void**);
    void (*m_serializeData)(std::ostream&, void*);
    void (*m_deserializeData)(std::istream&, void**);

    DataInterface(){
        m_destroyData = nullptr;
        m_copyData = nullptr;
        m_serializeData = nullptr;
        m_deserializeData = nullptr;
    }

    DataInterface(const DataInterface& interface){
        m_destroyData = interface.m_destroyData;
        m_copyData = interface.m_copyData;
        m_serializeData = interface.m_serializeData;
        m_deserializeData = interface.m_deserializeData;
    }
};

#endif
