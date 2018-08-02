
set(sources
    libcolcore.cpp libcolcore.h
    Assertions.h
    vector_ref.h
    Terminal.h
    Common.cpp Common.h
    Exceptions.h
    Log.cpp Log.h
    CommonData.cpp CommonData.h
    FixedHash.cpp FixedHash.h
    RLP.cpp RLP.h
    SHA3.cpp SHA3.h
    FileSystem.cpp FileSystem.h
    CommonIO.cpp CommonIO.h
    CommonJS.cpp CommonJS.h
    Address.cpp Address.h
    Guards.h
    Base64.cpp Base64.h
    Worker.cpp Worker.h

    dbfwd.h
    db.h

    LevelDB.cpp LevelDB.h
    DBImpl.h

    TrieCommon.cpp TrieCommon.h
    TrieHash.cpp TrieHash.h
    TrieDB.h
    MemoryDB.cpp MemoryDB.h
    OverlayDB.cpp OverlayDB.h

    JsonUtils.cpp JsonUtils.h
)

add_library(colcore ${sources})

target_include_directories(colcore PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(colcore PUBLIC cic-buildinfo Boost::filesystem Boost::system Boost::log Boost::thread PRIVATE ethash::ethash)

target_include_directories(colcore SYSTEM PUBLIC ${LEVELDB_INCLUDE_DIRS})
target_link_libraries(colcore PRIVATE ${LEVELDB_LIBRARIES})

