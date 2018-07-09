#ifndef LIBCOLCORE_OVERLAYDB_H
#define LIBCOLCORE_OVERLAYDB_H

class OverlayDB: public MemoryDB
{
public:
    explicit OverlayDB(std::unique_ptr<db::DatabaseFace> _db = nullptr)
      : m_db(_db.release(), [](db::DatabaseFace* db) {
            clog(VerbosityDebug, "overlaydb") << "Closing state DB";
            delete db;
        })
    {}

    ~OverlayDB();

    // Copyable
    OverlayDB(OverlayDB const&) = default;
    OverlayDB& operator=(OverlayDB const&) = default;
    // Movable
    OverlayDB(OverlayDB&&) = default;
    OverlayDB& operator=(OverlayDB&&) = default;

    void commit();
    void rollback();

    std::string lookup(h256 const& _h) const;
    bool exists(h256 const& _h) const;
    void kill(h256 const& _h);

    bytes lookupAux(h256 const& _h) const;

private:
    using MemoryDB::clear;

    std::shared_ptr<db::DatabaseFace> m_db;
};

#endif //LIBCOLCORE_OVERLAYDB_H
